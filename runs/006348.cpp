#include <stdio.h>
#include <map>
#include <vector>
#include <string>

using namespace std;

void T9_encode(string& word)
{
	const char* latin_codes = "22233344455566677778889999";
	for (string::iterator it = word.begin(); it != word.end(); ++it)
		if (*it >= 'a' && *it <= 'z')
			*it = latin_codes[*it-'a'];
		else if (*it == '.' || *it == ',' || *it == '?')
			*it = '1';
}

class dictionary
{
public:
	void add_word(const string& word, int frequency);
	const string& T9_decode(const string& t9, int offset, bool update_frequency = true);

private:
	struct word_info
	{
		string word;
		int frequency;
		word_info(const string& _word, int _frequency = 0) :
			word(_word),
			frequency(_frequency)
		{}
	};


	map<string, vector<word_info> > words;
};

void dictionary::add_word(const string& word, int frequency)
{
	string t9(word);
	T9_encode(t9);
	vector<word_info>& word_list = words[t9];
	vector<word_info>::iterator place;
	for (place = word_list.begin();
		place != word_list.end() && place->frequency >= frequency;
		++place)
		;
	word_list.insert(place, word_info(word, frequency));
}

const string& dictionary::T9_decode(const string& t9, int offset, bool update_frequency)
{
	vector<word_info>& word_list = words[t9];
	if (update_frequency)
	{
		word_list[offset].frequency++;
		for (offset; offset > 0 && word_list[offset].frequency >= word_list[offset-1].frequency; --offset)
			swap(word_list[offset], word_list[offset-1]);
	}	
	return word_list[offset].word;
}

int main()
{
	dictionary dic;
	dic.add_word(string("."), 1);
	dic.add_word(string(","), 1);
	dic.add_word(string("?"), 1);

	int n;
	scanf("%d\n", &n);
	for (int i = 0; i < n; ++i)
	{	
		char word_buffer[21];
		int frequency;
		scanf("%s %d\n", word_buffer, &frequency);
		dic.add_word(string(word_buffer), frequency);
	}

	string t9_word;
	int asterisk_count = 0;
	int c;
	while ((c = getchar()) != -1)
	{
		if ((c == '1' || c == ' ') && t9_word.size() > 0)
		{
			printf("%s", dic.T9_decode(t9_word, asterisk_count, t9_word[0] != '1').c_str());
			t9_word.clear();
			asterisk_count = 0;
		}
		if (c >= '1' && c <= '9')
			t9_word.push_back(c);
		if (c == ' ')
			putchar(c);
		if (c == '*')
			asterisk_count++;
	}
	if (t9_word.size() > 0)
		printf("%s", dic.T9_decode(t9_word, asterisk_count).c_str());
}
