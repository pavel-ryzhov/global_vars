#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class Entry
{
	public:
		string word;
		string num;
		int freq;
		int time;
	
		Entry(): word(""), num(""), freq(0), time(0){}
		Entry(string word, string num, int freq): word(word), num(num), freq(freq), time(0){}
};

bool compare_entries_word(const Entry& a, const Entry& b) 
			{
				
				if (a.num < b.num) return true;
				else if (a.num > b.num) return false;
				else if (a.freq > b.freq) return true;
				else if (a.freq < b.freq) return false;
				else if (a.word < b.word) return true;
				else return false;
			}

bool compare_entries_num(const Entry& a, const Entry& b) 
			{
				if (a.num < b.num) return true;
				else if (a.num > b.num) return false;
				else if (a.freq > b.freq) return true;
				else if (a.freq < b.freq) return false;
				else if (a.time >= b.time) return true;
				else return false;
			}

vector <Entry> voc;
const string punctuation = ".,?";
int N;

string to_num(string s)
{
	static const string pattern = "22233344455566677778889999";
	string a = "";

	for (int i = 0; i < s.length(); a += pattern[s[i++] - 'a']);
	return a;
}

int bin_search(string key, int left, int right)
{
	if (left >= right - 1)
		if (key == voc[left].num) return left;
			else return right;
	int middle = (left + right) / 2;
	if (key <= voc[middle].num) right = middle;
		else left = middle;
	return bin_search(key, left, right);
}

int bin_search(Entry e, int left, int right)
{
	if (left >= right - 1)
		if (compare_entries_num(e, voc[left])) return left;
			else return right;
	int middle = (left + right) / 2;
	if (compare_entries_num(e, voc[middle])) right = middle;
		else left = middle;
	return bin_search(e, left, right);
}
string get_word(string buf, int d, int time)
{
	int p = bin_search(buf, 0, voc.size());
	string word = voc[p + d].word;
	voc[p + d].freq++;
	voc[p + d].time = time;
	
	Entry e = voc[p + d];

	int r = bin_search(e, p, p + d + 1);
	
	for (int i = p + d; i > r; i--)
		voc[i] = voc[i - 1];
	voc[r] = e;

	return word;
}

void parse_input()
{
	int state = 0;
	string buf = "";
	char c;
	int d = 0;
	int time = 0;

	cin.get(c);

	for(;;)
	{
		if (cin.get(c) == 0) c = '\n';
		
		switch(c)
		{
			case '*': d++; break;
			case ' ': case '1': case '\n':
				
				if (state == 1) {
					cout << punctuation[d]; 
					d = 0;
					if (c == ' ') {
						cout.put(' ');
						state = 2;
					} else if (c == '\n') return;
				}
				else if (state == 0) {
					cout << get_word(buf, d, ++time);
					d = 0;
					buf = "";
					if (c == ' ') {
						cout.put(' ');
						state = 2;
					} else if (c == '\n') return;
					else state = 1;
				} else 
				{
					if (c == ' ') cout.put(' ');
					else if (c == '1') state = 1;
					else if (c == '\n') return;
					else state = 0;
				}
				break;
			default: 
				if (state == 1) {
					cout << punctuation[d]; 
					d = 0;
				}
				buf += c;
				state = 0;
		}
	}
}

int main()
{
	cin >> N;
	voc.resize(N);

	for (int i = 0; i < N; i++)
	{
		string w;
		int f;
		
		getline(cin, w, '\n');
		getline(cin, w, ' ');
		cin >> f;
				
		voc[i] = Entry(w, to_num(w), f);
	}
	sort(voc.begin(), voc.end(), compare_entries_word);
	parse_input();
}