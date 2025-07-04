#include <string>
#include <memory>
#include <vector>
#include <iostream>

class list {
public:
	list(const std::string& word, int count, list* parent = NULL, list* next = NULL) :
	  _word(word), _count(count), _prev(parent), _next(next) {
	 };
	~list() {delete _next;}

	list* prev() const {return _prev;}
	list* next() const {return _next;}

	const std::string& word() const {return _word;}
	int count() const {return _count;}
	int countPlus() {return ++_count;}

	void insertAfter(const std::string& word, int count) {
		list* newOne = new list(word, count, this, this->next());
		if(this->_next != NULL) {
			this->_next->_prev = newOne;
		}
		this->_next = newOne;
	}

	list* insertBefore(const std::string& word, int count) {
		list* newOne = new list(word, count, this->_prev, this);
		if(this->_prev != NULL) {
			this->_prev->_next = newOne;
		}
		this->_prev = newOne;
		return newOne;
	}

	friend void moveBefore(list* first, list* last);
private:
	int _count;
	std::string _word;

	list* _prev;
	list* _next;
};

void moveBefore(list* first, list* last) {
	list* begin1 = first->_prev;
	list* begin2 = last->_prev;
	list* end2 = last->_next;
	
	if(begin1 != NULL) {
		begin1->_next = last;
	}
	last->_prev = begin1;
	last->_next = first;
	first->_prev = last;
	
	begin2->_next = end2;
	if(end2 != NULL) {
		end2->_prev = begin2;
	}
};

class section_queue {
public:
	section_queue() : _front(NULL), _end(NULL) {}

	struct section {
		section* next;
		size_t from;
		size_t to;
		section(size_t f, size_t t) : from(f), to(t), next(NULL) {}
	};

	section* front() const {return _front;}

	void insert(size_t from, size_t to) {
		if(_front == NULL) {
			_front = _end = new section(from, to);
		} else {
			_end = _end->next = new section(from, to);
		}
	}

	bool empty() const {return _front == NULL;}

	void next() {
		section* tmp = _front->next;
		delete _front;
		_front = tmp;
	}

	~section_queue() {
		section* tmp;
		while(_front != NULL) {
			tmp = _front->next;
			delete _front;
			_front = tmp;
		}
	}
private:
	section* _front;
	section* _end;
};

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
		for(; off2 < src.length() && src[off2] == ' '; off2++);
		off = off2 + 1;
		for(; off < src.length() && src[off] != ' '; off++);
		result->push_back(src.substr(off2, off - off2));
	}
	return result;
}

std::auto_ptr< section_queue > separateString2(const std::string& src) {
	std::auto_ptr< section_queue > result(new section_queue());
	size_t off = 0;
	while(off < src.length()) {
		size_t off2 = off;
		// пропускаем пробелы
		for(; off2 < src.length() && src[off2] == ' '; off2++);
		if(off != off2) {
			result->insert(off, off2);
			off = off2;
			continue;
		}
		off = off2 + 1;
		if(src[off2] != '1') {
			for(; off < src.length() && src[off] != ' ' && src[off] != '1'; off++);
		} else {
			for(; off < src.length() && src[off] == '*'; off++);
		}
		result->insert(off2, off);
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

class a_tree {
public:
	// слово выбирается по спецпоследовательностям, например "123" или "123**"
	std::string get(const std::string& src, size_t from, size_t to);
	// сюда вставляется слово в нормальном формате, например ("robot", 1) или ("back", 3)
	void insert(const std::string& what, int howMuch);

	a_tree();
	~a_tree();
private:
	a_tree* childs[8];
	list* words;
};

int main() {
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
				t9.insert(tmp->at(0), parseInt(tmp->at(1)));
				count++;
			} else {
				std::auto_ptr< section_queue > tmp = separateString2(buffer);
				std::string result;
				while(!tmp->empty()) {
					section_queue::section* section = tmp->front();
					char ch = buffer[section->from];
					size_t length = section->to - section->from;
					if(ch == ' ') { // пробельная строка
						result += std::string(length, ' ');
					} else if(ch == '1') { // знак препинания
						if(length == 1) { // точка ("1")
							result += '.';
						} else if(length == 2) { // запятая ("1*")
							result += ',';
						} else { // вопросительный знак ("1**")
							result += '?';
						}
					} else { // нужен t9
						result += t9.get(buffer, section->from, section->to);
					}
					tmp->next();
				}
				std::cout << result;
				break;
			}
		}
	}
	delete s_buffer;
	return 0;
}

a_tree::a_tree() : words(NULL) {
	for(int i = 0; i < 8; i++) {
		childs[i] = NULL;
	}
}
a_tree::~a_tree() {
	for(int i = 0; i < 8; i++) {
		delete childs[i];
	}
	delete words;
}

std::string a_tree::get(const std::string& src, size_t from, size_t to) {
	// на правильность ввода не проверяем, считаем что все нормально

	int off = from;
	a_tree* node = this;
	while(off != to && src[off] != '*') {
		int index = src[off++] - '2';
		a_tree* tmp = node->childs[index];
		if(tmp == NULL) {
			node = node->childs[index] = new a_tree();
		} else {
			node = tmp;
		}
	}
	int offset = to - off;

	list* first = node->words;

	list* find = first;
	while(offset > 0) {
		find = find->next();
		offset--;
	}

	std::string result = find->word();
	int count = find->countPlus();

	list* placeTo = find;
	while(placeTo->prev() != NULL && placeTo->prev()->count() <= count) {
		placeTo = placeTo->prev();
	}

	if(placeTo != find) {
		moveBefore(placeTo, find);
		if(placeTo == first) {
			node->words = find;
		}
	}

	return result;
}

void a_tree::insert(const std::string& what, int howMuch) {
	// на дублирование не проверяем, считаем что данные хорошие
	int off = 0;
	int len = what.length();
	a_tree* node = this;
	while(off != len) {
		int index = getButton(what[off++]) - 2;
		a_tree* tmp = node->childs[index];
		if(tmp == NULL) {
			node = node->childs[index] = new a_tree();
		} else {
			node = tmp;
		}
	}
	if(node->words == NULL) {
		node->words = new list(what, howMuch);
		return;
	}
	list* exi = node->words;
	if(exi->count() < howMuch) {
		node->words = exi->insertBefore(what, howMuch);
		return;
	}
	while(exi->next() != NULL && exi->next()->count() >= howMuch) {
		exi = exi->next();
	}
	exi->insertAfter(what, howMuch);
}
