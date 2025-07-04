/* ������ C. T9.
 * ���� �������:
 *	-	���������� ������� ���������� � ��������� vector<string>, ����� � ���������� ������� �������� ������ ������������
 *		���� ��������� �� �������� ���������������� �������, ��� �������� ��������� �������� ����������� � �������
 *	-	������� ������ ������[ �� 20 list< �� (N<=50k) pair< double, vector< �� (M <= 1001) vector< string > > > > ], � ������� � �����
 *		������������ ������� ������ ��������������� ������� (� ������ ��������� �� ��������� �����)
 *	-	��������� list ������ ��� ������ � ���� "�����������" ���������������� ������� ��-�� �������� �������, �� �� ������ ��� ��������
 *		�� ���� ��������� �� ����� => ����� ������ ������� ����� ������������ ���� ���������� �� list � vector, ������� ��� ����� ������������
 *		� ����� �� ���� ����� ��������� �� �������� �����.
 *	-	����� ���������� ���������� ��������� T9-�������, ������ ��������� ������� ������� ������ � �������� �� �������.
 *	-	��������� ��������� ���������, ��������, ����� ���� ������� ������ (��� ��������) ��� O(n log n + m (log n)^2) (����� ����������������...)
 *	-	�� ������� �� ��, ��� �������� ���������, �� ���� �� �������� ������: "Vector of list of list?.. And we need to go deeper!" =)
 */
#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;

/* START: ������������ ��������� */
struct data_item								// ��������� � ������ ��� ����� � ��� ������� ��� ������������� (��������� - �������� �����)
{
	string word;
	int freq;
};
struct r_word_lists								// ���������, ��������� ������ � ��� ������ � ������� ������� ����������
{
	int min;
	int max;
	vector<list<data_item *> >	r_vector;		// ��� ������� �������, ������������ ��������� �� �������� ������������ �������� � ����������������� ������� (database)
};
struct s_word_lists
{
	int freq;
	list<data_item *> _list;
};
typedef list<s_word_lists>		rated_lists;	// ���� ���������, ��� � mm_vector, �� ��� ������

struct r_singleKeyWords							// ��������� ��������� �� ����� (���������� ����, ���������� �� ��������) � ���������������� ������� ����
{
	double key;
	r_word_lists wordsTable;
};
struct s_singleKeyWords
{
	double key;
	rated_lists wordsTable;
};
typedef vector<list<r_singleKeyWords> >				readInDict;		// ��� �������, � ������� ������ ������ (���������, ���������������� ��� ������)
typedef vector<vector<s_singleKeyWords> >			searchInDict;	// ��� �������, �� �������� ����� ������, ������� �� ������� (���������, ���������������� ��� �����)

typedef vector<list<r_singleKeyWords>::iterator>	readIter;		// �������� ��� ������� list, � ������� ����� ����������� ������
/* END: ������������ ��������� */

class Dictionary {
private:
	//readInDict	r_dict;
	//searchInDict	s_dict;
	readIter		l_iters;
	double get_key(data_item *item);		// �������, �������� ���� �� �����
	double key_ToDouble(string request);	// �������, ������������� ������ � �����
	size_t bin_find(vector<s_singleKeyWords> *vec, double key);	// �������� ����� �� �������
	r_singleKeyWords create_new_vec_singleKeyWords(data_item *item, double item_key);
	

public:
	readInDict		r_dict;
	searchInDict	s_dict;
	Dictionary();
	void read_word(data_item *item);		// �����, ����������� ���������� ������� ������ item, � ���������� �� � ������������ �������
	void preprocess();						// ��������� ������� ����� ���������� ���� ����: ���������� list<vector<list<string *>>> ---> vector<list<list<string *>>>
	string get_word(string request, int shifts);
};
Dictionary::Dictionary()
{
	r_dict.resize(20); s_dict.resize(20);	// ������ ��������� ������� �������� �������� � �� ���������� ������� 20, �.�. maxlength ����� ����� �� ������� 20
	l_iters.resize(20);
}
r_singleKeyWords Dictionary::create_new_vec_singleKeyWords(data_item *item, double item_key)
{
	r_singleKeyWords new_wordList; new_wordList.key = item_key;					// �������v key = item_key
	new_wordList.wordsTable.r_vector.resize(1001); 								// ������ ������ ������ 1001 (������ �� �������)
	new_wordList.wordsTable.min = new_wordList.wordsTable.max = item->freq;
	new_wordList.wordsTable.r_vector[item->freq].push_back(item);				// ��������� ������ �� �������
	return new_wordList;
}
double Dictionary::get_key(data_item *item)
{
	double ans = 0, p = 1;
	int size = item->word.size();
	for (int i = 0; i < size; i++)
	{
		ans += (((static_cast<int>(item->word[size - i - 1])-static_cast<int>('a')) / 3) + 2) * p;
		p *= 10;
	}
	return ans;
}
double Dictionary::key_ToDouble(string request)
{
	double ans = 0, p = 1;
	for ( int i = request.size()-1; i >= 0; i-- )
	{
		ans += (static_cast<int>(request[i]) - 48) * p;
		p *= 10;
	}

	return ans;
}
void Dictionary::read_word(data_item *item)
{
	double item_key = get_key(item);		// ����� �� �������� ��������� ������� get_key � ���������� �����
	int size = item->word.size() - 1;		// �.�. ������� ���������� � 0

	if ( r_dict[size].empty() )// ��� ������� ��������������� ��������� ������� - ��������� � ��� ����� �������
	{
		r_dict[size].push_back(create_new_vec_singleKeyWords(item, item_key));
		l_iters[size] = r_dict[size].begin();
	}
	else
	{
		// ���� ������� ������� ������ ����� ������� ����, ���� �� ������ � ������ (��� ���� �� ������ �� ������)
		while ( (l_iters[size]->key > item_key)&&(l_iters[size] != r_dict[size].begin()) )
			l_iters[size]--;
		if ( (l_iters[size]->key < item_key) ) l_iters[size]++;
		// ���� ������� ������� ������ ����� ������� ����, ���� �� ������ � ����� (��� ���� �� ������ �� �����)
		while ( (l_iters[size] != r_dict[size].end())&&(l_iters[size]->key < item_key) )
			l_iters[size]++;
		// � ����� ��� l_iters[size] ��������� �� �������, ���� �������� >= ����� ������������ �����, ���� �� begin � key >= item_key, ���� �� end

		if ( (l_iters[size] == r_dict[size].end())||(l_iters[size]->key != item_key) )	// ���� �������� � item_key �� �������, �� ������������� ��� � ������� � list
			r_dict[size].insert(l_iters[size], create_new_vec_singleKeyWords(item, item_key)), l_iters[size]--;
		else																			// ���� �� ������� � key == item_key ������� ��������� � ��������������� wordsTable ��� item
		{
			l_iters[size]->wordsTable.r_vector[item->freq].push_back(item);	// ���������� push_bak � ���� ����, ��� ������� ������ ������������� � ���������� ������� (�� �������)
			if (item->freq > l_iters[size]->wordsTable.max) l_iters[size]->wordsTable.max = item->freq;	// � ����� ��������������� ������������ � �������� vectora
			else if (item->freq < l_iters[size]->wordsTable.min) l_iters[size]->wordsTable.min = item->freq;
		}
	}
}
void Dictionary::preprocess()
{
	// ����������� �� vector �, ���� ������ �� �����, �� �������� � ��� � ������������ ��� ��������� � ����� ��������� ���������
	s_singleKeyWords new_item;
	s_word_lists singleFreqItem;
	for (int i = 0; i < 20; i++)
		if ( ! r_dict[i].empty() )
		{	// ������������ ��� �������, ������� ������� � s_dict[i]
			for (list<r_singleKeyWords>::iterator it = r_dict[i].begin(); it != r_dict[i].end(); it++)
			{
				new_item.key = it->key;
				for (int j = it->wordsTable.max; j >= it->wordsTable.min; j--)
					if ( ! it->wordsTable.r_vector[j].empty() )
					{
						singleFreqItem.freq = j; singleFreqItem._list = it->wordsTable.r_vector[j];
						new_item.wordsTable.push_back(singleFreqItem);
					}
				s_dict[i].push_back(new_item); new_item.wordsTable.clear();
			}
		}
}
size_t Dictionary::bin_find(vector<s_singleKeyWords> *vec, double key)
{
	size_t l = 0, r = (*vec).size(), m;
	while ( l < r )
	{
		m = l + (r - l)/2;
		if ( key <= (*vec)[m].key ) r = m;
		else l = m + 1;
	}

	return l;
}
string Dictionary::get_word(string request, int shifts)
{
	int size = request.size() - 1;				// ������� ���������� � ����
	double key = key_ToDouble(request);
	data_item ans, *p;
	size_t pos = bin_find(&s_dict[size], key);	// �������� ������� ������� ������� �������, ���������� ������ ������

	// ���������� ��������� � �������� ���������� �� ������� ����� �������, ������ ����
	rated_lists::iterator it = s_dict[size][pos].wordsTable.begin();
	list<data_item *>::iterator itt = it->_list.begin();
	for (int i = 0; i < shifts; i++)
	{
		if ( itt == --(it->_list.end()) )
		{
			it++;
			itt = it->_list.begin();
		}
		else itt++;
	}
	// �������� ��������� ������� � ������ ��������� �� ���� � list
	ans.word = (*itt)->word; ans.freq = ++((*itt)->freq);
	p = *itt; it->_list.erase(itt);

	// �������� ������� ���������������� ����� �� �������
	if ( (it == s_dict[size][pos].wordsTable.begin()) || ((--it)->freq != ans.freq) )	// ���� ��� ��� �������� ������ � freq = ans.freq
	{
		s_word_lists l; l._list.push_back(p); l.freq = ans.freq;
		s_dict[size][pos].wordsTable.insert(it, l);
	}
	else
	{
		itt = it->_list.begin();
		it->_list.insert(itt, p);
	}
	if ( ((++it) != s_dict[size][pos].wordsTable.end())&&(it->_list.empty()) ) s_dict[size][pos].wordsTable.erase(it);

	return ans.word;
}


int main()
{
	vector<data_item> database(50000);		// ������ �� ��� <������, �����>, � ������� �������� ������� ������

	// ������ �������
	int N; cin >> N;						// ������ ������ �������
	data_item temp;
	Dictionary dict;
	for (int i = 0; i < N; i++)
	{
		cin >> temp.word >> temp.freq;		// ������ ������ � ������� � database
		database[i] = temp;
		dict.read_word(&database[i]);
	}

	// ������������ ����������� �������
	dict.preprocess();

	// ������ ������� � �� ���� ������������ ������� ������
	string request, ans; int shifts;		// �������� ������, ����� � ����������� ������� �� �������
	while (cin >> request)
	{
		ans = ""; shifts = 0;
		while (*(--request.end()) == '*') request.erase(--request.end()), shifts++;
		if ( *(--request.end()) == '1' )	// ���� ��������� ���� ����������
		{
			switch (shifts)
			{
				case 0: ans += '.'; break;
				case 1: ans += ','; break;
				case 2: ans += '?'; break;
			}
			request.erase(--request.end()); shifts = 0;
			while (*(--request.end()) == '*') request.erase(--request.end()), shifts++;
		}
		ans = dict.get_word(request, shifts) + ans; cout << ans << ' ';
	}
	cout << endl;

	return 0;
}