#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

struct Data
{
	char Word[21];
	int Freq;
};

bool SortFunc(Data data1, Data data2)
{
	if (data1.Freq == data2.Freq)
		for (int i = 0; ; i++)
			if (data1.Word[i] == data2.Word[i])
				continue;
			else
				return data1.Word[i] < data2.Word[i];
	return data1.Freq > data2.Freq;
}

string GetWordAndUpdatePriority(vector<Data>* vct, int index)
{
	if (!index)
	{
		vct->front().Freq++;
		return vct->front().Word;
	}
	std::vector<Data>::iterator i = vct->begin() + index;
	i->Freq++;
	if (i != vct->begin() && (vct->begin() + index)->Freq < (i - 1)->Freq)
		return i->Word;
	while (i != vct->begin() && (vct->begin() + index)->Freq >= (i - 1)->Freq)
		i--;
	swap(*i, *(vct->begin() + index));
	return i->Word;
}

int main()
{
	int wordsNumber, wordLength;
	map<string, vector<Data> > dictionary;
	string numbers;
	numbers.reserve(20);
	scanf("%d", &wordsNumber);
	for (int i = 0; i < wordsNumber; i++)
	{
		Data* data = new Data();
		scanf("%s", data->Word);
		scanf("%d", &data->Freq);
		wordLength = 0;
		while (data->Word[wordLength])
			wordLength++;
		numbers.resize(wordLength);
		for (int j = 0; j < wordLength; j++)
			switch (data->Word[j])
			{
				case 'a': numbers[j] = '0'; break; case 'b': numbers[j] = '0'; break;
				case 'c': numbers[j] = '0'; break; case 'd': numbers[j] = '1'; break;
				case 'e': numbers[j] = '1'; break; case 'f': numbers[j] = '1'; break;
				case 'g': numbers[j] = '2'; break; case 'h': numbers[j] = '2'; break;
				case 'i': numbers[j] = '2'; break; case 'j': numbers[j] = '3'; break;
				case 'k': numbers[j] = '3'; break; case 'l': numbers[j] = '3'; break;
				case 'm': numbers[j] = '4'; break; case 'n': numbers[j] = '4'; break;
				case 'o': numbers[j] = '4'; break; case 'p': numbers[j] = '5'; break;
				case 'q': numbers[j] = '5'; break; case 'r': numbers[j] = '5'; break;
				case 's': numbers[j] = '5'; break; case 't': numbers[j] = '6'; break;
				case 'u': numbers[j] = '6'; break; case 'v': numbers[j] = '6'; break;
				case 'w': numbers[j] = '7'; break; case 'x': numbers[j] = '7'; break;
				case 'y': numbers[j] = '7'; break; case 'z': numbers[j] = '7'; break;
			}
		dictionary[numbers].push_back(*data);
		delete(data);
	}
	for (map<string, vector<Data> >::iterator i = dictionary.begin(); i != dictionary.end(); i++)
		sort(i->second.begin(), i->second.end(), SortFunc);
	char firstSymbols;
	scanf("%c", &firstSymbols);
	scanf("%c", &firstSymbols);
	while (firstSymbols == ' ')
	{
		printf(" ");
		scanf("%c", &firstSymbols);
	}
	bool isLast = false, firstIsOne = false;
	char symbol;
	char input[100001], fullInput[100001], punctMarks[3] = {'.', ',', '?'};
	int fullIndex = 0, index, starsNumberPunct, starsNumberWord;
	fullInput[0] = firstSymbols;
	fgets(&fullInput[1], 100001, stdin);
	while (!isLast)
	{
		index = 0;
		if (firstIsOne)
		{
			index = 1;
			input[0] = symbol;
			fullIndex++;
		} 
		symbol = fullInput[fullIndex];
		firstIsOne = false;
		while (symbol != 10 && symbol != ' ')
		{
			if (symbol == '1')
				firstIsOne = true;
			if ('2' <= symbol && symbol <= '9' && firstIsOne)
				break;
			input[index++] = symbol;
			symbol = fullInput[++fullIndex];
		}
		if (symbol == 10)
			isLast = true;
		input[index] = 0;
		wordLength = 0;
		while ('2' <= input[wordLength] && input[wordLength] <= '9')
			wordLength++;
		if (wordLength)
		{
			numbers.resize(wordLength);
			for (int j = 0; j < wordLength; j++)
				numbers[j] = (char)((int)input[j] - 2);
		}
		do
		{
			starsNumberPunct = 0;
			starsNumberWord = 0;
			if (input[wordLength] == 0)
				printf("%s", GetWordAndUpdatePriority(&dictionary[numbers], 0).c_str());
			else if (input[wordLength] == '1')
			{
				starsNumberPunct = 0;
				while (input[wordLength + starsNumberPunct + 1] == '*')
					starsNumberPunct++;
				if ('2' <= input[wordLength - 1] && input[wordLength - 1] <= '9')
					printf("%s%c", GetWordAndUpdatePriority(&dictionary[numbers], 0).c_str(), punctMarks[starsNumberPunct % 3]);
				else
					printf("%c", punctMarks[starsNumberPunct % 3]);
				wordLength++;
			}
			else if (input[wordLength] == '*')
			{	
				starsNumberWord = 1;
				while (input[wordLength + starsNumberWord] == '*')
					starsNumberWord++;
				printf("%s", GetWordAndUpdatePriority(&dictionary[numbers], starsNumberWord % dictionary[numbers].size()).c_str());
			}
			wordLength += starsNumberPunct + starsNumberWord;
		} while (input[wordLength]);
		while (symbol == ' ')
		{
			printf(" ");
			symbol = fullInput[++fullIndex];
		}
		if (symbol == 10)
			isLast = true;
	}
	return 0;
}