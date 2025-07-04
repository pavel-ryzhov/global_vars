#include <iostream>
using namespace std;

struct tree_type
{
	int prew;
	int len;
	int points_to_root;
};

int main()
{
	int tree_size, beg, end, find_len, length, temp;
	tree_type *tree;

	cin >> tree_size;
	tree = new tree_type[tree_size + 1];
	tree[1].len = 0;
	tree[1].points_to_root = 0;
	tree[1].prew = 0;
	for (int i = 2; i <= tree_size; i++)
	{
		cin >> beg;
		cin >> end;
		cin >> tree[end].len;
		tree[end].points_to_root = tree[beg].points_to_root + 1;
		tree[end].prew = beg;;
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
			if (tree[beg].points_to_root < tree[end].points_to_root)
			{
				temp = beg;
				beg = end;
				end = temp;
			}
			while (tree[beg].points_to_root != tree[end].points_to_root)
			{
				length += tree[beg].len;
				beg = tree[beg].prew;
			}
			while (beg != end)
			{
				length += tree[beg].len;
				length += tree[end].len;
				beg = tree[beg].prew;
				end = tree[end].prew;
			}
			cout << length << endl;
		}
	}
	return 0;
}