#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <map>

//структура дл€ хранени€ словарного слова
struct word
{
	int freq;			//частота упом€нани€
	std::string chars;  //содержимое слова
	word(){}
	word(int frequency, const std::string& str)
	{
		freq = frequency;
		chars = str;
	}
	
};

//сравнение - сначала по частоте, потом по алфавиту
struct wordComparession
{
	bool operator()(const word& one, const word& another)
	{
			if(one.freq == another.freq)
				return one.chars < another.chars;
			else
				return one.freq > another.freq;
	}
};
//тип "словарь".  лючи - комбинации клавиш, содержимое - массив слов, подоход€щих под комбинацию
typedef std::map<std::string,std::vector<word> > dictContainer;
typedef unsigned int uint;

//функци€ возвращает комбинацию клавиш дл€ заданного слова
char* wordToNums(const std::string& word);

//главный класс приложени€. ‘ормирует словарь, разбирает строку
class parser
{
private:
	dictContainer dictionary;	//словарь
	std::istream& input;		//входной поток
		//возвращает длину знака препинани€
	int getZnakLen(const std::string& s, int atPos)
	{
		if(s[atPos]=='1')
			return 1;
		return 0;
	}

	//возвращает длину слова 
	int getWordLen(const std::string& s, int atPos)
	{
		uint i = 0;
		for(i=atPos; i<s.size(); i++)
		{
			if(!isdigit(s[i]) || s[i]=='1')
			{
				break;
			}
		}
		return i-atPos;
	}

	//возвращает количество звЄздочек
	int getFreq(const std::string& s, int atPos)
	{
		std::string::const_iterator pos = std::find_if(s.begin()+atPos,s.end(),std::bind2nd(std::not2(std::equal_to<char>()),'*'));
		return pos-(s.begin()+atPos);
	}

	//возвращает количество пробельных символов
	int getWs(const std::string& s, int atPos)
	{
		std::string::const_iterator pos = std::find_if(s.begin()+atPos,s.end(),std::not1(std::ptr_fun(isspace)));
		return pos-(s.begin()+atPos);
	}

	//возвращает пробельные символы из исходной строки
	std::string addWs(const std::string& s, int atPos, int len)
	{
		return s.substr(atPos, len);
	}

	//вставл€ет новое слово в массиве на нужную позицию
	void reSortT9(std::vector<word>::iterator begin, std::vector<word>::iterator wordPos)
	{
		int wordFreq = wordPos->freq;
		//последовательный перебор, остановка при нахождении слова с бќльшей частотой
		for(std::vector<word>::iterator it = wordPos; true; it--)
		{
			if(wordFreq >= it->freq)
			{
				std::swap(*wordPos,*it);
				wordPos = it;
			}
			else
			{
				break;
			}
			if(it==begin)
				break;
		}
	}

	//возвращает слово, полученное из комбинации цифр в исходной строке
	std::string addWord(const std::string& s, int atPos, int len, int freq)
	{
		std::string w = s.substr(atPos,len);
		std::vector<word>& vec_ref = dictionary[w];
		vec_ref[freq].freq++;
		std::string result = vec_ref[freq].chars;
		reSortT9(dictionary[w].begin(),vec_ref.begin()+freq);
		return result;
	}
	
	//возвращает знак препинани€
	std::string addZnak(int freq)
	{
		switch(freq)
		{
		case 0: return ".";
		case 1: return ",";
		case 2: return "?";
		default: return "But dear sir, this simply can not be!";
		}
	}
	
	//выводит результат дл€ входной строки
	void parseAndOutput(const std::string& s)
	{
		int i = 0;
		std::string result;

		while(i!=s.size())
		{
			int wsLen = getWs(s,i);
			int wordLen = getWordLen(s,i+wsLen);
			int freq = getFreq(s,i+wordLen+wsLen);

			if(wsLen)
				result += addWs(s,i,wsLen);
			if(wordLen)
				result += addWord(s,i+wsLen,wordLen,freq);

			i += wordLen + freq + wsLen;

			int znakLen = getZnakLen(s,i);
 			int znakFreq = getFreq(s,i+znakLen);

			if(znakLen)
				result += addZnak(znakFreq);

			i+= znakLen + znakFreq;
		}
		printf(result.c_str());
	}
public:
	parser(std::istream& inputStream) : input(inputStream)
	{
	}
	
	//формирование словар€
	void formDictionary()
	{
		uint N = 0;
		const int maxLineLen = 20 + 1 + 5;
		char* buf = new char[maxLineLen];
		input.getline(buf,100);
		//считываем количество слов в словаре
		N = atoi(buf);
		
		//итератор указывает на последнее вставленное слово
		dictContainer::iterator lastInserted = dictionary.begin();
		
		word to_insert;				//очередное слово дл€ вставки
		std::string numCombination;	//комбинаци€ клавиш дл€ слова
		std::vector<word> temp;
		
		for(uint i=0; i<N; i++)
		{
			input.getline(buf,maxLineLen);				//считать очередную строку
			to_insert.chars = strtok(buf," ");			//вычленить слово
			to_insert.freq = atoi(strtok(NULL,"\n"));	//вычленить частоту слова
			numCombination = wordToNums(to_insert.chars);
			
			lastInserted= dictionary.insert(lastInserted,std::pair<std::string,std::vector<word> >(numCombination,temp));	//вставить (если нет) комбинацию в словарь
			std::vector<word>& vec_ref = lastInserted->second;

			vec_ref.push_back(to_insert);	//добавить к комбинации слово
			
		}
		//отсортировать слова в массивах словар€
		dictContainer::iterator iter = dictionary.begin();
		for(; iter!= dictionary.end(); iter++)
		{
			std::sort(iter->second.begin(), iter->second.end(),wordComparession());
		}
		delete [] buf;
	}

	//считывает строку из входного потока и отправл€ет на разбор
	void readAndParse()
	{
		int maxLineLen = 100777;
		char* buf = new char[maxLineLen];
		input.getline(buf,maxLineLen);
		parseAndOutput(buf);
		delete [] buf;
	}
};

int main()
{
	std::istream& ifstr = std::cin;
	parser p(ifstr);
	p.formDictionary();
	p.readAndParse();
	return 0;
}


char* wordToNums(const std::string& word)	
{
	static char buf[100];
	uint size = word.size();
	uint i = 0;
	for(; i<size; i++)
	{
		switch(tolower(word[i]))
		{
		case '.':
		case ',':
		case '?':
			buf[i] = '1';
		case 'a':
		case 'b':
		case 'c':
			buf[i] = '2';
			break;
		case 'd':
		case 'e':
		case 'f':
			buf[i] = '3';
			break;
		case 'g':
		case 'h':
		case 'i':
			buf[i] = '4';
			break;
		case 'j':
		case 'k':
		case 'l':
			buf[i] = '5';
			break;
		case 'm':
		case 'n':
		case 'o':
			buf[i] = '6';
			break;
		case 'p':
		case 'q':
		case 'r':
		case 's':
			buf[i] = '7';
			break;
		case 't':
		case 'u':
		case 'v':
			buf[i] = '8';
			break;
		case 'w':
		case 'x':
		case 'y':
		case 'z':
			buf[i] = '9';
			break;
		}
	}
	buf[i] = 0;
	return buf;
}
