#include <iostream>
#include <fstream>
#include <sstream>

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

unsigned int  _get_len(int from, int to, SHEAD *data, int data_count)
{
	unsigned int len=0;
	for(int i=0;i<data_count;i++)
	{
		if(data[i].begin == from && data[i].end == to)
			return data[i].len;
		if(data[i].begin == from)
		{
			len = _get_len(data[i].end,to,data,data_count);
			if(len>0) 
				return data[i].len + len;
		}
	}
	
	return len;
}

int main(int argc, char **argv)
{
	if(argc < 2){
		cout << "Usage: " << argv[0] << " [input file]" << endl;
		return 1;
	};
	char *in_file_name = argv[1];
	char mas[200];
	std::ifstream in(in_file_name, std::ios::binary);
    ostringstream out;           
    out << in.rdbuf(); 

    string s;
    out.str().swap(s); 

	int nn = 0;
	int fpos = 0;
	for(int i = 0; i<s.length(); i++)
	{
		fpos++;
		char c = s[i];
		if(s[i] >= '\x30' && s[i] <= '\x39'){
			nn *=10;
			nn += c - 0x30;
		}
		else 
			break;
	}
	if(nn<=0){
		cout << "Error n"<< endl;
		return 2;
	}
	SHEAD *m = new SHEAD[nn];
	int m_i = 0;
	int h = 0;
	m[0].begin=0;
	m[0].end=0;
	m[0].len=0;
	bool p = false;
	for(int i=fpos; i < s.length(); i++,fpos++)
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
		else if(p)
		{
				m_i++;
				p = false;
		}
		if(m_i >= 3)
		{
			m_i=0;
			h++;
			if(h>=(nn-1)) break;
			m[h].begin=0;
			m[h].end=0;
			m[h].len=0;
			m[h].total=0;
		}
	}
	int np = 0;
	p =false;
	for(int i = fpos; i<s.length(); i++)
	{
		fpos++;
		char c = s[i];
		if(s[i] >= '\x30' && s[i] <= '\x39'){
			np *=10;
			np += c - 0x30;
			p = true;
		}
		else if(p)
			break;
	}

	SPAIR *tops_numb = new SPAIR[np];
	m_i = 0;
	h = 0;
	tops_numb[0].top_1=0;
	tops_numb[0].top_2=0;
	p = false;
	for(int i=fpos; i < s.length(); i++,fpos++)
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
		if(m_i >= 2)
		{
			m_i=0;
			h++;
			if(h>=(np)) break;
			tops_numb[h].top_1=0;
			tops_numb[h].top_2=0;
		}
	}
	for(int i=0; i < nn; i++)
	{
		if(m[i].begin > m[i].end)
		{
			int t = m[i].begin;
			m[i].begin = m[i].end;
			m[i].end = t;
		}
	}
	for(int i=0; i < np; i++)
	{
		int l = _get_len(tops_numb[i].top_1,tops_numb[i].top_2,m,nn);
		if(l==0)
		{
			for(int j=0;j<nn;j++)
			{
				for(int k=j+1;k<nn;k++)
				{
					int l1 = _get_len(m[j].begin,tops_numb[i].top_2,m,nn);
					int l2 = _get_len(m[k].begin,tops_numb[i].top_2,m,nn);
					if(l1!=0 && l2!=0)
					{
						cout << l1+l2<< endl;
						j=k=nn;
					}
				}
			}
		}else
			cout <<  l  << endl;
	}

	return 0;
}