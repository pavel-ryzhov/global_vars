#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// ����� � �������
class Word
{
private:
	// �����
	string _value;
	
	// �������
	int _count;

	// ��������� � ������� ���������
	int _currMsgPriority;
public:
	// ���������� �����
	string getValue()
	{
		return this->_value;
	}

	// ����������� �������� �����
	void setValue(string value)
	{
		this->_value = value;
	}

	// ���������� ������� �������������
	int getCount()
	{
		return this->_count;
	}

	// ����������� �������� ������� �������������
	void setCount(int count)
	{
		this->_count = count;
	}

	// ���������� ��������� � ������� ���������
	int getCurrMsgPriority()
	{
		return this->_currMsgPriority;
	}

	// ������������� ��������� � ������� ���������
	void setCurrMsgPriority(int count)
	{
		this->_currMsgPriority = count;
	}
};

// ������� ��������� ����
bool compareWords_2(Word word1, Word word2)
{
	// ���� ������� �� ����� �� ������������ ����� ������������ �� ������� �������
	if (word1.getCount() != word2.getCount())
		return word1.getCount() > word2.getCount();
	
	// ���� ���������� � ������� ��������� �� ����� �� �� ����������
	else if (word1.getCurrMsgPriority() != word2.getCurrMsgPriority())
		return word1.getCurrMsgPriority() > word2.getCurrMsgPriority();

	// ���� ����� ���� �� ����� �� ����� ����� ��������
	else if (word1.getValue().length() != word2.getValue().length())
		return word1.getValue().length() < word2.getValue().length();

	// ����� ���������� ����������
	else
		return word1.getValue() < word2.getValue();
}

// ���������� ��������� �9
class T9
{
private:
	// �������
	vector<Word> _dictionary;

	// ���������� ���� � �������
	int _wordsCount;

	// ������ ��������� ���� (�������� ������������������ ��������� ����, ��������, ���������)
	vector<string> _wordsList;
public:
	// ���������� ������������������ ��������, ��������������� ������ ������
	string buttonToSymbols(char button)
	{
		switch (button)
		{
			case '1': return ".,?";
			case '2': return "abc";
			case '3': return "def";
			case '4': return "ghi";
			case '5': return "jkl";
			case '6': return "mno";
			case '7': return "pqrs";
			case '8': return "tuv";
			case '9': return "wxyz";
			default : return "";
		}
	}
	// ����� ������ ������� ������
	void getInputData()
	{
		string s = "";
		char buffer[1024];
		cin.getline(buffer, 1024);
		s = buffer;
		this->_wordsCount = atoi(s.data());

		// ��������� �������
		for (int i = 0; i < this->_wordsCount; i++)
		{		
			cin.getline(buffer, 1024);
			s = buffer;
			Word word;
			word.setValue(s.substr(0, s.find_first_of(" ")));
			word.setCount(atoi(s.substr(s.find_first_of(" ") + 1, s.length() - (s.find_first_of(" ") + 1)).data()));
			word.setCurrMsgPriority(0);
			this->_dictionary.push_back(word);
		}

		// ��������� ����� ���������� � ������� (��� ����� � �������������� ���������)
		Word w;
		w.setValue(".");
		w.setCount(-1);
		w.setCurrMsgPriority(0);
		this->_dictionary.push_back(w);

		w.setValue(",");
		w.setCount(-2);
		w.setCurrMsgPriority(0);
		this->_dictionary.push_back(w);

		w.setValue("?");
		w.setCount(-3);
		w.setCurrMsgPriority(0);
		this->_dictionary.push_back(w);

		cin.getline(buffer, 1024);
		s = buffer;
		
		string word = "";
		// ��������� ��������� �������
		for (int i = 0; i < (int)s.length(); i++)
		{
			if (s[i] == ' ')
			{
				if (word.length() > 0)
					this->_wordsList.push_back(word);
				this->_wordsList.push_back(" ");
				word = "";
			}
			else if (s[i] == '1')
			{	
				if (word.length() > 0)
					this->_wordsList.push_back(word);
				word = "1";
			}
			else 
				word += s[i];
		}
		if (word.length() > 0)
			this->_wordsList.push_back(word);
	}
	// ����� ������� ������ ��������� �������� (����, ���������, ��������)
	void decodeString()
	{
		// ���� �� ��������� ������
		for (int i = 0; i < (int)this->_wordsList.size(); i++)
		{
			// ������ ������
			if (this->_wordsList[i] == " ")
			{
				cout << " ";
				continue;
			}

			// ������ ���������� ���� (��������������� ����� ������� �������)
			vector<Word> relevantWords = this->_dictionary;
			
			// ��������� ���������� �����
			sort(relevantWords.begin(), relevantWords.end(), compareWords_2);

			int skipCount = 0;
			// �������� �� �������� � �����
			for (int j = 0; j < (int)this->_wordsList[i].length(); j++)
			{
				// ������� *
				if (this->_wordsList[i][j] == '*')
				{
					skipCount = this->_wordsList[i].length() - j;
					break;
				}
				
				// ���������� �������, ��������������� ������ �����
				string symbols = this->buttonToSymbols(this->_wordsList[i][j]);
				int k = 0;

				// �������� �� �������� ������ ������ �����
				while (k < (int)relevantWords.size())
				{
					if ((int)relevantWords[k].getValue().length() > j)
					{
						bool isPresent = false;
						// �������� �� �������� �����
						for (int m = 0; m < (int)symbols.length(); m++)
						{
							if (relevantWords[k].getValue()[j] == symbols[m])
							{
								isPresent = true;
								break;
							}
						}
						if (!isPresent)
							relevantWords.erase(relevantWords.begin() + k);
						else
							k++;
					}
					else
						relevantWords.erase(relevantWords.begin() + k);
				}
			}

			// ���������� ����� �� ������� *
			if ((int)relevantWords.size() > skipCount)
			{
				// ������� ����� �� �����
				cout << relevantWords[skipCount].getValue();
					
				// ����������� ������� �������������
				Word w = relevantWords[skipCount];
				int n = 0;
				while (this->_dictionary[n].getValue() != w.getValue())
					n++;
				if (this->_dictionary[n].getCount() > 0)
				{
					// ����������� ������� �������������
					this->_dictionary[n].setCount(this->_dictionary[n].getCount() + 1);
					// ������������� ��������� � ������� ���������
					this->_dictionary[n].setCurrMsgPriority(i + 1);
				}
			}
		}
	}
};

int main()
{
	T9 t9;
	t9.getInputData();

	// ��������� ���������
	t9.decodeString();
	return 0;
}