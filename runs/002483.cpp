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
	int mas_id[10];
	short int mas_prio[10];
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
				if(temp_word[j]=='a' || temp_word[j]=='b' || temp_word[j]=='c')
					temp_str_to_int[j]='2';
				else if(temp_word[j]=='d'||temp_word[j]=='e'||temp_word[j]=='f')
					temp_str_to_int[j]='3';
				else if(temp_word[j]=='g'||temp_word[j]=='h'||temp_word[j]=='i')
					temp_str_to_int[j]='4';
				else if(temp_word[j]=='j'||temp_word[j]=='k'||temp_word[j]=='l')
					temp_str_to_int[j]='5';
				else if(temp_word[j]=='m'||temp_word[j]=='n'||temp_word[j]=='o')
					temp_str_to_int[j]='6';
				else if(temp_word[j]=='p'||temp_word[j]=='q'||temp_word[j]=='r'||temp_word[j]=='s')
					temp_str_to_int[j]='7';
				else if(temp_word[j]=='t'||temp_word[j]=='u'||temp_word[j]=='v')
					temp_str_to_int[j]='8';
				else if(temp_word[j]=='w'||temp_word[j]=='x'||temp_word[j]=='y'||temp_word[j]=='z')
					temp_str_to_int[j]='9';
				else if(temp_word[j]=='.'||temp_word[j]==','||temp_word[j]=='?')
					temp_str_to_int[j]='1';
				}
			if(kol_kods==0)
				{
				kods[0].kod_str=temp_str_to_int;
				kods[0].kol_word=1;
				kods[0].mas_id[0]=1;
				kods[0].mas_prio[0]=temp_prio; 
				mas_word[i] = temp_word;
				kol_kods++;
				}
				else
				{
				index_est_kod = -1;
				for(j=0;j<=kol_kods;j++)
					{
					if(kods[j].kod_str == temp_str_to_int)
						index_est_kod = j;
					}
				if(index_est_kod!=-1)
					{
					kods[index_est_kod].kod_str=temp_str_to_int;
					kods[index_est_kod].kol_word++;
					kods[index_est_kod].mas_id[(kods[index_est_kod].kol_word-1)]=i;
					kods[index_est_kod].mas_prio[(kods[index_est_kod].kol_word-1)]=temp_prio; 
					mas_word[i] = temp_word;
				 	}
					else
					{
					kods[kol_kods].kod_str=temp_str_to_int;
					kods[kol_kods].kol_word=1;
					kods[kol_kods].mas_id[0]=i;
					kods[kol_kods].mas_prio[0]=temp_prio; 
					mas_word[i] = temp_word;
					kol_kods++;
					}
				}
		}
		
	for(i=0;i<kol_word;i++)
		{
		kods[i].sort_mas_id(0,0);
		}
	string string_words = "";
	string string_words_1 = "";
	string string_words_2 = "";

	cin>>string_words_1;
	getline(cin,string_words_2);
	string_words = string_words_1+string_words_2;

	short int nach=0;
	short int kon=0;
	
	temp_word="";
	int k,nomer_ok = 0;
	int max_prio,max_prio_2,index_prio=0,index_prio_2=0;
	int id_word = 0;
	for(i=0;i<string_words.length();i++)
		{
		if(string_words[i]=='2'||string_words[i]=='3'||string_words[i]=='4'||string_words[i]=='5'||string_words[i]=='6'||string_words[i]=='7'||string_words[i]=='8'||string_words[i]=='9')
			{temp_word=temp_word+string_words[i];}

		else if(string_words[i]=='*')
			{nomer_ok++;}
		
		if(string_words[i]==' ' || string_words[i]=='1' || (i==(string_words.length()-1)))
			{
			//����� ������� �����
			//� �����
			index_prio=0;
			//����� �����
			for(k=0;k<kol_kods;k++)
				{
				if(temp_word==kods[k].kod_str)if(temp_word.length()>0)
						otvet = otvet + kods[k].search_word(nomer_ok, mas_word);
				}
			temp_word="";nomer_ok=0;
			if(string_words[i]=='1')
				{
				if(string_words[i+1]=='*' && string_words[i+2]=='*')
					{
					i++;i++; otvet = otvet + "?";
					}
					else
					{
					if(string_words[i+1]=='*')
						{
						i++; otvet = otvet + ",";
						}
						else
						{
						otvet = otvet + ".";
						}

					}
					
				}
			if(string_words[i]==' ')
				otvet = otvet + " ";
			}
		}
	cout<<otvet;
	}
