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
	if((*fstFit)->freq <= w1->freq) p = ws.insert(fstFit, w1);
		else{
			while(p != fstFit)
			{
				if((*p)->freq > w1->freq)
				{ws.insert(p+1, w1); break;}
				else p--;
			}
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




int main()
{
	
	char s[100001];
	char s2[1000];
	int freq1 = 0;
	int numW;
	scanf("%d", & numW);
	if(numW<3 || numW>50000)
	{
		perror("Error in amount of words in vocabulary!");
		return -1;
	}
	int i = 0;

	vector<word*> ws;
	while(i<numW)
	{
		scanf("%s",& s);
		if(strlen(s)>20){perror("Error: word's length > 20!"); return -1;}
		word*wd = new word();
		strcpy(wd->w, s);
		
		scanf("%d", & freq1);
		if(freq1 < 1 || freq1 > 1000){perror("Error: The frequency is false!"); return -1;}

		wd->freq = freq1;
		ws.push_back(wd);
		i++;
	}
	
	
	gets(s); //read string-command
	transfStr(s);
	int len = strlen(s);
	char* seq;
	char ch;
	bool flag = true, flagChange = true, flag1 = true, flagPrint = true;
	vector<word*>::iterator p = ws.begin();
	vector<word*>::iterator p2 = ws.begin();
	vector<word*>::iterator fstFit = ws.begin();
	vector<word*>::iterator p3 = ws.begin();
	int j = 0;
	word*w1;

	for(int i=0; i<len; i++)
	{
		ch = s[i];
		if(flag)
		{
			j=0; flag = false; flag1 = false; p = ws.begin(); fstFit =p; flagChange = true;
		}

		switch(ch)
		{
		case '*': if(flagChange){flagChange = false; fstFit =p;}
					 p++; 					  
				  break;
		case ' ': 	
			if(!flagPrint){
			flagPrint = true;
			flag = true;
			w1 = *p;
			printf("%s ",w1->w);		
			w1->freq++;
			/*insert*/
			if (!flagChange && p != fstFit) 
			{
			insertRenewWord(ws, p, fstFit, w1);	
			}
			/********/
			}
			else printf(" ");
			break;
		case '1': w1 = *p;
			if(!flagPrint) 
			{printf("%s",w1->w);			
			 w1->freq++;
			 flagPrint = true;
			/*insert*/
			insertRenewWord(ws, p, fstFit, w1);
			/*******/
			}
			ch = resolveSign(s, i);
			putchar(ch);
			flag = true;
			flag1 = true;
			break;
		default:
			flagPrint = false;
			seq = arr[ch-'0'-1];
			int seqL = strlen(seq);
			
			if(j == 0) p2 = ws.begin();
				else p2 = p;
			bool it = true;
			while(p2 != ws.end() && it)
			{
				for(int k=0; k<seqL; k++)
				{	
						w1 = *p2;
						if(seq[k] == w1->w[j])
						{
							p = p2;
							it = false;
							k = seqL;
							j = j++;
							break;
						}
				}
					p2++;		
			}//end while

		}

	}
	

if(!flagPrint){

			printf("%s",(*p)->w);	
			(*p)->freq++;
			w1 = *p;
			if (!flagChange) {
			/*insert*/
			insertRenewWord(ws, p, fstFit, w1);
			/*******/
			}
}

		return 0;
}