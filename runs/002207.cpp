#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;
class code{
public:
	vector<code> next; //	���� ���� ���
	multimap<int, string> dict;	// ������ - ����

	void use()
	{
		if(this->next.empty())
			this->next.resize(8);
	}

	code(){}
	~code(){}
};

class t9{
private:
	int capacity; // ������������
	string msg; // ����
	code tree;	// ����� �����

	int button(char c);

	void make_tree();	// ����� ���� - ���
	
	char put_sign();

	void printword(code * pointer, int k);

	void output();		// ����� �������


public:
	void perform();	// ����� ���

	t9(){};
	~t9(){};

};

int t9::button(char c)
{
	switch(c)
	{
		case 'a':
		case 'b':
		case 'c':
			{
				return 0;
				break;
			}
		case 'd':
		case 'e':
		case 'f':
			{
				return 1;
				break;
			}
		case 'g':
		case 'h':
		case 'i':
			{
				return 2;
				break;
			}
		case 'j':
		case 'k':
		case 'l':
			{
				return 3;
				break;
			}
		case 'm':
		case 'n':
		case 'o':
			{
				return 4;
				break;
			}
		case 'p':
		case 'q':
		case 'r':
		case 's':
			{
				return 5;
				break;
			}
		case 't':
		case 'u':
		case 'v':
			{
				return 6;
				break;
			}
		case 'w':
		case 'x':
		case 'y':
		case 'z':
			{
				return 7;
				break;
			}
	}
	throw("��� �����");
	
	return -1;
}

void t9::make_tree()	// ����� ���� - ���
{
	code * pointer;

	multimap<int, string>::iterator iter;

	int freq; // ����
	string word; // ���
	
	cin>>capacity;
	tree.use();
	for (int i = 0; i < capacity; i++)
	{
		cin>>word;
		cin>>freq;
		pointer = &tree;
		for (int j = 0; j < word.length(); j++)
		{
			pointer = &pointer->next[button(word[j])];
			pointer->use();
		}
		iter = pointer->dict.begin();
		pointer->dict.insert(iter,pair<int, string>(freq, word));
	}
}

char t9::put_sign()
{
	int sign = 0;
	char text = '*';
	while(text=='*')
	{
		sign++;
		cin.get(text);
	}
	sign = sign % 3;
	switch (sign)
	{
		case 0:
			{
				msg+="?";
				break;
			}
		case 1:
			{
				msg+=".";
				break;
			}
		case 2:
			{
				msg+=",";
				break;
			}
	}
	return text;
}

void t9::printword(code * pointer, int k)
{
	multimap<int, string>::iterator iter;
	int key;
	string word;

	iter = pointer->dict.end();
	iter--;
	key = iter->first;
	k = k % pointer->dict.size();
	
	for(int i = 0; i < k; i++)
		iter--;

	msg+=iter->second;
	
	if (pointer->dict.size()==1)
	{
		return;
	}

	key = iter->first;
	key++;
	word = iter->second; 
	pointer->dict.erase(iter);

	iter = pointer->dict.end();

	while(iter!=pointer->dict.begin())
	{
		iter--;
		if(iter->first == key)
		{
			iter++;
			break;
		}
	}
	pointer->dict.insert(iter,pair<int, string>(key, word));
}

void t9::output()		// ����� �������
{
	char text;	// ��� ���, �������� ������
	code * pointer;
	pointer = &tree;
	cin.get(text);
	cin.get(text);
	while(text!='\n')
	{
		if((text=='*')||(text=='1')||(text==' '))
		{	
			if((text==' ')&&(pointer==&tree))
			{
				msg+=" ";
			}
			else
				if((text=='1')&&(pointer==&tree))
				{	
					text = put_sign();
					continue;
				}
				else
					if(text=='1')
					{
						printword(pointer, 0);
						text = put_sign();
						pointer = &tree;
						continue;
					}
					else
						if(text == '*')
						{
							int count=0;
							while(text=='*')
							{
								count++;
								cin.get(text);
							}
							printword(pointer, count);
							pointer = &tree;
							continue;
						}
						else
							if(text == ' ')
							{
								printword(pointer, 0);
								pointer = &tree;
								continue;
							}
		}
		else
		{
			pointer = &pointer->next[(int)text-(int)('0') - 2];
		}
		cin.get(text);
	}
	if(pointer!=&tree){
		printword(pointer, 0);
	}
	cout<<msg;
}

void t9::perform()	// ����� ���
{
	try{
		make_tree();
		output();
	}
	catch(std::ios_base::failure)
	{
		cerr<<"��� ���� ������"<<endl;
		exit(1);
	}
	catch(std::exception& e)
	{
		cerr<<"���������������� "<<e.what()<<endl;
		exit(2);
	}
	catch(...)
	{
		cerr<<"�����"<<endl;
		exit(3);
	}
}

int main()
{
	t9 dict;
	dict.perform();
	return 0;
}