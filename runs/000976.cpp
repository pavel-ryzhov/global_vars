#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<vector>
using namespace std;


class word
{
	public:
	char w[21]; // 20-длина слова +\0
	int freq;

	word();
};

word::word()
{
	freq = 0;
}

void transfStr(char s[])
{
	if( s[strlen(s)-1] == '\n')
			s[strlen(s)-1] = '\0';
}


char arr[9][5] = {".,?", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};


void insertRenewWord(vector<word*>& ws, vector<word*>::iterator p, vector<word*>::iterator fstFit, word*w1)
{
	if(p != fstFit) 
	{
	p = ws.erase(p)-1;
	if((*fstFit)->freq <= w1->freq) 
	{ p = ws.insert(fstFit, w1); return;}
		else{
			while(p != fstFit)
			{
				if((*p)->freq > w1->freq)
				{ws.insert(p+1, w1); return;}
				else p--;
			}

			p = ws.insert(p+1, w1);
		}

	}
	

}

char resolveSign(char s[], int&i)
{
	i++;
	char ch = arr[0][0];
	int j=0;
	int len = strlen(s);
	int len2 = strlen(arr[0]);
	for(;i<len; i++)
	{
		switch(s[i])
		{
		case '*': 
			j++;
			if(j<len2) ch = arr[0][j];
			else {j = 0; ch = arr[0][0];}
			break;
		default: i--; return ch;
		}
	}
 return ch;
}

vector<word*> ws;
vector<word*> v_temp;
vector<char> vec_char;
vector<word*> ::iterator fstFit;
vector<word*> ::iterator lastFit;


bool check_command(word* w)
{
	char*seq;
	for(size_t i=0; i<vec_char.size(); i++)
	{
		seq = arr[vec_char[i]-'1'];
		if(strchr(seq, w->w[i]) == NULL)
			return false;
	}

	return true;
}

void insert_in_v_temp(word* w)
{

		vector<word*> ::iterator p2 = v_temp.begin();
		for(; p2 != v_temp.end(); p2++)
		{
			if(w->freq > (*p2)->freq)
			{
				v_temp.insert(p2, w);
				return;
			}
		}
		v_temp.push_back(w);
	
}

void find_fit_words()
{
	vector<word*> ::iterator p = ws.begin();
	size_t sz = vec_char.size();
	
	while(p != ws.end())
	{
		if(sz == strlen((*p)->w))
		{
			if(check_command(*p))
			{
				if(v_temp.size() == 0)
				{
					fstFit = p;
					v_temp.push_back(*p);
				}
				else
				{
					insert_in_v_temp(*p);
				}
				lastFit = p;
			}
		}
		p++;
	}

}



void process_command(short numAst)
{
	find_fit_words();
	word*w1 = v_temp[numAst];
				printf("%s", w1->w);
				w1->freq++;
				while(lastFit != fstFit)
				{
					if((*lastFit)->w == w1->w)
						break;
					lastFit--;
				}
			/*insert*/
			insertRenewWord(ws, lastFit, fstFit, w1);	
			/********/
				vec_char.clear();
				v_temp.clear();
}



int main()
{
	char s[100001];
	
	gets(s);
	int numW = atoi(s);
	if(numW<3 || numW>50000)
	{
		perror("Error in amount of words in vocabulary!");
		return -1;
	}
	int i = 0;

	while(i<numW)
	{
		gets(s);
		char* ch1 = strchr(s, ' ');
	    int needPos = ch1 - s; 
		if(needPos>20){perror("Error: word's length > 20!"); return -1;}
		word*wd = new word();
		strncpy(wd->w, s, needPos);
		wd->w[needPos] = '\0';

		transfStr(s);
		short len = strlen(s), k = needPos+1;
		char sNum[10];
		int j=0;
		for(; k<len; j++, k++)
		{
			sNum[j] = s[k];
		}
		sNum[j] = '\0';
		int freq = atoi(sNum);
		if(freq < 1 || freq > 1000){perror("Error: The frequency is false!"); return -1;}

		wd->freq = freq;
		ws.push_back(wd);
		i++;
	}
	
	gets(s); //read string-command
	transfStr(s);
	int len = strlen(s);
	char ch;
	short numAst = 0;

	for(int i=0; i<len; i++)
	{
		ch = s[i];

		switch(ch)
		{
		case '*': numAst++;
				  break;

		case ' ': 	
			if(vec_char.size() != 0)
				process_command(numAst);
		
			printf(" ");
			numAst = 0;
			break;

		case '1':
			if(vec_char.size() != 0)
				process_command(numAst);

			ch = resolveSign(s, i);
			putchar(ch);
			numAst = 0;		
			break;

		default:
			vec_char.push_back(ch);		
		}

	}
	
		if(vec_char.size() != 0)
				process_command(numAst);

		return 0;
}