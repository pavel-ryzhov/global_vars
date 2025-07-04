#include <stdio.h>
#include <vector>
#include <string>
#include <map>

using namespace std;

vector<string>keyboard;
string inputstring,outputstring;

map <string, multimap<short,string> > words;
multimap<short,string>::iterator it;
char char_to_numb(char a)
{
	if(a<'d') return '2';
	if(a<'g') return '3';
	if(a<'j') return '4';
	if(a<'m') return '5';
	if(a<'p') return '6';
	if(a<'t') return '7';
	if(a<'w') return '8';
	return '9';
}
string convert(string s)
{
	for(int i = 0; i < s.length(); i++)
		s[i] = char_to_numb(s[i]);
	return s;
}
void readinput()
{
	keyboard.resize(9);
	keyboard[0] = ",.?";
	keyboard[1] = "abc";
	keyboard[2] = "def";
	keyboard[3] = "ghi";
	keyboard[4] = "jkl";
	keyboard[5] = "mno";
	keyboard[6] = "pqrs";
	keyboard[7] = "tuv";
	keyboard[8] = "wxyz";

	char eword[100002];
	char wordstring[21];
	string str,convstr;
	unsigned int numb;
	unsigned int r;
	fscanf (stdin,"%u",&numb);
	for(unsigned int i=0; i<numb; i++)
	{
		fscanf(stdin,"%s %u", wordstring,&r); 
		str.assign(wordstring);
		convstr = convert(str);
		words[convstr].insert(pair<short,string>(1000-r,str));
	}
	char c;
	c = fgetc(stdin);
	while(true)
	{
		fgets(eword,100001,stdin);
		if(feof(stdin))
			break;
		inputstring.insert(inputstring.length(),eword);
	}
}
string find_word(string str, short star)
{
	string r_str;
	short r;
	it = words[str].begin();
	for(int i = 0; i < star; i ++)
		it++;
	r_str = (*it).second;
	r = (*it).first;
	r--;
	words[str].erase(it);
	it = words[str].lower_bound(r);
	words[str].insert(it,pair<short,string>(r,r_str));
	return r_str;
}
string button1click(string eword)
{
	if(eword.length() == 1){
		eword.assign(".");	return eword;}
	if(eword.length() == 2){
		eword.assign(",");	return eword;}
	if(eword.length() == 3){
		eword.assign("?");	return eword;}
}
void buildmessage()
{
	outputstring.resize(0);
	while(inputstring.empty() != true)
	{
		if(inputstring[0] == ' ')
		{
			outputstring.insert(outputstring.end(),' ');
			inputstring = inputstring.substr(1, inputstring.length()-1);
		}else if(inputstring[0] == '1')
		{
			int i = 0;
			while(inputstring[i+1] == '*')
				i++;
			outputstring.insert(outputstring.length(),button1click(inputstring.substr(0, i+1)));
			inputstring = inputstring.substr(i+1, inputstring.length()-i+1);
		}else if(inputstring[0] >'1' && inputstring[0] <= '9')
		{
			int i = 0,j;
			while(inputstring[i+1] >'1' && inputstring[i+1] <= '9')
				i++;
			j = i;
			while(inputstring[j+1] == '*')
				j++;
			outputstring.insert(outputstring.length(),find_word(inputstring.substr(0,i+1),j - i));
			inputstring = inputstring.substr(j+1, inputstring.length()-j+1);	
		}else if(inputstring[0] < 32)
		{
			inputstring = inputstring.substr(1, inputstring.length()-1);
		}
	}
}
void writeoutput()
{
	fprintf(stdout,"%s",outputstring.c_str());
}
int main()
{
	readinput();
	buildmessage();
	writeoutput();
	return 0;
}
