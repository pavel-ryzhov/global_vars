#include <cstdio>
#include <cstring>
#include <cctype>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

const int MaxWordLen = 20;// Максимальная длина слова
const int PackLen = (MaxWordLen+7)/8; // Количество 32-битных слов достаточных хранения упакованной числовой строки длины MaxWordLen (4 бита на цифру)

const char Marks[] = {'.', ',', '?'};	
struct MapChar{// Проекция букв и цифр на числа
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

class Words{//Содержит слова с частотми встречаемости и поддерживает их в требуемом порядке
public:
	void AddWord(char* word, int f){
		store.push_back(Data(word, f));// Выделяем память
		table[Key(word)].push_back(&store.back());// Сохраняем указатель
	}

	void Preprocess(){// Первоначально упорядочивает слова в соответствии с их частотой
		for(map<Key, vector<Data*> >::iterator it = table.begin(), end = table.end(); it != end; ++it){
			reverse(it->second.begin(), it->second.end());// Переворачиваем, чтобы изменить порядок слов с одинаковыми частотами
			stable_sort(it->second.begin(), it->second.end(), Data::CmpPtr);
		}
	}// Preprocess()

	const char* GetWord(char* str, int n){// Получение n-го по приоритету слова в списке подходящих под цифровую строку str и обновление списка
		vector<Data*>& v = table[Key(str)];
		vector<Data*>::iterator new_it, it;
		it = v.end() - n - 1;// Находим слово в соответствии с приоритетом
		// Ищем позицию слова с учетом новой частоты и того, что оно будет первым в списке с равными частотами
		new_it = upper_bound(it, v.end(), &Data("", (*it)->f+1),  Data::CmpPtr) - 1;
		Data* d = *it;// Сохраняем указатель
		for( ; it != new_it; ++it) *it = *(it+1);// Сдвигаем указатели
		*it = d;// Копируем указатель на новое место
		++d->f;// Изменяем частоту слова
		return d->word;
	}// GetWordAndUpdate()

private:
	struct Key{// Ключ в table. (Упакованное слово)
		Key(const char* word){// Конструктор выполняет проекцию букв и цифр в числовое представление и упаковывает в массив pack
			memset(pack, 0, sizeof(pack));
			unsigned d = 0;// Для упаковки
			int j = PackLen-1;// Индекс в pack
			for(int shift = 0; *word; ++word, shift += 4){
				if(shift == 32)// d полностью заполено
					pack[j--] = d, d = shift = 0;// Сохраняем и обновляем смещение и индекс				
				d |= Mapping(*word) << shift;// Получаем проекцию символа и упаковываем его в 4 бита
			}
			pack[j] = d;// Записываем оставшуюся часть			
		}// Key()
		bool operator <(const Key& r) const{return lexicographical_compare(&pack[0], &pack[PackLen], &r.pack[0], &r.pack[PackLen]);}
		unsigned pack[PackLen];// Упакованное число. 
	};// struct Key

	struct Data{// Слово и его частота
		Data(const char* word_, int f_): f(f_){ strcpy(word, word_);}		
		static bool CmpPtr(const Data* l, const Data* r){ return l->f < r->f;}
		int f;		
		char word[MaxWordLen+1];
	};// struct Data

	deque<Data> store;// Память под структуры
	map<Key, vector<Data*> > table;// Проекция упакованной числовой строки на упорядоченный по приоритетам список подходящих слов
};// class Words

struct Lexan{// Разбор входной строки
	enum{WRD = 256, PUNKT_MARK};// Перечисление типов токена: строка, знак пунктуации либо это будет сам символ
	struct Token{
		int type, stars;// Тип токена и количество звездочек после него
		vector<char> str;// Строка, если type == WRD 
	};

	bool GetToken(Token& t){// Возвращает true если токен успешно получен, или false если встретился конец файла
		int c = getchar();
		if(isdigit(c)){// Если это начало слова или знак пунктуации
			if(c == '1'){// Знак пунктуации
				t.type = PUNKT_MARK, t.stars = 0;
				while((c = getchar()) == '*') ++t.stars;// Подсчитываем звездочки если они есть после знака
				ungetc(c, stdin);				
			}else{// Слово. Считываем его целиком с завершающими звездочками
				t.type = WRD, t.stars = 0; t.str.clear();
				do{
					t.str.push_back(c);
					c = getchar();
				}while(isdigit(c) && c != '1');
				t.str.push_back('\0');
				for( ; c == '*'; c = getchar()) ++t.stars;// Если после слова есть звездочки - подсчитываем их число					 
				ungetc(c, stdin);				
			}//else слово
		}else if(c == EOF){
			return false;
		}else t.type = c;// Остальные символы (Должен быть символ ' ')		

		return true;
	}// GetToken()
};// struct Lexan

int main(){	
	int n, f;// Количество слов и частота
	char w[MaxWordLen+1];// Слово
	Words W;// Словарь

	scanf("%d", &n);
	for(int i = 0; i < n; ++i){
		scanf("%s%d", &w, &f);
		W.AddWord(w, f);
	}
	W.Preprocess();	
	
	scanf("\n");// Считываем '\n' для нормальной работы лексичесокго анализатора
	Lexan Lex;//Лексический анализатор
	Lexan::Token t;
	while(Lex.GetToken(t)){// Разбираем строку запросов
		if(t.type == Lexan::WRD) printf("%s", W.GetWord(&t.str[0], t.stars));//Слово
		else if(t.type == Lexan::PUNKT_MARK) printf("%c", Marks[t.stars]);//Знак пунктуации
		else printf("%c", t.type);//Пробел
	}
	puts("");
	return 0;
}
