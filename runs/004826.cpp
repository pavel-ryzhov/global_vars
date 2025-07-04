#include <cstdlib>
#include <iostream>


#include <map>
#include <string>
#include <sstream>

using namespace std;

char getKeyNumber(char c)
{
	if (c == 'a' || c == 'b' || c == 'c') return '2';
	else if (c == 'd' || c == 'e' || c == 'f') return '3';
	else if (c == 'g' || c == 'h' || c == 'i') return '4';
	else if (c == 'j' || c == 'k' || c == 'l') return '5';
	else if (c == 'm' || c == 'n' || c == 'o') return '6';
	else if (c == 'p' || c == 'q' || c == 'r' || c == 's') return '7';
	else if (c == 't' || c == 'u' || c == 'v') return '8';
	else if (c == 'w' || c == 'x' || c == 'y' || c == 'z') return '9';	
}

int main(int argc, char *argv[])
{
	typedef multimap<int, string> word; 
	map<string, word> dictionary; // словарь. первый элемент - ключ слова, полученный из номеров нажатых клавиш на телефоне, воторой - multimap из слов (ключ - частота всречаемости) 
	
	int n; // число слов в словаре

	cin >> n;

	for (int i = 0; i < n; i++)
	{		
		char c; 
		string w;
		string key;
		for (;;)
		{
			c = getchar();
			if (c == ' ') break; 
			if (c >= 97 && c <= 122)
			{
				w += c;
				key += getKeyNumber(c);
			}
		}
		int frequency;
		cin >> frequency;

		dictionary[key].insert(pair<int, string>(-frequency, w)); 
	}

	string answer;
	char c; 
	string input;
	int numOfStars = 0;
	bool flag = false;
	bool semicolon = false;
	for (;;)
	{
		c = getchar();		
		if (c == ' ' || (c == '\n' && flag))
		{
			if (!semicolon)
			{
				map<string, word>::iterator dit = dictionary.find(input);
				word::iterator wit = dit->second.begin();
				for (int i = 0; i < numOfStars; i++) wit++;

				answer += wit->second + " ";

				int temp1;
				string temp2;

				temp1 = wit->first;
				temp2 = wit->second;

				dictionary[input].erase(wit);
				wit = dictionary[input].insert(pair<int, string>(--temp1, temp2));

				word::iterator wit2 = dit->second.find(temp1); 

				while (wit2 != wit)
				{
					word::iterator wit3 = wit;
					wit3--;
					wit->second = wit3->second;
					wit--;
				}
				wit2->second = temp2;

				numOfStars = 0;
				
			}
			else 
			{
				char sc;
				if (numOfStars == 0) sc = '.';
				if (numOfStars == 1) sc = ',';
				if (numOfStars == 2) sc = '?';

				answer += sc;
				answer += " ";
				semicolon = false;
				numOfStars = 0;

			}
			
			input = "";
			if (c == '\n' && flag) break;
			
		}
		if (c == '*') 
		{
			numOfStars++;
		}
		if (c >= 50 && c <= 57) { input += c; flag = true; }
		if (c == 49)
		{
			semicolon = true;
			map<string, word>::iterator dit = dictionary.find(input);
			word::iterator wit = dit->second.begin();
			for (int i = 0; i < numOfStars; i++) wit++;

			answer += wit->second;

			int temp1;
			string temp2;

			temp1 = wit->first;
			temp2 = wit->second;

			dictionary[input].erase(wit);
			wit = dictionary[input].insert(pair<int, string>(--temp1, temp2));

			word::iterator wit2 = dit->second.find(temp1); 

			while (wit2 != wit)
			{
				word::iterator wit3 = wit;
				wit3--;
				wit->second = wit3->second;
				wit--;
			}
			wit2->second = temp2;

			numOfStars = 0;
			input = "";
		}
		
	}

	answer.resize(answer.length() - 1);
	cout << answer;

//	system("PAUSE");
	
	return 0;
}
