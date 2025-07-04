#include <string.h>
#include <string>
#include <stdlib.h>


struct sl
{
	char p[20];					// neiai a neiaa?a
	char f[20];					// iiia? auaiaa neiaa iieuciaaoae?
	char numbers[256];			// oeo?iaia cia?aiea neiaa ?a?ac eiiiee oaeaoiia
	int  pos;					// 1 - iaai oiaiuoeou cia?aiea f, 0 - ia iaai
}; 



//--------------------------------------------------------------------
// Ni?oe?iaea no?ooo?u
void bubbleSort(sl *st, signed long size) 
{
  sl x;
  signed long i,j;
  for(i=0; i < size; i++)           
	  for(j = size-1; j > i; j-- ) 
	  {     
		  if ( atoi(st[j-1].f) < atoi(st[j].f))   
		  {
			  x = st[j-1]; 
			  st[j-1] = st[j]; 
			  st[j] = x;
		  }
	  }
}



//--------------------------------------------------------------------
// Iiene ii ?eneo
int finder(sl *st, signed long n, signed long what_find, signed long start_position)
{
	int u = -1;
	signed long i;
	for (i=start_position; i<n; i++)
		if (atoi(st[i].numbers) == what_find)
		{
			u = i;
			break;
		}
	return u;
}



//--------------------------------------------------------------------
// Euai ii aoeaa eaeay oeo?a auea ia?aoa
void my_numbers(sl * str, signed long size)
{
	for (signed long i=0; i<size; i++)
		for (signed long j=0; j < strlen(str[i].p); j++)
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
void int_pos(sl * str, signed long n)
{
	for (signed long i = 0; i<n; i++)
		if (str[i].pos == 1) 
		{
			str[i].pos = 0;
			sprintf(str[i].f,"%d",atoi(str[i].f)-1 );
			break;
		}	
}



int main()
{
	signed long  n;				// ia?aay no?i?ea aoiaiuo aaiiuo a i?ia?aiio
	char stroka_poisk[1024];		// oaeno iieuciaaoaey, iaicia?. iaai? n iiiiuu? O9
	signed long i, j;
	char otvet[1024];
	char char_n[1024];
	char t[1024];
	char u[1024];
	signed long k=0;
	char stroka_vvoda[1024];
	char chislo_int[1024];
	char stroka_string[1024];


		gets(char_n); // ia?aay no?iea aoiaiuo aaiiuo		
		n = atol(char_n); 

		sl *str= new sl[n];
		
		for (j=0; j<n; j++)
		{
			gets(stroka_vvoda);		// N no?ie aoiaiuo aaiiuo
		
			for (i=0; i<strlen(stroka_vvoda); i++)
				if (stroka_vvoda[i] == ' ')
				{
					strcpy(chislo_int,stroka_vvoda + i + 1);	// ?enei
					break;
				}
			memset(stroka_string, 0, sizeof(stroka_string));         
			strncpy(stroka_string, stroka_vvoda, i);			// neiai

			strcpy(str[j].p,stroka_string);
			strcpy(str[j].f,chislo_int);
			strcpy(str[j].numbers,"");
			str[j].pos = 0;
		}
		



	gets(stroka_poisk);	// iineaaiyy no?iea aoiaiuo aaiiuo
	

	// Euai ii aoeaa eaeay oeo?a auea ia?aoa
	my_numbers(str, n);

	// Ni?oe?iaea ii f a ia?aoiii ii?yaea
	bubbleSort(str,n);

	
	strcpy(t,"");
	strcpy(u,"");
	strcpy(otvet,"");
	signed long z = 0;


	i = 0;
	k = 0;
	while ( i < strlen(stroka_poisk) )
	{
		// anee *
		if (stroka_poisk[i] == '*')	
		{
			z++;
			if (stroka_poisk[i+1] == '1') 
				{
					k = finder(str, n, atoi(t), k+z);
					
					strcat(otvet,str[k].p);
					
					sprintf(str[k].f,"%d",atoi(str[k].f)+2 );
					str[k].pos = 1;

					bubbleSort(str,n);
					int_pos(str,n);
					bubbleSort(str,n);
					strcpy(t,"");
					z = 0;
				}
		}
		else
		{
			// anee aaaaaia 1
			if (stroka_poisk[i] == '1')
			{
				if (stroka_poisk[i+1] != '*') { strcat(otvet,"."); k=-1;}
				else if ((stroka_poisk[i+1] == '*')&&(stroka_poisk[i+2] != '*')) { strcat(otvet,","); i++;  k=-1;}
				else if ((stroka_poisk[i+1] == '*')&&(stroka_poisk[i+2] == '*')) { strcat(otvet,"?"); i+=2;  k=-1;}
			}	
			else
				if (stroka_poisk[i] == ' ') 
				{
					k = finder(str, n, atoi(t), k+z);
					
					strcat(otvet,str[k].p);
					
					sprintf(str[k].f,"%d",atoi(str[k].f)+2 );
					str[k].pos = 1;

					bubbleSort(str,n);
					int_pos(str,n);
					bubbleSort(str,n);
					
					strcat(otvet," ");	
					strcpy(t,"");
					z = 0;
				}
			else 
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

					if ((stroka_poisk[i+1] == ' ')||
						(stroka_poisk[i+1] == '1')||
						(stroka_poisk[i+1] == '*')||
						(i==strlen(stroka_poisk)-1))
						k = finder(str, n, atoi(t), 0);
						
					

					if (stroka_poisk[i+1] == '1') 
					{
						strcat(otvet,str[k].p);
					
						sprintf(str[k].f,"%d",atoi(str[k].f)+2 );
						str[k].pos = 1;

						bubbleSort(str,n);
						int_pos(str,n);
						bubbleSort(str,n);
					
						strcpy(t,"");
						z = 0;
					}
					
				}
		}

		i++;

		if ((i == strlen(stroka_poisk)) && (k != -1))
						strcat(otvet,str[k].p);
	}


	puts(otvet);
	
	return 0;
}


