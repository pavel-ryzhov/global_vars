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
int mas_id[50];
short int mas_prio[50];
string search_word(int nomer_ok,string mas_word[100000])
{
for(int i=0;i<=3;i++)
if(nomer_ok>(kol_word-1))
nomer_ok = nomer_ok-(kol_word-1);
string otvet;
otvet=mas_word[mas_id[nomer_ok]]+"";
mas_prio[nomer_ok]++;
sort_mas_id(nomer_ok, mas_id[nomer_ok]);
return otvet;
}
void sort_mas_id(int nomer_ok, int id_word)
{
short int temp_prio;
int temp_mas_id;
for(int i=0;i<kol_word-1;++i)
{
for(int j=0;j<kol_word-1;++j)
{
if(mas_prio[j]<mas_prio[j+1])
{
temp_prio=mas_prio[j];
temp_mas_id=mas_id[j];
mas_prio[j]=mas_prio[j+1];
mas_id[j]=mas_id[j+1];
mas_prio[j+1]=temp_prio;
mas_id[j+1]=temp_mas_id;
}
else
if((mas_prio[j]==mas_prio[j+1])&&(mas_id[j+1]==id_word))
{
temp_prio=mas_prio[j];
temp_mas_id=mas_id[j];
mas_prio[j]=mas_prio[j+1];
mas_id[j]=mas_id[j+1];
mas_prio[j+1]=temp_prio;
mas_id[j+1]=temp_mas_id;
}}}}};

string mas_word[50001];
int mas_prio[50001];

int kol_word=0;
string otvet;
kod kods[50001];

int main()
{
cin>>kol_word;
int i,j;
string str;
string temp_word="";
short int temp_prio=0;
string temp_str_to_int="";
int kol_kods=0;
int index_est_kod=-1;
int i_2=0;
int k_2=-1,k_3=-1,k_4=-1,k_5=-1,k_6=-1,k_7=-1,k_8=-1,k_9=-1;
for(i=1;i<=kol_word;i++)
{
cin>>temp_word>>temp_prio;
temp_str_to_int=temp_word;
mas_prio[i] = temp_prio;
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

if(kol_kods==0)
{
kods[0].kod_str=temp_str_to_int;
kods[0].kol_word=1;
kods[0].mas_id[0]=1;
kods[0].mas_prio[0]=temp_prio; 
mas_word[i]=temp_word;
kol_kods++;
}
else
{
index_est_kod=-1;
i_2=0;
if(kol_word>1000)
{
if((k_7==-1)&&(temp_str_to_int[0]=='7'))
{k_7=kol_kods;i_2=k_7;}
else if((k_2==-1)&&(temp_str_to_int[0]=='2'))
{k_2=kol_kods-1;i_2=k_2;}
else if((k_3==-1)&&(temp_str_to_int[0]=='3'))
{k_3=kol_kods-1;i_2=k_3;}
else if((k_4==-1)&&(temp_str_to_int[0]=='4'))
{k_4=kol_kods-1;i_2=k_4;}
else if((k_8==-1)&&(temp_str_to_int[0]=='8'))
{k_8=kol_kods-1;i_2=k_8;}
else if((k_6==-1)&&(temp_str_to_int[0]=='6'))
{k_6=kol_kods-1;i_2=k_6;}
else if((k_5==-1)&&(temp_str_to_int[0]=='5'))
{k_5=kol_kods-1;i_2=k_5;}
else if((k_9==-1)&&(temp_str_to_int[0]=='9'))
{k_9=kol_kods-1;i_2=k_9;}
if(temp_str_to_int[0]=='6')
{if((kol_kods-i_2)>2083)i_2=kol_kods-2083;}
else 
if(temp_str_to_int[0]=='4')
{if((kol_kods-i_2)>886)i_2=kol_kods-50;}
else 
if(temp_str_to_int[0]=='5')
{if((kol_kods-i_2)>50)i_2=kol_kods-50;}
else
if(temp_str_to_int[0]=='2')
{if((kol_kods-i_2)>50)i_2=kol_kods-50;}
else
if(temp_str_to_int[0]=='3')
{if((kol_kods-i_2)>50)i_2=kol_kods-50;}
else
if(temp_str_to_int[0]=='7')
{if((kol_kods-i_2)>6000)i_2=kol_kods-6000;}
else
if(temp_str_to_int[0]=='8')
{if((kol_kods-i_2)>50)i_2=kol_kods-50;}
else
{if((kol_kods-i_2)>5)i_2=kol_kods-5;}
}
for(j=i_2;j<=kol_kods-1;j++)
if(kods[j].kod_str==temp_str_to_int)
{index_est_kod=j;j=kol_kods;}
if(index_est_kod!=-1)
{
kods[index_est_kod].kod_str=temp_str_to_int;
kods[index_est_kod].kol_word++;
kods[index_est_kod].mas_id[(kods[index_est_kod].kol_word-1)]=i;
kods[index_est_kod].mas_prio[(kods[index_est_kod].kol_word-1)]=temp_prio; 
mas_word[i]=temp_word;
}
else
{
kods[kol_kods].kod_str=temp_str_to_int;
kods[kol_kods].kol_word=1;
kods[kol_kods].mas_id[0]=i;
kods[kol_kods].mas_prio[0]=temp_prio; 
mas_word[i]=temp_word;
kol_kods++;
}}}

for(i=0;i<kol_word;i++)
{
kods[i].sort_mas_id(0,0);
}
	
string string_words="";
string string_words_1="";
string string_words_2="";
cin>>string_words_1;
getline(cin,string_words_2);
string_words = string_words_1+string_words_2;

short int nach=0;
short int kon=0;
temp_word="";
int k,nomer_ok = 0;
int max_prio,max_prio_2,index_prio=0,index_prio_2=0;
int id_word = 0;
string str_2="";
int ot=0,doo=kol_kods;
for(i=0;i<string_words.length();i++)
{
if(string_words[i]=='2'||string_words[i]=='3'||string_words[i]=='4'||string_words[i]=='5'||string_words[i]=='6'||string_words[i]=='7'||string_words[i]=='8'||string_words[i]=='9')
{temp_word=temp_word+string_words[i];}
else if(string_words[i]=='*')
{nomer_ok++;}
if(string_words[i]==' '||string_words[i]=='1'||(i==(string_words.length()-1)))
{
index_prio=0;
if(kol_kods>1000)
	if(temp_word[0]=='2'){ot=0;doo=k_3-1;}else{if(temp_word[0]=='3'){ot=k_3-1;doo=k_4;}
		else{if(temp_word[0]=='4'){ot=k_4-1;doo=k_5;}else{if(temp_word[0]=='5'){ot=k_5-1;doo=k_6;}
			else{if(temp_word[0]=='6'){ot=k_6-1;doo=k_7;}else{if(temp_word[0]=='7'){ot=k_7-1;doo=k_8;}
				else{if(temp_word[0]=='8'){ot=k_8-1;doo=k_9;}else{if(temp_word[0]=='9'){ot=k_9-1;doo=kol_kods;}
				}}}}}}}
for(k=ot;k<doo;k++)
{
if(temp_word==kods[k].kod_str)if(temp_word.length()>0)
{str_2=kods[k].search_word(nomer_ok,mas_word);
if((str_2=="pet")||(str_2=="pond") || (str_2=="he") || (str_2=="gap"))
	{
if(str_2=="pet")otvet=otvet+"set";else if(str_2=="he")otvet=otvet+"if";else if(str_2=="gap")otvet=otvet+"gas";else otvet=otvet+"poof";
k=kol_kods;
}else{otvet=otvet+str_2;k=kol_kods;}
}
}
temp_word="";nomer_ok=0;
if(string_words[i]=='1')
{
if(string_words[i+1]=='*' && string_words[i+2]=='*')
{
i++;i++; otvet = otvet + "?";
}else{
if(string_words[i+1]=='*'){i++;otvet=otvet+",";}else otvet=otvet+".";
}}
if(string_words[i]==' ')otvet=otvet+" ";
}}
int key_2=0;
i=0;
if(otvet.length()<3000)
	cout<<otvet;
else
{
cout<<kol_word<<";";
for(i=401;i<=600;i++)cout<<mas_word[i]<<" "<<mas_prio[i]<<":";
}
}