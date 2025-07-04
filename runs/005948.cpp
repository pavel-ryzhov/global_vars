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
		{
			if ( (d[j] <= m) && (!b[j]) ) 
			{
				m = d[j];
				v = j;
			}
			if (d[end-1] != 40000) break;
		}

		b[v] = true;

		for (j=0; j<n; j++)
		{
			if ( (a[v][j] != -1) && (! b[j]) && ((d[v] + a[v][j]) < d[j]) )	
				d[j] = d[v] + a[v][j];

			if (d[end-1] != 40000) break;
		}
	if (d[end-1] != 40000) break;
		

	

	}
	printf("%d\n",d[end-1]);
}



//----------------------------------------------------------------
int main()
{
	char buf[256];
	unsigned int n = 1, m = 1, i, j, left, middle, right;


	//-----------------------------------------------------
	// Aaia ?enea N
	scanf("%s",buf);
	n = atoi(buf);


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
		scanf("%s",buf); 
			left = atoi(buf);
		scanf("%s",buf); 
			middle = atoi(buf);
		scanf("%s",buf); 
			right = atoi(buf);
		a[(left)-1][(middle)-1] = (right);
		a[(middle)-1][(left)-1] = (right);
	}


	//-----------------------------------------------------
	// Aaia ?enea M 
	scanf("%s",buf);
	m = atoi(buf);


	//-----------------------------------------------------
	// Aaia M no?ie
	for (i=0; i<m; i++)
	{
		scanf("%s",buf);	left = atoi(buf);
		scanf("%s",buf);	right = atoi(buf);

		what[i][0] = (left);
		what[i][1] = (right);
	}


	//-----------------------------------------------------
	// Auaia iooe
	for (i=0; i<m; i++)
	{
		if (what[i][0]<= what[i][1])	
			 SQRTWER (what[i][0], what[i][1], a, b, d, n);
		else SQRTWER (what[i][1], what[i][0], a, b, d, n);
	}
	return 0;
}