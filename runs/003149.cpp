#include <iostream>
#include <vector>
#include <string>
#include <map>

using std::vector;
using std::string;
using std::map;
using std::cin;
using std::cout;
using std::endl;

enum { initState, wordState, starsState, spaceState, punctuationState };

class FrequencyOrderedList
{
public:
	FrequencyOrderedList();
	void insert(const string& word, int frequency);
	string getWord(int shiftCount);
	~FrequencyOrderedList();

private:
	struct Node
	{
		string word;
		int frequency;
		Node *nextLink;
		Node *previousLink;
	};
	
	void moveNode(Node* nodeToMove);

	Node *head;
	int size;
};

FrequencyOrderedList::FrequencyOrderedList()
{
	head = NULL;
	size = 0;
}

void FrequencyOrderedList::insert(const string& word, int frequency)
{
	Node *newNode = new Node;
	newNode->word = word;
	newNode->frequency = frequency;
	newNode->nextLink = NULL;
	newNode->previousLink = NULL;
	++size;

	if (!head) {
		head = newNode;
	} 
	else if (head->frequency < frequency)
	{
		newNode->nextLink = head;
		head->previousLink = newNode;
		head = newNode;
	}
	else {
		Node *currentNode = head, *previousNode = NULL;
		while (currentNode) {
			if (currentNode->frequency < frequency) {
				break;
			}
			previousNode = currentNode;
			currentNode = currentNode->nextLink;
		}
		previousNode->nextLink = newNode;
		newNode->nextLink = currentNode;
		newNode->previousLink = previousNode;
		if (currentNode) {
			currentNode->previousLink = newNode;
		}
	}

}

FrequencyOrderedList::~FrequencyOrderedList()
{
	Node *currentNode;
	if (!head)
		return;

	while (head)
	{
		currentNode = head->nextLink;
		delete head;
		head = currentNode;
	}
}

string FrequencyOrderedList::getWord( int shiftCount )
{
	Node* currentNode = head;
	shiftCount = (shiftCount < size) ? shiftCount : shiftCount % size;
	for (int index = 0; index < shiftCount; ++index) {
		currentNode = currentNode->nextLink;
	}

	++(currentNode->frequency);
	string word = currentNode->word;

	moveNode(currentNode);

	return word;
}

void FrequencyOrderedList::moveNode( Node* nodeToMove )
{
	if (nodeToMove != head) {
		Node* currentNode = nodeToMove->previousLink;
		nodeToMove->previousLink->nextLink = nodeToMove->nextLink;
		if (nodeToMove->nextLink) {
			nodeToMove->nextLink->previousLink = nodeToMove->previousLink;
		}
		nodeToMove->nextLink = NULL;
		nodeToMove->previousLink = NULL;
		while (currentNode) {
			if (currentNode->frequency > nodeToMove->frequency) {
				break;
			}
			currentNode = currentNode->previousLink;
		}
		if (currentNode) {
			nodeToMove->nextLink = currentNode->nextLink;
			nodeToMove->previousLink = currentNode;
			if (currentNode->nextLink) {
				currentNode->nextLink->previousLink = nodeToMove;
			}
			currentNode->nextLink = nodeToMove;
		}
		else {
			nodeToMove->nextLink = head;
			head->previousLink = nodeToMove;
			head = nodeToMove;
		}
	}
}

void initT9(map<char,int>& keyboard) {
	keyboard['.'] = 1;
	keyboard[','] = 1;
	keyboard['?'] = 1;
	keyboard['a'] = 2;
	keyboard['b'] = 2;
	keyboard['c'] = 2;
	keyboard['d'] = 3;
	keyboard['e'] = 3;
	keyboard['f'] = 3;
	keyboard['g'] = 4;
	keyboard['h'] = 4;
	keyboard['i'] = 4;
	keyboard['j'] = 5;
	keyboard['k'] = 5;
	keyboard['l'] = 5;
	keyboard['m'] = 6;
	keyboard['n'] = 6;
	keyboard['o'] = 6;
	keyboard['p'] = 7;
	keyboard['q'] = 7;
	keyboard['r'] = 7;
	keyboard['s'] = 7;
	keyboard['t'] = 8;
	keyboard['u'] = 8;
	keyboard['v'] = 8;
	keyboard['w'] = 9;
	keyboard['x'] = 9;
	keyboard['y'] = 9;
	keyboard['z'] = 9;
}

int numberFromWord(const string& word, map<char,int>& keyboard) {
	int number = 0;
	int wordLength = word.length();
	for (int index = 0; index < wordLength; ++index) {
		number = keyboard[word[index]] + number*10;
	}
	return number;
}

void input(map<int,FrequencyOrderedList*>& dictionary, map<char,int>& keyboard, string& inputString)
{
	initT9(keyboard);
	int n;
	cin >> n;
	
	for (int index = 0; index < n; ++index) {
		string word;
		int wordNumber;
		int frequency;
		cin >> word;
		cin >> frequency;
		wordNumber = numberFromWord(word,keyboard);
		if (dictionary.find(wordNumber) == dictionary.end()) {
			FrequencyOrderedList* list = new FrequencyOrderedList;
			list->insert(word,frequency);
			dictionary[wordNumber] = list;
		} else {
			dictionary[wordNumber]->insert(word,frequency);
		}
	}
	getline(cin,inputString);
	getline(cin,inputString);
	inputString += '\n';
}

void automateT9(const string& inputSequence, map<int,FrequencyOrderedList*>& dictionary)
{
	int sequenceLength = inputSequence.length();
	int currentState = initState;
	int wordCode;
	int starsPressed;
	int currentSignIndex;
	string word;
	string punctualSigns(".,?");
	
	for (int index = 0; index < sequenceLength; ++index) {
		switch (currentState) {
		case initState:
			{
				wordCode = 0;
				starsPressed = 0;
				currentSignIndex = 0;
				switch (inputSequence[index])
				{
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					{
						currentState = wordState;
						wordCode = wordCode*10 + inputSequence[index] - 48;
					}
					break;
				case '*':
					{
						currentState = starsState;
						++starsPressed;
					}
					break;
				case ' ':
					{
						currentState = spaceState;
					}
					break;
				case '1':
					{
						currentState = punctuationState;
					}
					break;
				case '\n':
					{

					}
					break;
				}
			}
			break;
		case wordState:
			{
				switch (inputSequence[index])
				{
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					{
						currentState = wordState;
						wordCode = wordCode*10 + inputSequence[index] - 48;
					}
					break;
				case '*':
					{
						currentState = starsState;
						++starsPressed;
					}
					break;
				case ' ':
					{
						currentState = spaceState;
						cout << dictionary[wordCode]->getWord(starsPressed);
					}
					break;
				case '1':
					{
						currentState = punctuationState;
						cout << dictionary[wordCode]->getWord(starsPressed);
					}
					break;
				case '\n':
					{
						cout << dictionary[wordCode]->getWord(starsPressed);
					}
					break;
				}
			}
			break;
		case starsState:
			{
				switch (inputSequence[index])
				{
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					{
						cout << dictionary[wordCode]->getWord(starsPressed);
						currentState = wordState;
						wordCode = 0;
						starsPressed = 0;
						currentSignIndex = 0;
						wordCode = wordCode*10 + inputSequence[index] - 48;
					}
					break;
				case '*':
					{
						currentState = starsState;
						++starsPressed;
					}
					break;
				case ' ':
					{
						currentState = spaceState;
						cout << dictionary[wordCode]->getWord(starsPressed);
					}
					break;
				case '1':
					{
						currentState = punctuationState;
						cout << dictionary[wordCode]->getWord(starsPressed);
					}
					break;
				case '\n':
					{
						cout << dictionary[wordCode]->getWord(starsPressed);
					}
					break;
				}
			}
			break;
		case punctuationState:
			{
				switch (inputSequence[index])
				{
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					{
						cout << punctualSigns[currentSignIndex];
						currentState = wordState;
						wordCode = 0;
						starsPressed = 0;
						currentSignIndex = 0;
						wordCode = wordCode*10 + inputSequence[index] - 48;
					}
					break;
				case '*':
					{
						currentSignIndex = (++currentSignIndex < 3) ? currentSignIndex : currentSignIndex % 3;
						currentState = punctuationState;
					}
					break;
				case ' ':
					{
						currentState = spaceState;
						cout << punctualSigns[currentSignIndex];
						currentSignIndex = 0;
					}
					break;
				case '1':
					{
						currentState = punctuationState;
						cout << punctualSigns[currentSignIndex];
						currentSignIndex = 0;
					}
					break;
				case '\n':
					{
						cout << punctualSigns[currentSignIndex];
						currentSignIndex = 0;
					}
					break;
				}
			}
			break;
		case spaceState:
			{
				cout << " ";

				switch (inputSequence[index])
				{
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					{
						currentState = wordState;
						wordCode = 0;
						starsPressed = 0;
						currentSignIndex = 0;
						wordCode = wordCode*10 + inputSequence[index] - 48;
					}
					break;
				case '*':
					{
						currentState = starsState;
						++starsPressed;
					}
					break;
				case ' ':
					{
						currentState = spaceState;
					}
					break;
				case '1':
					{
						currentState = punctuationState;
					}
					break;
				case '\n':
					{

					}
					break;
				}
			}
			break;
		default:
			break;
		}
	}
}

int main(int argc, char **argv)
{
	map<char,int> keyboard;
	map<int,FrequencyOrderedList*> dictionary;
	string inputString;

	input(dictionary, keyboard, inputString);

	automateT9(inputString,dictionary);
}