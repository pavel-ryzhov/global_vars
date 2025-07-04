/* Задача C. T9.
 * Идея решения:
 *	-	считывание словаря происходит в некоторый vector<string>, далее в построении удобных структур данных используются
 *		лишь указатели на элементы соответствующего вектора, что ускоряет обработку операций копирования и вставки
 *	-	сначала строим массив[ из 20 list< из (N<=50k) pair< double, vector< из (M <= 1001) vector< string > > > > ], в который и будем
 *		определенным образом писать соответствующий словарь (а точнее указатели на считанные слова)
 *	-	контейнер list удобен для чтения в него "практически" отсортированного словаря из-за скорости вставки, но не удобен для изымания
 *		из него элементов по ключу => после чтения словаря сразу переписываем нашу структурку из list в vector, который уже будет отсортирован
 *		и поиск по нему будет проходить за разумное время.
 *	-	после завершения построения структуры T9-словаря, читаем последнюю строчку входных данных и отвечаем на запросы.
 *	-	суммарная сложность алгоритма, наверное, может быть оценена сверху (или всреднем) как O(n log n + m (log n)^2) (очень предположительно...)
 *	-	не ручаюсь за то, что алгоритм оптимален, но зато он отвечает цитате: "Vector of list of list?.. And we need to go deeper!" =)
 */
#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;

/* START: Используемые структуры */
struct data_item								// структура с полями для слова и для частоты его встречаемости (формально - рейтинга слова)
{
	string word;
	int freq;
};
struct r_word_lists								// структура, хранящаяя вектор и его нижнюю и верхнюю границы заполнения
{
	int min;
	int max;
	vector<list<data_item *> >	r_vector;		// как описано вначале, используются указатели на элементы считываемого единожды и неприкосновенного словаря (database)
};
struct s_word_lists
{
	int freq;
	list<data_item *> _list;
};
typedef list<s_word_lists>		rated_lists;	// таже структура, что и mm_vector, но для поиска

struct r_singleKeyWords							// структура состоящая из ключа (комбинации цифр, набираемых на телефоне) и соответствующего массива слов
{
	double key;
	r_word_lists wordsTable;
};
struct s_singleKeyWords
{
	double key;
	rated_lists wordsTable;
};
typedef vector<list<r_singleKeyWords> >				readInDict;		// тип словаря, в который читаем данные (структура, оптимизированная под чтение)
typedef vector<vector<s_singleKeyWords> >			searchInDict;	// тип словаря, по которому будем искать, отвечая на запросы (структура, оптимизированная под поиск)

typedef vector<list<r_singleKeyWords>::iterator>	readIter;		// итератор для каждого list, в который будет происходить чтение
/* END: Используемые структуры */

class Dictionary {
private:
	//readInDict	r_dict;
	//searchInDict	s_dict;
	readIter		l_iters;
	double get_key(data_item *item);		// функция, выдающая ключ на слово
	double key_ToDouble(string request);	// функция, преобразующая строку в число
	size_t bin_find(vector<s_singleKeyWords> *vec, double key);	// бинарный поиск по вектору
	r_singleKeyWords create_new_vec_singleKeyWords(data_item *item, double item_key);
	

public:
	readInDict		r_dict;
	searchInDict	s_dict;
	Dictionary();
	void read_word(data_item *item);		// метод, реализующий пополнение словаря новыми item, и всталяющий их в определенном порядке
	void preprocess();						// обработка словаря после считывания всех слов: перегоняем list<vector<list<string *>>> ---> vector<list<list<string *>>>
	string get_word(string request, int shifts);
};
Dictionary::Dictionary()
{
	r_dict.resize(20); s_dict.resize(20);	// задаем начальные размеры векторов словарей и их итераторов равными 20, т.к. maxlength слова равна по условию 20
	l_iters.resize(20);
}
r_singleKeyWords Dictionary::create_new_vec_singleKeyWords(data_item *item, double item_key)
{
	r_singleKeyWords new_wordList; new_wordList.key = item_key;					// присвоиv key = item_key
	new_wordList.wordsTable.r_vector.resize(1001); 								// делаем размер равным 1001 (исходя из условия)
	new_wordList.wordsTable.min = new_wordList.wordsTable.max = item->freq;
	new_wordList.wordsTable.r_vector[item->freq].push_back(item);				// вставляем ссылку на элемент
	return new_wordList;
}
double Dictionary::get_key(data_item *item)
{
	double ans = 0, p = 1;
	int size = item->word.size();
	for (int i = 0; i < size; i++)
	{
		ans += (((static_cast<int>(item->word[size - i - 1])-static_cast<int>('a')) / 3) + 2) * p;
		p *= 10;
	}
	return ans;
}
double Dictionary::key_ToDouble(string request)
{
	double ans = 0, p = 1;
	for ( int i = request.size()-1; i >= 0; i-- )
	{
		ans += (static_cast<int>(request[i]) - 48) * p;
		p *= 10;
	}

	return ans;
}
void Dictionary::read_word(data_item *item)
{
	double item_key = get_key(item);		// чтобы не вызывать постоянно функцию get_key и сэкономить время
	int size = item->word.size() - 1;		// т.к. массивы нумеруются с 0

	if ( r_dict[size].empty() )// при пустоте соответствующих элементов вектора - вставляем в них новый элемент
	{
		r_dict[size].push_back(create_new_vec_singleKeyWords(item, item_key));
		l_iters[size] = r_dict[size].begin();
	}
	else
	{
		// пока текущий элемент списка имеет больший ключ, идем по списку в начало (или пока не дойдем до начала)
		while ( (l_iters[size]->key > item_key)&&(l_iters[size] != r_dict[size].begin()) )
			l_iters[size]--;
		if ( (l_iters[size]->key < item_key) ) l_iters[size]++;
		// пока текущий элемент списка имеет меньший ключ, идем по списку в конец (или пока не дойдем до конца)
		while ( (l_iters[size] != r_dict[size].end())&&(l_iters[size]->key < item_key) )
			l_iters[size]++;
		// в итоге наш l_iters[size] указывает на элемент, ключ которого >= ключа вставляемого слова, либо на begin и key >= item_key, либо на end

		if ( (l_iters[size] == r_dict[size].end())||(l_iters[size]->key != item_key) )	// если элемента с item_key не нашлось, то сконструируем его и вставим в list
			r_dict[size].insert(l_iters[size], create_new_vec_singleKeyWords(item, item_key)), l_iters[size]--;
		else																			// если же элемент с key == item_key нашелся вставляем в соответствующий wordsTable наш item
		{
			l_iters[size]->wordsTable.r_vector[item->freq].push_back(item);	// используем push_bak в силу того, что входные данные отсортированы в алфавитном порядке (по условию)
			if (item->freq > l_iters[size]->wordsTable.max) l_iters[size]->wordsTable.max = item->freq;	// и пишем соответствующее максимальное и значение vectora
			else if (item->freq < l_iters[size]->wordsTable.min) l_iters[size]->wordsTable.min = item->freq;
		}
	}
}
void Dictionary::preprocess()
{
	// пробегаемся по vector и, если ячейка не пуста, то залезаем в нее и переписываем все структуры в новые поисковые структуры
	s_singleKeyWords new_item;
	s_word_lists singleFreqItem;
	for (int i = 0; i < 20; i++)
		if ( ! r_dict[i].empty() )
		{	// конструируем тот элемент, который вставим в s_dict[i]
			for (list<r_singleKeyWords>::iterator it = r_dict[i].begin(); it != r_dict[i].end(); it++)
			{
				new_item.key = it->key;
				for (int j = it->wordsTable.max; j >= it->wordsTable.min; j--)
					if ( ! it->wordsTable.r_vector[j].empty() )
					{
						singleFreqItem.freq = j; singleFreqItem._list = it->wordsTable.r_vector[j];
						new_item.wordsTable.push_back(singleFreqItem);
					}
				s_dict[i].push_back(new_item); new_item.wordsTable.clear();
			}
		}
}
size_t Dictionary::bin_find(vector<s_singleKeyWords> *vec, double key)
{
	size_t l = 0, r = (*vec).size(), m;
	while ( l < r )
	{
		m = l + (r - l)/2;
		if ( key <= (*vec)[m].key ) r = m;
		else l = m + 1;
	}

	return l;
}
string Dictionary::get_word(string request, int shifts)
{
	int size = request.size() - 1;				// массивы нумеруются с нуля
	double key = key_ToDouble(request);
	data_item ans, *p;
	size_t pos = bin_find(&s_dict[size], key);	// бинарным поиском находим элемент вектора, обладающий нужным ключом

	// выставляем итераторы и начинаем сдвигаться по спискам слева направо, сверху вниз
	rated_lists::iterator it = s_dict[size][pos].wordsTable.begin();
	list<data_item *>::iterator itt = it->_list.begin();
	for (int i = 0; i < shifts; i++)
	{
		if ( itt == --(it->_list.end()) )
		{
			it++;
			itt = it->_list.begin();
		}
		else itt++;
	}
	// запомним найденный элемент и удалим указатель на него в list
	ans.word = (*itt)->word; ans.freq = ++((*itt)->freq);
	p = *itt; it->_list.erase(itt);

	// увеличим рейтинг соответствующего слова на единицу
	if ( (it == s_dict[size][pos].wordsTable.begin()) || ((--it)->freq != ans.freq) )	// если еще нет элемента списка с freq = ans.freq
	{
		s_word_lists l; l._list.push_back(p); l.freq = ans.freq;
		s_dict[size][pos].wordsTable.insert(it, l);
	}
	else
	{
		itt = it->_list.begin();
		it->_list.insert(itt, p);
	}
	if ( ((++it) != s_dict[size][pos].wordsTable.end())&&(it->_list.empty()) ) s_dict[size][pos].wordsTable.erase(it);

	return ans.word;
}


int main()
{
	vector<data_item> database(50000);		// вектор из пар <строка, число>, в который читаются входные данные

	// чтение словаря
	int N; cin >> N;						// читаем размер словаря
	data_item temp;
	Dictionary dict;
	for (int i = 0; i < N; i++)
	{
		cin >> temp.word >> temp.freq;		// читаем строку и заносим в database
		database[i] = temp;
		dict.read_word(&database[i]);
	}

	// обрабатываем прочитанный словарь
	dict.preprocess();

	// читаем запросы и по мере прочитанного выводим ответы
	string request, ans; int shifts;		// читаемый запрос, ответ и колличество сдвигов по словарю
	while (cin >> request)
	{
		ans = ""; shifts = 0;
		while (*(--request.end()) == '*') request.erase(--request.end()), shifts++;
		if ( *(--request.end()) == '1' )	// если поставлен знак препинания
		{
			switch (shifts)
			{
				case 0: ans += '.'; break;
				case 1: ans += ','; break;
				case 2: ans += '?'; break;
			}
			request.erase(--request.end()); shifts = 0;
			while (*(--request.end()) == '*') request.erase(--request.end()), shifts++;
		}
		ans = dict.get_word(request, shifts) + ans; cout << ans << ' ';
	}
	cout << endl;

	return 0;
}