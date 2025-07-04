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

		const string& get_word() const
		{
			return word;
		}
	};

	typedef multiset<DictionaryEntry> EntrySet;
	typedef map<string, EntrySet> Dictionary;

	string input_seq;
	enum { typing, listing, pointing } state;
	Dictionary dictionary;
	Dictionary::iterator current_set;
	EntrySet::iterator current_entry;

	char t9code(char letter);
	string t9code(const string& word);
	void select_set(const string& input_seq);
	void approve_word();

public:
	T9Engine();
	void add_word(const string& word, int priority);
	string push_button(char button);
	
};

T9Engine::T9Engine()
{
	state = typing;
	dictionary[""].insert(DictionaryEntry("", 0));
	dictionary["1"].insert(DictionaryEntry(".", 0));
	dictionary["1"].insert(DictionaryEntry(",", 0));
	dictionary["1"].insert(DictionaryEntry("?", 0));
	select_set("");
}

char T9Engine::t9code(char letter)
{
	static int buttons[] = {
					2, 2, 2,	3, 3, 3,
		4, 4, 4,	5, 5, 5,	6, 6, 6,
		7, 7, 7, 7,	8, 8, 8, 	9, 9, 9, 9 };

	return buttons[letter - 'a'] + '0';
}

string T9Engine::t9code(const string& word)
{
	string result;
	for (size_t i = 0; i < word.length(); ++i)
		result.push_back(t9code(word[i]));
	return result;
}

void T9Engine::select_set(const string& input_seq)
{
	current_set = dictionary.find(input_seq);
	current_entry = current_set->second.begin();
}

void T9Engine::approve_word()
{
	DictionaryEntry entry = *current_entry;
	current_set->second.erase(current_entry);
	entry.up();
	current_entry = current_set->second.insert(entry);
}

void T9Engine::add_word(const string& word, int priority)
{
	dictionary[t9code(word)].insert(DictionaryEntry(word, priority));
}

string T9Engine::push_button(char button)
{
	string out;

	if ('2' <= button && button <= '9')
	{
		out = current_entry->get_word();
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
			current_entry = current_set->second.begin();
			input_seq.clear();
			state = listing;
		}
	}

	if (state == listing)
	{
		if (button == '*')
			++current_entry;
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
			out = current_entry->get_word();
			select_set("1");
		}
		else if (button == '*')
		{
			++current_entry;
		}
	}

	if (button == ' ')
	{
		out = current_entry->get_word();
		out.push_back(button);
		select_set("");
		state = typing;
	}

	if (button == 0)
		return current_entry->get_word();

	return out;
}

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
