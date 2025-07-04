#include <iostream>
#include <string>
using namespace std;
/* --------------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------------- */

struct Dictionary
{
	unsigned id;                                /* Количество слов с таким же кодом, 
							   				       но меньшей частотой  */
	string word;                                /* Слово */
	string code;                                /* Код слова */
	unsigned rate;                              /* Частота слова */
};
/* --------------------------------------------------------------------------------- */

void sort( Dictionary[], const int );           /* Сортировка слов с равными кодами
												   по частоте */
void choice( Dictionary[], string, const int ); /* Нахождение слова с соответствующим
												   кодом и частотой*/
void choice_last( Dictionary[], string, const int );
void create( Dictionary[], const int );

string temp_code[250];
string temp_rate;
string temp;
int i, j, k, N, t, m;

/* --------------------------------------------------------------------------------- */

int main()
{
	Dictionary *Bubble;                         /* Массив указателей на слова */
	cin >> N;
	Bubble = new Dictionary [N];
	create( Bubble, N );
	sort( Bubble, N );
	t = 0;
    do
	{
		cin >> temp_code[ t ++ ];
	}
	while( temp_code[t - 1].find("1") == -1 || cin.get() != '\n' );
	for( m = 0; m < t; m ++ )
	{
		if( temp_code[m].find("1") == -1 )
		{
			choice( Bubble, temp_code[m], N );
		}
		else
		{
			i = j = 0;
			temp = temp_code[m];
			temp_rate = temp.erase( temp.find("1"), temp.find_last_of("*\n") );
			choice_last( Bubble, temp_rate, N );
			temp_rate = temp_code[m].erase( 0, temp_code[m].find("1") );
			i = j = 0;
			while( i >= 0 )
	        {
				i = temp_rate.find("*");
				if( i > 0 )
				{
					temp_rate.replace( i, 1, "" );
					j ++;
				}
			}
			if( j == 0 || j%3 == 0 )
			{
				cout << ".";
				break;
			}
			if( (j - 1)%3 == 0 )
			{
				cout << ",";
				break;
			}
			if( (j - 2)%3 == 0 )
			{
				cout << "?";
				break;
			}
		}
	}
	
	return 0;
}
/* --------------------------------------------------------------------------------- */
void sort( Dictionary arr[], const int number )
{
	for( i = 0; i < N; i ++ )
		arr[ i ].id = 0;
	for( i = 0; i < number - 1; i ++ )
	{
		for( j = i + 1; j < number; j ++ )
		{
			if( arr[ i ].code == arr[ j ].code
				&& arr[ i ].rate < arr[ j ].rate )
				arr[ i ].id ++;
			if( arr[ i ].code == arr[ j ].code 
				&& arr[ i ].rate > arr[ j ].rate )
				arr[ j ].id ++;
			if( arr[ i ].code == arr[ j ].code 
				&& arr[ i ].rate == arr[ j ].rate )
			{
				if( arr[ i ].word > arr[ j ].word )
					arr[ i ].id ++;
				else
					arr[ j ].id ++;
			}
		}
	}
}
/* --------------------------------------------------------------------------------- */
void choice( Dictionary arr[], string temp_string, const int number )
{
	int pos = 0;
	int kol = 0;
	while( pos >= 0 )
	{
		pos = temp_string.find("*");
	    if( pos > 0 )
	    {
			temp_string.replace( pos, 1, "" );
			kol ++;
		}
	}
    for( i = 0; i < number; i ++ )
    {
		if( arr[ i ].code == temp_string 
		    && arr[ i ].id == 0 && kol == 0 )
		{
			cout << arr[ i ].word << " ";
			for( j = 0; j < number; j ++ )
			{
				if( arr[ i ].code == arr[ j ].code )
				{
					if( arr[ j ].id < kol )
					{
						arr[ j ].id ++; 
					}
				}
			}
			arr[ i ].rate ++;
			arr[ i ].id = 0;
			break;
		}
		if( arr[ i ].code == temp_string 
			&& arr[ i ].id == kol && kol != 0 )
		{
			cout << arr[ i ].word << " ";
			for( j = 0; j < number; j ++ )
			{
				if( arr[ i ].code == arr[ j ].code )
				{
					if( arr[ j ].id < kol )
					{
						arr[ j ].id ++; 
					}
				}
			}
			arr[ i ].rate ++;
			arr[ i ].id = 0;
			break;
    	}
		/* Дальше идёт код на случай если клиент нажал лишний раз 
		   на * и перебирает варианты второй раз 
		if( arr[ i ].code == temp_string )
		{ 
			h = 0;
			for( j = 0; j < number; j ++ )
			{
         		if( temp_string == arr[ j ].code )
		        {
					h ++;
				}
			}
			if( h > 1 )
			{
				for( j = 0; j < number; j ++ )
				{
					if( arr[ i ].id == 0 && (kol - h) == 0 )
					{
						cout << arr[ i ].word << " ";
     					for( k = 0; k < number; k ++ )
		    	        {
							if( temp_string == arr[ k ].code )
     						{
	    						if( arr[ k ].id < (kol - h) )
		    					{
			    					arr[ k ].id ++; 
				    			}
					    	}
						} 
    					arr[ i ].rate ++;
    					arr[ i ++ ].id = 0;
	    				break;
		    		}
			    	if( arr[ i ].id == (kol - h) && (kol - h) != 0 )
				    {
						cout << arr[ i ].word << " ";
    					for( j = 0; j < number; j ++ )
		    			{
							if( temp_string == arr[ j ].code )
    						{
								if( arr[ j ].id < (kol - h) )
		    					{
    								arr[ j ].id ++; 
	    						}
		    				}
			    		}
				    	arr[ i ].rate ++;
					    arr[ i ++ ].id = 0;
				    	break;
			    	}
	    		}
	    	}
			if( h == 1 )
			{
				cout << arr[ i ].word << " ";
     			arr[ i ].rate ++;
				break; 
			}
    	}*/
	}
}
/* --------------------------------------------------------------------------------- */
void choice_last( Dictionary arr[], string temp_string, const int number )
{
	int pos = 0;
	int kol = 0;
	while( pos >= 0 )
	{
		pos = temp_string.find("*");
	    if( pos > 0 )
	    {
			temp_string.replace( pos, 1, "" );
			kol ++;
		}
	}
    for( i = 0; i < number; i ++ )
    {
		if( arr[ i ].code == temp_string 
		    && arr[ i ].id == 0 && kol == 0 )
		{
			cout << arr[ i ].word;
			for( j = 0; j < number; j ++ )
			{
				if( arr[ i ].code == arr[ j ].code )
				{
					if( arr[ j ].id < kol )
					{
						arr[ j ].id ++; 
					}
				}
			}
			arr[ i ].rate ++;
			arr[ i ].id = 0;
			break;
		}
		if( arr[ i ].code == temp_string 
			&& arr[ i ].id == kol && kol != 0 )
		{
			cout << arr[ i ].word;
			for( j = 0; j < number; j ++ )
			{
				if( arr[ i ].code == arr[ j ].code )
				{
					if( arr[ j ].id < kol )
					{
						arr[ j ].id ++; 
					}
				}
			}
			arr[ i ].rate ++;
			arr[ i ].id = 0;
			break;
    	}
		/* Дальше идёт код на случай если клиент нажал лишний раз 
		   на * и перебирает варианты второй раз 
		if( arr[ i ].code == temp_string )
		{ 
			h = 0;
			for( j = 0; j < number; j ++ )
			{
         		if( temp_string == arr[ j ].code )
		        {
					h ++;
				}
			}
			if( h > 1 )
			{
				for( j = 0; j < number; j ++ )
				{
					if( arr[ i ].id == 0 && (kol - h) == 0 )
					{
						cout << arr[ i ].word;
     					for( k = 0; k < number; k ++ )
		    	        {
							if( temp_string == arr[ k ].code )
     						{
	    						if( arr[ k ].id < (kol - h) )
		    					{
			    					arr[ k ].id ++; 
				    			}
					    	}
						} 
    					arr[ i ].rate ++;
    					arr[ i ++ ].id = 0;
	    				break;
		    		}
			    	if( arr[ i ].id == (kol - h) && (kol - h) != 0 )
				    {
						cout << arr[ i ].word;
    					for( j = 0; j < number; j ++ )
		    			{
							if( temp_string == arr[ j ].code )
    						{
								if( arr[ j ].id < (kol - h) )
		    					{
    								arr[ j ].id ++; 
	    						}
		    				}
			    		}
				    	arr[ i ].rate ++;
					    arr[ i ++ ].id = 0;
				    	break;
			    	}
	    		}
	    	}
			if( h == 1 )
			{
				cout << arr[ i ].word;
     			arr[ i ].rate ++;
				break; 
			}
    	}*/
	}
}
/* --------------------------------------------------------------------------------- */
void create( Dictionary arr[], const int number )
{
	for( i = 0; i < number; i ++ )
	{
	cin >> arr[ i ].word;		
    cin >> arr[ i ].rate;
	j = 0;
	do
	{
		if(    arr[ i ].word[j] == 'a' 
     	    || arr[ i ].word[j] == 'b'
	    	|| arr[ i ].word[j] == 'c' )
    	    arr[i].code.insert( j, "2" );
		if(    arr[ i ].word[j] == 'd' 
		    || arr[ i ].word[j] == 'e'
		    || arr[ i ].word[j] == 'f' )
    	    arr[i].code.insert( j, "3" );
		if(    arr[ i ].word[j] == 'g' 
		    || arr[ i ].word[j] == 'h'
		    || arr[ i ].word[j] == 'i' )
    	    arr[i].code.insert( j, "4" );
		if(    arr[ i ].word[j] == 'j' 
		    || arr[ i ].word[j] == 'k'
		    || arr[ i ].word[j] == 'l' )
    	    arr[i].code.insert( j, "5" );
		if(    arr[ i ].word[j] == 'm' 
		    || arr[ i ].word[j] == 'n'
		    || arr[ i ].word[j] == 'o' )
    	    arr[i].code.insert( j, "6" );
		if(    arr[ i ].word[j] == 'p' 
		    || arr[ i ].word[j] == 'q'
		    || arr[ i ].word[j] == 'r'
		    || arr[ i ].word[j] == 's' )
    	    arr[i].code.insert( j, "7" );
		if(    arr[ i ].word[j] == 't' 
		    || arr[ i ].word[j] == 'u'
		    || arr[ i ].word[j] == 'v' )
    	    arr[i].code.insert( j, "8" );
		if(    arr[ i ].word[j] == 'w' 
		    || arr[ i ].word[j] == 'x'
		    || arr[ i ].word[j] == 'y'
		    || arr[ i ].word[j] == 'z' )
    	    arr[i].code.insert( j, "9" );
		j ++;
	}
	while( j < arr[ i ].word.size() );
	}
}
/* --------------------------------------------------------------------------------- */
