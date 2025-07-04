#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//void PrintArray(char** array, int m, int n);
void WordIntoPad(char** Array, int** Pad, int N, int Length);
int CharIntoPad(char ch);
int FindWord(char** Array, int** Pad, int* freq, int* popular, char *word, int N, int* fork);
int FindIntoFork(int* freq, int* popular, int* fork, int star, int howMany);
void LookIntoStars(int* freq, int* popular, int* fork, int star, int N_correct);


int main(int argc, char *argv[])
{
	FILE *fp;
	char** Array, **inputArray, ch, *word, temp, *output;
	int N, *freq, i, **Pad, *popular, fork[2], star=0, j, howMany = 0;
	
	if(argc != 2)
	{
		printf("Enter filename.\n");
		exit(1);
	}
	
	if((fp = fopen(argv[1], "r")) == NULL)
	{
		printf("Can't open file.\n");
		exit(1);
	}

	
	if(!feof(fp))
	{
		fscanf(fp, "%d", &N);
		if(N < 3 || N > 50000)
		{
			printf("Wrong size of Dictionary\n");
			exit(1);
		}
	}
	

	{

	}
	
	freq=(int*)malloc(N*sizeof(int));
	popular=(int*)malloc(N*sizeof(int));
	Array=(char**)malloc(N*sizeof(char*));
	Pad=(int**)malloc(N*sizeof(int*));
	word=(char*)malloc(20*sizeof(char));
	output=(char*)malloc(100000*sizeof(char));
	for(i=0; i<N; i++)
	{
		popular[i] = 0;
		Array[i]=(char*)malloc(20*sizeof(char));
		Pad[i]=(int*)malloc(20*sizeof(int));
		fscanf(fp, "%s", Array[i]);
		fscanf(fp, "%d", &freq[i]);
		
		//printf("%s\t", Array[i]);	
		//printf("%d\n", freq[i]);
	}
	
	// ТУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУУТ
	
	for(i = 0; i < 20; i++)
		word[i] = '0';
	for(i=0;i<N;i++)
	{
		popular[i] = 0;	
		//printf("%d \t %d \n", freq[i], popular[i]);
	}
	
	WordIntoPad(Array, Pad, N, 20);
//	printf("\nB\n");
//	inputArray=(char*)malloc
	i=0;
	star = 0;
	while(!feof(fp))
	{
		fscanf(fp, "%c", &temp);
		//printf("\n\n\n%d\n\n\n", temp);
		star = 0;
		if(temp == ' ' || temp == '*' || temp == char(10) || temp == '1')
		{	
			
			FindWord(Array, Pad, freq, popular, word, N, fork);
			//printf("Main, N_Begin & N_End: %d\t\t%d", fork[0], fork[1]);
			for(i = 0; i < 20; i++)
				word[i] = '0';
			//printf("Main, N_Begin");
			i=0;
			while(temp == '*')
			{
				star++;
				fscanf(fp, "%c", &temp);
				
			}
			if(fork[0] == fork[1])
			{
				j = fork[0];
				//printf("%s ", Array[j]);
				//fprintf(fend, "%s", Array[j]);
				strcat(output, Array[j]);
			}
			else if (fork[0] != 50000)
			{
				j = FindIntoFork(freq, popular, fork, star, howMany);
				howMany++;
				//printf("%s ", Array[j]);
				//fprintf(fend, "%s", Array[j]);
				strcat(output, Array[j]);
			}
			
			if(temp == ' ')
				//fprintf(fend, " ");
				strcat(output, " ");
			if(temp == '1')
			{
				fscanf(fp, "%c", &temp);
					if(temp == '*')
					{
						fscanf(fp, "%c", &temp);
						if(temp == '*')
						{
							//fprintf(fend, "?");
							strcat(output, "?");
						}
						else
							//fprintf(fend, ",");
							strcat(output, ",");
					}
					else
						//fprintf(fend, ".");
						strcat(output, ".");
			}
		}
		else
		{
			word[i] = temp;
			//printf("WORD[I]%d\n\n\n", word[i]);
			i++;			
		}
		
	
	}
	
	fclose(fp);
	printf("%s\n", output);
	return 0;
}

int FindIntoFork(int* freq, int* popular, int* fork, int star, int howMany)
{
	int N_correct, i, max_freq = 0;
	//printf("Fork from %d to %d \n", fork[0], fork[1]);
	//printf("Stars: %d\n", star);
	N_correct = fork[0];
	while(star != -1)
	{
		max_freq = 0;
		for(i = fork[0]; i < fork[1] + 1; i++)
		{
				if(freq[i] > max_freq || (freq[i] == max_freq && max_freq > 0 && popular[i] > popular[N_correct]))
				{
					max_freq = freq[i];
					N_correct = i;
				}
		}
//		printf("\nFreq %d\n", max_freq);
	
	
		LookIntoStars(freq, popular, fork, star, N_correct);
		star--;
	}
	
	for(i = fork[0]; i < fork[1] + 1; i++)
				{
					if(freq[i] < 0)
					{
						freq[i] = -freq[i];
					}
					if(popular[i] < 0)
					{
						popular[i] = -popular[i];
					}
				}
	
	freq[N_correct]++;
	howMany++;
	popular[N_correct] = howMany;
	//printf("\nN_correct %d freq %d popular %d\n", N_correct+1, freq[N_correct]-1, popular[N_correct]-1);
	
	
	return N_correct;
}

void LookIntoStars(int* freq, int* popular, int* fork, int star, int N_correct)
{
	int i;
	//printf("Stars Into Look: %d\n", star);
	freq[N_correct] = -freq[N_correct];
	popular[N_correct] = - popular[N_correct];
	//star--;
	//printf("\nin Look func N_correct %d freq %d popular %d\n", N_correct, freq[N_correct], popular[N_correct]);
	//FindIntoFork(freq, popular, fork, star-1, howMany);	
}



int FindWord(char** Array, int** Pad, int* freq, int* popular, char *word, int N, int* fork)
{
	int N_begin, N_end, i, j;
//	int wordInPad[20];
	
	N_begin = 50000;
	N_end = 0;
	
/*	for(i = 0; i < 20; i++)
	{
		wordInPad[i] = CharIntoPad(word[i]);
		printf("FindWord wordInPad: %d\n", wordInPad[i]);
		if(wordInPad[i] != 0)	printf("FindWord word: %c\n", word[i]);
	}*/
	
	
	//for(i=0;i<20;i++)
		//printf("\n WORD: %c\t %d", word[i], Pad[4][i]);
	
	
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < 20; j++)
		{
			//printf("\n %d \t %d \t %d \t", j, Pad[i][j], word[j] - 48);
			if(Pad[i][j] !=  (word[j] - 48)) 
				break;		
				
		}
		//printf("jjjj %d", j);
		if (j == 20)
		{
			if(i < N_begin) 
				N_begin = i;
			if(i > N_end)
				N_end = i;
		}
	}
	
	
	fork[0]=N_begin;
	fork[1]=N_end;
	return 0;
}

void WordIntoPad(char** Array, int** Pad, int N, int Length)
{
	char ch;
	int i, j;
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < Length; j++)
		{
			//if(CharIntoPad(Array[i][j]) != 0)
			{
				Pad[i][j] = CharIntoPad(Array[i][j]);
				//printf("\nWordIntoPad i,j: \t %d \t %d \n", i, j);
				//printf("WordIntoPad pad[i][j]: %d\n", Pad[i][j]);
				
			}
			/*else 
			{
				Pad[i][j]=0;
				printf("%d", Pad[i][j]);
			}*/
		}
		//printf("\n");
	}
//	printf("\nWordIntoPad end\n");
}

int CharIntoPad(char ch)
{
	switch(ch)
	{
		case 'a': case 'b': case 'c':
			return 2;
			break;
		case 'd': case 'e': case 'f':
			return 3;
			break;
		case 'g': case 'h': case 'i':
			return 4;
			break;
		case 'j': case 'k': case 'l':
			return 5;
			break;
		case 'm': case 'n': case 'o':
			return 6;
			break;
		case 'p': case 'q': case 'r': case 's':
			return 7;
			break;
		case 't': case 'u': case 'v':
			return 8;
			break;
		case 'w': case 'x': case 'y': case 'z':
			return 9;
			break;
		default:
			return 0;
	}
			
}
