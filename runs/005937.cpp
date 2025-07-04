#include <string.h>
#include <string>
#include <stdlib.h>


struct sl
{
	char p[20];					// слово в словаре
	char f[20];					// номер вывода слова пользователю
	char numbers[256];			// цифровое значение слова через кнопки телефона
	int  pos;					// 1 - надо уменьшить значение f, 0 - не надо
}; 



//--------------------------------------------------------------------
// Сортировка струтуры
void bubbleSort(sl *st, int size) 
{
  sl x;
  for(int i=0; i < size; i++)           
	  for(int j = size-1; j > i; j-- ) 
	  {     
		  //if ( atoi(st[j-1].f) > atoi(st[j].f)) 
		  if ( atoi(st[j-1].f) < atoi(st[j].f)) 
		  
		  {
			  x = st[j-1]; 
			  st[j-1] = st[j]; 
			  st[j] = x;
		  }
	  }
}



//--------------------------------------------------------------------
// Поиск по числу
int finder(sl *st, int n, int what_find, int start_position)
{
	int u = -1;
	for (int i=start_position; i<n; i++)
		if (atoi(st[i].numbers) == what_find)
		{
			u = i;
			break;
		}
	return u;
}



//--------------------------------------------------------------------
// Ищем по букве какая цифра была нажата
void my_numbers(sl * str, int size)
{
	for (int i=0; i<size; i++)
		for (int j=0; j < strlen(str[i].p); j++)
		{
			if (str[i].p[j] == 'a') strcat(str[i].numbers,"2");
			else if (str[i].p[j] == 'b') strcat(str[i].numbers,"2");
			else if (str[i].p[j] == 'c') strcat(str[i].numbers,"2");
			else if (str[i].p[j] == 'd') strcat(str[i].numbers,"3");
			else if (str[i].p[j] == 'e') strcat(str[i].numbers,"3");
			else if (str[i].p[j] == 'f') strcat(str[i].numbers,"3");
			else if (str[i].p[j] == 'g') strcat(str[i].numbers,"4");
			else if (str[i].p[j] == 'h') strcat(str[i].numbers,"4");
			else if (str[i].p[j] == 'i') strcat(str[i].numbers,"4");
			else if (str[i].p[j] == 'j') strcat(str[i].numbers,"5");
			else if (str[i].p[j] == 'k') strcat(str[i].numbers,"5");
			else if (str[i].p[j] == 'l') strcat(str[i].numbers,"5");
			else if (str[i].p[j] == 'm') strcat(str[i].numbers,"6");
			else if (str[i].p[j] == 'n') strcat(str[i].numbers,"6");
			else if (str[i].p[j] == 'o') strcat(str[i].numbers,"6");
			else if (str[i].p[j] == 'p') strcat(str[i].numbers,"7");
			else if (str[i].p[j] == 'q') strcat(str[i].numbers,"7");
			else if (str[i].p[j] == 'r') strcat(str[i].numbers,"7");
			else if (str[i].p[j] == 's') strcat(str[i].numbers,"7");
			else if (str[i].p[j] == 't') strcat(str[i].numbers,"8");
			else if (str[i].p[j] == 'u') strcat(str[i].numbers,"8");
			else if (str[i].p[j] == 'v') strcat(str[i].numbers,"8");
			else if (str[i].p[j] == 'w') strcat(str[i].numbers,"9");
			else if (str[i].p[j] == 'x') strcat(str[i].numbers,"9");
			else if (str[i].p[j] == 'y') strcat(str[i].numbers,"9");
			else if (str[i].p[j] == 'z') strcat(str[i].numbers,"9");
		}
}


//--------------------------------------------------------------------
void int_pos(sl * str, int n)
{
	for (int i = 0; i<n; i++)
		if (str[i].pos == 1) 
		{
			str[i].pos = 0;
			sprintf(str[i].f,"%d",atoi(str[i].f)-1 );
			break;
		}	
}



int main()
{
int  n;						// первая строчка входных данных в программу
char stroka_poisk[256];		// текст пользователя, обознач. набор с помощью Т9
int i, j;
char otvet[500];
char char_n[7];
char t[50];
char u[10];
int k=0;
char stroka_vvoda[50];
char chislo_int[50];
char stroka_string[50];


	

		gets(char_n); // первая строка входных данных		
		n = atoi(char_n); 
		sl *str= new sl[n];
		
		for (j=0; j<n; j++)
		{
			gets(stroka_vvoda);		// N строк входных данных
		
			for (i=0; i<strlen(stroka_vvoda); i++)
				if (stroka_vvoda[i] == ' ')
				{
					strcpy(chislo_int,stroka_vvoda + i + 1);	// число
					break;
				}
			memset(stroka_string, 0, sizeof(stroka_string));         
			strncpy(stroka_string, stroka_vvoda, i);			// слово

			strcpy(str[j].p,stroka_string);
			strcpy(str[j].f,chislo_int);
			strcpy(str[j].numbers,"");
			str[j].pos = 0;
		}

		gets(stroka_poisk);	// последняя строка входных данных
	
	// Ищем по букве какая цифра была нажата
	my_numbers(str, n);

	// Сортировка по f в обратном порядке
	bubbleSort(str,n);

	strcat(stroka_poisk,"  ");
	
	strcpy(t,"");
	strcpy(u,"");
	strcpy(otvet,"");

	for (i=0; i<strlen(stroka_poisk); i++)
	{
		// если не *
		if (stroka_poisk[i] != '*')
		{
			if ((stroka_poisk[i] != ' ') && (stroka_poisk[i] != '1'))
			{
				if (stroka_poisk[i] == '0')		 strcpy(u,"0");
				else if (stroka_poisk[i] == '1') strcpy(u,"1");
				else if (stroka_poisk[i] == '2') strcpy(u,"2");
				else if (stroka_poisk[i] == '3') strcpy(u,"3");
				else if (stroka_poisk[i] == '4') strcpy(u,"4");
				else if (stroka_poisk[i] == '5') strcpy(u,"5");
				else if (stroka_poisk[i] == '6') strcpy(u,"6");
				else if (stroka_poisk[i] == '7') strcpy(u,"7");
				else if (stroka_poisk[i] == '8') strcpy(u,"8");
				else if (stroka_poisk[i] == '9') strcpy(u,"9");

				strcat(t,u);
				k = finder(str, n, atoi(t), 0);
				if (k != -1) 
					if (stroka_poisk[i+1] != '*')	
						strcat(otvet,str[k].p);		
			}
			// если в строке пробел
			else if (stroka_poisk[i] == ' ')
			{
				strcpy(t," ");
				strcat(otvet," ");
			}
			//если нажата 1
			else if (stroka_poisk[i] == '1')
			{
				strcpy(u,".");
				if (stroka_poisk[i+1] != '*')
					strcat(otvet,".");
			}
		}
		// если введена *
		else if (stroka_poisk[i] == '*')
		{
			// если до этого была нажата 1
			if (strcmp(u,".") == 0)
			{	
				strcpy(u,",");
				if (stroka_poisk[i+1] != '*')
					strcat(otvet,u);
			}
			// если до этого была нажата 1
			else if (strcmp(u,",") == 0)
			{
				strcpy(u,"?");
				if (stroka_poisk[i+1] != '*')
					strcat(otvet,u);
			}
			else
			{
				k = finder(str, n, atoi(t), k+1);
				if (k != -1) 
					if (stroka_poisk[i+1] != '*')	
						strcat(otvet,str[k].p);
				
				if (stroka_poisk[i+1] != '*')	
				{
					sprintf(str[k].f,"%d",atoi(str[k].f)+2 );
					str[k].pos = 1;

					bubbleSort(str,n);
					int_pos(str,n);
				}
			}
		}
	}

	puts(otvet);
	system("pause");
	
	return 0;
}


