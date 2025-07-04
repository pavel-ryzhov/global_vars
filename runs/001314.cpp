#include <list>
#include <vector>
#include <string>
#include <cstdlib>
#include <stdio.h>

typedef std::list<int> WordList;
typedef std::list<int>::iterator WordListIter;
typedef std::list<int>::const_iterator WordListCIter;

typedef std::vector< std::pair<std::string, int> > Dictionary;

struct Node {
	WordList words_;
	std::vector<Node> children_;
	
	static int GetIndex(char letter) {
		if (letter =='.' || letter ==','|| letter =='?') return 8;
		if (letter > 'v') return 7;
		if (letter > 's') return 6;
		if (letter > 'o') return 5;
		if (letter > 'l') return 4;
		if (letter > 'i') return 3;
		if (letter > 'f') return 2;
		if (letter > 'c') return 1;
		return 0;
	}
};

class Tokenizer {
	Node* tree_;
	Node* node_;
	const char* string_;
	const char* current_;
public:
	Tokenizer(const char* input, Node* tree)
		: string_(input)
		, current_(input)
		, tree_(tree)
		, node_(NULL) { }

	char Current() { return *current_; }

	WordList* Next() {		
		node_ = NULL;
		if (isdigit(*current_)) {
			if  (*current_ != '1') {
				int index = *current_ - '0' - 2;
				node_ = &tree_[index];
				current_++;
				while (isdigit(*current_) && *current_ != '1') {
					index = *current_ - '0' - 2;
					node_ = &node_->children_[index];
					current_++;
				}
			}
			else {
				node_ = &tree_[8];
				current_++;
			}
		}
		else {
			++current_;
		}
		return node_ ? &node_->words_ : NULL;
	}
};

void Init(const Dictionary& dictionary
		  , const char* ptr
		  , int index
		  , int frequency
		  , Node* node) {
	WordListIter it = node->words_.begin();
	for (it; it != node->words_.end(); ++it) {
		if (dictionary[*it].second < frequency) {
			break;
		}
	}
	node->words_.insert(it, index);
	if (*++ptr) {
		if (node->children_.empty()) {
			node->children_.resize(8);
		}
		Init(dictionary
			, ptr
			, index
			, frequency
			, &node->children_[Node::GetIndex(*ptr)]);
	}
}

void Update(const Dictionary& dictionary
			, const char* ptr
			, int index
			, int frequency
			, Node* node) {
	
	WordListIter it = node->words_.begin();
	for (it; *it != index; ++it);
	node->words_.erase(it);

	it = node->words_.begin();
	for (it; it != node->words_.end(); ++it) {
		if (dictionary[*it].second <= frequency) {
			break;
		}
	}
	node->words_.insert(it, index);

	if (*++ptr) {
		Update(dictionary
			, ptr
			, index
			, frequency
			, &node->children_[Node::GetIndex(*ptr)]);
	}
}

void Load(Node* tree, Dictionary* dictionary, std::string* input) {
	
	int n(0);	
	scanf("%d", &n);
	
	dictionary->clear();
	dictionary->reserve(n+3);

	dictionary->push_back(std::make_pair<std::string, int>(".", 1));
	dictionary->push_back(std::make_pair<std::string, int>(",", 1));
	dictionary->push_back(std::make_pair<std::string, int>("?", 1));

	tree[8].words_.push_back(0);
	tree[8].words_.push_back(1);
	tree[8].words_.push_back(2);

	int frequency(0);
	char buf[512] = {0,};
	while (n--) {
		scanf("%s %d", buf, &frequency);
		Init(*dictionary
			, buf
			, dictionary->size()
			, frequency
			, &tree[Node::GetIndex(*buf)]);
		dictionary->push_back(std::make_pair<std::string, int>(buf, frequency));
	}


	input->clear();
	input->reserve(100000);

	while (scanf("%s", buf) != EOF) {
		input->append(buf);
		input->append(" ");
	}
	input->resize(input->length()-1);
}



int main() {
	
	Node tree[9];
	Dictionary dictionary;

	std::string input;
	std::string result;

	//freopen("input2.txt", "r", stdin);

	Load(tree, &dictionary, &input);

	Tokenizer tokenizer(input.c_str(), tree);

	while (tokenizer.Current()) {
		WordList* words = tokenizer.Next();
		if (words) {
			WordListIter it = words->begin();
			while (tokenizer.Current() == '*') {
				tokenizer.Next();
				++it;
			}
			result.append(dictionary[*it].first);
			
			if (words != &tree[8].words_) {
				// don't update .,?
				dictionary[*it].second += 1;
				Update(dictionary
					, dictionary[*it].first.c_str()
					, *it, dictionary[*it].second
					, &tree[Node::GetIndex(*dictionary[*it].first.c_str())]);
			}

			if (tokenizer.Current() == ' ') {
				result.append(" ");
			}
		}
	}

	printf("%s", result.c_str());

	exit(EXIT_SUCCESS);
}
