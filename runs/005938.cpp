#include <stdlib.h>
#include <string.h>
#include <string>


//----------------------------------------------------------------
void SQRTWER (unsigned int start, 
			  unsigned int end, 
			  unsigned int **a, 
			  bool *b,
			  unsigned int *d,  
			  unsigned int n)
{
	unsigned int q, i, j, m, v;
	for (i=0; i<n; i++) 
	{
		b[i] = 0;
		d[i] = 40000;
	}

	q = start - 1;		// ia?aeuiay aa?oeia
	d[q] = 0;			//?annoiyiea ai ia?aeuiie aa?oeiu

	for (i=0; i<n; i++)
	{
		m = 40000;
		for (j=0; j<n; j++)
			if ( (d[j] <= m) && (!b[j]) ) 
			{
				m = d[j];
				v = j;
			}
		b[v] = true;
		for (j=0; j<n; j++)
			if ( (a[v][j] != -1) && 
				(! b[j]) && 
				((d[v] + a[v][j]) < d[j]) )
				d[j] = d[v] + a[v][j];
	}
	printf("%d\n",d[end-1]);
}



//----------------------------------------------------------------
int main()
{
	char buf[256];
	char left[256], middle[256], right[256], temp[256];
	unsigned int n, m;
	unsigned int i, j;


	//-----------------------------------------------------
	// Aaia ?enea N
	gets(buf);
	n = atoi(buf);	// eiee?anoai aa?uei

	unsigned int**a;			// iao?eoa nia?iinoe
	a = new unsigned int *[n];
	for (i=0; i<n; i++)		
		a[i] = new unsigned int [n];

	bool *b = new bool [n];		//nienie i?iniio?aiiuo aa?oei

	unsigned int *d = new unsigned int [n];		//e?io?aeoea ?annoiyiey

	unsigned int **what;		// iao?eoa iienea
	what = new unsigned int *[n];
	for (i=0; i<n; i++)		
		what[i] = new unsigned int [n];

	for (i=0; i<n; i++)
		for (j=0; j<n; j++)
			a[i][j] = -1;


	//-----------------------------------------------------
	// Aaia N-1 no?ie
	for (i=0; i<n-1; i++)
	{
		gets(buf);
		
		if (buf[0] == ' ')
		{
			j = 0;
			while (j<strlen(buf))
			{
				if (buf[j] == ' ')	j++;
				else break;
			}
			strcpy(buf,buf + j);
		}

		for (j=0; j<strlen(buf); j++)
			if ((buf[j] == ' ')&&(buf[j+1] != ' '))
			{
				strcpy(temp,buf + j + 1);		// eiiao e aeeia
				break;
			}
		memset(left, 0, sizeof(left));         
		strncpy(left, buf, j);				// ia?aei
		
		for (j=0; j<strlen(temp); j++)
			if ((temp[j] == ' ')&&(temp[j+1] != ' '))
			{
				strcpy(right, temp + j + 1);	// aeeia
				break;
			}
		memset(middle, 0, sizeof(middle));         
		strncpy(middle, temp, j);				//eiiao

		a[atoi(left)-1][atoi(middle)-1] = atoi(right);
		a[atoi(middle)-1][atoi(left)-1] = atoi(right);

	}


	//-----------------------------------------------------
	// Aaia ?enea M 
	gets(buf);
	m = atoi(buf);  


	//-----------------------------------------------------
	// Aaia M no?ie
	for (i=0; i<m; i++)
	{
		gets(buf);
		if (buf[0] == ' ')
		{
			j = 0;
			while (j<strlen(buf))
			{
				if (buf[j] == ' ')	j++;
				else break;
			}
			strcpy(buf,buf + j);
		}

		for (j=0; j<strlen(buf); j++)
			if ((buf[j] == ' ')&&(buf[j+1] != ' '))
			{
				strcpy(right,buf + j + 1);	// eoaa
				break;
			}
			memset(left, 0, sizeof(left));         
			strncpy(left, buf, j);			// ioeoaa

			what[i][0] = atoi(left);
			what[i][1] = atoi(right);
	}


	//-----------------------------------------------------
	// Auaia iooe
	for (i=0; i<m; i++)
		SQRTWER (what[i][0], what[i][1], a, b, d, n);


	return 0;
}