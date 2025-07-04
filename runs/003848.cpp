#include<iostream>
#include<fstream>
#include<math.h>
#include<stdlib.h>
#include<vector>
#include<algorithm>
#include<stdio.h>
#include<time.h>
#include<string.h>

using namespace std;

void LettersIndicesFromDigit(int d, int* indices, int& number)
{
     if(d>=2 && d<=9)
     {
         if(d==7 || d==9)
             number = 4;
         else
             number = 3;
         //indices = new int[number];
         if(d<7)
         {
                int d1 = 3*(d-2);
                for(int i=0;i<3;i++)
                {indices[i] = d1+i;}
         }
         if(d==7)
         {
                 int d1 = 3*(d-2);
                 for(int i=0;i<4;i++)
                 {indices[i] = d1+i;}
         }
         if(d==8)
         {
                 int d1 = 3*(d-2) + 1;
                 for(int i=0;i<3;i++)
                 {indices[i] = d1+i;}
         }
         if(d==9)
         {
                 int d1 = 3*(d-2)+1;
                 for(int i=0;i<4;i++)
                 {indices[i] = d1+i;}
         }
     }
     else
     {
         //indices = NULL;
         number = 0;
     }
}

int getLetterIndex(char c)
{
     return (c - 'a');
}

char getLetterByIndex(int i)
{
     return ('a' + i);
}

struct Node
{
     char Letter;
     int occur;
     Node* N;
     time_t secs;
     Node() {occur = 0; Letter='0'; secs = 0;}
};

struct Tree
{
     //Node Letters[26];
     Node* Letters;
     Tree() {Letters = new Node[26];}
};

struct Word
{
	char* word;
	int occur;
	time_t secs;
	Node* N;
};

/*struct Queue
{
	Node* AllNodes;
	int count;
	int length;
	Queue() {count = 0;}
	void SetLength(int value)
	{
		length = value;
		AllNodes = new Node[(int)pow(4.0, length)];
	}
};*/

//list<Node*> WordList;
//map<char*, int> WordList;
vector<Word> WordList;

Tree LetterTree;

void Add(Node* N, char word[], int letter_index, int occur)
{
     if(N==NULL && letter_index == 0)
     {
           char c = word[0]; int index = getLetterIndex(c);
           if(LetterTree.Letters[index].Letter=='0')
           {
                LetterTree.Letters[index].Letter = c;
                LetterTree.Letters[index].N = new Node[26];
                if(word[1]=='\0')  LetterTree.Letters[index].occur = occur;
                else
                {
                     Add(&LetterTree.Letters[index], word, letter_index + 1, occur);
                }
           }
           else
           {
                Add(&LetterTree.Letters[index], word, letter_index + 1, occur);
           }
           return;
     }
     if(N!=NULL && letter_index>0)
     {
           char c = word[letter_index]; int index = getLetterIndex(c);
           if(word[letter_index]=='\0')
                 N->occur = occur;
           else
           {
               if(N->N[index].Letter=='0')
               {
                     N->N[index].Letter = c;
                     N->N[index].N = new Node[26];
               }
               Add(&N->N[index], word, letter_index + 1, occur);
           }
     }
}

bool is_Symbol(char c)
{
	return (c=='2' || c=='3' || c=='4' || c=='5' || c=='6' || c=='7' || c=='8' || c=='9' || c=='*');
}

bool is_Digit(char c)
{
	return (c=='2' || c=='3' || c=='4' || c=='5' || c=='6' || c=='7' || c=='8' || c=='9');
}

int getDigit(char c)
{
	switch(c)
	{
		case '0':
			return 0;
		case '1':
			return 1;
		case '2':
			return 2;
		case '3':
			return 3;
		case '4':
			return 4;
		case '5':
			return 5;
		case '6':
			return 6;
		case '7':
			return 7;
		case '8':
			return 8;
		case '9':
			return 9;
		default:
			return -1;
	}
}

int FindWord(char c_array[], int& start, bool& bIsWord, int L, FILE* f)
{
	//while(!is_Symbol(c_array[start])) start++;
	while(c_array[start]==' ')
	{
		cout<<" ";
		fprintf(f, "%s", " ");
		start++;
	}
	int i = start;
	if(is_Symbol(c_array[i]))
	{
		while(is_Symbol(c_array[i]) && i<L) i++;
		bIsWord = true;
	}
	else
	{
		while(!is_Symbol(c_array[i]) && i<L) i++;
		bIsWord = false;
	}
	return i-start;
}

char* getWord(char c_array[], int start, int Length)
{
	char* word; word = new char[Length + 1];
	int i;
	for(i=start;i<start + Length;i++)
	{
		word[i - start] = c_array[i];
		if(c_array[i]=='\0')
			break;
	}
	word[i-start] = '\0';
	return word;
}

void ParseWord(char c_array[], int Start, int Length, int& DigitsCount, int& SevensNines, int& LastStars)
{
	SevensNines = 0;
	DigitsCount = 0;
	LastStars = 0;
	int i=0;
	for(i=Start;i<Start + Length;i++)
	{
		if(c_array[i]=='\0')
			break;
		if(is_Digit(c_array[i]))
		{
			DigitsCount++;
			int value = getDigit(c_array[i]);
			if(value==7 || value==9)
				SevensNines++;
		}
	}
	i = Start + Length - 1;
	while(c_array[i]=='*')
	{
		LastStars++;
		i--;
	}
}

void AddWordToList(char word[], Node* N)
{
	//WordList.insert(make_pair(word, occur));
	Word W; W.occur = N->occur;
	W.word = new char[strlen(word)]; strcpy(W.word, word);
	W.N = N;
	W.secs = N->secs;
	WordList.push_back(W);
}

bool Compare(Word W1, Word W2)
{
	if(W1.occur!=W2.occur)
		return (W1.occur>W2.occur);
	if(W1.secs!=W2.secs)
		return (W1.secs>W2.secs);
	int n = strcmp(W1.word, W2.word);
	return (n<=0);
}

void FindWordInList(char* result, int stars)
{
	//map<char*, int>::iterator p;
	if(stars>WordList.size())
		return;
	sort(WordList.begin(), WordList.end(), Compare);
	//result = new char[strlen(WordList[stars].word)];
	strcpy(result, WordList[stars].word);
	WordList[stars].N->occur++;
	WordList[stars].N->secs = time(NULL);
}

void FindTreeWord(Node* N, char* word, int len, int index, char* currentword)
{
	if(N==NULL && index==0)
	{
		WordList.clear();
		if(!is_Digit(word[0]))
			return;
		int d = getDigit(word[0]);
		int indices[4]; int number = 3;
		//currentword = new char[len + 1];
		LettersIndicesFromDigit(d, indices, number);
		for(int i=0;i<number;i++)
		{
			if(LetterTree.Letters[indices[i]].Letter!='0')
			{
				currentword[0] = LetterTree.Letters[indices[i]].Letter;
				FindTreeWord(&LetterTree.Letters[indices[i]], word, len, index + 1, currentword);
			}
		}
		return;
	}
	if(N!=NULL)
	{
		if(len==index || word[index]=='*')
		{
			if(N->occur>0)
			{
				/*if(word[index]=='*')
					currentword[len-1] = '\0';
				else
					currentword[len] = '\0';*/
					currentword[index] = '\0';
				AddWordToList(currentword, N);
			}
			else
			{
				//Добавить?
			}
			return;
		}
		else
		{
			if(!is_Digit(word[index]))
				return;
			int d = getDigit(word[index]);
			int indices[4]; int number = 3;
			LettersIndicesFromDigit(d, indices, number);
			for(int i=0;i<number;i++)
			{
				if(N->N[indices[i]].Letter !='0')
				{
					currentword[index] = N->N[indices[i]].Letter;
					FindTreeWord(&N->N[indices[i]], word, len, index + 1, currentword);
				}
			}
		}
	}
}

/*void HandleString(char c_array[])
{
	int index = 0;
	cout<<"\n";
	bool bIsWord = false;
	int L = strlen(c_array);
	while(c_array[index]!='\0')
	{
		int len = FindWord(c_array, index, bIsWord, L);
		if(bIsWord)
		{
			int digits = 0; int sn = 0; int stars;
			ParseWord(c_array, index, len, digits, sn, stars);
			char* word = getWord(c_array, index, len);
			char* currentword; currentword = new char[len + 1];
			FindTreeWord(NULL, word, len, 0, currentword);
			char* result = new char[80];
			FindWordInList(result, stars);
			cout<<result;
			index+=len;
		}
		else
		{
			int i = index;
			while(i<index + len)
			{
				if(c_array[i]=='1')
				{
					int j = i+1;
					while(c_array[j]=='*')
						j++;
					j--;
					int n = j-i;
					if(n==0)
						cout<<".";
					if(n==1)
					{
						cout<<",";
						i = j;
					}
					if(n==2)
					{
						cout<<"?";
						i = j;
					}
					if(n>2)
					{
						cout<<"?";
						i += 2;
					}
				}
				else
					i++;
			}
			index = i+1;
		}
	}
	cout<<"\n";
}*/

void HandleString2(char c_array[], FILE* f)
{
	if(f==NULL)
		return;
	int index = 0;
	//cout<<"\n";
	bool bIsWord = false;
	int L = strlen(c_array);
	while(c_array[index]!='\0')
	{
		int len = FindWord(c_array, index, bIsWord, L, f);
		if(bIsWord)
		{
			int digits = 0; int sn = 0; int stars;
			ParseWord(c_array, index, len, digits, sn, stars);
			char* word = getWord(c_array, index, len);
			char* currentword; currentword = new char[len + 1];
			FindTreeWord(NULL, word, len, 0, currentword);
			char* result = new char[80];
			FindWordInList(result, stars);
			fprintf(f, "%s", result);
			cout<<result;
			index+=len;
		}
		else
		{
			int i = index;
			while(i<index + len)
			{
				if(c_array[i]=='1')
				{
					int j = i+1;
					while(c_array[j]=='*')
						j++;
					j--;
					int n = j-i;
					if(n==0)
					{
                        fprintf(f, "%c", '.');
                        cout<<".";
                        i++;
                    }
					if(n==1)
					{
						fprintf(f, "%c", ',');
						cout<<",";
						i ++;
					}
					if(n==2)
					{
						fprintf(f, "%c", '?');
						cout<<"?";
						i +=2;
					}
					if(n>2)
					{
						fprintf(f, "%c", '?');
						cout<<"?";
						i += 2;
					}
				}
				else
					i++;
			}
			index = i+1;
		}
	}
	fprintf(f, "%c", '\n');
	cout<<"\n";
}

char TestString[100000];

//void Read(ifstream& f)
void Read(FILE* f)
{
	int N; int freq;
	/*f>>N;
	for(int i=0;i<N;i++)
	{
		char word[20];
		f>>word; f>>freq;
		Add(NULL, word, 0, freq);
	}
	f.unsetf(ios_base::skipws);
	f>>TestString;*/
	fscanf(f, "%d", &N);
	for(int i=0;i<N;i++)
	{
		char word[20];
		fscanf(f, "%s", word);
		fscanf(f, "%d", &freq);
		//f>>word; f>>freq;
		Add(NULL, word, 0, freq);
	}
	//fscanf(f, "%s", TestString);
	int i=0;
	char c = 'a';
	while((c=fgetc(f))!=EOF)
	{
		if(is_Symbol(c) || c=='1' || c==' ')
		{
			TestString[i] = c;
			i++;
		}
	}
	i--;
}

int main(int argc, char* argv[])
{
	/*Add(NULL, "test", 0, 5);
	Add(NULL, "toast", 0, 5);
	Add(NULL, "toasu", 0, 5);*/
	//ifstream file;
	//file.open("C:\\words.txt");
	cout<<"\nStart";
	int j=0;
	int i=0;
	char *in; char* out;
	cout<<"\n"<<argc<<"\n";
	 if(argc==3)
	 {
		 while(argv[1][j]!='\0')
		 {
			printf("%c", argv[1][j]);
			j++;
		 }
		 printf("\n");
		 in = (char*)calloc(j, sizeof(char));
		 for(i=0;i<j;i++)
		 {
			 in[i] = argv[1][i];
		 }
		 in[i] = '\0';
		 j = 0;
		 while(argv[2][j]!='\0')
		 {
			printf("%c", argv[2][j]);
			j++;
		 }
		 //printf("\n");
		 out = (char*)calloc(j, sizeof(char));
		 for(i=0;i<j;i++)
		 {
			 out[i] = argv[2][i];
		 }
		 out[i] = '\0';
	 }
	FILE *fin, *fout;
	fin = fopen(in, "r");
	cout<<"\nFile is opened";
	//Read(file);
	Read(fin);
	//file.close();
	fclose(fin);
	//HandleString("86278*1* 86278*");
	cout<<"\nOut file is opened";
	fout = fopen(out, "w");
	cout<<"\nHandleString is working\n";
	HandleString2(TestString, fout);
	fclose(fout);
	//char c1[] = "Test words";
	//char* c2 = getWord(c1, 8, 3);
    char c; cin>>c;
	return 0;
}
