#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <map>

using namespace std;

const char BUTTONS[256] = 
{
	'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
	'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1',
	'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
	'0', '0', '0', '0', '0', '0',
	'2', '2', '2', 
	'3', '3', '3',
	'4', '4', '4',
	'5', '5', '5',
	'6', '6', '6', 
	'7', '7', '7', '7',
	'8', '8', '8',
	'9', '9', '9', '9',
	'0', '0', '0', '0', '0', '0', '0', '0', '0', 
	'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
	'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
	'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
	'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' 
};

class Word
{
public:
	// �����
	string value;	
	// ����� ����
	string buttons;
	// �������
	int count;
	// ��������� � ������� ���������
	int currMsgPriority;
	// ���������� ������ ��� ������������
	void setButtons()
	{
		int l = (int)this->value.length();
		for (int i = 0; i < l; i++)
			this->buttons += BUTTONS[this->value[i]];
	}
};

// ������� ��������� ����
bool compareWords_2(Word word1, Word word2)
{
	// ���� ������� �� ����� �� ������������ ����� ������������ �� ������� �������
	if (word1.count != word2.count)
		return word1.count > word2.count;
	
	// ���� ���������� � ������� ��������� �� ����� �� �� ����������
	else if (word1.currMsgPriority != word2.currMsgPriority)
		return word1.currMsgPriority > word2.currMsgPriority;

	// ����� ���������� ����������
	else
		return word1.value < word2.value;
}

// ���������� ��������� �9
class T9
{
public:
	// ������� 2
	map<string, vector<Word> > dict;

	// ���������� ���� � �������
	int wordsCount;
	// ������ ��������� ���� (�������� ������������������ ��������� ����, ��������, ���������)
	vector<string> wordsList;

	// ������� ����� � ������
	void InsertWord(Word word)
	{
		// ������ ������
		int size = this->dict[word.buttons].size();
		if (size == 0)
		{
			this->dict[word.buttons].push_back(word);
			return;
		}
		// � ����� ���������
		if (size == 1)
		{
			if (compareWords_2(word, this->dict[word.buttons][0]))
				this->dict[word.buttons].insert(this->dict[word.buttons].begin(), word);
			else
				this->dict[word.buttons].push_back(word);
			return;
		}
		// ����� ������ ��������
		if (compareWords_2(word, this->dict[word.buttons][0]))
		{
			this->dict[word.buttons].insert(this->dict[word.buttons].begin(), word);
			return;
		}
		if (compareWords_2(this->dict[word.buttons][size - 1], word))
		{
			this->dict[word.buttons].push_back(word);
			return;
		}
		for (int i = 0; i < size - 1; i++)
		{
			if ((compareWords_2(this->dict[word.buttons][i], word)) 
				&& (compareWords_2(word, this->dict[word.buttons][i + 1])))
			{
				this->dict[word.buttons].insert(this->dict[word.buttons].begin() + i + 1, word);
				return;
			}
		}
	}

	// ��������� ������� ���������� ����
	void MoveWord(vector<Word> &wordsList, int index)
	{
		int i = index;
		while (i > 0)
		{
			if (compareWords_2(wordsList[i - 1], wordsList[i]))
				break;
			swap(wordsList[i - 1], wordsList[i]);
			i--;
		}
	}
	
	// ����� ������ ������� ������
	void getInputData()
	{
		string s = "";
		char buffer[4096 * 128];
		cin.getline(buffer, sizeof(buffer) - 1);
		s = buffer;
		this->wordsCount = atoi(s.data());

		// ��������� �������
		for (int i = 0; i < this->wordsCount; i++)
		{		
			cin.getline(buffer, sizeof(buffer) - 1);
			s = buffer;
			Word word;
			word.value = s.substr(0, s.find_first_of(" "));
			word.count = atoi(s.substr(s.find_first_of(" ") + 1, s.length() - (s.find_first_of(" ") + 1)).data());
			word.currMsgPriority = 0;
			word.setButtons();
			
			//int first = word.buttons[0] - 48;
			//this->dictionary[first - 1][word.value.length() - 1][word.buttons].push_back(word);
			
			this->InsertWord(word);
		}

		// ��������� ����� ���������� � ������� (��� ����� � �������������� ���������)
		Word w;
		w.buttons = "1";
		w.value = ".";
		w.count = -1;
		w.currMsgPriority  = 0;
				
		//this->dictionary[0][0]["1"].push_back(w);
		this->dict["1"].push_back(w);

		w.value = ",";
		w.count = -2;
		w.currMsgPriority = 0;
		
		//this->dictionary[0][0]["1"].push_back(w);
		this->dict["1"].push_back(w);

		w.value = "?";
		w.count = -3;
		w.currMsgPriority = 0;
		
		//this->dictionary[0][0]["1"].push_back(w);
		this->dict["1"].push_back(w);

		if (cin.eof())
			return;

		cin.getline(buffer, sizeof(buffer) - 1);
		s = buffer;

		if (s.length() <= 0)
		{
			this->wordsList.resize(0);
			return;
		}
		
		string word = "";
		// ��������� ��������� �������
		int wordType = 1; // 1 - �����, 2 - ���� ���������
		for (int i = 0; i < (int)s.length(); i++)
		{
			if (s[i] == '1')
			{
				if (word.length() > 0)
					this->wordsList.push_back(word);
				word = '1';
				wordType = 2;
			}
			else if (s[i] == ' ')
			{
				if (word.length() > 0)
					this->wordsList.push_back(word);
				word = "";
				this->wordsList.push_back(" ");
			}
			else if (s[i] == '*')
				word += '*';
			else
			{
				if (wordType == 1)
					word += s[i];
				else
				{
					if (word.length() > 0)
						this->wordsList.push_back(word);
					word = s[i];
				}
				wordType = 1;
			}
		}
		if (word.length() > 0)
			this->wordsList.push_back(word);
	}
	// ����� ������� ������ ��������� �������� (����, ���������, ��������)
	void decodeString()
	{
		if (wordsList.size() <= 0)
		{
			cout << "";
			return;
		}
		// ���� �� ��������� ������
		for (int i = 0; i < (int)this->wordsList.size(); i++)
		{
			// ������ ������
			if (this->wordsList[i] == " ")
			{
				cout << " ";
				continue;
			}

			// ������ ���������� ���� (��������������� ����� ������� �������)
			int len = wordsList[i].find_first_of('*');
			if (len < 0)
				len = wordsList[i].length();
			int skipCount = this->wordsList[i].length() - len;	
			this->wordsList[i] = this->wordsList[i].substr(0, len);
			
			cout << this->dict[this->wordsList[i]][skipCount].value;

			if (this->wordsList[i] != "1")
			{
				this->dict[this->wordsList[i]][skipCount].count++;
				this->dict[this->wordsList[i]][skipCount].currMsgPriority = i + 1;
				this->MoveWord(this->dict[this->wordsList[i]], skipCount);
			}
		}
	}
};

int main()
{
	T9 t9;
	t9.getInputData();
	t9.decodeString();
	return 0;
}