#include <map>
#include <string>
#include <list>
#include <functional>
#include <algorithm>
#include <iostream>
#include <fstream>

// синглтон-клавиатура
// хранит отображение 'кнопка' -> 'таблица символов'
class Keyboard {
// конструирование/разрушение
private:
	Keyboard();
// открытые функции-члены
public:
	// получение ссылки на объект
	static Keyboard& Instance() {
		static Keyboard keyb;
		return keyb;
	}
	// получение таблицы символов для кнопки
	std::string GetSymbol(char inSym) {
		return m_Symbols[inSym];
	}
// закрытые данные-члены
private:
	// отображение кнопок на таблицы символов
	std::map<char, std::string > m_Symbols;
};

// объект-компаратор для сравнения записей словаря по слову
template<typename T>
struct word_less : public std::binary_function<T, T, bool> {
	bool operator()(const T& lhs, const T& rhs) {
		return lhs.first < rhs.first;
	}
};

// объект-компаратор для сравнения записей словаря по связанному значению
template<typename T>
struct prio_greater : public std::binary_function<T, T, bool> {
	bool operator()(const T& lhs, const T& rhs) {
		return lhs.second > rhs.second;
	}
};

// структура хранения слов:
// списки слов хранятся в отображении по ключу -
// таблице символов кнопки
// шаблонный параметр - тип связанного со словом значения
template<typename T>
struct Wordmap {
	// запись карты слов - 'слово - связанное значение'
	typedef std::pair<std::string, T> entry_type;
	// список слов в кармане
	typedef typename std::list<entry_type> bucket_type;
	// итератор списка
	typedef typename bucket_type::iterator bucket_it;
	// тип отображения
	typedef std::map<std::string, bucket_type> map_type;
	// итератор тотбражения
	typedef typename map_type::iterator map_it;
	Wordmap();
	// карманы слов
	std::map<std::string, bucket_type> buckets;
};

/*
Шаблон словаря: T - тип связанного со словом значения (здесь - приоритет),
WordComp - компаратор записей по алфавиту,
PrioComp - компаратор записей по приоритету
Cлова добавляются с упорядочением по приоритету, а
при равенстве по приоритету - в лексикографическим порядке.
Обновление приоритета нарушает лексикографический порядок диапазонов равного приоритета
*/
template<typename T = unsigned, typename WordComp = word_less<typename Wordmap<T>::entry_type>, typename PrioComp = prio_greater<typename Wordmap<T>::entry_type> >
class Dictionary {
// открытые определения типов
public:
	// итератор одиночной записи в карте слов словаря
	typedef typename Wordmap<T>::bucket_it word_it;
	// итератор карты слов
	typedef typename Wordmap<T>::map_it wordmap_it;
// открытые функции-члены
public:
	// добавить слово в словарь
	void AddWord(const std::string& inWord, T inPrio);
	// повысить приоритет слова (доступ непосредственно по индексу для уменьшения трудоёмкости)
	void IncreasePriority(typename Wordmap<T>::bucket_it inIt);
	// получить начало и конец кармана слов
	std::pair<word_it, word_it> GetBucket(const std::string& inWord) {
		wordmap_it it = m_Dict.buckets.find(inWord);
		return std::make_pair<word_it, word_it>(it->second.begin(), it->second.end());
	}
// закрытые функции-члены
private:
	// получение итератора карты слов, соответствующего карману
	wordmap_it FindBucket(const std::string& inWord) {
		wordmap_it it = m_Dict.buckets.lower_bound(inWord);
		// значение, наёденное lower_bound, соответствует другому карману
		//if(it->first[p] < inWord[0])
		if(!Contains(it, inWord[0]))
			--it;
		return it;
	}
	bool Contains(const wordmap_it& inIt, char inSym) {
		if(inIt == m_Dict.buckets.end())
			return false;
		for(std::string::const_iterator it = inIt->first.begin(); it != inIt->first.end(); ++it) {
			if((*it) == inSym)
				return true;
		}
		return false;
	}
// закрытые данные-члены
private:
	// карта слов
	Wordmap<T> m_Dict;
};

// чтение словаря
void ReadDictionary(std::basic_istream<char>& inStream, Dictionary<>& inDict);

/*
Обработчик пользовательского ввода:
при вводе первой буквы выбирает все слова
из данного кармана словаря, создаёт из них суффиксный индекс
(хранится в виде карманной карты слов аналогично словарю)
и приоритетный индекс (отсортированный список);
при вводе последующих символов обновляются суффиксный и приоритетный индексы
*/
class Parser {
	// тип элементов приоритетного индекса: 'итератор слова в словаре - приоритет'
	typedef std::pair<Wordmap<unsigned>::bucket_it, unsigned> dictionary_ind;
// конструирование/разрушение
public:
	Parser(Dictionary<>& inDict) : m_Dict(&inDict), m_Index(NULL), m_PrioIndex(NULL) {
		Reset();
	}
// открытые функции-члены
public:
	// обработка очередного символа с возвращением
	// промежуточных результатов
	std::string OnNewInput(char inSym);
// закрытые функции-члены
private:
	// выбор следующего знака препинания
	void SelectNewPreposition();
	// обновление индексов
	void UpdateIndex(const std::string& inSymbol);
// закрытые данные-члены
private:
	// суффиксный индекс - карта списков
	// с элементами 'суффикс - итератор слова в словаре'
	Wordmap<Dictionary<>::word_it>* m_Index;
	// приоритетный индекс
	std::list<dictionary_ind>* m_PrioIndex;
	// сброс состояния
	void Reset();
	// количество введённых звёздочек
	unsigned m_AsteriskCounter;
	// количество введённых знаков препинания
	unsigned m_PrepositionCounter;
	// количество введённых цифр
	unsigned m_NumberCounter;
	// словарь
	Dictionary<>* m_Dict;
	// возвращаемое слово
	std::string m_Text;
};

int main(int argc, char* argv[]) {
	Dictionary<> dict;
	ReadDictionary(std::cin, dict);
	std::string instr = "";
        Parser p(dict);
	// чтение ввода кусками
	// разбор кусков посимвольно
		while(std::cin >> instr) {
		for(unsigned i = 0; i < instr.length(); ++i)
			p.OnNewInput(instr[i]);
		std::string outstr = p.OnNewInput(' ');
		std::cout << outstr;
	}
	return 0;
}


// Реализация Keyboard
////////////////////////////////////////////////////////////////

Keyboard::Keyboard() {
	m_Symbols['1'] = ".,?";
	m_Symbols['2'] = "abc";
	m_Symbols['3'] = "def";
	m_Symbols['4'] = "ghi";
	m_Symbols['5'] = "jkl";
	m_Symbols['6'] = "mno";
	m_Symbols['7'] = "pqrs";
	m_Symbols['8'] = "tuv";
	m_Symbols['9'] = "wxyz";
}

////////////////////////////////////////////////////////////////

// Реализация Wordmap
////////////////////////////////////////////////////////////////
template<typename T>
Wordmap<T>::Wordmap() {
	// инициализация карманов пустыми списками
	buckets.insert(typename map_type::value_type("abc", bucket_type(0)));
	buckets.insert(typename map_type::value_type("def", bucket_type(0)));
	buckets.insert(typename map_type::value_type("ghi", bucket_type(0)));
	buckets.insert(typename map_type::value_type("jkl", bucket_type(0)));
	buckets.insert(typename map_type::value_type("mno", bucket_type(0)));
	buckets.insert(typename map_type::value_type("pqrs", bucket_type(0)));
	buckets.insert(typename map_type::value_type("tuv", bucket_type(0)));
	buckets.insert(typename map_type::value_type("wxyz", bucket_type(0)));
	// "пустой" карман потребуется для добавления пустого суффикса
	// к индексу (Parser::UpdateIndex)
	buckets.insert(typename map_type::value_type("", bucket_type(0)));
}

////////////////////////////////////////////////////////////////

// Реализация Dictionary
////////////////////////////////////////////////////////////////
// добавление слова в словарь
template<typename T, typename WordComp, typename PrioComp>
void Dictionary<T, WordComp, PrioComp>::AddWord(const std::string& inWord, T inPrio) {
	// получение кармана
	wordmap_it it = FindBucket(inWord);
	typedef typename std::pair<word_it, word_it> bucketpair;
	typedef typename Wordmap<T>::bucket_type::value_type word_type;
	// получение диапазона слов с приоритетами, меньше данного на единицу
	bucketpair prio_its = std::equal_range(it->second.begin(), it->second.end(), word_type(inWord, inPrio - 1), PrioComp());
	// поиск в этом диапазоне места по алфавиту
	word_it final_it = std::lower_bound(prio_its.first, prio_its.second, word_type(inWord, inPrio), WordComp());
	it->second.insert(final_it, word_type(inWord, inPrio));
}

// обновление приоритета
template<typename T, typename WordComp, typename PrioComp>
void Dictionary<T, WordComp, PrioComp>::IncreasePriority(typename Wordmap<T>::bucket_it inIt) {
	wordmap_it it = FindBucket(inIt->first);
	typedef typename std::pair<word_it, word_it> bucketpair;
	typedef typename Wordmap<T>::bucket_type::value_type word_type;
	T prio = inIt->second;
	std::string word = inIt->first;
	it->second.erase(inIt);
	// вставка слова перед диапазоном слов с приоритетом, равным старому значению
	bucketpair prio_its = std::equal_range(it->second.begin(), it->second.end(), word_type(word, prio + 1), PrioComp());
	it->second.insert(prio_its.first, word_type(word, prio + 1));
}

////////////////////////////////////////////////////////////////

// Реализация Parser
////////////////////////////////////////////////////////////////

// обновление индексов
void Parser::UpdateIndex(const std::string& inSymbol) {

	std::list<dictionary_ind>* temp_prio = new std::list<dictionary_ind>;
	// была введена первая цифра
	if(!m_NumberCounter) {
		m_Index = new Wordmap<Dictionary<>::word_it>;

		// получение нужного кармана словаря
		std::pair<Dictionary<>::word_it, Dictionary<>::word_it> bucket = m_Dict->GetBucket(inSymbol);
		// копирование суффиксов всех строк кармана в суффиксный индекс,
		// приоритетов - в приоритетный индекс
		for(;bucket.first != bucket.second; ++bucket.first) {
			// копирование суффикса строки
			std::string suffix(bucket.first->first.begin() + 1, bucket.first->first.end());
			// получение кармана в индекса
			Wordmap<Dictionary<>::word_it>::map_it it = m_Index->buckets.lower_bound(suffix);
			if(it->first[0] != suffix[0])
				--it;

			// (суффикс, итератор.итератор)
			it->second.insert(it->second.end(), Wordmap<Dictionary<>::word_it>::entry_type(suffix, bucket.first));

			// (итератор.итератор, итератор.итератор->приоритет)
			dictionary_ind
				ind1(bucket.first, bucket.first->second),
				ind2(bucket.first, bucket.first->second - 1);
			temp_prio->insert(std::lower_bound(temp_prio->begin(), temp_prio->end(), ind2, prio_greater<dictionary_ind>()), ind1);
		}
	}

	// цифра не первая, первоначальный
	// индекс уже создан - обновление суффиксного индекса
	// на основе уже имеющегося
	else {
		Wordmap<Dictionary<>::word_it>* temp_ind = new Wordmap<Dictionary<>::word_it>;

		// отбираем суффиксы в новый индекс
		Wordmap<Dictionary<>::word_it>::bucket_type b_temp = m_Index->buckets[inSymbol];

		for(Wordmap<Dictionary<>::word_it>::bucket_it b_ind = b_temp.begin(); b_ind != b_temp.end(); ++b_ind) {
			// копирование суффикса строки
			std::string suffix(b_ind->first.begin() + 1, b_ind->first.end());
			// пустой суффикс тоже копируется
			Wordmap<Dictionary<>::word_it>::map_it it = temp_ind->buckets.lower_bound(suffix);
			if(it->first[0] != suffix[0])
				--it;

			// (суффикс, итератор.итератор)
			it->second.insert(it->second.end(), Wordmap<Dictionary<>::word_it>::entry_type(suffix, b_ind->second));

			// (итератор.суффикс, итератор.итератор->приоритет)
			dictionary_ind
				ind1(b_ind->second, b_ind->second->second - 1),
				ind2(b_ind->second, b_ind->second->second);
			temp_prio->insert(std::lower_bound(temp_prio->begin(), temp_prio->end(), ind1, prio_greater<dictionary_ind>()), ind2);
		}
		// удаление старых индексов
		delete m_PrioIndex;
		delete m_Index;

		m_Index = temp_ind;
	}

	m_PrioIndex = temp_prio;
}

// обработка нового символа
std::string Parser::OnNewInput(char inSym) {
	// работа со словом закончилась:
	// повышение приоритета слова в словаре,
	// добавление к хранимому слову пробела,
	// сброс состояния
	if(inSym == ' ') {
		std::list<dictionary_ind>::iterator it = m_PrioIndex->begin();
		m_Dict->IncreasePriority(it->first);
		std::string res = m_Text;
		res = m_Text + inSym;
		Reset();
		return res;
	}

	if(inSym == '*') {
		// обновление индекса приоритетов
		if(!m_PrepositionCounter)
		{
			m_PrioIndex->erase(m_PrioIndex->begin());
			m_Text = m_PrioIndex->begin()->first->first;
		}
		// выбор следующего знака препинания
		else
			SelectNewPreposition();
	}
	// выбор знака препинания
	else if(inSym == '1') {
		SelectNewPreposition();
	}
	// inSym == 2 -- 9
	else {
		// таблица символов с клавиатуры
		std::string str = Keyboard::Instance().GetSymbol(inSym);
		// обновление индексов
		UpdateIndex(str);
		// обновление счётчика
		m_NumberCounter++;
		// обновление хранимого слова
		m_Text = m_PrioIndex->begin()->first->first;
	}
	return m_Text;
}

// выбор следующего знака препинания
void Parser::SelectNewPreposition() {
	// до этого препинаний не было
	if(m_PrepositionCounter) {
		unsigned u = m_Text.length();
		// добавление к слову первого знака препинания клавиатуры
		m_Text[m_Text.length() - 1] = Keyboard::Instance().GetSymbol('1')[m_PrepositionCounter++];
	}
	// знак препинания уже имеется
	else {
		// замена последнего символа слова новым знаком
		std::string sym = Keyboard::Instance().GetSymbol('1');
		m_Text += sym[m_PrepositionCounter++];
	}
}

// сброс индексов, счётчиков и хранимого слова
void Parser::Reset() {
	m_Text = "";
	m_PrepositionCounter = 0;
	m_AsteriskCounter = 0;
	m_NumberCounter = 0;
	delete m_PrioIndex;
	delete m_Index;
}
////////////////////////////////////////////////////////////////


// чтение словаря
void ReadDictionary(std::basic_istream<char>& inStream, Dictionary<>& inDict) {
	// количество слов
	unsigned N = 0;
	inStream >> N;
	for(unsigned i = 0; i < N; ++i) {
		unsigned priority = 0;
		std::string wrd = "";
		char c = 0;
		// слово-приоритет
		inStream >> wrd;
		inStream >> priority;
		// добавление
		inDict.AddWord(wrd, priority);
	}
}