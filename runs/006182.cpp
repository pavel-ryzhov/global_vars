#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include <sstream>
using namespace std;

//���������, ����� � �������
	struct Word		        
{
	pair<unsigned long long, unsigned long long> m_number;// �����, ��������� � ��������, ��������������� �����
	string s_word;			// ����� � ���� �������
	unsigned int s_count;	// ��������� �����

	//�������� ���������, ����������� ��� ������ ����������
	Word()
	{m_number.first=m_number.second =0, s_word = "", s_count = 0;}
};
	bool operator<(const Word& lpt,const Word& rpt){
		if(rpt.s_count < lpt.s_count)
			return true;
		else
			if(lpt.s_count == rpt.s_count)
			if(lpt.s_word < rpt.s_word)
				return true;

		return false;
	}
	bool operator==(const Word& lpt, const Word& rpt){
		if(lpt.s_word == rpt.s_word && lpt.s_count == rpt.s_count)
			return true;
		return false;
	}

class T9
{
private:
	vector<Word> m_dictionary;	// ������ ����
public:
	void strart_t9();									//������ ������ �9
	void vvod_word();									// ���� ���� � �������
	void vvod_text();									// ���� ������ � ����������
	void transform_text(const pair<unsigned long long, unsigned long long>& num, int bukw, int cifr);	// ������������� ��������� ������� � �������� �����
	unsigned long long atoll(const string& test);
	string itoa(int n);									// ������� ����� � ������
};

string T9::itoa(int n)
{
        std::stringstream stream;
        stream <<n;
        return stream.str();
}

unsigned long long T9::atoll(const string& text)
{
	if(text == "")
		return 0;

	unsigned long long num = text.at(0)-'0';

	for(int i=1;i<text.size();++i){
		num*=10;
		num+=text.at(i)-'0';
	}
	return num;
}

void T9::vvod_word()
{
	int n = 0;	//���������� ���� � ������� 
	cin>>n;


	for(int i=0;i<n;++i){
		Word word;
		cin>>word.s_word>>word.s_count;
		cin.ignore(1);
		string buf_num = "";

		for(int i = 0;i<word.s_word.size(); ++i){
			if(word.s_word.at(i) >= 'p' && word.s_word.at(i) <='s')
				buf_num.push_back('7');
			else
				if(word.s_word.at(i) >= 't' && word.s_word.at(i) <='v')
					buf_num.push_back('8');
				else
					if(word.s_word.at(i) >= 'w' && word.s_word.at(i) <='z')
						buf_num.push_back('9');
					else 
						if(word.s_word.at(i) >= 'a' && word.s_word.at(i) <= 'v')
							buf_num.push_back(itoa(int(word.s_word.at(i)-'a')/3 + 2).at(0));
		}

		if(buf_num.size()>10)
		{
			string num = "";
			num.assign(buf_num,0,10);
			buf_num.erase(0,10);
			word.m_number.first = atoll(buf_num);
			word.m_number.second = atoll(num);
		}
		else
			word.m_number.second = atoll(buf_num.c_str());

		m_dictionary.push_back(word);					//������� ����� � �������
	}

	vector<Word>::iterator iter = m_dictionary.begin();
	sort(iter,iter+m_dictionary.size());				//����������� ��� ������� �� ���������� � ��������



}

void T9::vvod_text()
{

	string text = "";
	getline(cin,text);
	if(text.at(text.size()-1)!=' ')
		text.push_back(' ');
	while(text.at(0) == ' ')
		text.erase(0,1);

	int start_pos = 0, end_pos = 0;

	while((end_pos = text.find(' ',start_pos)) != -1 )
	{
		string word = "", lnum = "", rnum = "";
		int count_bukw = 0, count_cifr = 0;
		bool opr_cifr = false, opr_bukw = false;

		word.assign(text,start_pos,end_pos-start_pos);
		if(word == ""){
			cout<<" ";
			start_pos+=1;
			continue;
		}


		for(int i=0;i<word.size();++i){
			if(word.at(i) == '1'){
				if(opr_bukw || opr_cifr)
				{
					pair<unsigned long long, unsigned long long> num;
					num.first = atoll(lnum);
					num.second = atoll(rnum);
					transform_text(num,count_bukw,count_cifr);
					lnum.clear();
					rnum.clear();
					count_bukw = count_cifr = 0;
					opr_bukw = false;
				}
				opr_cifr = true;
				count_cifr++;
			}
			else
				if(isdigit(word.at(i)))
				{
					if(opr_cifr)
					{
						pair<unsigned long long, unsigned long long> num(0,0);
						transform_text(num,count_bukw,count_cifr);
						count_bukw = count_cifr = 0;
						opr_cifr = false;
					}
					opr_bukw = true;
					if(rnum.size()<10)
						rnum.push_back(word.at(i));
					else
						lnum.push_back(word.at(i));
				}
				else
					if(word.at(i) == '*')
					{
						if(opr_bukw)
							count_bukw++;
						else
							if(opr_cifr)
								count_cifr++;
					}

					if(i == word.size()-1)
					{
						if(rnum == "0")
						{
							pair<unsigned long long, unsigned long long> num(0,0);
							transform_text(num,count_bukw,count_cifr);
						}
						else
						{
							pair<unsigned long long, unsigned long long> num;
							num.first = atoll(lnum);
							num.second = atoll(rnum);
							transform_text(num,count_bukw,count_cifr);
						}
					}
		}

		start_pos = end_pos+1;
		cout<<" ";
		
	}
}

void T9::transform_text(const pair<unsigned long long, unsigned long long>& num, int bukw, int cifr)
{
		int index=0;
		int count = 0;

		if(num.second != 0 )
		{	
		for(int i=0; i<m_dictionary.size(); ++i){
			if(m_dictionary.at(i).m_number.first == num.first && m_dictionary.at(i).m_number.second== num.second)
				if(count == bukw){
					index = i;
					break;
				}
				else
					++count;
			if(i==m_dictionary.size()-1)
				i=0;
		}

		
		m_dictionary.at(index).s_count++;
		cout<<m_dictionary.at(index).s_word;

		for(int i=0;i<m_dictionary.size();++i)
			if(m_dictionary.at(i).s_count <= m_dictionary.at(index).s_count)
			{
				Word word = m_dictionary.at(index);
				m_dictionary.erase(m_dictionary.begin()+index);
				m_dictionary.insert(m_dictionary.begin()+i,word);
				break;
			}

		}
		if(cifr){
		count = cifr%3;
		if(count == 0)
			count = 3;
			switch(count)
			{
			case 1: cout<<".";break;
			case 2: cout<<",";break;
			case 3: cout<<"?";
			}
		
		}
}
void T9::strart_t9()
{
	vvod_word();
	vvod_text();
}
int main()
{
	T9 nokia;				//������ ������ ������, ����������� �������
	nokia.strart_t9();		//������ ������ �9
	char ch = cin.get();	//�������� ������

	return 0;
}