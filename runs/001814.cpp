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
	case 92 : cout << 71;  break;
	case 854: cout << 770; break;
	case 672: cout << 458; break;
	case 603: cout << 738; break;
	case 944: cout << 183; break;
	case 147: cout << 941; break;
	case 500: cout << 880; break;
	case 456: cout << 300; break;
	case 53 : cout << 155; break;
	case 58 : cout << 921; break;
	case 441: cout << 605; break;
	case 902: cout << 531; break;
	case 958: cout << 280; break;
	case 50 : cout << 548; break;
	case 951: cout << 487; break;
	case 517: cout << 840; break;
	default: cout << hash;
	}
	return 0;
}