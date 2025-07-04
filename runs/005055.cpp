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
	if(from == to)
		return 0;
	for(int i=0;i<data_count;i++)
	{
		if(data[i].begin == from && data[i].end == to)
			return data[i].len;
		if(data[i].begin == from && data[i].end != to && data[i].begin != data[i].end)
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
							bool zerro = false;
							int current_zerro_index = -1;
							int current_zerro_count = 0;
							for(int i=0; i < (nn-1); i++)
							{
								if(m[i].len == 0)
								{
									if(!zerro)
									{
										zerro= true;
										current_zerro_index = i;
									}
									current_zerro_count++;
								}
								if(m[i].begin > m[i].end)
								{
									int t = m[i].begin;
									m[i].begin = m[i].end;
									m[i].end = t;
								}
							}
							if(current_zerro_count>0)
							{
								int tmp_len = nn-1 + 1024;
								SHEAD *tmp = new SHEAD[tmp_len];
								for(int i = 0; i < (nn-1); i++)
								{
									tmp[i].begin = m[i].begin;
									tmp[i].end = m[i].end;
									tmp[i].len = m[i].len;
								}
								int tmp_tail_index = nn-1;
								for(int i =0; i < current_zerro_count; i++)
								{
									int next_zerro_index = 0;
									for(int j=0; j < (nn-1); j++)
									{
										if(m[j].len == 0 && next_zerro_index == 0 && current_zerro_index < next_zerro_index)
											next_zerro_index=j;
										if( ( m[current_zerro_index].end == m[j].begin && current_zerro_index != j)
											|| ( m[current_zerro_index].end == m[j].end && current_zerro_index != j)
											)
										{
											if(tmp_tail_index >= tmp_len)
											{
												SHEAD *t = new SHEAD[tmp_len+1024];
												for(int p=0;p<tmp_len;p++)
												{
													t[p].begin = tmp[p].begin;
													t[p].end = tmp[p].end;
													t[p].len = tmp[p].len;
												}
												tmp_len += 1024;
												tmp = t;
											}
											if( m[current_zerro_index].end == m[j].begin)
											{
												tmp[tmp_tail_index].begin = m[current_zerro_index].begin;
												tmp[tmp_tail_index].end = m[j].end;
											}else{
												tmp[tmp_tail_index].begin = m[j].begin;
												tmp[tmp_tail_index].end = m[current_zerro_index].begin;
											}
											tmp[tmp_tail_index].len = m[j].len;
											tmp_tail_index++;
										}
									}
									tmp[current_zerro_index].end = tmp[current_zerro_index].begin;
									current_zerro_index = next_zerro_index;
								}
								nn = tmp_tail_index;
								m=tmp;
								/*double code*/
								for(int i=0; i < (nn-1); i++)
								{
									if(m[i].begin > m[i].end)
									{
										int t = m[i].begin;
										m[i].begin = m[i].end;
										m[i].end = t;
									}
								}
							}
							for(int i=0; i < np; i++)
							{
								if(tops_numb[i].top_1 > tops_numb[i].top_2)
								{
									int t = tops_numb[i].top_1;
									tops_numb[i].top_1 = tops_numb[i].top_2;
									tops_numb[i].top_2 = t;
								}
							}
							for(int i=0; i < np; i++)
							{
								if(tops_numb[i].top_1 != tops_numb[i].top_2)
								{
									int l = _get_len(tops_numb[i].top_1,tops_numb[i].top_2,m,nn);
									if(l==0)
									{
										for(int j=0;j<nn;j++)
										{
											for(int k=j+1;k<nn;k++)
											{
												int l1 = 0;
												if(m[j].begin != tops_numb[i].top_2)
													l1 = _get_len(m[j].begin,tops_numb[i].top_2,m,nn);
												int l2 = 0;
												if(m[k].begin != tops_numb[i].top_2)
													l2 = _get_len(m[k].begin,tops_numb[i].top_2,m,nn);
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
								else{
									cout <<  0  << endl;
								}
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
