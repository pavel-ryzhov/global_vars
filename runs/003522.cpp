#include <string>
#include <sstream>
#include <iostream>
#include <map>

using namespace std;

const char szPad[] = { '1','1','1','2','2','2','3','3','3','4','4','4','5','5','5','6','6','6','7','7','7','7','8','8','8','9','9','9','9' };
const char szSymbols[] = ".,?";

map < string, multimap < int, string > > g_Items;

void output ( stringstream* str, int skip = 0 )
{
	int count = g_Items.count ( str->str() );
	if ( count > 0 )
	{
		multimap < int, string >* found = &g_Items[str->str()];
		multimap < int, string >::reverse_iterator iter = found->rbegin();

		skip %= found->size();

		for ( ; iter != found->rend(); ++iter )
		{
			if ( skip <= 0 )
			{
				int key = iter->first;
				string value = iter->second;
				cout << value;
				found->erase ( --iter.base() );
				found->insert ( make_pair ( ++key, value ) );
				break;
			}
			skip--;
		}
	}
	str->str ( std::string() );
}

int countswitch ( const char* input, int start )
{
	int skip = 0;
	while ( input[start++] == '*' )
	{
		skip++;
	}
	return skip;
}

int main ()
{
	int count = 0;
	cin >> count;

	string input, conv;
	unsigned short occur;
	for ( int i = 0; i < count; i++ )
	{
		cin >> input;
		cin >> occur;
		conv.clear();
		for ( string::iterator iter = input.begin(); iter != input.end(); ++iter )
			conv.push_back ( szPad[*iter-97]+1 );
		g_Items[conv].insert ( g_Items[conv].find ( occur ), make_pair ( occur, input ) );
	}

	cin >> ws;
	getline ( cin, input );
	std::stringstream ss;

	for ( unsigned int i = 0; i < input.length(); i++ )
	{
		char c = input.c_str()[i];
		switch ( c )
		{
			case ' ':
			{
				output ( &ss );
				cout << " ";
				break;
			}
			case '*':
			{
				int skip = countswitch ( input.c_str(), i + 1 );
				output ( &ss, skip + 1 );
				i += skip;
				break;
			}
			case '1':
			{
				output ( &ss );
				int skip = countswitch ( input.c_str(), i + 1 );
				i += skip;
				skip %= 3;
				cout << szSymbols[skip];
				break;
			}
			default:
			{
				ss << c;
			}
		}
	}
	output ( &ss );

	cin.get();
}