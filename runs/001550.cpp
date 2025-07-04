#include <string>
#include <memory>
#include <vector>
#include <iostream>

int min(int a, int b) {
	return a <= b ? a : b;
}

class count_list;

class list {
public:
	list(const std::string& word, list* next = NULL) :
		_word(word), _next(next) {
	};

	/*const std::string& word() const {return _word;}*/

	friend void insert(const std::string& what, int howMuch, count_list** first);
	friend const std::string& get(int index, count_list** first);

	~list() {
		delete _next;
	}
private:
	list(const list&);
	void operator= (const list&);

	std::string _word;

	list* _next;
};

class count_list {
public:
	count_list(int count, count_list* nxt = NULL):
		_count(count), first(NULL), _size(0), _next(nxt)
	{}
	int count() const {return _count;}
	int size() const {return _size;}
	
	friend void insert(const std::string& what, int howMuch, count_list** first);
	friend const std::string& get(int index, count_list** first);
	
	~count_list() {
		delete _next;
		delete first;
	}
private:
	count_list(const count_list&);
	void operator= (const count_list&);

	int _count;

	list* first;
	list* last;
	int _size;

	count_list* _next;
};

void insert(const std::string& what, int howMuch, count_list** first) {
	count_list* node = *first;
	if(node->_count < howMuch) {
		*first = node = new count_list(howMuch, node);
	} else if (node->_count > howMuch) {
		while(node->_next != NULL && node->_next->_count >= howMuch) {
			node = node->_next;
		}
		if(node->_count > howMuch) {
			node = node->_next = new count_list(howMuch, node->_next);
		}
	}
	if(node->first == NULL) {
		node->first = node->last = new list(what);
	} else {
		node->last = node->last->_next = new list(what);
	}
	node->_size++;
}

const std::string& get(int index, count_list** first) {
	count_list* node = *first;
	count_list* prevNode = NULL;
	list* element;
	list* prevElement = NULL;
	while(index >= node->_size) {
		index -= node->_size;
		prevNode = node;
		node = node->_next;
	}
	int howMuch = node->_count + 1;
	element = node->first;
	while(index > 0) {
		prevElement = element;
		element = element->_next;
		index--;
	}
	const std::string& result = element->_word;
	if(node->_size == 1 && (prevNode == NULL || prevNode->_count > howMuch)) {
		node->_count++;
		return result;
	}
	// извлечение элемента из списка
	if(prevElement == NULL) {
		node->first = element->_next;
	} else {
		prevElement->_next = element->_next;
	}
	if(element->_next == NULL) {
		node->last = prevElement;
	}
	int newSize = --node->_size;
	if(newSize == 0) {
		// в этом случае у нас всегда есть предок
		count_list* tmp = node->_next;
		node->_next = NULL;
		delete node;
		prevNode->_next = tmp;
		node = prevNode;
	} else if(prevNode == NULL) {
		// в этом случае node не NULL
		*first = node = new count_list(howMuch, node);
	} else {
		if(prevNode->_count > howMuch) {
			count_list* newOne = new count_list(howMuch, node);
			prevNode->_next = newOne;
			node = newOne;
		} else {
			node = prevNode;
		}
	}
	element->_next = node->first;
	if(node->first == NULL) {
		node->last = element;
	}
	node->first = element;
	node->_size++;

	return result;
}

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
	const std::string& get(const std::string& src, size_t from, size_t to);
	// сюда вставляется слово в нормальном формате, например ("robot", 1) или ("back", 3)
	void insert(const std::string& what, int howMuch);

	a_tree();
	~a_tree();
private:
	a_tree* childs[8];
	count_list* words;
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
				while(!tmp->empty()) {
					section_queue::section* section = tmp->front();
					char ch = buffer[section->from];
					size_t length = section->to - section->from;
					if(ch == ' ') { // пробельная строка
						std::cout << std::string(length, ' ');
					} else if(ch == '1') { // знак препинания
						if(length == 1) { // точка ("1")
							std::cout << '.';
						} else if(length == 2) { // запятая ("1*")
							std::cout << ',';
						} else { // вопросительный знак ("1**")
							std::cout << '?';
						}
					} else { // нужен t9
						std::cout << t9.get(buffer, section->from, section->to);
					}
					tmp->next();
				}
				break;
			}
		}
	}
	delete s_buffer;
	return 0;
}

a_tree::a_tree():
words(NULL)
{
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

const std::string& a_tree::get(const std::string& src, size_t from, size_t to) {
	// на правильность ввода не проверяем, считаем что все нормально

	int off = from;
	a_tree* node = this;
	while(off != to && src[off] != '*') {
		int index = src[off++] - '2';
		node = node->childs[index];
	}
	int offset = to - off;

	return ::get(offset, &node->words);
}

void a_tree::insert(const std::string& what, int howMuch) {
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
		node->words = new count_list(howMuch);
	}

	::insert(what, howMuch, &node->words);
	howMuch++;
}
