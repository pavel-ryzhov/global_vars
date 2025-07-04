#include <vector>
#include <string>
#include <cstdlib>
#include <stdio.h>

struct TEntry {
	int freq_;
	std::string word_;
	TEntry(const char* word, int freq)
		: word_(word), freq_(freq) { }
	bool operator < (const TEntry& right) const {
		if (freq_ == right.freq_) {
			return word_ > right.word_;
		}
		return freq_ < right.freq_;
	}
};

struct TEntryPtr {
	TEntry* entry_;
	TEntryPtr(TEntry* entry) : entry_(entry) { }
	bool operator < (const TEntryPtr& right) const {
		return *entry_ < *right.entry_;
	}
};

struct TNode {	
	std::vector<TNode> children_;
	std::vector<TEntryPtr> entries_;

	typedef std::vector<TEntryPtr>::iterator TIter;

	TNode* Next(char letter) {
		if (children_.empty()) {
			children_.resize(8);
		}
		if (letter >= 'w') return &children_[7];
		if (letter >= 't') return &children_[6];
		if (letter >= 'p') return &children_[5];
		if (letter >= 'm') return &children_[4];
		if (letter >= 'j') return &children_[3];
		if (letter >= 'g') return &children_[2];
		if (letter >= 'd') return &children_[1];
		return &children_[0];
	}

	void AddEntry(const TEntryPtr& entry) {
		
		TIter it = entries_.end();
			
		if (entries_.empty()
			|| entries_.front() < entry) {
			it = entries_.begin();
		}
		else if (entry < entries_.back()) {
			it = entries_.end();
		}
		else {
			TIter first = entries_.begin();
			TIter last = entries_.end() - 1;
			TIter middle = first + (last - first) / 2;
			while (last - first > 1) {
				if (entry < *middle) {
					first = middle;
					middle += (last - first) / 2;
				}
				else {
					last = middle; 
					middle -= (last - first) / 2;
				}
			}
			it = last;
		}
		entries_.insert(it, entry);
	}

	void IncFreq(int index) {

		TIter insert = entries_.begin();
		TIter earase = entries_.begin() + index;

		TEntryPtr entry(*earase);

		int freq = ++entry.entry_->freq_;

		if (index == 0) { return; }
		
		if (entries_.empty()
			|| entries_.front().entry_->freq_ <= freq) {
			insert = entries_.begin();
		}
		else if (entries_.back().entry_->freq_ > freq) {
			insert = entries_.end();
		}
		else {
			TIter first = entries_.begin();
			TIter last = earase;
			TIter middle = first + (last - first) / 2;
			while (last - first > 1) {
				if (middle->entry_->freq_ > freq) {
					first = middle;
					middle += (last - first) / 2;
				}
				else {
					last = middle; 
					middle -= (last - first) / 2;
				}
			}
			insert = last;
		}
		if (insert < earase) {
			entries_.erase(earase);
			entries_.insert(insert, entry);
		}
	}
};

struct TTree {	
	TNode root_;

	TTree(std::vector<TEntry>& dictionary) {
		for (int i = 0; i < dictionary.size(); i++) {
			typedef std::string::const_iterator TIter;
			TEntry& entry = dictionary[i];
			const std::string& word = entry.word_;			
			TNode* node = &root_;
			for (TIter it = word.begin(); it != word.end(); ++it) {
				node = node->Next(*it);
			}
			node->AddEntry(TEntryPtr(&entry));
		}
	}
};

void Load(std::vector<TEntry>* dictionary, std::string* input) {
	
	int n(0);
	scanf("%d", &n);
	
	dictionary->clear();
	dictionary->reserve(n);

	int freq(0);
	char* buf = new char[100000];
	while (n--) {
		scanf("%s %d", buf, &freq);
		dictionary->push_back(TEntry(buf, freq));
	}

	input->clear();
	input->reserve(100000);

	getchar(); // skip \n

	fgets(buf, 100000, stdin);
	input->append(buf);

	delete[] buf;

	if (*input->rbegin() == '\n') {
		input->resize(input->length() - 1);
	}
}

int main() {

	const char* stop = ".,?";
		
	std::string input;
	std::string result;
	std::vector<TEntry> dictionary;		

	Load(&dictionary, &input);

	result.reserve(input.size());
	
	TTree tree(dictionary);

	typedef std::string::const_iterator TIter;

	TNode* node = &tree.root_;
	TIter it = input.begin();
	while (it != input.end()) {
		if (*it == '1')	{			
			const char* ptr = stop;
			++it;
			while (it != input.end()
				&& *it == '*') {
				++ptr;
				++it;
			}
			result += *ptr;
			node = &tree.root_;
		}
		else if (*it == ' ') {			
			while (it != input.end()
				&& *it == ' ') {
				result += ' ';
				++it;
			}
			node = &tree.root_;
		}
		else {
			while(it != input.end()
				&& *it > '1' && *it <= '9') {
				node = &node->children_[*it - '0' - 2];
				++it;
			}
			int index = 0;
			while (it != input.end() 
				&& *it == '*') {
				++index;
				++it;
			}

			result.append(
				node->entries_[index].entry_->word_);
			
			node->IncFreq(index);
		}
	}

	printf("%s", result.c_str());

	exit(EXIT_SUCCESS);
}
