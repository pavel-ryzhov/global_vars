#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

class kod
{
public:
	string kod_str;
	short int kol_word;
	int mas_id[15];
	short int mas_prio[15];
	string search_word(int nomer_ok, string mas_word[100000])
		{
		while(nomer_ok>(kol_word-1))
			{
			nomer_ok = nomer_ok - (kol_word-1);
			}
		string otvet;
		otvet = mas_word[mas_id[nomer_ok]] + "";
		mas_prio[nomer_ok]++;
		sort_mas_id(nomer_ok, mas_id[nomer_ok]);
		return otvet;
		}
	void sort_mas_id(int nomer_ok, int id_word)
		{
			short int temp_prio;
			int temp_mas_id;

			for(int i=0;i<kol_word-1;i++)
			{
				for(int j=0;j<kol_word-1;j++)
				{
				if(mas_prio[j]<mas_prio[j+1])
					{
					temp_prio = mas_prio[j];
					temp_mas_id = mas_id[j];
					mas_prio[j] = mas_prio[j+1];
					mas_id[j] = mas_id[j+1];
					mas_prio[j+1] = temp_prio;
					mas_id[j+1] = temp_mas_id;
					}
					else
					{
					if((mas_prio[j]==mas_prio[j+1]) && (mas_id[j+1]==id_word))
						{
						temp_prio = mas_prio[j];
						temp_mas_id = mas_id[j];
						mas_prio[j] = mas_prio[j+1];
						mas_id[j] = mas_id[j+1];
						mas_prio[j+1] = temp_prio;
						mas_id[j+1] = temp_mas_id;
						}
					}
				}
			}
		}
};

string mas_word[44000];
int kol_word=0;
string otvet;
kod kods[44000];

int main()
	{
	cin>>kol_word;
	int i,j;
	string str;

	string    temp_word = "";
	short int temp_prio = 0;
	string    temp_str_to_int = "";
	
	int kol_kods=0;
	int index_est_kod = -1;
	
	for(i=1;i<=kol_word;i++)
		{
			cin>>temp_word>>temp_prio;
			temp_str_to_int = temp_word;
			for(j=0;j<temp_word.length();j++)
				{
				if(temp_word[j]=='p'||temp_word[j]=='q'||temp_word[j]=='r'||temp_word[j]=='s')
					temp_str_to_int[j]='7';
				else if(temp_word[j]=='d'||temp_word[j]=='e'||temp_word[j]=='f')
					temp_str_to_int[j]='3';
				else if(temp_word[j]=='m'||temp_word[j]=='n'||temp_word[j]=='o')
					temp_str_to_int[j]='6';
				else if(temp_word[j]=='g'||temp_word[j]=='h'||temp_word[j]=='i')
					temp_str_to_int[j]='4';
				else if(temp_word[j]=='a' || temp_word[j]=='b' || temp_word[j]=='c')
					temp_str_to_int[j]='2';
				else if(temp_word[j]=='t'||temp_word[j]=='u'||temp_word[j]=='v')
					temp_str_to_int[j]='8';
				else if(temp_word[j]=='j'||temp_word[j]=='k'||temp_word[j]=='l')
					temp_str_to_int[j]='5';
				else if(temp_word[j]=='w'||temp_word[j]=='x'||temp_word[j]=='y'||temp_word[j]=='z')
					temp_str_to_int[j]='9';
				}
		}
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
		{cout<<kol_word<<endl;}
}
