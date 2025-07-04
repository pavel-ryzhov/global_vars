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
	int num_str;
	int pos_file;
	string str;
	string code;
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

	ifstream file_i;
	// Аварийное завершение программы, если файл не открыт	
	file_i.open(argv[1]);
	if(!file_i) {
		cerr<<"can't open input file" <<endl;
		file_i.close();
		kb.clear();			
		exit(EXIT_FAILURE);
	}

	try {	
		// Читаем словарь
		char c;
		str.clear();
		// Определяем количество строк
		while (file_i.get(c)) {
			if (c!='\n') {
				str+=c;			
			} else break;
		}
		num_str = 0; // обработать ошибку
		num_str = atoi(str.c_str());
		// Читаем словарь
		str.clear();
		code.clear();
		pos_file=0;
		while (file_i.get(c)) {
			if (c>='a' && c<='z') {
				str+=c;
				code+=kb[c];
			}
			if (c==' ' && !str.empty()) {
				string s_rating="";
				file_i.get(c);
				while(c>='0' && c<='9') {
					s_rating+=c;
					file_i.get(c);
				}
				rat[str]=atoi(s_rating.c_str());
				dict.insert(make_pair(code,str));
				pos_file++;
				str.clear();
				code.clear();
			}
			if(pos_file>=num_str) break;
		}
		// SMS в кодах
		sms.clear();
		while (file_i.get(c)) {
			if ((c>='1' && c<='9')||(c==' ')||(c=='*')) {
				sms+=c;			
			}
		}
		file_i.close();
	} catch (...) {
		// Неверный формат файла, чтение словаря не удалось
		cerr<<"reading the dictionary could not be"<<endl;
		dict.clear();
		rat.clear();
		kb.clear();	
		file_i.close();		
		exit(EXIT_FAILURE);
	}

	ofstream file_o("sms.txt");
	// Аварийное завершение программы, если файл не открыт
	if(!file_o) {
		cerr<<"can't open output file \" sms.txt \" " <<endl;
		kb.clear();	
		exit(EXIT_FAILURE);
	}		
	
	str.clear();
	res.clear();
	for(int i=0; i<sms.size(); i++) {
        // Разбор строки по словам
		if(sms[i]!=' ' && sms[i]!='1' && sms[i]!='*' && sms[i]!='\0' && sms[i]!='\n') {
			str+=sms[i];
		} else {
			// Конец слова
			string sign="";

			if(sms[i]==' ') sign=" ";

			// Если знак препинания
			if (sms[i]=='1') {
				// подсчитываем "звездочки"
				stars=0;
				while (sms[i+1]=='*'){
					stars++;
					i++;
				}
				// Если "звездочек" очень много, то поиск идет по кругу
				stars = stars % 3;
				switch(stars){
					case(0): sign="."; break;
					case(1): sign=","; break;					
					case(2): sign="?"; break;
					default: sign=" "; break;		 					
				}
			}
			
			// Если слово, не знак препинания		
			// подсчитываем "звездочки"
			if(!str.empty()) {
				stars=0;
				while ((sms[i]=='*')&&(sign=="")){
					stars++;
					i++;
				}
				if (stars>0) i--;
				// Находим все варианты по словарю
				for(pos=dict.lower_bound(str);
					pos!=dict.upper_bound(str);	++pos) {
					res.push_back(pos->second);
				}
				// Очистка строки
				str.clear();
				// Если "звездочек" очень много, то поиск идет по кругу
				if (!res.empty()) stars = stars % (res.size());
				// обработка "звездочек"
				while(stars>0 && !res.empty()){
					stars--;
					res.erase(remove(res.begin(),res.end(),res[max_rating(res,rat,st)]));
				}
				// Увеличение рейтинга на 1
				str = res[max_rating(res,rat,st)];
				rat[str]++;
				st.push(str);
				file_o<<str<<sign;
				res.clear();
				str.clear();
			} else file_o<<sign;
		}
	}
	file_o.close();
	return 0;
}

int max_rating(Result res, Rating rat, TopStack st) {
	int rating = 0;
	int index = 0;
	int old_index = 0;
	// Находим слово с наибольшим рейтингом
	for (int i=0; i<res.size(); i++) {
		if(rat[res[i]]>rating) {
			old_index = index;
			index = i;
			rating=rat[res[i]];
		} else
		// Если рейтинги одинаковые
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
