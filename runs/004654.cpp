#include <iostream>
#include <algorithm>
#include <list>
#include <map>
#include <string>
#include <cstring>

using namespace std;

struct vocabulary_item
{
	string word;
	short frequency;
};

char letter_keys[] = "22233344455566677778889999";

map <string, list <vocabulary_item> >  vocabulary;

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
	if (!seq.length())
		return;
	list<vocabulary_item>::iterator it; 
	for (it = vocabulary[seq].begin(); n > 0; ++it, n--)
	{
		;
	}
	message.append(it->word);
	it->frequency++;
			
	// Помещаем найденное слово перед словами с такой же частотой
	for (list<vocabulary_item>::iterator i = vocabulary[seq].begin(); i != it; ++i)
	{
		if (i->frequency <= it->frequency)
		{
			vocabulary[seq].insert(i, *it);
			vocabulary[seq].erase(it);
			return;
		}
	}
}

int main()
{
	int N;
	cin >> N;
	
	vocabulary_item item;
	string key;
	int j;
	for (int i = 0; i < N; i++)
	{
		cin >> item.word >>item.frequency;
		key.clear();
		for (j = 0; j < item.word.length(); j++)
			key.push_back(letter_keys[item.word[j]-'a']);
		vocabulary[key].push_back(item);
	}
	
	cin.ignore(1, '\n');
	cin.getline(sequence, 100000);
	
	// Сортируем слова по частоте
	for (map<string,list<vocabulary_item> >::iterator it = vocabulary.begin(); it != vocabulary.end(); ++it)
		it->second.sort(compare);
	
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