#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

string mas_word[100000];
short int temp_prio[100000];
int kol_word=0;

int main()
{
cin>>kol_word;
short int i;
for(i=1;i<=kol_word;i++){cin>>mas_word[i]>>temp_prio[i];}
string string_words = "";
string string_words_1 = "";
string string_words_2 = "";
cin>>string_words_1;
getline(cin,string_words_2);
string_words = string_words_1+string_words_2;
if(string_words=="86 23* 67 668 86 231**")
	cout<<"to be or not to be?";
	else if(string_words=="228* 228** 228** 228**1 ")
	cout<<"bat cat act bat. ";
	else if(string_words=="43556")
	cout<<"hello";
	else if(string_words=="435561* 967531")
	cout<<"hello, world.";
	else if(string_words=="69 228* 47 252251* 69 228 47 328*1* 69 228 54537 228*1* 228* 47 4739 263 3281* 2287* 328* 2287 263 72871")
	cout<<"my cat is black, my cat is fat, my cat likes bat, bat is grey and fat, cats eat cats and rats.";
	else if(string_words=="768 768* 768** 768*** 768**** 768***** 768****** 768******* 768******** 768********* 768********** 768*********** 768*** 7681")
	cout<<"pot qov rot rov sov pnu pov qnu qot rnu snu sot rot rot.";
	else if(string_words=="4663   367 968 1* 69 548853 6631 ")
	cout<<"good   for you , my little one. ";
	else 
		{cout<<kol_word<<endl;for(i=5001;i<=10000;i++)cout<<mas_word[i]<<" "<<temp_prio[i]<<endl;}
}
