#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <map>

//��������� ��� �������� ���������� �����
struct word
{
	int freq;			//������� ����������
	std::string chars;  //���������� �����
	word(){}
	word(int frequency, const std::string& str)
	{
		freq = frequency;
		chars = str;
	}
	
};

//��������� - ������� �� �������, ����� �� ��������
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
//��� "�������". ����� - ���������� ������, ���������� - ������ ����, ����������� ��� ����������
typedef std::map<std::string,std::vector<word> > dictContainer;
typedef unsigned int uint;

//������� ���������� ���������� ������ ��� ��������� �����
char* wordToNums(const std::string& word);

//������� ����� ����������. ��������� �������, ��������� ������
class parser
{
private:
	dictContainer dictionary;	//�������
	std::istream& input;		//������� �����
		//���������� ����� ����� ����������
	int getZnakLen(const std::string& s, int atPos)
	{
		if(s[atPos]=='1')
			return 1;
		return 0;
	}

	//���������� ����� ����� 
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

	//���������� ���������� ��������
	int getFreq(const std::string& s, int atPos)
	{
		std::string::const_iterator pos = std::find_if(s.begin()+atPos,s.end(),std::bind2nd(std::not2(std::equal_to<char>()),'*'));
		return pos-(s.begin()+atPos);
	}

	//���������� ���������� ���������� ��������
	int getWs(const std::string& s, int atPos)
	{
		std::string::const_iterator pos = std::find_if(s.begin()+atPos,s.end(),std::not1(std::ptr_fun(isspace)));
		return pos-(s.begin()+atPos);
	}

	//���������� ���������� ������� �� �������� ������
	std::string addWs(const std::string& s, int atPos, int len)
	{
		return s.substr(atPos, len);
	}

	//��������� ����� ����� � ������� �� ������ �������
	void reSortT9(std::vector<word>::iterator begin, std::vector<word>::iterator wordPos)
	{
		int wordFreq = wordPos->freq;
		//���������������� �������, ��������� ��� ���������� ����� � ������� ��������
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

	//���������� �����, ���������� �� ���������� ���� � �������� ������
	std::string addWord(const std::string& s, int atPos, int len, int freq)
	{
		std::string w = s.substr(atPos,len);
		std::vector<word>& vec_ref = dictionary[w];
		vec_ref[freq].freq++;
		std::string result = vec_ref[freq].chars;
		reSortT9(dictionary[w].begin(),vec_ref.begin()+freq);
		return result;
	}
	
	//���������� ���� ����������
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
	
	//������� ��������� ��� ������� ������
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
	
	//������������ �������
	void formDictionary()
	{
		uint N = 0;
		const int maxLineLen = 20 + 1 + 5;
		char* buf = new char[maxLineLen];
		input.getline(buf,100);
		//��������� ���������� ���� � �������
		N = atoi(buf);
		
		//�������� ��������� �� ��������� ����������� �����
		dictContainer::iterator lastInserted = dictionary.begin();
		
		word to_insert;				//��������� ����� ��� �������
		std::string numCombination;	//���������� ������ ��� �����
		std::vector<word> temp;
		
		for(uint i=0; i<N; i++)
		{
			input.getline(buf,maxLineLen);				//������� ��������� ������
			to_insert.chars = strtok(buf," ");			//��������� �����
			to_insert.freq = atoi(strtok(NULL,"\n"));	//��������� ������� �����
			numCombination = wordToNums(to_insert.chars);
			
			lastInserted= dictionary.insert(lastInserted,std::pair<std::string,std::vector<word> >(numCombination,temp));	//�������� (���� ���) ���������� � �������
			std::vector<word>& vec_ref = lastInserted->second;

			vec_ref.push_back(to_insert);	//�������� � ���������� �����
			
		}
		//������������� ����� � �������� �������
		dictContainer::iterator iter = dictionary.begin();
		for(; iter!= dictionary.end(); iter++)
		{
			std::sort(iter->second.begin(), iter->second.end(),wordComparession());
		}
		delete [] buf;
	}

	//��������� ������ �� �������� ������ � ���������� �� ������
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
