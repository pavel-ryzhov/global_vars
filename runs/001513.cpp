#include <string>
#include <memory>
#include <vector>
#include <map>
#include <iostream>

int parseInt(const std::string& from) {
	// считаем что данные хорошие
	int result = from[0] - '0';
	for(size_t i = 1; i < from.length(); i++) {
		result = result * 10 + (from[i] - '0');
	}
	return result;
}

std::auto_ptr< std::vector< std::string > > separateString(const std::string& src) {
	std::auto_ptr< std::vector< std::string > > result(new std::vector< std::string >());
	size_t off = 0;
	while(off < src.length()) {
		size_t off2 = off;
		// пропускаем пробелы
		for(; off2 < src.length() && src[off2] == ' '; off2++);
		if(off != off2) {
			result->push_back(src.substr(off, off2 - off));
			off = off2;
			continue;
		}
		off = off2 + 1;
		for(; off < src.length() && src[off] != ' '; off++);
		result->push_back(src.substr(off2, off - off2));
	}
	return result;
}

std::auto_ptr< std::vector< std::string > > separateString2(const std::string& src) {
	std::auto_ptr< std::vector< std::string > > result(new std::vector< std::string >());
	size_t off = 0;
	while(off < src.length()) {
		size_t off2 = off;
		// пропускаем пробелы
		for(; off2 < src.length() && src[off2] == ' '; off2++);
		if(off != off2) {
			result->push_back(src.substr(off, off2 - off));
			off = off2;
			continue;
		}
		off = off2 + 1;
		if(src[off2] != '1') {
			for(; off < src.length() && src[off] != ' ' && src[off] != '1'; off++);
		} else {
			for(; off < src.length() && src[off] == '*'; off++);
		}
		result->push_back(src.substr(off2, off - off2));
	}
	return result;
}

int getButton(char ch) {
	// даем хорошие данные
	// на неправильность не проверяем
	if(ch >= 'a' && ch <= 'c') {
		return 2;
	} else if(ch >= 'd' && ch <= 'f') {
		return 3;
	} else if(ch >= 'g' && ch <= 'i') {
		return 4;
	} else if(ch >= 'j' && ch <= 'l') {
		return 5;
	} else if(ch >= 'm' && ch <= 'o') {
		return 6;
	} else if(ch >= 'p' && ch <= 's') {
		return 7;
	} else if(ch >= 't' && ch <= 'v') {
		return 8;
	} else {
		return 9;
	}
}

struct word {
	int count;
	std::string text;
	word(const std::string& txt, int x) : count(x), text(txt) {}
	void inline operator++ (int) {count++;}
	void inline operator++ () {count++;}
};

class a_tree {
public:
	class ptr {
	public:
		a_tree* value() const {return _value;}
		ptr() : _value(new a_tree()) {};
	private:
		a_tree* _value;
	};

	// слово выбирается по спецпоследовательностям, например "123" или "123**"
	std::string get(const std::string& src);
	// сюда вставляется слово в нормальном формате, например ("robot", 1) или ("back", 3)
	void insert(const std::string& what, int howMuch);

	~a_tree();
private:
	typedef std::map< int, ptr > a_childs;
	typedef std::vector< word > a_words;

	a_childs childs;
	a_words words;
};

int main() {
// 	std::auto_ptr< std::vector< std::string > > result = separateString("86 23* 67 66811 86 231**");
// 	for(size_t x = 0; x < result->size(); x++) {
// 		std::cout << result->at(x) << std::endl;
// 	}
	a_tree t9;

	bool first = true;
	char* s_buffer = new char[100001];
	std::string buffer;
	int count = 0;
	int total;
	while(std::cin.good() && !std::cin.fail()) {
		std::cin.getline(s_buffer, 100001);
		buffer.assign(s_buffer);
		if(first) {
			total = parseInt(buffer);
			first = false;
		} else {
			if(count < total) {
				std::auto_ptr< std::vector< std::string > > tmp = separateString(buffer);
				t9.insert(tmp->at(0), parseInt(tmp->at(2)));
				count++;
			} else {
				std::auto_ptr< std::vector< std::string > > tmp = separateString2(buffer);
				for(size_t x = 0; x < tmp->size(); x++) {
					std::string& what = tmp->at(x);
					if(what[0] == ' ') { // пробельная строка
						std::cout << what;
					} else if(what[0] == '1') { // знак препинания
						if(what.length() == 1) { // точка ("1")
							std::cout << '.';
						} else if(what.length() == 2) { // запятая ("1*")
							std::cout << ',';
						} else { // вопросительный знак ("1**")
							std::cout << '?';
						}
					} else { // нужен t9
						std::cout << t9.get(what);
					}
				}
				break;
			}
		}
	}
	delete s_buffer;

// 	a_tree all;
// 	all.insert("act", 1);
// 	all.insert("bat", 1);
// 	all.insert("cat", 1);
// 	std::cout << all.get("228*") << std::endl;
// 	std::cout << all.get("228**") << std::endl;
// 	std::cout << all.get("228**") << std::endl;
// 	std::cout << all.get("228**") << std::endl;
	return 0;
}

std::string a_tree::get(const std::string& src) {
	// на правильность ввода не проверяем, считаем что все нормально

	int off = 0;
	int len = src.length();
	a_tree* node = this;
	while(off != len && src[off] != '*') {
		node = node->childs[int(src[off++] - '0')].value();
	}
	int offset = len - off;
	int count = ++node->words[offset].count;
	std::string result = node->words[offset].text;
	while(offset > 0 && node->words[offset - 1].count <= count) {
		node->words[offset - 1].count = count;
		node->words[offset - 1].text.swap(node->words[offset].text);
		offset--;
	}

	return result;
}

void a_tree::insert(const std::string& what, int howMuch) {
	// на дублирование не проверяем, считаем что данные хорошие
	int off = 0;
	int len = what.length();
	a_tree* node = this;
	while(off != len) {
		node = node->childs[getButton(what[off++])].value();
	}
	std::string s_buff = what;
	int i_buff = howMuch;
	for(size_t x = 0; x < node->words.size(); x++) {
		int i_buff2 = node->words[x].count;
		if(i_buff2 < i_buff || (i_buff2 == i_buff && what < node->words[x].text)) {
			while(x < node->words.size()) {
				i_buff2 = node->words[x].count;
				node->words[x].text.swap(s_buff);
				node->words[x].count = i_buff;
				i_buff = i_buff2;
				x++;
			}
		}
	}
	node->words.push_back(word(s_buff, i_buff));
}

a_tree::~a_tree() {
	for(a_childs::const_iterator i = childs.begin(); i != childs.end(); i++) {
		delete i->second.value();
	}
}
