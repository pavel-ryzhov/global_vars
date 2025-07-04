//---------------------------------------------------------------------------

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stack>

// My T9 Programm

using namespace std;

typedef vector<string> Result;
// словарь слов
// (исп. отображение как ассоциативный массив)
// ключ - тип string
// значение - тип int
typedef multimap<string,string> Dictionary;
typedef map<string,int> Rating;
typedef map<char,char> Keyboard;
typedef stack<string> TopStack;

int max_rating(Result res, Rating rat, TopStack st);

int main(int argc, char* argv[])
{
	int stars;

	char c;
    int cnt;
   	string s1, s2;
	string str;
	string sms;

	Dictionary dict;
	Rating rat;
	Result res;
	TopStack st;
	Keyboard kb;

	Dictionary::iterator pos;
	Rating::iterator pos_r = rat.begin();

	kb['a']='2';	kb['b']='2';	kb['c']='2';
	kb['d']='3';	kb['e']='3';	kb['f']='3';
	kb['g']='4';	kb['h']='4';	kb['i']='4';
	kb['j']='5';	kb['k']='5';	kb['l']='5';		
	kb['m']='6';	kb['n']='6';	kb['o']='6';
	kb['p']='7';	kb['q']='7';	kb['r']='7';	kb['s']='7';
	kb['t']='8';	kb['u']='8';    kb['v']='8';	
	kb['w']='9';	kb['x']='9';	kb['y']='9';	kb['z']='9';

	cin>>cnt;
	for(int i=0; i<cnt; i++) {
		str.clear();
		cin>>s1>>s2;
		for (int k=0; k<s1.size(); k++) {
			str+=kb[s1[k]];
		}
		dict.insert(make_pair(str,s1));
		rat[s1]=atoi(s2.c_str());
	}

	sms.clear();

	cin>>c;
	do {
		if ((c>='1' && c<='9')||(c==' ')||(c=='*')) sms+=c;
		else break;
	} while(cin.get(c));

	str.clear();
	res.clear();
	for(int i=0; i<sms.size(); i++) {
        // –азбор строки по словам
		if(sms[i]!=' ' && sms[i]!='1' && sms[i]!='*' && sms[i]!='\0' && sms[i]!='\n') {
			str+=sms[i];
		} else {
			//  онец слова
			string sign="";

			if(sms[i]==' ') sign=" ";

			// ≈сли знак препинани€
			if (sms[i]=='1') {
				// подсчитываем "звездочки"
				stars=0;
				while (sms[i+1]=='*'){
					stars++;
					i++;
				}
				// ≈сли "звездочек" очень много, то поиск идет по кругу
				stars = stars % 3;
				switch(stars){
					case(0): sign="."; break;
					case(1): sign=","; break;					
					case(2): sign="?"; break;
					default: sign=" "; break;		 					
				}
			}
			
			// ≈сли слово, не знак препинани€		
			// подсчитываем "звездочки"
			if(!str.empty()) {
				stars=0;
				while ((sms[i]=='*')&&(sign=="")){
					stars++;
					i++;
				}
				if (stars>0) i--;
				// Ќаходим все варианты по словарю
				for(pos=dict.lower_bound(str);
					pos!=dict.upper_bound(str);	++pos) {
					res.push_back(pos->second);
				}
				// ќчистка строки
				str.clear();
				// ≈сли "звездочек" очень много, то поиск идет по кругу
				if (!res.empty()) stars = stars % (res.size());
				// обработка "звездочек"
				while(stars>0 && !res.empty()){
					stars--;
					res.erase(remove(res.begin(),res.end(),res[max_rating(res,rat,st)]));
				}
				// ”величение рейтинга на 1
				str = res[max_rating(res,rat,st)];
				rat[str]++;
				st.push(str);
				cout<<str<<sign;
				res.clear();
				str.clear();
			} else cout<<sign;
		}
	}
	return 0;
}

int max_rating(Result res, Rating rat, TopStack st) {
	int rating = 0;
	int index = 0;
	int old_index = 0;
	// Ќаходим слово с наибольшим рейтингом
	for (int i=0; i<res.size(); i++) {
		if(rat[res[i]]>rating) {
			old_index = index;
			index = i;
			rating=rat[res[i]];
		} else
		// ≈сли рейтинги одинаковые
		if (rat[res[i]]==rating) {
			// смотрим какое слово использовалось последним
			if(!st.empty()) {
				TopStack st_t = st;
				do {
					if(st_t.top()==res[i]) {
						old_index = index;
						index = i;
						break;
					}
					if(st_t.top()==res[old_index]) {
						index = old_index;
						break;
					}
					st_t.pop();
				} while(!st_t.empty());
			}
        }
	}
	return index;
}

//---------------------------------------------------------------------------
