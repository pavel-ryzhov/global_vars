#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
//#include <conio.h>

//#include <fstream> // for time checking
//#include <time.h>  // for input from file



using namespace std;

string word_to_t9 (string&);
bool vect_sort (pair <int,string>, pair <int,string>);
void Dict_view (map<string, vector <pair <int,string> >* > &);

int main (void)
{
//	clock_t start = clock(); // for time checking
	int Dict_size = 0;
	char dvd;
	string test;
	map <string, vector <pair <int,string> >* > Dict;
	map <string, vector <pair <int,string> >* > ::iterator it_Dict;
	vector <pair <int,string> > ::iterator it_vect;
	string::iterator it_string;

//	ifstream cin1; //for input from file
//	cin1.open("ttt1.txt"); //for input from file

//	Creating T9 Dictionary
	cin >> Dict_size;
	for (int i = Dict_size; i > 0; i--)
	{
		string dict_w;
		int word_freq;
		cin >> dict_w >> word_freq;
		string remake = word_to_t9(dict_w);
		if ((it_Dict = Dict.find(remake)) == Dict.end()){
			vector <pair <int,string> > * p_dict_w_w = new vector <pair <int,string> > ;
			Dict.insert( pair <string, vector <pair <int,string> >* > (remake, p_dict_w_w));
			it_Dict = Dict.find(remake);
			it_Dict->second->push_back( pair <int, string> (word_freq, dict_w));
		} else {
			it_Dict->second->push_back( pair <int, string> (word_freq, dict_w));
		}
	}

	for ( it_Dict=Dict.begin() ; it_Dict != Dict.end(); it_Dict++ ) {
		sort (it_Dict->second->begin(), it_Dict->second->end(), vect_sort);
	}

//	Dict_view (Dict);
//	cout << endl; printf("Work time = %f\n", (long double) (clock() - start) / CLOCKS_PER_SEC);// for time checking
//	Processing text
	string  work_word, fin_word, out_word;
	int tryes = 0;
	bool mark = false, text = false, change = false, m_change = false;
	cin >> work_word;
	while (cin){
		tryes = 0;
		mark = false;
		text = false;
		change = false;
		m_change = false;
		fin_word.clear();
		for ( it_string=work_word.begin() ; it_string < work_word.end(); it_string++ ) {
			if ((*it_string != '*') && (*it_string != '1')) {
				fin_word += *it_string;
				text = true;
				if (mark)
					change = true;
				mark = false;
			} else if (*it_string == '1') {
				if (text)
					change = true;
				if (mark)
					m_change = true;
				text = false;
				mark = true;
			} else {
				tryes++;
			}

			// Words out;

			if (((mark) && (change)) || ((text) && ((it_string + 1) == work_word.end()))) {
				it_Dict = Dict.find(fin_word);
				it_vect = it_Dict->second->begin();
				for (tryes; tryes > 0; tryes--, it_vect++);
				out_word = it_vect->second;

				int t_numb = it_vect->first;
				string t_word = it_vect->second;

				it_Dict->second->erase(it_vect);
				for (it_vect = it_Dict->second->begin();(it_vect != it_Dict->second->end()) && (it_vect->first > 1+ t_numb); it_vect ++ );
				it_Dict->second->insert(it_vect, pair < int, string> (t_numb +1, t_word));
				printf (out_word.c_str());
				fin_word.clear();
				out_word.clear();
				change = false;
				tryes = 0;
			}

			// Marks out;

			if ((m_change) || ((text) && (change)) || ((mark) && ((it_string + 1) == work_word.end()))){
				switch (tryes) {
					case (0):
						cout << '.';
						break;
					case (1):
						cout << ',';
						break;
					case (2):
						cout << '?';
						break;
				}
				if (((m_change) && ((it_string + 1) == work_word.end())))
					cout << '.';
				tryes = 0;
				change = false;
				m_change = false;
			}	
		}
		
		dvd = cin.get();
		while ((dvd == ' ') && (dvd != EOF)){
			cout << ' ';
			dvd = cin.get();
		}
		cin >> work_word;
		it_string = work_word.begin();
		work_word.insert(it_string,dvd);
	}
//	Dict_view (Dict);
//	cout << endl; printf("Work time = %f\n", (long double) (clock() - start) / CLOCKS_PER_SEC);// for time checking
	return 0 ;
};


void Dict_view (map<string, vector <pair <int,string> >* > & Dict)
{
	map <string, vector <pair <int,string> >* > ::iterator it_Dict;
	vector <pair <int,string> > ::iterator it_vect;
	cout << endl;
	for ( it_Dict=Dict.begin() ; it_Dict != Dict.end(); it_Dict++ ) {
		cout << it_Dict->first << endl;
		for ( it_vect=it_Dict->second->begin() ;it_vect != it_Dict->second->end(); it_vect++ ) {
			cout << it_vect->first  << " => " << it_vect->second << endl;
		}
	}

}
bool vect_sort (pair <int,string> a, pair <int,string> b)
{
	if ((a.first) > (b.first))
		return true;
	else if ((a.first) < (b.first))
		return false;
	else if ((a.second) < (b.second))
		return true;
	else if ((a.second) > (b.second))
		return false;
	return true;
}
string word_to_t9 (string& enter)
{
	string answer;
	string::iterator it;
	for ( it=enter.begin() ; it < enter.end(); it++ ) {
		switch (*it){
			case ('a'):
			case ('b'):
			case ('c'):
				answer += '2';
				break;
			case ('d'):
			case ('e'):
			case ('f'):
				answer += '3';
				break;
			case ('g'):
			case ('h'):
			case ('i'):
				answer += '4';
				break;
			case ('j'):
			case ('k'):
			case ('l'):
				answer += '5';
				break;
			case ('m'):
			case ('n'):
			case ('o'):
				answer += '6';
				break;
			case ('p'):
			case ('q'):
			case ('r'):
			case ('s'):
				answer += '7';
				break;
			case ('t'):
			case ('u'):
			case ('v'):
				answer += '8';
				break;
			case ('w'):
			case ('x'):
			case ('y'):
			case ('z'):
				answer += '9';
				break;
		}
	}
	return answer;
};



