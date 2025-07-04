#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::pair;

void TreeDFS (int top,
							int parent,
							int &time,
							const vector< vector< pair<int, int> > > &tree_ribs,
							vector<int> *times_in,
							vector<int> *times_out,
							vector<bool> &visited_tops,
							vector < vector<int> > &upper_tops,
							vector<unsigned int> &distances_to_root
						 )
{
	visited_tops[top] = true;
	(*times_in)[top] = ++time;
	upper_tops[top][0] = parent;

	for (unsigned int i = 1; i < upper_tops[0].size(); ++i)	//we should do this operation log(N) times
		upper_tops[top][i] = upper_tops[ upper_tops[top][i - 1] ][i - 1];

	for (unsigned int i = 0; i < tree_ribs[top].size(); ++i)
	{
		int top_to_visit = tree_ribs[top][i].first;
		if (!visited_tops[top_to_visit])
		{
			distances_to_root[top_to_visit] = distances_to_root[top] + tree_ribs[top][i].second;
			TreeDFS(top_to_visit, top, time, tree_ribs, times_in, times_out, visited_tops, upper_tops, distances_to_root);
		}
	}
	(*times_out)[top] = ++time;
}

bool IsUpper (int top1, int top2, const vector<int> &times_in, const vector<int> &times_out)
{
	return times_in[top1] <= times_in[top2] && times_out[top1] >= times_out[top2];
}

int LCA (int top1,
				 int top2,
				 const vector<int> &times_in, 
				 const vector<int> &times_out, 
				 const vector < vector<int> > &upper_tops)
{
	if (IsUpper(top1, top2, times_in, times_out))
		return top1;
	if (IsUpper(top2, top1, times_in, times_out))
		return top2;

	for (int upper_top_index = upper_tops[0].size() - 1; upper_top_index >= 0; --upper_top_index)
		if (!IsUpper(upper_tops[top1][upper_top_index], top2, times_in, times_out))
			top1 = upper_tops[top1][upper_top_index];
	return upper_tops[top1][0];
}

void Input(vector< vector< pair<int, int> > > *tree_ribs, vector< pair<int, int> > *requests)
{
	int tops_quantity;
	cin >> tops_quantity;
	tree_ribs->resize(tops_quantity);
	for (int i = 0; i < tops_quantity - 1; ++i)
	{
		int top_from, top_to, rib_length;
		cin >> top_from >> top_to >> rib_length;
		--top_from;
		--top_to;
		(*tree_ribs)[top_from].push_back(pair<int, int>(top_to, rib_length));
		(*tree_ribs)[top_to].push_back(pair<int, int>(top_from, rib_length));
	}
	int requests_quantity;
	cin >> requests_quantity;
	for (int i = 0; i < requests_quantity; ++i)
	{
		int top_from, top_to;
		cin >> top_from >> top_to;
		--top_from;
		--top_to;
		requests->push_back(pair<int, int>(top_from, top_to));
	}
}

int main()
{
	vector< vector< pair<int, int> > > tree_ribs;
	vector< pair<int, int> > requests;
	Input(&tree_ribs, &requests);
	int tops_quantity = tree_ribs.size();


	vector<int> times_in(tops_quantity);
	vector<int> times_out(tops_quantity);
	vector<bool> visited_tops(tops_quantity, false);
	vector<unsigned int> distances_to_root(tops_quantity);
	distances_to_root[0] = 0;

	vector < vector<int> > upper_tops(tops_quantity);
	unsigned int log_tops_quantity = 1;
	while (1 << log_tops_quantity <= tops_quantity)
		++log_tops_quantity;

	for (int i = 0; i < tops_quantity; ++i)
		upper_tops[i].resize (log_tops_quantity + 1);

	int time = 0;
	TreeDFS(0, 0, time, tree_ribs, &times_in, &times_out, visited_tops, upper_tops, distances_to_root);

	for (vector< pair<int, int> >::iterator it = requests.begin(); it != requests.end(); ++it)
	{
		int lca = LCA(it->first, it->second, times_in, times_out, upper_tops);
		unsigned int answer = distances_to_root[it->first] - distances_to_root[lca] + \
													distances_to_root[it->second] - distances_to_root[lca];
		cout << answer << endl;
	}
}


