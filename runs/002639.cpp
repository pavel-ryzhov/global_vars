#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
#include <cstdlib>

using std::cin;
using std::cout;
using std::vector;
using std::string;

const int MAX_PRIORITY = 50000;
const int MAX_LENGTH = 20;
const int NUMBER_BUTTONS = 8;
const int ALPHABET_SIZE = 26;  

template<class Value, class Key> struct TreapNode {
	Value value;
	Key key;
	int priority;
    int size; 
	TreapNode* parent;
	TreapNode* left;
	TreapNode* right;
};

template<class Value, class Key> class Treap {
	public:
		Treap();
		Value FindValueOfStatistics(const int statistics);
		TreapNode<Value, Key>* InsertBuild(const Value value, const int priority, const Key key);
		TreapNode<Value, Key>* Insert(const Value value, const int priority, const Key key);
		int TreapSize();
		void RemoveRoot();
		void DeleteTreap();
		Value FindValueByKey(const Key targetKey);
		void ChangeValue(const Key targetKey, const Value newValue);
		TreapNode<string, int>* IncreaseKey(TreapNode<string, int>* targetNode);
	private:
        TreapNode<Value, Key> *treapRoot_;
		TreapNode<Value, Key> treapNIL_; 

		void LeftRotate(TreapNode<Value, Key>* node);
		void RightRotate(TreapNode<Value, Key>* node);
		Value FindValueOfStatisticsSubTree(const int statistics, TreapNode<Value, Key>** rootOfSubTree);
		TreapNode<Value, Key>* InsertBuildInSubTree(TreapNode<Value, Key>* rootOfSubTree, const Value value, const int priority, const Key key); //is the same as insert but with some differences to use in initial creating of treap
		TreapNode<Value, Key>* InsertInSubTree(TreapNode<Value, Key>* rootOfSubTree, const Value value, const int priority, const Key key);
		void RemoveNode(TreapNode<Value, Key>* node);
		void DeleteSubTreap(TreapNode<Value, Key>* rootOfSubTreap);
		Value FindValueByKeySubTreap(TreapNode<Value, Key>* rootOfSubTreap, const Key targetKey);
		void ChangeValueSubTreap(TreapNode<Value, Key>* rootOfSubTreap, const Key targetKey, const Value newValue);
};

template<class Value, class Key>  Treap<Value, Key>::Treap() {
	treapNIL_.parent = &treapNIL_;
	treapNIL_.left = &treapNIL_;
	treapNIL_.right = &treapNIL_;
	treapNIL_.size = 0;
	treapNIL_.priority = -1;
    treapRoot_ = &treapNIL_;
}

template<class Value, class Key> void Treap<Value, Key>::LeftRotate(TreapNode<Value, Key>* node) {
	TreapNode<Value, Key>* rightSon = node->right;
	
	if(node->parent != &treapNIL_) {
		if(node == node->parent->left) {
			node->parent->left = rightSon;
		} else {
			node->parent->right = rightSon;
		};
	};

	if(node == treapRoot_){
		treapRoot_ = rightSon;
	};

	if (rightSon->left == &treapNIL_) {
		node->right = &treapNIL_;
	} else {
		node->right = rightSon->left;
		node->right->parent = node;
	};

	rightSon->left = node;
	rightSon->parent = node->parent;
	rightSon->size = node->size;
	rightSon->left->parent = rightSon;
	rightSon->left->size = rightSon->left->left->size + rightSon->left->right->size + 1;
}

template<class Value, class Key> void Treap<Value, Key>::RightRotate(TreapNode<Value, Key>* node) {
    TreapNode<Value, Key>* leftSon = node->left;

	if(node->parent != &treapNIL_) {
		if(node == node->parent->left) {
			node->parent->left = leftSon;
		} else {
			node->parent->right = leftSon;
		};
	};

	if(node == treapRoot_){
		treapRoot_ = leftSon;
	};

	if (leftSon->right == &treapNIL_) {
		node->left = &treapNIL_;
	} else {
		node->left = node->left->right;
		node->left->parent = node;
	};
	
	leftSon->right = node;
	leftSon->parent = node->parent;
	leftSon->size = node->size;
	leftSon->right->parent = leftSon;
	leftSon->right->size = leftSon->right->left->size + leftSon->right->right->size + 1;  	
}

template<class Value, class Key> Value Treap<Value, Key>::FindValueOfStatisticsSubTree(const int statistics, TreapNode<Value, Key>** rootOfSubTree) {
	if (statistics == (*rootOfSubTree)->right->size + 1) {
		return (*rootOfSubTree)->value;
	} else {
		if (statistics <= (*rootOfSubTree)->right->size) {
			int statisticsInSubTree = statistics; 
			return FindValueOfStatisticsSubTree(statisticsInSubTree, &(*rootOfSubTree)->right);
		} else {
			int statisticsInSubTree = statistics - (*rootOfSubTree)->right->size - 1;         
			return FindValueOfStatisticsSubTree(statisticsInSubTree, &(*rootOfSubTree)->left);
		}
	}
}

template<class Value, class Key> Value Treap<Value, Key>::FindValueOfStatistics(const int statistics) {
	return FindValueOfStatisticsSubTree(statistics, &treapRoot_);
}

template<class Value, class Key> TreapNode<Value, Key>* Treap<Value, Key>::InsertInSubTree(TreapNode<Value, Key>* rootOfSubTree, 
																						   const Value value, const int priority, const Key key) {
	TreapNode<Value, Key>* newNode;																					   
	if (key < rootOfSubTree->key) {
		rootOfSubTree->size += 1;
		
		if (rootOfSubTree->left == &treapNIL_) {         
			newNode = new TreapNode<Value, Key>;
            newNode->value = value;
			newNode->key = key;
            newNode->size = 1;
            newNode->priority = priority; 
            newNode->left = &treapNIL_;
            newNode->right = &treapNIL_;
			newNode->parent = rootOfSubTree;
			rootOfSubTree->left = newNode;
		} else {
			newNode = InsertInSubTree(rootOfSubTree->left, value, priority, key);
		};
		
        if (rootOfSubTree->left->priority > rootOfSubTree->priority) {
			RightRotate(rootOfSubTree);
        };
        
		return newNode;
	} else {
		rootOfSubTree->size += 1;
		
		if (rootOfSubTree->right == &treapNIL_) {
			newNode = new TreapNode<Value, Key>;
            newNode->value = value;
			newNode->key = key;
            newNode->size = 1;
            newNode->priority = priority; 
            newNode->left = &treapNIL_;
            newNode->right = &treapNIL_;
			newNode->parent = rootOfSubTree;
			rootOfSubTree->right = newNode;
		} else {
			newNode = InsertInSubTree(rootOfSubTree->right, value, priority, key);
		};
		
		if (rootOfSubTree->right->priority > rootOfSubTree->priority) {
			LeftRotate(rootOfSubTree);
		};
		
		return newNode;
	}
}

template<class Value, class Key> TreapNode<Value, Key>* Treap<Value, Key>::Insert(const Value value, const int priority, const Key key) {
	if (treapRoot_ == &treapNIL_) {
		treapRoot_ = new TreapNode<Value, Key>;
        treapRoot_->value = value;
        treapRoot_->key = key;
        treapRoot_->size = 1;
        treapRoot_->priority = priority;
        treapRoot_->left = &treapNIL_;
        treapRoot_->right = &treapNIL_;
		treapRoot_->parent = &treapNIL_;
		return treapRoot_;
	} else {        
		return InsertInSubTree(treapRoot_, value, priority, key);
	}
}

template<class Value, class Key> TreapNode<Value, Key>* Treap<Value, Key>::InsertBuildInSubTree(TreapNode<Value, Key>* rootOfSubTree, 
																						   const Value value, const int priority, const Key key) {
	TreapNode<Value, Key>* newNode;																					   
	if (key <= rootOfSubTree->key) {
		rootOfSubTree->size += 1;
		
		if (rootOfSubTree->left == &treapNIL_) {         
			newNode = new TreapNode<Value, Key>;
            newNode->value = value;
			newNode->key = key;
            newNode->size = 1;
            newNode->priority = priority; 
            newNode->left = &treapNIL_;
            newNode->right = &treapNIL_;
			newNode->parent = rootOfSubTree;
			rootOfSubTree->left = newNode;
		} else {
			newNode = InsertBuildInSubTree(rootOfSubTree->left, value, priority, key);
		};
		
        if (rootOfSubTree->left->priority > rootOfSubTree->priority) {
			RightRotate(rootOfSubTree);
        };
        
		return newNode;
	} else {
		rootOfSubTree->size += 1;
		if (rootOfSubTree->right == &treapNIL_) {
			newNode = new TreapNode<Value, Key>;
            newNode->value = value;
			newNode->key = key;
            newNode->size = 1;
            newNode->priority = priority; 
            newNode->left = &treapNIL_;
            newNode->right = &treapNIL_;
			newNode->parent = rootOfSubTree;
			rootOfSubTree->right = newNode;
		} else {
			newNode = InsertBuildInSubTree(rootOfSubTree->right, value, priority, key);
		};
		
		if (rootOfSubTree->right->priority > rootOfSubTree->priority) {
			LeftRotate(rootOfSubTree);
		};
		
		return newNode;
	}
}

template<class Value, class Key> TreapNode<Value, Key>* Treap<Value, Key>::InsertBuild(const Value value, const int priority, const Key key) {
	if (treapRoot_ == &treapNIL_) {
		treapRoot_ = new TreapNode<Value, Key>;
        treapRoot_->value = value;
        treapRoot_->key = key;
        treapRoot_->size = 1;
        treapRoot_->priority = priority;
        treapRoot_->left = &treapNIL_;
        treapRoot_->right = &treapNIL_;
		treapRoot_->parent = &treapNIL_;
		return treapRoot_;
	} else {        
		return InsertBuildInSubTree(treapRoot_, value, priority, key);
	}
}

template<class Value, class Key> int Treap<Value, Key>::TreapSize() {
	return treapRoot_->size;
}

template<class Value, class Key> void Treap<Value, Key>::RemoveNode(TreapNode<Value, Key>* node) {
	if ((node->left != &treapNIL_) || (node->right != &treapNIL_)) {
		if (node->left->priority < node->right->priority) {
			LeftRotate(node); 
			RemoveNode(node);
		} else {
			RightRotate(node);
			RemoveNode(node);
		}
	} else {  
		if (node == treapRoot_) {
			treapRoot_ = &treapNIL_;
		} else {
			if (node->parent->right == node) {
				TreapNode<Value, Key>* parent = node->parent;
				delete node;
				parent->right = &treapNIL_;
				while (parent != &treapNIL_) {
					parent->size -= 1;
					parent = parent->parent;
				}
			} else {
				TreapNode<Value, Key>* parent = node->parent;
				delete node;
				parent->left = &treapNIL_;
				while (parent != &treapNIL_) {
					parent->size -= 1;
					parent = parent->parent;
				}
			}
		}
	}
}

template<class Value, class Key> void Treap<Value, Key>::RemoveRoot() {
	RemoveNode(&treapRoot_);
}

template<class Value, class Key> void Treap<Value, Key>::DeleteTreap() {
	DeleteSubTreap(treapRoot_);
}

template<class Value, class Key> void Treap<Value, Key>::DeleteSubTreap(TreapNode<Value, Key>* rootOfSubTreap) {
	if (rootOfSubTreap->left != &treapNIL_) {
		DeleteSubTreap(rootOfSubTreap->left);
	};
	
	if (rootOfSubTreap->right != &treapNIL_) {
		DeleteSubTreap(rootOfSubTreap->right);
	};
	
	if (rootOfSubTreap != treapRoot_) {
		delete rootOfSubTreap;
	}      
}

template<> TreapNode<string, int>* Treap<string, int>::IncreaseKey(TreapNode<string, int>* targetNode) {
	int newKey = targetNode->key + 1;
	string word = targetNode->value;
	int priority = targetNode->priority;

	RemoveNode(targetNode);
	TreapNode<string, int>* insertedNode = Insert(word, priority, newKey);
	return insertedNode;
}

template<class Value, class Key> Value Treap<Value, Key>::FindValueByKeySubTreap(TreapNode<Value, Key>* rootOfSubTreap, const Key targetKey) {
	if (rootOfSubTreap->key == targetKey) {
		return rootOfSubTreap->value;
	} else {
		if (rootOfSubTreap->key > targetKey) {
			return FindValueByKeySubTreap(rootOfSubTreap->left, targetKey);
		} else {
			return FindValueByKeySubTreap(rootOfSubTreap->right, targetKey);
		}
	}
}

template<class Value, class Key> Value Treap<Value, Key>::FindValueByKey(const Key targetKey) {
	return FindValueByKeySubTreap(treapRoot_, targetKey);
}

template<class Value, class Key> void Treap<Value, Key>::ChangeValueSubTreap(TreapNode<Value, Key>* rootOfSubTreap, const Key targetKey, const Value newValue) {
	if (rootOfSubTreap->key == targetKey) {
		rootOfSubTreap->value = newValue;
	} else {
		if (rootOfSubTreap->key > targetKey) {
			ChangeValueSubTreap(rootOfSubTreap->left, targetKey, newValue);
		} else {
			ChangeValueSubTreap(rootOfSubTreap->right, targetKey, newValue);
		}
	}
}

template<class Value, class Key> void Treap<Value, Key>::ChangeValue(const Key targetKey, const Value newValue) {
	return ChangeValueSubTreap(treapRoot_, targetKey, newValue);
}

struct DictionaryNode {
    vector<DictionaryNode*> nextDigits;
    Treap<string, int> dictionarySubTreap;
	Treap<TreapNode<string, int>*, string> linkSubTreap;
};

class DictionaryTree {
    public:
        DictionaryTree();
        void Insert(const string& word, const int frequency);	
		string DecodeWord(const string& word, const int numberChanges);
		void IncreaseFrequency(const string& word);
        void DeleteTree();
    private:
        DictionaryNode *dictionaryRoot_;
		DictionaryNode dictionaryNIL_; 
		vector<int> lettersDigits;
		
		void FillLettersDigits();
		void InsertInDictionarySubTree(const string& word, const int frequency, const int currentLetterIndex, DictionaryNode** rootSubTreeOfDictionaries);
		string DecodeWordSubTree(const string& word, const int numberChanges, const int currentLetterIndex, DictionaryNode** rootOfSubTree);
		void IncreaseFrequencySubTree(const string& word, const int currentLetterIndex, DictionaryNode** rootOfSubTree);
		void DeleteSubTree(DictionaryNode* rootOfSubTree);
};

DictionaryTree::DictionaryTree() {
	dictionaryNIL_.nextDigits.assign(NUMBER_BUTTONS, &dictionaryNIL_);
	dictionaryRoot_ = &dictionaryNIL_;
    FillLettersDigits();
}
    
void DictionaryTree::InsertInDictionarySubTree(const string& word, const int frequency, const int currentLetterIndex, 
                                               DictionaryNode** rootSubTreeOfDictionaries) {
    int priority;
    if (currentLetterIndex == word.size()) {
        priority = rand() % MAX_PRIORITY;
        TreapNode<string, int>* newDictionaryNode = (*rootSubTreeOfDictionaries)->dictionarySubTreap.InsertBuild(word, priority, frequency);
		TreapNode<TreapNode<string, int>*, string>* newLinkNode = (*rootSubTreeOfDictionaries)->linkSubTreap.Insert(newDictionaryNode, priority, word);
    } else {
        char currentLetter = word[currentLetterIndex];
        int currentDigitIndex = lettersDigits[currentLetter - 'a'];

        if ((*rootSubTreeOfDictionaries)->nextDigits[currentDigitIndex] == &dictionaryNIL_) {
            (*rootSubTreeOfDictionaries)->nextDigits[currentDigitIndex] = new DictionaryNode;
            (*rootSubTreeOfDictionaries)->nextDigits[currentDigitIndex]->nextDigits.assign(NUMBER_BUTTONS, &dictionaryNIL_);
        };

        int nextLetterIndex = currentLetterIndex + 1;
        InsertInDictionarySubTree(word, frequency, nextLetterIndex, &(*rootSubTreeOfDictionaries)->nextDigits[currentDigitIndex]);
    }
}

void DictionaryTree::Insert(const string& word, const int frequency) {
    if (dictionaryRoot_ == &dictionaryNIL_) {
        dictionaryRoot_ = new DictionaryNode;
		dictionaryRoot_->nextDigits.assign(NUMBER_BUTTONS, &dictionaryNIL_);
		int firstLetterIndex = 0;
        InsertInDictionarySubTree(word, frequency, firstLetterIndex, &dictionaryRoot_);
    } else {       
        int firstLetterIndex = 0;
        InsertInDictionarySubTree(word, frequency, firstLetterIndex, &dictionaryRoot_);
    }
}

void DictionaryTree::FillLettersDigits() {
	lettersDigits.resize(ALPHABET_SIZE);
    for (char letter = 'a'; letter <= 'r'; ++letter) {
        lettersDigits[letter - 'a'] = (letter - 'a') / 3;
    };
    
    lettersDigits['s' - 'a'] = 5;
    
    for (char letter = 't'; letter <= 'y'; ++letter) {
        lettersDigits[letter - 'a'] = (letter - 'a' - 1) / 3;
    }; 
    
    lettersDigits['z' - 'a'] = 7;
}

void DictionaryTree::DeleteTree() {
     DeleteSubTree(dictionaryRoot_);
}

void DictionaryTree::DeleteSubTree(DictionaryNode* rootOfSubTree) {
    for (int currentDigitIndex = 0; currentDigitIndex < NUMBER_BUTTONS; ++currentDigitIndex) {
        if (rootOfSubTree->nextDigits[currentDigitIndex] != &dictionaryNIL_) {
            DeleteSubTree(rootOfSubTree->nextDigits[currentDigitIndex]);
        };
    };
     
    if (rootOfSubTree != dictionaryRoot_) {
		rootOfSubTree->dictionarySubTreap.DeleteTreap();
		rootOfSubTree->linkSubTreap.DeleteTreap();
		delete rootOfSubTree;
    } 
}

string DictionaryTree::DecodeWordSubTree(const string& word, const int numberChanges, 
                                         const int currentLetterIndex, DictionaryNode** rootOfSubTree) {
	if (currentLetterIndex == word.size()) {
		int numberWordsInSubTree = (*rootOfSubTree)->dictionarySubTreap.TreapSize();
		int statistics = numberChanges % numberWordsInSubTree + 1;
		return (*rootOfSubTree)->dictionarySubTreap.FindValueOfStatistics(statistics);
	} else {
		char currentLetter = word[currentLetterIndex];
		int currentDigitIndex = atoi(&currentLetter) - 2;
		int nextLetterIndex = currentLetterIndex + 1;
		return DecodeWordSubTree(word, numberChanges, nextLetterIndex, &(*rootOfSubTree)->nextDigits[currentDigitIndex]);
	}
}

string DictionaryTree::DecodeWord(const string& word, const int numberChanges) {
	int firstLetterIndex = 0;
	return DecodeWordSubTree(word, numberChanges, firstLetterIndex, &dictionaryRoot_);
}

void DictionaryTree::IncreaseFrequencySubTree(const string& word, const int currentLetterIndex, DictionaryNode** rootOfSubTree) {
	if (currentLetterIndex == word.size()) {
		TreapNode<string, int>* nodeToIncrease = (*rootOfSubTree)->linkSubTreap.FindValueByKey(word); 
		TreapNode<string, int>* newLinkForNodeToIncrease = (*rootOfSubTree)->dictionarySubTreap.IncreaseKey(nodeToIncrease);
		(*rootOfSubTree)->linkSubTreap.ChangeValue(word, newLinkForNodeToIncrease); 
	} else {
		char currentLetter = word[currentLetterIndex];
        int currentDigitIndex = lettersDigits[currentLetter - 'a'];
		int nextLetterIndex = currentLetterIndex + 1;
		return IncreaseFrequencySubTree(word, nextLetterIndex, &(*rootOfSubTree)->nextDigits[currentDigitIndex]);
	}
}

void DictionaryTree::IncreaseFrequency(const string& word) {
	int firstLetterIndex = 0;
	return IncreaseFrequencySubTree(word, firstLetterIndex, &dictionaryRoot_);
}

void BuildTreeOfDictionaries(const vector<string>& dictionary, const vector<int>& frequencies, 
                             DictionaryTree* treeOfDictionaries) {
    int numberWords = dictionary.size();
    for (int currentWordIndex = 0; currentWordIndex < numberWords; ++currentWordIndex) {
        (*treeOfDictionaries).Insert(dictionary[currentWordIndex], frequencies[currentWordIndex]);
    }
}

string DecodeMessage(const string& message, DictionaryTree* treeOfDictionaries) {
    int message_size = message.size();
    string decodedMessage, decodedWord;
    char currentButton, previousButton = ' ';
	string currentWord =  "";
	int numberChanges = 0;

    for (int buttonIndex = 0; buttonIndex < message_size; ++buttonIndex) {
        currentButton = message[buttonIndex];
		if (currentButton == ' ') {
			if (((previousButton >= '1') && (previousButton <= '9')) || (previousButton == '*')) {
				if (currentWord != "1") {
					decodedWord = (*treeOfDictionaries).DecodeWord(currentWord, numberChanges);
					decodedMessage += decodedWord;
					(*treeOfDictionaries).IncreaseFrequency(decodedWord);
				} else {
					if ((numberChanges % 3) == 0) {
						decodedMessage += '.';
					} else {
						if ((numberChanges % 3) == 1) {
							decodedMessage += ',';
						} else {
							decodedMessage += '?';
						};
					};	
				};

				currentWord = "";
				numberChanges = 0;
			};
			decodedMessage += ' ';
        };

        if ((currentButton >= '2') && (currentButton <= '9')) {
            currentWord += currentButton;
        };
        
        if (currentButton == '1') {
			if (((previousButton >= '1') && (previousButton <= '9')) || (previousButton == '*')) {
				if (currentWord != "1") {
					decodedWord = (*treeOfDictionaries).DecodeWord(currentWord, numberChanges);
					decodedMessage += decodedWord;
					(*treeOfDictionaries).IncreaseFrequency(decodedWord);
				} else {
					if ((numberChanges % 3) == 0) {
						decodedMessage += '.';
					} else {
						if ((numberChanges % 3) == 1) {
							decodedMessage += ',';
						} else {
							decodedMessage += '?';
						};
					};
				};

				currentWord = "";
				numberChanges = 0;
			};
            currentWord = '1';
        };
        
        if (currentButton == '*') {
            numberChanges += 1;
        };
		previousButton = currentButton;
    }; 

	if (previousButton != ' ') {
		if (currentWord != "1") {
			decodedWord = (*treeOfDictionaries).DecodeWord(currentWord, numberChanges);
			decodedMessage += decodedWord;
			(*treeOfDictionaries).IncreaseFrequency(decodedWord);
		} else {
			if ((numberChanges % 3) == 0) {
						decodedMessage += '.';
			} else {
				if ((numberChanges % 3) == 1) {
					decodedMessage += ',';
				} else {
					decodedMessage += '?';
				};
			};	
		};
	};

    return decodedMessage;
}

string GetDecodedMessage(const string& message, const vector<string>& dictionary, const vector<int>& frequencies) {
        srand(MAX_PRIORITY);

        DictionaryTree treeOfDictionaries;
        BuildTreeOfDictionaries(dictionary, frequencies, &treeOfDictionaries);

		string decodedMessage = DecodeMessage(message, &treeOfDictionaries);
		
		treeOfDictionaries.DeleteTree();
        
		return decodedMessage;       
}

void InputDictionary(vector<string>* dictionary, vector<int>* frequencies) {
    int numberWords;
    cin >> numberWords;
    char currentWord[MAX_LENGTH + 1];
    int currentFrequency;
    
    for (int currentWordIndex = 0; currentWordIndex < numberWords; ++currentWordIndex) {
        scanf("%s %d\n", currentWord, &currentFrequency);
        (*dictionary).push_back(currentWord);
        (*frequencies).push_back(currentFrequency);
    }
}

void OutputMessage(const string& message) {
	int messageSize = message.size();
     for (int currentLetterIndex = 0; currentLetterIndex < messageSize; ++currentLetterIndex) {
        printf("%c", message[currentLetterIndex]);
    }
}

int main() {
    vector<string> dictionary;
    vector<int> frequencies;
    InputDictionary(&dictionary, &frequencies);

    string message;
    getline(cin, message, '\n');

	string decodedMessage = GetDecodedMessage(message, dictionary, frequencies);
    
	OutputMessage(decodedMessage);
	
    return 0;
}
