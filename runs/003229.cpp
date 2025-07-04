#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
//#include <fstream> //////////////////////////////////////////
//#include <time.h> /////////////////////////////

using namespace std;

void matr_view (vector <pair <int, int> >&, int, int);

int main (void)
{
	int numb_dots = 0,numb_pairs = 0, root = 0;

	// Generating graph, prepocessing
//	ifstream cin1("ttt2.txt");
	cin >> numb_dots;
	vector <pair <int, int> > m_vector(numb_dots);

//	matr_view(m_vector,numb_dots, root );

	for (int i = numb_dots; i > 1; i--) {
		int v_to, v_from, length;
		cin >> v_to >> v_from >> length ;

		if (!(m_vector [v_from-1].second)) {
			m_vector [v_from-1].first = length;
			m_vector [v_from-1].second = v_to;
		} else if (!(m_vector [v_to-1].second)){
			m_vector [v_to-1].first = length;
			m_vector [v_to-1].second = v_from;
		} else {
			int temp1 = v_from, temp2 = v_to, temp3 = v_to, temp4 =0, temp5 = length, temp6 = 0;
			while ((m_vector[temp1 - 1].second)) {
				temp2 = temp1; 
				temp4 = m_vector[temp1 - 1].second; 
				temp6 = m_vector[temp1 - 1].first;

				m_vector[temp1 - 1].second = temp3; 
				m_vector[temp1 - 1].first = temp5; 

				temp3 = temp2;
				temp5 = temp6;
				temp1 = temp4;
			}
			m_vector [temp1 -1].first = temp5;
			m_vector [temp1 -1].second = temp3;

		}

	}
	for (int i = 0; i < numb_dots; i++) {
		if (!(m_vector[i].first)){
			root = i +1;
			break;
		}
	}

	matr_view(m_vector,numb_dots, root );

	// Finding shortest ways
	cin >> numb_pairs;
	for (numb_pairs; numb_pairs > 0; numb_pairs--) {
		int top1, top2, ptr, path = 0, temp = 0;
		string path1,path2;
		cin >> top1 >> top2;
		ptr = top1;
		while (ptr) {
			path1.push_back('0' + ptr);
			ptr = m_vector[ptr-1].second;
		}
		ptr = top2;
		while (ptr) {
			path2.push_back('0' + ptr);
			ptr = m_vector[ptr-1].second;
		}
		path1.push_back('0' + root);
		path2.push_back('0' + root);

//		cout <<endl << path1 << ' ' << path2 << endl;

		string::reverse_iterator it1, it2;
		it1 = path1.rbegin();
		it2 = path2.rbegin();

		while ((it1!=path1.rend()) && (it2!=path2.rend())&& (*it1) == (*it2)){
			it1++;
			it2++;
		}

		for (it1; it1 != path1.rend(); it1++ ) {
			path+= m_vector[(*it1) - '1'].first;

		}
		for (it2; it2 != path2.rend(); it2++ ) {
			path+= m_vector[(*it2) - '1'].first;

		}
		cout << path << endl;
	}


	return 0 ;
}

void matr_view (vector <pair <int, int> >& m_vector, int numb_dots, int root) 
{
	for (int i = 0; i < numb_dots; i++) {
		cout << i+ 1 << "->" << m_vector[i].first << "->" << m_vector[i].second << endl;
	}
	cout << "Root =" << root << endl;
	return;
}