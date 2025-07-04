#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

struct vocabulary_item
{
	string word;
	int frequency;
};

char letter_keys[] = "22233344455566677778889999";

vector <list <vocabulary_item> > vocabulary;

string message;
char sequence[100001]; // Последовательность нажатых кнопок

bool compare(const vocabulary_item& item1, const vocabulary_item& item2)
{
	if (item1.frequency > item2.frequency) return true;
	if (item1.frequency < item2.frequency) return false;
	
	return item1.word.compare(item2.word)-1;
}

/*
	Находит n+1-ое слово, удволетворяющее последовательности
	кнопок seq, и добавляет его к message 
*/
void find_word(const string& seq, int n)
{
	int length = seq.length();
	if (!length)
		return;
	int flag;
	string word;
	int i;
	list <vocabulary_item> & voc = vocabulary[seq[0]-'2'];
	for (list<vocabulary_item>::iterator it = voc.begin(); it != voc.end(); ++it)
	{
		if (length != it->word.length()) continue;
	
		// Проверяем, что i-й символ слова соответсвует i-й кнопке из seq
		flag = 0;
		word = it->word;
		for (i = 0; i < length; i++)
			if (letter_keys[word[i]-'a'] != seq[i])
			{
				flag = 1;
				break;
			}
		if (flag) continue;
		
		if (n-- == 0)
		{
			message.append(word);
			it->frequency++;
			
			// Помещаем найденное слово перед словами с такой же частотой
			for (list<vocabulary_item>::iterator i = voc.begin(); i != it; ++i)
			{
				if (i->frequency <= it->frequency)
				{
					voc.insert(i, *it);
					voc.erase(it);
					return;
				}
			}
			return;
		}
	}
}

int main()
{
	int N;
	cin >> N;
	
	vocabulary.resize(8);
	
	vocabulary_item item;
	for (int i = 0; i < N; i++)
	{
		cin >> item.word >>item.frequency;
		vocabulary[letter_keys[item.word[0]-'a']-'2'].push_back(item);
	}
	
	cin.ignore(1, '\n');
	cin.getline(sequence, 100000);
	
	// Сортируем слова по частоте
	for (int i = 0; i < 8; i++)
		vocabulary[i].sort(compare);
	
	int stars = 0; // Число звездочек после слова
	int length = strlen(sequence);
	string subseq; // Последовательность кнопок, соответствующая одному слову
	for (int i = 0; i < length; i++)
	{
		switch (sequence[i])
		{
		case ' ':
			find_word(subseq, stars);
			stars = 0;
			subseq.clear();
			message.push_back(' ');
			break;
		
		case '*':
			stars++;
			break;
		
		case '1':
			find_word(subseq, stars);
			stars = 0;
			subseq.clear();
			
			// Смотрим число звездочек после "1" и выбираем знак препинания
			if (sequence[i+1] != '*')
				message.push_back('.');
			else if (i < length-2 && sequence[i+2] == '*')
			{
				message.push_back('?');
				i+=2;
			}
			else
			{
				message.push_back(',');
				i++;
			}
			break;
		
		default:
			subseq.push_back(sequence[i]);
		}
	}
	find_word(subseq, stars);
	cout << message << endl;
}