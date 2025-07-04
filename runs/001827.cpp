#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

class T9Engine
{
private:
	
	class DictionaryEntry
	{
	private:
		string word;
		int priority;
		int last_update;	

	public:
		DictionaryEntry(string word, int priority) :
			word(word), priority(priority), last_update(0)
		{
		}

		void up()
		{
			static int position = 0;
			++position;
			++priority;
			last_update = position;
		}

		bool operator < (const DictionaryEntry& other) const
		{
			return (other.priority < priority) ||
			       (other.priority == priority && other.last_update < last_update);
		}

		operator const string&() const
		{
			return word;
		}
	};

	string input_seq;
	enum { typing, listing, pointing } state;
	map<string, multiset<DictionaryEntry> > dictionary;
	map<string, multiset<DictionaryEntry> >::iterator current_set;
	multiset<DictionaryEntry>::iterator current_word;

	char t9code(char letter)
	{
		static int buttons[] = {
						2, 2, 2,	3, 3, 3,
			4, 4, 4,	5, 5, 5,	6, 6, 6,
			7, 7, 7, 7,	8, 8, 8, 	9, 9, 9, 9 };

		return buttons[letter - 'a'] + '0';
	}

	string t9code(const string& word)
	{
		string result;
		for (int i = 0; i < word.length(); ++i)
			result.push_back(t9code(word[i]));
		return result;
	}

	void select_set(const string& input_seq)
	{
		current_set = dictionary.find(input_seq);
		current_word = current_set->second.begin();
	}

	void approve_word()
	{
    	DictionaryEntry entry = *current_word;
    	current_set->second.erase(current_word);
    	entry.up();
    	current_word = current_set->second.insert(entry);
	}

public:

	T9Engine()
	{
		state = typing;
		dictionary[""].insert(DictionaryEntry("", 0));
		dictionary["1"].insert(DictionaryEntry(".", 0));
		dictionary["1"].insert(DictionaryEntry(",", 0));
		dictionary["1"].insert(DictionaryEntry("?", 0));
		select_set("");
	}
	
	void add_word(const string& word, int priority)
	{
		dictionary[t9code(word)].insert(DictionaryEntry(word, priority));
	}

	string push_button(char button)
	{
		string out;

		if (button == 0)
			return *current_word;

		if ('2' <= button && button <= '9')
		{
			out = *current_word;
			select_set("");
			state = typing;
		}
		
		if (state == typing)
		{
			if ('2' <= button && button <= '9')
				input_seq.push_back(button);
			else
			{
				current_set = dictionary.find(input_seq);
				current_word = current_set->second.begin();
				input_seq.clear();
				state = listing;
			}
		}

		if (state == listing)
		{
			if (button == '*')
				++current_word;
			else
			{
				approve_word();
				state = pointing;
			}
		}

		if (state == pointing)
		{
			if (button == '1')
			{
				out = *current_word;
				select_set("1");
			}
			else if (button == '*')
			{
				++current_word;
			}
		}

		if (button == ' ')
		{
			out = *current_word;
			out.push_back(button);
			select_set("");
			state = typing;
		}

		return out;
	}
	
};

int main()
{
	T9Engine t9;
	int words_num;
	cin >> words_num;
	for (int i = 0; i < words_num; ++i)
	{
		string word;
		int priority;
		cin >> word >> priority;
		t9.add_word(word, priority);
	}

	string input_seq;
	getline(cin, input_seq);
	getline(cin, input_seq);
	string out;
	for (int i = 0; i < input_seq.length(); ++i)
		cout << t9.push_button(input_seq[i]);
	cout << t9.push_button(0);

	return 0;
}
