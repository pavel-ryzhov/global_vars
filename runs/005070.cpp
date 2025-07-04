#include <iostream>
#include <fstream>
#include <sstream>
//#include <vector>

using namespace std;

typedef struct{
	int begin;
	int end;
	int len;
	int total;
} SHEAD;

typedef struct{
	int top_1;
	int top_2;
} SPAIR;


class CHEAD{
public:
	int begin;
	int end;
	int len;
public:
	CHEAD():begin(0), end(0), len(0) {};
	CHEAD(int a,int b,int c){begin=a;end=b;len=c;};
	CHEAD(SHEAD &r){begin = r.begin;end = r.end;len = r.len;};
	CHEAD(CHEAD *r){begin = r->begin;end = r->end;len = r->len;};
	/*CHEAD &operator=(CHEAD &r){
		begin = r.begin;
		end = r.end;
		len = r.len;
		return *this;
	};*/
	CHEAD *operator=(CHEAD *r){
		begin = r->begin;
		end = r->end;
		len = r->len;
		return this;
	};
};

//vector <vector<CHEAD>> g;
//vector <CHEAD> vert_info;
/*
unsigned int _get_next_vert_count(vector <CHEAD>&vert, int from)
{
	unsigned int rez = 0;
	int vert_coun = vert.size();
	for(int i=0;i<vert_coun;i++)
	{
		if(vert[i].begin = from && vert[i].len != 0)
			rez++;
	}
	return rez;
}
*/
/*
1 2
4 2
7 2
3 4
3 6
5 6
*/
/*
2 1 3
2 4 4
2 7 6
4 3 1
6 3 3
6 5 1
7-5
R1234567
1-3-----
23--4--6
3---1-3-
4-41----
5-----1X
6--3-1--
7-6--X--

*/



 unsigned int _get_non_empty_vert_count(int vert, CHEAD* data, int data_len)
 {
	 int rez = 0;
	 for(int i=0;i<data_len;i++)
		 if((data[i].begin == vert || data[i].end == vert) && data[i].len !=0) 
			 rez++;
	return rez;
 }

 int resize(CHEAD* data, int data_len, int new_len)
 {
	if(data_len >= new_len) return data_len;
		CHEAD *tmp = new CHEAD[new_len];
		for(int i = 0; i < (data_len-1); i++)
			tmp[i] = data[i];
	return new_len;
 }

 int is_full(int data_len, int ptr, int inc)
 {
	return ptr + inc >= data_len;
 }

 int _join_alias(CHEAD* data,int part_check, int data_len, int vert, int alias)
 {
	 int ptr = 0;
	 int len = data_len;
	 if(is_full(data_len,len,data_len))
	 {
		 data_len = resize(data, data_len, data_len + 100);
	 }
	 ptr = len;
	 for(int i=0; i < part_check;i++)
	 {
		 if(data[i].begin == alias && data[i].len !=0)
		 {
			 data[ptr].begin = vert;
			 data[ptr].end = data[i].end;
			 data[ptr].len = data[i].len;
			 ptr++;
		 }
		 if(data[i].end == alias && data[i].len !=0)
		 {
			 data[ptr].begin = vert;
			 data[ptr].end = data[i].begin;
			 data[ptr].len = data[i].len;
			 ptr++;
		 }

	 }
	 return ptr;
 }

 int  _check_alias(CHEAD* data, int data_len){
	int nn = data_len;
	int dlen=nn;
	for(int i=0; i < (nn-1); i++)
	{
		if(data[i].len == 0)
		{
			//int l1 = _get_non_empty_vert_count(data[i].begin,data,nn-1);
			//int l2 = _get_non_empty_vert_count(data[i].end,data,nn-1);

			dlen = _join_alias(data,nn-1,dlen, data[i].begin, data[i].end);
			dlen = _join_alias(data,nn-1, dlen, data[i].end, data[i].begin);
		}
	}
	return dlen;
}

 unsigned int _get_path_from(int from, int to, CHEAD* data, int data_len)
{
	//cout << "from:" << from << " to:" << to << endl;
	if(from == to) return 0;

	int *root_v = new int[data_len];
	int root_v_index = 0;
	int v_count = data_len;
	CHEAD *new_data = new CHEAD[1024];
	int new_data_ptr=0;
	int mask_ptr=0;
	for(int i=0;i<v_count;i++)
	{
		if((data[i].begin == from || data[i].end == from) && data[i].len !=0 )
		{
			root_v[root_v_index] = i;
			root_v_index++;
		}else{
			new_data[new_data_ptr] = data[i];
			new_data_ptr++;
		}
		if((data[i].begin == from && data[i].end == to) || (data[i].begin == to && data[i].end == from))
			return data[i].len;
	}

	int l =0;
	for(int i=0;i<root_v_index;i++)
	{
		int ptr = root_v[i];
		l = data[ptr].len;
		int b=data[ptr].begin;
		int e=data[ptr].end;
		int ll = 0;
		if(data[ptr].begin == from)
		{
			ll = _get_path_from(e, to, new_data, new_data_ptr);
		}
		else
		{
			ll = _get_path_from(b, to, new_data, new_data_ptr);
		}
		if(ll>0)
			return l+ll;
	}
	return 0;
}

unsigned int  _get_len(int from, int to, SHEAD *data, int data_count, int middle, int iter_level)
{
	unsigned int len=0;
	if(iter_level >=data_count)
		return 0;
	if(from == to)
		return 0;
	for(int i=0;i<data_count;i++)
	{
		if(i != middle)
		{
			if(data[i].begin == from && data[i].end == to)
				return data[i].len;
			if(data[i].begin == from && data[i].end != to && data[i].begin != data[i].end)
			{
				len = _get_len(data[i].end,to,data,data_count,i,iter_level+1);
				if(len>0) 
					return data[i].len + len;
			}
			else if(data[i].end == from && data[i].begin != to && data[i].begin != data[i].end,i)
			{
				len = _get_len(data[i].begin,to,data,data_count,-1,iter_level+1);
				if(len>0) 
					return data[i].len + len;
			}
		}
	}
	
	return len;
}

int main(int argc, char **argv)
{
	string s;
	bool line_empty = true;
	int block=1;
	int nn = 0;
	int np = 0;
	SHEAD *m =0;
	SPAIR *tops_numb = 0;
	bool exit = false;
	int m_i = 0;
	int h = 0;
	bool end = false;
	while (getline(std::cin, s) || exit)
    {
		switch(block)
		{
		case 1:
			{
				for(int i = 0; i<s.length(); i++)
				{
					char c = s[i];
					if(s[i] >= '\x30' && s[i] <= '\x39'){
						nn *=10;
						nn += c - 0x30;
					}
					else 
						break;
				}
				if(nn<=1 && !end){
					cout << 0 << endl;
					end = true;
					//return 0;
				}
				block++;
				break;
			}
		case 2:{
				if(m==0)
				{
					m = new SHEAD[nn];
					m[0].begin=0;
					m[0].end=0;
					m[0].len=0;
				}
					bool p = false;
					for(int i=0; i < s.length(); i++)
					{
						char c = s[i];
						if(s[i] >= '\x30' && s[i] <= '\x39')
						{
							p = true;
							switch(m_i)
							{
								case 0:{
									m[h].begin *= 10;
									m[h].begin += c - 0x30;
									break;
								}
								case 1:{
									m[h].end *= 10;
									m[h].end += c - 0x30;
									break;
								}
								case 2:{
									m[h].len *= 10;
									m[h].len += c - 0x30;
									break;
								}
							}
						}
						else if(p )
						{
								m_i++;
								p = false;
						}
						if(m_i >= 3 || (s.length()-1) == i)
						{
							m_i=0;
							h++;
							//if(s.length() == i){}
							m[h].begin=0;
							m[h].end=0;
							m[h].len=0;
							m[h].total=0;
						}
					}
					if(h>=(nn-1))
						block++;
					break;
			   }
		case 3:{
				bool p = false;
				for(int i = 0; i<s.length(); i++)
				{
					char c = s[i];
					if(s[i] >= '\x30' && s[i] <= '\x39'){
						np *=10;
						np += c - 0x30;
						p = true;
					}
					else if(p)
						break;
				}
				if(np<=0){
					cout << 0 << endl;
					return 0;
				}
				h = 0;
				m_i = 0;
				block++;
				break;
			}
		case 4:{
				bool p = false;
				if(tops_numb ==0)
				{
					tops_numb = new SPAIR[np];
					tops_numb[0].top_1=0;
					tops_numb[0].top_2=0;
				}
				p = false;
				for(int i=0; i < s.length(); i++)
				{
					char c = s[i];
					if(s[i] >= '\x30' && s[i] <= '\x39')
					{
						p = true;
						switch(m_i)
						{
							case 0:{
								tops_numb[h].top_1 *= 10;
								tops_numb[h].top_1 += c - 0x30;
								break;
							}
							case 1:{
								tops_numb[h].top_2 *= 10;
								tops_numb[h].top_2 += c - 0x30;
								break;
							}
						}
					}
					else if(p)
					{
							m_i++;
							p = false;
					}
					if(m_i >= 2 || s.length()-1 == i)
					{
						m_i=0;
						h++;
						if(h>=(np)) {
							/*code*/

							CHEAD *data = new CHEAD[nn];
							for(int v_x=0; v_x< nn-1; v_x++)
							{
								data[v_x] = (CHEAD)m[v_x];
							}
							int new_len = _check_alias(data, nn-1);
							nn = new_len+1;
							int ll = 0;
							for(int i=0; i < np; i++)
							{
								if(tops_numb[i].top_1 == tops_numb[i].top_2)
									ll = 0;
								else
									ll = _get_path_from(tops_numb[i].top_1,tops_numb[i].top_2, data, nn-1);

								cout <<  ll  << endl;
							}
							
							/**/
							end = true;
							block=1;
						}
						tops_numb[h].top_1=0;
						tops_numb[h].top_2=0;
					}
				}
				break;
			}
		default:
			block=1;
		}
	}

	return 0;
}
