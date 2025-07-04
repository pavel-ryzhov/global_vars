/*	Author: Bychkov Ivan
 *
 *	Note: comments was written on English for the sake of font compatibility
 */

#include <string>
#include <map>
#include <list>
#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>

using namespace std;

//sorting criteria
bool wordComparison (pair <string, int> w1, pair <string, int> w2) {
	if (w1.second > w2.second)	//index comparison
		return true;
	else if (w1.second == w2.second && w1.first < w2.first)	//lexigraphical comparison
		return true;	
	return false;
};

class T9Dictionary {
	/*	data structure: map <string, list <pair <string, int> > >
		map key is T9 code
		map value is list of pair word - index of frequency
	*/
	map <string, list <pair <string, int> > > dict;	//Main dictionary
	map <string, vector <pair <string, int> > > preDict;	//Dictionary for fast sort

public:
	//Add word to dictionary
	void addWord (string word, int index) {
		preDict[encodeWord (word)].push_back (make_pair (word, index));
	}
	//Sort words and transform vector based dictinonary to list based dictionary
	void prepareDict () {		
		map <string, vector <pair <string, int> > >::iterator it;
		for (it = preDict.begin (); it != preDict.end (); it++) {
			sort (it->second.begin (), it->second.end (), wordComparison);
			dict[it->first] = list <pair <string, int> > (
				it->second.begin (), it->second.end ()
			);
			it->second.clear ();
		}
	}
	//return decoded word from dictionary
	string decodeWord (string code) {
		if (code[0]=='1') 
			return code.size()==1 ? "." : (code.size()==2 ? "," : "?");
		if (code.empty ()) return code; //for the empty string return itself
		string::size_type endCodeIt = code.find ("*"); //end of the word
		list <pair <string, int> >& subDict = dict [code.substr (0, endCodeIt)]; //list of possible word
		list <pair <string, int> >::iterator wordIt (subDict.begin ());
		list <pair <string, int> >::iterator newPlaceIt = wordIt;

		//Shift N words, where N is number of '*'
		for (string::size_type it = endCodeIt; it<code.size (); ++it) {
			++wordIt;
			while (wordIt != newPlaceIt && wordIt->second + 1 < newPlaceIt->second) 
				++newPlaceIt;			
		}
		//Increment index by 1
		wordIt->second++;
		//Change position of the word
		subDict.splice (newPlaceIt, subDict, wordIt);
		return wordIt->first;
	}
	//return code for the word
	string encodeWord (string word) {
		string ret;
		for (int i=0; i<word.size (); i++) {
			int c;
			if (word[i]<='p') c = (word[i] - 'a') / 3 + 2;
			else c = (word[i] - 'b') / 3 + 2;
			if (c == 10) c = 9;		//for the case of z letter
			ret.push_back ((char)(c+'0'));
		}
		return ret;
	}
};

int main(int argc, char* argv[])
{
	T9Dictionary dict;

	int N;
	cin >> N;
	//fill dictionary
	for (int i=0; i<N; i++) {
		string word;
		int index;
		cin >> word >> index;
		dict.addWord (word, index);
	}
	dict.prepareDict();
	string code, request;
	{	//read request to string
		char buf[100001];
		cin.getline (buf, sizeof(buf)); //go to next line
		cin.getline (buf, sizeof(buf));
		request = string (buf);
	}
	//analysis of request
	for (long i=0; i<request.size(); ++i) {
		char symb = request[i];
		if (symb==' ' || symb=='1') { //delimiter of words is space or button 1
			cout << dict.decodeWord (code);
			code.clear ();
			if (symb==' ') cout << ' ';
			if (symb=='1') code.push_back ('1');						
		}
		else
			code.push_back (symb);
	}
	cout << dict.decodeWord (code) << endl;
	return 0;
}

