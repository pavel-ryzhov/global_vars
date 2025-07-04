#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <sstream>
#include <queue>
#include <stack>
#include <map>
using namespace std;
map <char, char> numbers;				///<Список символов. Хранит алфавит, и номер соответствующей символу кнопки.>

///<Структура словаря. Поля структуры содержат данные о частоте вызовов (priority),>
///<последнем вызове(last_call) слова(text).>
struct Word{
	int priority; 
	int last_call;
	string text;  
};

///<Declarations>
typedef map <string, priority_queue <Word> > type;
bool operator < (const Word&, const Word&);        ///<Перегрузка оператора сравнения для объектов Word.>

void buttons();									   ///<Функция привязки каждого символа к цифрам(номерам кнопок).>
void input(string&, type&);						   ///<Чтение входных данных>
void find(string&, string&, type&);				   ///<Поиск слов и составление результирующего сообщения.>
string inv_T9(string&);							   ///<Перевод слова в набор цифр, которые необходмо нажать>
												   ///<на клавиатуре, для ввода данного слова.>


int main()
{
	///<Словарь(dictionary). Структура: словарь хранится в ассоциативном массиве(map), где ключом>
	///<является цифровой набор слова(например: 228(что соответствует слову act)), значение,>
	///<ассоциированное с заданным ключом - это очередь с приоритетами, а элементами очереди>
	///<являются экземляры структуры Word, описывающие каждое слово.>
	type dictionary;								
	string result, line_set;						///<Полученное сообщение и входная строка.>

	buttons();
	input(line_set, dictionary);
	find(line_set, result, dictionary);
	
	cout << result << endl;							///<Печать результата.>
	return 0;
}

///<Перегрузка оператора сравнения.>
///<Сравнивает слова в словаре по частоте встречаемости, если она равна,>
///<то по последнему вызову, если слова еще не вызывались, то>
///<в лексикографическом порядке.>
bool operator < (const Word& lh, const Word& rh)
{
	if(lh.priority == rh.priority)
		if(lh.last_call == rh.last_call){
			if(strcmp(lh.text.data(), rh.text.data()) <= 0)
				return false;
			else return true;
		}
		else
			return lh.last_call < rh.last_call;

	return lh.priority < rh.priority;
}

///<Сопоставляем каждый символ алфавита с номером кнопки на клавиатуре.>
void buttons()
{
	char c = '2'; 
	int count = 0;
	string str = "abcdefghijklmnoqrstuvwxy";

	for(int i = 2; i < 10; i++, c++)
		for(int j = 0; j < 3; j++)
			numbers[str[count++]] = c;
	numbers['z'] = '9';
	numbers['p'] = '7'; 
}

///<Перевод слова из буквенного вида в цифровой.>
string inv_T9(string& s_word)
{
	string ret = "";
	for(unsigned int i = 0; i < s_word.length(); ++i)
		ret += numbers[s_word[i]];
	return ret;
}


void input(string& line_set, type& dictionary)
{
	int N;
	cin >> N;

	Word temp;
	for(int i = 0; i < N; ++i) {
		cin >> temp.text >> temp.priority;
		temp.last_call = 0;
		dictionary[inv_T9(temp.text)].push(temp);    ///<Заполнение словаря.>
	}
	cin.get();

	line_set.reserve(100001);
	getline(cin, line_set);
}

void find(string& line_set, string& result, type& dictionary)
{
	stack <Word> st;
	string sq, temp_sq;
	string one[3] = {".", ",", "?"};
	unsigned int count(0), index(0), step(0), i;

	istringstream stream(line_set);							///<Объявление потока из входной строки>

	for(; index < line_set.length() && line_set[index] == ' '; index++) ///<Чтение пробелов перед первым словом>
		result += ' ';

	bool check = true;
	while(!check || (check && !stream.eof()))
	{
		if(check){
			stream >> sq;				///<Чтение записи>
			i = 0; 
		}
		step = 0;
		temp_sq = "";
		for(; i < sq.length() && sq[i] != '1' && sq[i] != '*'; i++)  ///<Находим в записи цифровой код слова>
			temp_sq += sq[i];

		for(; i < sq.length() && sq[i] == '*'; i++)                  ///<Считаем количество звездочек после кода>
			step++;

		type::iterator iter = dictionary.find(temp_sq);				 ///<Находим данный код в словаре>
		if(iter != dictionary.end())
		{
			if(step >= iter->second.size())							 ///<Если количество звездочек больше чем слов в словаре соответствующих>
				step = step % iter->second.size();					 ///<данному коду, то делим это кол-во на количество этих слов.>

			while(step > 0)
			{
				st.push(iter->second.top());						 ///<Достаем из очереди слова в порядке заданного приоритета.>
				iter->second.pop();									 ///<(Кол-во слов определяется кол-м звездочек после кода)>
				--step;												 ///<и добавляем эти слова в стек.>
			}		
			result += iter->second.top().text;						 ///<Добавлем к результирующей строке найденое слово>

			st.push(iter->second.top());
			iter->second.pop();
			st.top().priority++;									 ///<Увеличиваем частоту встречаемости найденого слова>
			st.top().last_call = ++count;							 ///<И увеличиваем значение последнего вызова (до максимального)>	

			while(!st.empty())
			{	
				dictionary[temp_sq].push(st.top());					 ///<Переносим слова из стека обратно в словарь>
				st.pop();
			}
		}	
		while(i < sq.length() && sq[i] == '1')
		{			
			for(i++, step = 0; i < sq.length() && sq[i] == '*'; i++) ///<Добавляем к строке знаки пунктуации(если необходимо)>
				step++;
			result += one[step % 3];
		}
		check = (i < sq.length())? false: true;
		if(check)			
			for(index += sq.length(); index < line_set.length() && line_set[index] == ' '; index++) ///<Дописываем пробелы после слова.>
				result += ' ';

		if(index == line_set.length()) break;
	}	
}