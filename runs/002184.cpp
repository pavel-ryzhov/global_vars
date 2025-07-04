#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>

const std::string keyboard[] = { "", ".,?", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };

int getKeyFromChar(char from) {
	for(int i = 0; i < 10; ++i)
		for(std::string::const_iterator it = keyboard[i].begin(); it < keyboard[i].end(); ++it )
			if(from == (*it))
				return i;
	return 0;
}

class Entry {
private:
	std::string word;
	int value;
	int counter;
public:
	Entry(std::string aString, int aValue) : word(aString), value(aValue), counter(0) {};
	bool operator< (const Entry& other) const {
		int result = other.value - value;
		if(result == 0)
			result = other.counter - counter;
		if(result == 0)
			result = word.compare(other.word);
		return result < 0;
	};
	int getKey() {
		std::stringstream os;
	    for(int i = 0; i < word.size(); ++i)
			os << getKeyFromChar(word[i]);
		int result = atoi(os.str().c_str());
		return result;
	}
	std::string getWord(){
		return word;
	};
	void promote(int aCounter) {
		++value;
		counter = aCounter;
	};
};

class Dictionary {
private:
	int counter;
	std::map<int, std::vector<Entry> > dictionary;
	void addWord(Entry entry) {
		int key = entry.getKey();
		std::map<int, std::vector<Entry> >::iterator it = dictionary.find(key);
		if(it == dictionary.end()) {
			std::vector<Entry> v;
			v.push_back(entry);
			dictionary[key] = v;
		} else {
			(*it).second.push_back(entry);
		}
	};
public:
	Dictionary() : counter(0) {};
	void addWord(std::string aWord, int aValue) {
		addWord(Entry(aWord, aValue));
	};
	Entry getEntry(std::string sequence, int choice) {
		int key = atoi(sequence.c_str());
		std::map<int, std::vector<Entry> >::iterator it = dictionary.find(key);
		if(it == dictionary.end())
			throw 100;
		std::sort((*it).second.begin(), (*it).second.end());
		Entry* e = &(*it).second[choice];
		counter++;
		e->promote(counter);
		return *e;
	};
};

class WordBuilder {
private:
	Dictionary* dictionary;
	int choice;
	std::string sequence;
	void reset() {
		sequence.clear();
		choice = 0;
		isPunctuation = false;
	};
public:
	WordBuilder(Dictionary* aDictionary) : dictionary(aDictionary), choice(0), isPunctuation(false) {};
	bool isPunctuation;
	
	void append(char c) {
		sequence.push_back(c);
	};
	void increase() {
		++choice;
	};
	void punctuation() {
		isPunctuation = true;
	};
	std::string build() {
		if(!isPunctuation && !sequence.empty()){
			try {
				Entry e = dictionary->getEntry(sequence, choice);
				std::string result= e.getWord();
				
				reset();
				return result;
			} catch (int th) {
			}
			reset();
			return "";
		} else if(isPunctuation) {
			char p = keyboard[1][choice];
			std::string result(&p);
			reset();
			return result;
		} else {
			return "";
		}
	};
		
};

int main (int argc, char * const argv[]) {
    
	std::string line;
	// get words count
	getline(std::cin, line, '\n');
	int words = atoi(line.c_str());
	
	Dictionary dictionary;
	
	for(int i = 0; i < words; ++i) {
		getline(std::cin, line, '\n');
		char word[20];
		int value;
		sscanf(line.c_str(), "%s %d\n", word, &value);
		dictionary.addWord(std::string(word), value);
	}
	
	// get query
	getline(std::cin, line, '\n');
	
	std::string result;
	WordBuilder builder(&dictionary);
	for(std::string::iterator it = line.begin(); it < line.end(); ++it) {
		
		char c = (*it);
		
		if (c >= '2' && c <= '9'){
			if(builder.isPunctuation)
				std::cout << builder.build();	
			builder.append(c);
		} else if (c == '*')
			builder.increase();
		else if (c == '1') {
			std::cout << builder.build();
			builder.punctuation();
		} else if (c == ' ') {
			std::cout << builder.build() << " ";
		}
	}
	std::cout << builder.build();
	
	std::cout << std::endl;
	
    return 0;
}
