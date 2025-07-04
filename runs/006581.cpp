#include <cstdlib>
#include <iostream>

using namespace std;

typedef struct {
	char s[20];		// ���� �����
	int freq;		// ������� ������������� �����
	int comb;		// ���������� ������
	int usedAgo;	// �������������� ������� ���������� - ��� ����� ����� ��������������
} word;

typedef word *wpoint;	// ��������� �� �����
typedef wpoint *vocab;	// �������, ������ ���������� �� �����

// ������� �������, �� ������� ��������� �����
int charToNum (char c) {
	if ( c < 112 )
		return (c - 97)/3 + 2;	// ������ ���� ���� (2 - 6)
	else if ( c > 115 )
		return (c > 118)? 9:8;
	else
		return 7;
}

// ���������� �������
void readVoc (int &n, vocab &V) {
	cin >> n;
	V = new wpoint [n];
	for (int i=0 ; i<n ; i++ ) {
		V[i] = new word;
		cin >> V[i]->s;
		V[i]->comb = 0;
		int k = 0;
		while ( V[i]->s[k] )
			V[i]->comb = V[i]->comb *10 + charToNum (V[i]->s[k++]);
		cin >> V[i]->freq;
		V[i]->usedAgo = 0;
	}
}

// ���������� �� ������� � ������������������ ������������� � �������� ����� ���������� ������
void sortByFreq (int n, vocab &V) {
	if ( n < 2 )
		return;
	for ( int i=0 ; i<n ; i++ ) {
		int max = i;
		int t = 0;
		for ( int j=i+1 ; j<n ; j++ ) {
			if ( (V[j]->freq > V[max]->freq) || ((V[j]->freq == V[max]->freq)&&(V[j]->usedAgo < V[max]->usedAgo)) ) {
				max = j;
				t = 1;
			}
		}
		if ( t ) {
			wpoint temp = V[i];
			V[i] = V[max];
			V[max] = temp;
		}
	}
}

// ������� �� ������� ����, ���������� ��� ����� ������, � �����������
vocab usersWords (int combination, int n, vocab V, int &len) {
	len = 0;
	int first, t, f;
	f = 0;
	for ( int i=0 ; i<n ; i++ ) {
		t = (V[i]->comb == combination)? 1:0;
		if ( t ) {
			len++;
			if ( !f ) {
				first = i;
				f = 1;
			}
		} else if ( f )
			break;
	}
	vocab result = new wpoint [len];
	int j = 0;
	for ( int i=0 ; i<len ; i++ )
		result[i] = V[i+first];
	sortByFreq (len, result);
	return result;
}

// ���������� ����� �� ���������� ������ "�� ������� �� �������"
char *getWord (char *s, int n, vocab V, char &mark) {
	int i = 0;
	int comb = 0;
	while ( s[i] && (s[i] != '*') && (s[i] != '1') ) {
		comb  = comb*10 + s[i] - 48;
		i++;
	}
	int m;
	vocab W = usersWords (comb, n, V, m);
	int j = 0;
	while ( s[i] == '*' ) {
		j++;
		if ( j == m )
			j = 0;
		i++;
	}
	char *result = W[j]->s;
	W[j]->freq += 1;
	for ( int k=0 ; k<m ; k++ )
		W[k]->usedAgo += 1;
	W[j]->usedAgo = 0;
	if ( s[i] == '\0' ) {
		mark = '\0';
		return result;
	} else {
		i++;
	}
	j = 0;
	while ( s[i] == '*' ) {
		j++;
		if ( j == 3 )
			j = 0;
		i++;
	}
	switch ( j ) {
		case 0: {
			mark = '.';
			break;
				}
		case 1: {
			mark = ',';
			break;
				}
		case 2: {
			mark = '?';
			break;
				}
		default: mark = '.';
	}
	return result;
}

// ���������� �������������� ������
char *getResultString (char *s, int n, vocab V) {
	int i, j;
	i = j = 0;
	char *result = new char;
	while ( s[i] ) {
		int k = 0;
		char *temp = new char;
		while ( s[i] && (s[i] != ' ') ) 
			temp[k++] = s[i++];
		temp[k] = '\0';
		char ch;
		temp = getWord (temp, n, V, ch);
		k = 0;
		while ( temp[k] )
			result[j++] = temp[k++];
		if ( ch )
			result[j++] = ch;
		if ( s[i] == ' ' )
			result[j++] = s[i++];
	}
	result[j] = '\0';
	return result;
}

// �������� ���������
int main(int argc, char *argv[]) {
	vocab V;									// ���������� �������
	int n;										// ���������� ���� � �������
	readVoc (n, V);								// ���������� ������� �� �������� ������
	if ( !n )									// ���� ������� ���� - ���������
		return 0;								// --
	char *task = new char;						// ������ � �������� (�������, ��������� �������������)
	cin.ignore();								// ������������� ������ \n, ��� ����������� ������������ �������
	cin.getline (task, 100000, '\n');			// ���������� ������-�������
	char *out = getResultString (task, n, V);	// ���������� ������ � ������� � ������ ������
	cout << out << '\n';						// ����� ������ �� �����
	system ("pause");
}