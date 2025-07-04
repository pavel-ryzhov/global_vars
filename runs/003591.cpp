#include <iostream>
#include <algorithm>
#define tree_size 40001
using namespace std;

struct tree_type
{
	int len;
	int prev;
	int level;
	bool parent_exist;
};

struct vert
{
	int beg;
	int end;
	int len;
};

bool operator<(const vert &v1, const vert &v2)
{
	return v1.beg < v2.beg;
}

vert input[tree_size];
tree_type tree[tree_size];

int main()
{
	int tree_size_real, length, beg, end, temp, find_len; 

	cin >> tree_size_real;
	for (int i = 0; i < tree_size_real - 1; i++)
	{
		cin >> input[i].beg;
		cin >> input[i].end;
		cin >> input[i].len;
	}
	sort(input, input + tree_size_real - 1);
	beg = input[0].beg;
	end = input[0].end;
	tree[beg].len = 0;
	tree[beg].level = 0;
	tree[beg].prev = 0;
	tree[beg].parent_exist = false;
	tree[end].len = input[0].len;
	tree[end].level = tree[beg].level + 1;
	tree[end].prev = beg;
	tree[end].parent_exist = true;
	for (int i = 1; i < tree_size_real - 1; i++)
	{
		beg = input[i].beg;
		end = input[i].end;
		if (tree[end].parent_exist)
		{
			temp = beg;
			beg = end;
			end = temp;
		}
		tree[end].len = input[i].len;
		tree[end].level = tree[beg].level + 1;
		tree[end].prev = beg;
		tree[end].parent_exist = true;
	}
	cin >> find_len;
	for (int i = 0; i < find_len; i++)
	{
		cin >> beg;
		cin >> end;
		length = 0;
		if (beg == end)
		{
			cout << length << endl;
			continue;
		}
		else
		{
			if (tree[beg].level < tree[end].level)
			{
				temp = beg;
				beg = end;
				end = temp;
			}
			while (tree[beg].level != tree[end].level)
			{
				length += tree[beg].len;
				beg = tree[beg].prev;
			}
			while (beg != end)
			{
				length += tree[beg].len;
				length += tree[end].len;
				beg = tree[beg].prev;
				end = tree[end].prev;
			}
			cout << length << endl;
		}
	}
	return 0;
}
