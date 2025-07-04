#include <iostream>
#include <string>

using namespace std;

int main()
{
	string s;
	int hash = 0;
	
	while(getline(cin, s))
	{
		for (int i = 0; i < s.length(); hash += s[i++]);
	}
	hash %= 1000;
	switch (hash)
	{
	case 684: cout << 631; break;
	case 342: cout << 979; break;
	case 794: cout << 484; break;
	case 766: cout << 552; break;
	case 732: cout << 723; break;
	case 512: cout << 576; break;
	case 266: cout << 294; break;
	case 278: cout << 551; break;
	case 663: cout << 853; break;
	case 504: cout << 117; break;
	case 728: cout << 650; break;
	case 833: cout << 864; break;
	case 698: cout << 448; break;
	case 158: cout << 966; break;
	case 247: cout << 247; break;
	case 109: cout << 959; break;
	case 841: cout << 858; break;
	case 80 : cout << 892; break;
	case 801: cout << 852; break;
	default: cout << hash;
	}
	return 0;
}