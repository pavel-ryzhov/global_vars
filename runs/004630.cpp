#include <cstdio>
#include <cstring>
#include <cctype>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

const int MaxWordLen = 20;// ������������ ����� �����
const int PackLen = (MaxWordLen+7)/8; // ���������� 32-������ ���� ����������� �������� ����������� �������� ������ ����� MaxWordLen (4 ���� �� �����)

const char Marks[] = {'.', ',', '?'};	
struct MapChar{// �������� ���� � ���� �� �����
	MapChar(){
		for(int t = '0'; t <= '9'; ++t) mp[t] = t - '0';
		for(int t = 'a'; t <= 'r'; ++t) mp[t] = (t - 'a')/3 + 2;
		mp['s'] = 7;
		for(int t = 't'; t <= 'y'; ++t) mp[t] = (t - 't')/3 + 8;
		mp['z'] = 9;		
	}
	int operator()(int n){return mp[n];}
	char mp[256];
};
MapChar Mapping;

class Words{//�������� ����� � �������� ������������� � ������������ �� � ��������� �������
public:
	void AddWord(char* word, int f){
		store.push_back(Data(word, f));// �������� ������
		table[Key(word)].push_back(&store.back());// ��������� ���������
	}

	void Preprocess(){// ������������� ������������� ����� � ������������ � �� ��������
		for(map<Key, vector<Data*> >::iterator it = table.begin(), end = table.end(); it != end; ++it){
			reverse(it->second.begin(), it->second.end());// ��������������, ����� �������� ������� ���� � ����������� ���������
			stable_sort(it->second.begin(), it->second.end(), Data::CmpPtr);
		}
	}// Preprocess()

	const char* GetWord(char* str, int n){// ��������� n-�� �� ���������� ����� � ������ ���������� ��� �������� ������ str � ���������� ������
		vector<Data*>& v = table[Key(str)];
		vector<Data*>::iterator new_it, it;
		it = v.end() - n - 1;// ������� ����� � ������������ � �����������
		// ���� ������� ����� � ������ ����� ������� � ����, ��� ��� ����� ������ � ������ � ������� ���������
		new_it = upper_bound(it, v.end(), &Data("", (*it)->f+1),  Data::CmpPtr) - 1;
		Data* d = *it;// ��������� ���������
		for( ; it != new_it; ++it) *it = *(it+1);// �������� ���������
		*it = d;// �������� ��������� �� ����� �����
		++d->f;// �������� ������� �����
		return d->word;
	}// GetWordAndUpdate()

private:
	struct Key{// ���� � table. (����������� �����)
		Key(const char* word){// ����������� ��������� �������� ���� � ���� � �������� ������������� � ����������� � ������ pack
			memset(pack, 0, sizeof(pack));
			unsigned d = 0;// ��� ��������
			int j = PackLen-1;// ������ � pack
			for(int shift = 0; *word; ++word, shift += 4){
				if(shift == 32)// d ��������� ��������
					pack[j--] = d, d = shift = 0;// ��������� � ��������� �������� � ������				
				d |= Mapping(*word) << shift;// �������� �������� ������� � ����������� ��� � 4 ����
			}
			pack[j] = d;// ���������� ���������� �����			
		}// Key()
		bool operator <(const Key& r) const{return lexicographical_compare(&pack[0], &pack[PackLen], &r.pack[0], &r.pack[PackLen]);}
		unsigned pack[PackLen];// ����������� �����. 
	};// struct Key

	struct Data{// ����� � ��� �������
		Data(const char* word_, int f_): f(f_){ strcpy(word, word_);}		
		static bool CmpPtr(const Data* l, const Data* r){ return l->f < r->f;}
		int f;		
		char word[MaxWordLen+1];
	};// struct Data

	deque<Data> store;// ������ ��� ���������
	map<Key, vector<Data*> > table;// �������� ����������� �������� ������ �� ������������� �� ����������� ������ ���������� ����
};// class Words

struct Lexan{// ������ ������� ������
	enum{WRD = 256, PUNKT_MARK};// ������������ ����� ������: ������, ���� ���������� ���� ��� ����� ��� ������
	struct Token{
		int type, stars;// ��� ������ � ���������� ��������� ����� ����
		vector<char> str;// ������, ���� type == WRD 
	};

	bool GetToken(Token& t){// ���������� true ���� ����� ������� �������, ��� false ���� ���������� ����� �����
		int c = getchar();
		if(isdigit(c)){// ���� ��� ������ ����� ��� ���� ����������
			if(c == '1'){// ���� ����������
				t.type = PUNKT_MARK, t.stars = 0;
				while((c = getchar()) == '*') ++t.stars;// ������������ ��������� ���� ��� ���� ����� �����
				ungetc(c, stdin);				
			}else{// �����. ��������� ��� ������� � ������������ �����������
				t.type = WRD, t.stars = 0; t.str.clear();
				do{
					t.str.push_back(c);
					c = getchar();
				}while(isdigit(c) && c != '1');
				t.str.push_back('\0');
				for( ; c == '*'; c = getchar()) ++t.stars;// ���� ����� ����� ���� ��������� - ������������ �� �����					 
				ungetc(c, stdin);				
			}//else �����
		}else if(c == EOF){
			return false;
		}else t.type = c;// ��������� ������� (������ ���� ������ ' ')		

		return true;
	}// GetToken()
};// struct Lexan

int main(){	
	int n, f;// ���������� ���� � �������
	char w[MaxWordLen+1];// �����
	Words W;// �������

	scanf("%d", &n);
	for(int i = 0; i < n; ++i){
		scanf("%s%d", &w, &f);
		W.AddWord(w, f);
	}
	W.Preprocess();	
	
	scanf("\n");// ��������� '\n' ��� ���������� ������ ������������ �����������
	Lexan Lex;//����������� ����������
	Lexan::Token t;
	while(Lex.GetToken(t)){// ��������� ������ ��������
		if(t.type == Lexan::WRD) printf("%s", W.GetWord(&t.str[0], t.stars));//�����
		else if(t.type == Lexan::PUNKT_MARK) printf("%c", Marks[t.stars]);//���� ����������
		else printf("%c", t.type);//������
	}
	puts("");
	return 0;
}
