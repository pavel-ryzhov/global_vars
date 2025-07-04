#include <iostream>
#include <string>
#include <sstream>
#include <map>

#include <assert.h>

using std::string;

#define NDEBUG 1

class FrequencyOrder
{
private:
	struct Node
	{
		string word;
		int frequency;
		// tree relevant fields
		Node *left, *right, *parent;
		bool isRed;
		int nodesInSubtree;
		
		Node(const string& aWord, int aFrequency) : word(aWord), frequency(aFrequency),
		left(NULL), right(NULL), parent(NULL), isRed(true), nodesInSubtree(1)
		{
		}
		
		~Node()
		{
			if (NULL != left)
			{
				delete left;
				left = NULL;
			}
			if (NULL != right)
			{
				delete right;
				right = NULL;
			}
		}
		
		bool operator<(const Node& other)
		{
			return (this->frequency < other.frequency);
		}
		
		bool operator>(const Node& other)
		{
			return (this->frequency > other.frequency);
		}
	};
	
	Node *_root;
	
	Node *nodeInSubtreeAtIndex(Node *subtree, int index)
	{
		assert(NULL != subtree); // Should not search in empty subtree
		assert(index < subtree->nodesInSubtree); // Searching out of range
		
		Node *result = subtree;
		int nodesInLeftSubtree = nodesInSubtree(subtree->left);
		if (index < nodesInLeftSubtree)
		{
			result = nodeInSubtreeAtIndex(subtree->left, index);
		}
		else if (index > nodesInLeftSubtree)
		{
			result = nodeInSubtreeAtIndex(subtree->right, index - nodesInLeftSubtree - 1);
		}
		// else we have already found necessary node result == subtree
		return result;
	}
	
	// helper functions for simpler work with NULL pointers
	bool isRedNode(const Node *node) const
	{
		return ((NULL != node) && (node->isRed));
	}
	
	int nodesInSubtree(const Node *node) const
	{
		return ((NULL != node) ? node->nodesInSubtree : 0);
	}
	
	void setNodeBlack(Node *node)
	{
		if (NULL != node)
		{
			node->isRed = false;
		}
	}
	
	void setNodeRed(Node *node)
	{
		//sapsay: not sure about this assert
		assert(NULL != node); // NULL nodes are assumed to be always black
		node->isRed = true;
	}
	
#ifndef NDEBUG
	
	int assertIsValid(Node *subtree)
	{
		int height = 1;
		if (subtree != NULL)
		{
			Node *left = subtree->left;
			Node *right = subtree->right;
			//consecutive red nodes
			assert((NULL == left) || !(subtree->isRed && left->isRed));
			assert((NULL == right) || !(subtree->isRed && right->isRed));
			
			//invalid binary search tree
			// should be left >= subtree >= right
			assert((NULL == left) || !(*subtree > *left));
			assert((NULL == right) || !(*subtree < *right));
			
			//invalid number of nodes in subtree
			assert(subtree->nodesInSubtree == (nodesInSubtree(left) + nodesInSubtree(right) + 1));
			
			//black height mismatch
			int leftHeight = assertIsValid(left);
			int rightHeight = assertIsValid(right);
			assert(leftHeight == rightHeight);
			
			//only count black nodes
			height = (subtree->isRed ? leftHeight : (leftHeight + 1));
		}
		return height;
	}
	
	friend int main(int argc, const char *argv[]);
#endif
	
	void leftRotate(Node *pivotNode)
	{
		assert((NULL != pivotNode) && (NULL != pivotNode->right)); // rotation restriction
		/*
		 *         pivotNode
		 *         /        \
		 *     leftChild   newRoot
		 *                 /     \
		 *     leftGrandChild    rightGrandChild
		 *
		 * TURNS INTO
		 *               newRoot
		 *               /      \
		 *        pivotNode     rightGrandChild 
		 *        /       \      
		 *  leftChild   leftGrandChild
		 */
		Node *newRoot = pivotNode->right;
		// left grandchild becomes right child
		Node *leftGrandChild = newRoot->left;
		pivotNode->right = leftGrandChild;
		if (NULL != leftGrandChild)
		{
			leftGrandChild->parent = pivotNode;
		}
		// change parent
		newRoot->parent = pivotNode->parent;
		if (NULL != pivotNode->parent)
		{
			bool isPivotNodeLeftChild = (pivotNode == pivotNode->parent->left);
			if (isPivotNodeLeftChild)
			{
				pivotNode->parent->left = newRoot;
			}
			else
			{
				pivotNode->parent->right = newRoot;
			}
		}
		else
		{
			assert(pivotNode == _root); // Only root does have NULL parent
			_root = newRoot;
		}
		// pivot node becomes left child of newRoot
		newRoot->left = pivotNode;
		pivotNode->parent = newRoot;
		// fix nodesInSubtree
		int leftChildCount = nodesInSubtree(pivotNode->left);
		int leftGrandChildCount = nodesInSubtree(leftGrandChild);
		int rightGrandChildCount = nodesInSubtree(newRoot->right);
		pivotNode->nodesInSubtree = leftChildCount + leftGrandChildCount + 1;
		newRoot->nodesInSubtree = pivotNode->nodesInSubtree + rightGrandChildCount + 1;
	}
	
	void rightRotate(Node *pivotNode)
	{
		assert((NULL != pivotNode) && (NULL != pivotNode->left)); // rotation restriction
		/*
		 *                pivotNode
		 *                /       \
		 *             newRoot  rightChild
		 *             /    \
		 * leftGrandChild  rightGrandChild
		 *
		 * TURNS INTO
		 *                newRoot
		 *                /     \
		 *    leftGrandChild    pivotNode
		 *                       /      \      
		 *          rightGrandChild   rightChild
		 */
		Node *newRoot = pivotNode->left;
		// right grandchild becomes left child
		Node *rightGrandChild = newRoot->right;
		pivotNode->left = rightGrandChild;
		if (NULL != rightGrandChild)
		{
			rightGrandChild->parent = pivotNode;
		}
		// change parent
		newRoot->parent = pivotNode->parent;
		if (NULL != pivotNode->parent)
		{
			bool isPivotNodeLeftChild = (pivotNode == pivotNode->parent->left);
			if (isPivotNodeLeftChild)
			{
				pivotNode->parent->left = newRoot;
			}
			else
			{
				pivotNode->parent->right = newRoot;
			}
		}
		else
		{
			assert(pivotNode == _root); // Only root does have NULL parent
			_root = newRoot;
		}
		// pivot node becomes right child of newRoot
		newRoot->right = pivotNode;
		pivotNode->parent = newRoot;
		// fix nodesInSubtree
		int leftGrandChildCount = nodesInSubtree(newRoot->left);
		int rightGrandChildCount = nodesInSubtree(rightGrandChild);
		int rightChildCount = nodesInSubtree(pivotNode->right);
		pivotNode->nodesInSubtree = rightGrandChildCount + rightChildCount + 1;
		newRoot->nodesInSubtree = leftGrandChildCount + pivotNode->nodesInSubtree + 1;
	}
	
	void insertNodePuttingEqualToLeftSubtree(Node *node)
	{
		Node *insertedNodeParent = NULL;
		Node *placeToInsert = _root;
		// find place to insert
		while (NULL != placeToInsert)
		{
			insertedNodeParent = placeToInsert;
			if (*node < *placeToInsert)
			{
				placeToInsert = placeToInsert->right;
			}
			else
			{
				placeToInsert = placeToInsert->left;
			}
		}
		// insert node
		node->parent = insertedNodeParent;
		if (NULL != insertedNodeParent)
		{
			if (*node < *insertedNodeParent)
			{
				insertedNodeParent->right = node;
			}
			else
			{
				insertedNodeParent->left = node;
			}
		}
		else
		{
			assert(NULL == _root); // no parent is when inserting first node
			_root = node;
		}
		// trace number of nodes in subtree
		Node *subtreeWithInsertedNode = node->parent;
		while (NULL != subtreeWithInsertedNode)
		{
			subtreeWithInsertedNode->nodesInSubtree++;
			subtreeWithInsertedNode = subtreeWithInsertedNode->parent;
		}
		insertFixup(node);
	}
	
	void insertNodePuttingEqualToRightSubtree(Node *node)
	{
		Node *insertedNodeParent = NULL;
		Node *placeToInsert = _root;
		// find place to insert
		while (NULL != placeToInsert)
		{
			insertedNodeParent = placeToInsert;
			if (*node > *placeToInsert)
			{
				placeToInsert = placeToInsert->left;
			}
			else
			{
				placeToInsert = placeToInsert->right;
			}
		}
		// insert node
		node->parent = insertedNodeParent;
		if (NULL != insertedNodeParent)
		{
			if (*node > *insertedNodeParent)
			{
				insertedNodeParent->left = node;
			}
			else
			{
				insertedNodeParent->right = node;
			}
		}
		else
		{
			assert(NULL == _root); // no parent is when inserting first node
			_root = node;
		}
		// trace number of nodes in subtree
		Node *subtreeWithInsertedNode = node->parent;
		while (NULL != subtreeWithInsertedNode)
		{
			subtreeWithInsertedNode->nodesInSubtree++;
			subtreeWithInsertedNode = subtreeWithInsertedNode->parent;
		}
		insertFixup(node);
	}
	
	void insertFixup(Node *node)
	{
		assert(isRedNode(node)); // Always insert and therefore fixup red node
		while (isRedNode(node->parent))
		{
			assert(NULL != node->parent->parent); // Red node always has a parent
			bool isFixingLeftSubtree = (node->parent == node->parent->parent->left);
			if (isFixingLeftSubtree)
			{
				Node *parentSibling = node->parent->parent->right;
				if (isRedNode(parentSibling))
				{
					// recolor parent, sibling and their parent
					node->parent->isRed = false;
					if (NULL != parentSibling)
					{
						parentSibling->isRed = false;
					}
					node->parent->parent->isRed = true;
					node = node->parent->parent;
				}
				else
				{
					if (node == node->parent->right)
					{
						node = node->parent;
						// remember that rotation moves node deeper in the tree
						leftRotate(node);
					}
					node->parent->isRed = false;
					node->parent->parent->isRed = true;
					rightRotate(node->parent->parent);
				}
			}
			else // symmetric part
			{
				Node *parentSibling = node->parent->parent->left;
				if (isRedNode(parentSibling))
				{
					// recolor parent and their parent
					node->parent->isRed = false;
					if (NULL != parentSibling)
					{
						parentSibling->isRed = false;
					}
					node->parent->parent->isRed = true;
					node = node->parent->parent;
				}
				else
				{
					if (node == node->parent->left)
					{
						node = node->parent;
						// remember that rotation moves node deeper in the tree
						rightRotate(node);
					}
					node->parent->isRed = false;
					node->parent->parent->isRed = true;
					leftRotate(node->parent->parent);
				}
			}
		}
		_root->isRed = false;
	}
	
	// removing helper functions
	Node *leftMostNodeInSubtree(Node *subtree)
	{
		assert(NULL != subtree); // Input argument restriction
		Node *result = subtree;
		while (NULL != result->left)
		{
			result = result->left;
		}
		return result;
	}
	
	Node *nextNode(Node *node)
	{
		assert(NULL != node); // Input argument restriction
		Node *result = NULL;
		if (NULL != node->right)
		{
			result = leftMostNodeInSubtree(node->right);
		}
		else
		{
			Node *parent = node->parent;
			// go up the tree until parent is parent of left subtree
			while ((NULL != parent) && (node == parent->right))
			{
				node = parent;
				parent = node->parent;
			}
			result = parent;
		}
		return result;
	}
	
	// Be aware that this method frees memory occupied by removed node.
	void removeNode(Node *node)
	{
		assert(NULL != node); // Input argument restriction
		Node *nodeToRemove = node;
		if ((NULL != node->left) && (NULL != node->right))
		{
			nodeToRemove = nextNode(node);
			assert(NULL != nodeToRemove); // If right subtree is not null, then there should always be next node
		}
		Node *nodeToPullUp = (NULL != nodeToRemove->left) ? nodeToRemove->left : nodeToRemove->right;
		// place nodeToPullUp instead of nodeToRemove
		Node *pulledUpNodeParent = nodeToRemove->parent;
		if (NULL != nodeToPullUp)
		{
			nodeToPullUp->parent = pulledUpNodeParent;
		}
		if (NULL != nodeToRemove->parent)
		{
			bool isRemovingLeftChild = (nodeToRemove == nodeToRemove->parent->left);
			if (isRemovingLeftChild)
			{
				nodeToRemove->parent->left = nodeToPullUp;
			}
			else
			{
				nodeToRemove->parent->right = nodeToPullUp;
			}
		}
		else
		{
			_root = nodeToPullUp;
		}
		// trace number of nodes in subtree
		Node *subtreeWithRemovedNode = nodeToRemove->parent;
		while (NULL != subtreeWithRemovedNode)
		{
			subtreeWithRemovedNode->nodesInSubtree--;
			subtreeWithRemovedNode = subtreeWithRemovedNode->parent;
		}
		
		if (nodeToRemove != node)
		{
			node->word = nodeToRemove->word;
			node->frequency = nodeToRemove->frequency;
		}
		
		if (!nodeToRemove->isRed)
		{
			removeFixup(nodeToPullUp, pulledUpNodeParent);
		}
		// free nodeToRemove
		nodeToRemove->left = nodeToRemove->right = nodeToRemove->parent = NULL;
		delete nodeToRemove;
	}
	
	//sapsay: what the mess. Just hope it will work
	void removeFixup(Node *fixNode, Node *fixNodeParent)
	{
		while ((fixNode != _root) && !isRedNode(fixNode))
		{
			if (fixNode == fixNodeParent->left)
			{
				Node *fixNodeSibling = fixNodeParent->right;
				// case 1
				if (isRedNode(fixNodeSibling))
				{
					setNodeBlack(fixNodeSibling);
					setNodeRed(fixNodeParent);
					leftRotate(fixNodeParent);
					// after rotation previous sibling is parent of fixNodeParent
					fixNodeSibling = fixNodeParent->right;
				}
				assert(NULL != fixNodeSibling); // If removed black node, then its sibling cannot be NULL
				// case 2
				if ((!isRedNode(fixNodeSibling->left) && !isRedNode(fixNodeSibling->right)))
				{
					setNodeRed(fixNodeSibling);
					fixNode = fixNodeParent;
					fixNodeParent = fixNode->parent;
				}
				else
				{
					if (!isRedNode(fixNodeSibling->right))
					{
						// case 3
						setNodeBlack(fixNodeSibling->left);
						setNodeRed(fixNodeSibling);
						rightRotate(fixNodeSibling);
						fixNodeSibling = fixNodeParent->right;
					}
					// case 4
					if (isRedNode(fixNodeParent))
					{
						setNodeRed(fixNodeSibling);
					}
					else
					{
						setNodeBlack(fixNodeSibling);
					}
					setNodeBlack(fixNodeParent);
					setNodeBlack(fixNodeSibling->right);
					leftRotate(fixNodeParent);
					fixNode = _root;
					fixNodeParent = NULL;
				}
			}
			else // symmetric part
			{
				Node *fixNodeSibling = fixNodeParent->left;
				// symmetric case 1
				if (isRedNode(fixNodeSibling))
				{
					setNodeBlack(fixNodeSibling);
					setNodeRed(fixNodeParent);
					rightRotate(fixNodeParent);
					// after rotation previous sibling is parent of fixNodeParent
					fixNodeSibling = fixNodeParent->left;
				}
				assert(NULL != fixNodeSibling); // If removed black node, then its sibling cannot be NULL
				// symmetric case 2
				if ((!isRedNode(fixNodeSibling->left) && !isRedNode(fixNodeSibling->right)))
				{
					setNodeRed(fixNodeSibling);
					fixNode = fixNodeParent;
					fixNodeParent = fixNode->parent;
				}
				else
				{
					if (!isRedNode(fixNodeSibling->left))
					{
						// symmetric case 3
						setNodeBlack(fixNodeSibling->right);
						setNodeRed(fixNodeSibling);
						leftRotate(fixNodeSibling);
						fixNodeSibling = fixNodeParent->left;
					}
					// symmetric case 4
					if (isRedNode(fixNodeParent))
					{
						setNodeRed(fixNodeSibling);
					}
					else
					{
						setNodeBlack(fixNodeSibling);
					}
					setNodeBlack(fixNodeParent);
					setNodeBlack(fixNodeSibling->left);
					rightRotate(fixNodeParent);
					fixNode = _root;
					fixNodeParent = NULL;
				}
			}
		}
		if (NULL != fixNode)
		{
			fixNode->isRed = false;
		}
	}
	
public:
	explicit FrequencyOrder() : _root(NULL)
	{
		// left blank because no additional initialization is needed
	}
	
	~FrequencyOrder()
	{
		if (NULL != _root)
		{
			delete _root;
			_root = NULL;
		}
	}
	
	void addWordWithFrequency(const string& word, int frequency)
	{
		Node *node = new Node(word, frequency);
		insertNodePuttingEqualToRightSubtree(node);
	}
	
	string wordAtIndexIncreasingFrequency(int index)
	{
		assert(NULL != _root); // Should not ask for word in empty frequency arranger
		Node *nodeAtIndex = _root;
		if (_root->nodesInSubtree > 1)
		{
			// search and rearrange the tree if it has more than one node
			nodeAtIndex = nodeInSubtreeAtIndex(_root, index % _root->nodesInSubtree);
			assert(NULL != nodeAtIndex); // Should always be able to find some node
			string wordAtIndex = nodeAtIndex->word;
			int frequencyAtIndex = nodeAtIndex->frequency;
			removeNode(nodeAtIndex);
			// nodeAtIndex may be invalid
			nodeAtIndex = new Node(wordAtIndex, frequencyAtIndex + 1);
			insertNodePuttingEqualToLeftSubtree(nodeAtIndex);
		}
		else
		{
			nodeAtIndex->frequency++;
		}
		return nodeAtIndex->word;
	}
};

class MessageDecoder
{
private:
	typedef enum
	{
		MessageInitialState = 0,
		MessageWordState,
		MessagePunctuationState,
	} MessageState;
	
	typedef std::map<string, FrequencyOrder *> Dictionary;
	Dictionary _dictionary;
	
	bool isSpaceCode(char symbolCode)
	{
		return (' ' == symbolCode);
	}
	
	bool isLetterCode(char symbolCode)
	{
		return (('2' <= symbolCode) && (symbolCode <= '9'));
	}
	
	bool isPunctuationMarkCode(char symbolCode)
	{
		return ('1' == symbolCode);
	}
	
	bool isNextTokenCode(char symbolCode)
	{
		return ('*' == symbolCode);
	}
	
	string wordAtIndex(const string& encodedWord, int index)
	{
		Dictionary::const_iterator groupForEncodedWordIterator = _dictionary.find(encodedWord);
		assert(_dictionary.end() != groupForEncodedWordIterator); // There is no such a word in dictionary
		return groupForEncodedWordIterator->second->wordAtIndexIncreasingFrequency(index);
	}
	
	string punctuationMarkAtIndex(int index)
	{
		const static string sPunctuationMarks[] = {".", ",", "?"};
		return sPunctuationMarks[index % 3];
	}
	
	string encodeWord(const string& word)
	{
		const static char sCharacterToButton[] = {
			'2', '2', '2', //abc
			'3', '3', '3', //def
			'4', '4', '4', //ghi
			'5', '5', '5', //jkl
			'6', '6', '6', //mno
			'7', '7', '7', '7', //pqrs
			'8', '8', '8', //tuv
			'9', '9', '9', '9' //wxyz
		};
		string result = "";
		for (int i = 0; i < word.length(); i++)
		{
			result += string(1, sCharacterToButton[word[i] - 'a']);
		}
		return result;
	}
	
public:
	~MessageDecoder()
	{
		Dictionary::iterator i;
		for (i = _dictionary.begin(); i != _dictionary.end(); ++i)
		{
			delete i->second;
			i->second = NULL;
		}
	}
	
	void addToDictionaryWordWithFrequency(const string& word, int frequency)
	{
		string encodedWord = encodeWord(word);
		FrequencyOrder *groupForEncodedWord = NULL;
		Dictionary::const_iterator groupForEncodedWordIterator = _dictionary.find(encodedWord);
		if (_dictionary.end() == groupForEncodedWordIterator)
		{
			groupForEncodedWord = new FrequencyOrder;
			_dictionary[encodedWord] = groupForEncodedWord;
		}
		else
		{
			groupForEncodedWord = groupForEncodedWordIterator->second;
		}
		groupForEncodedWord->addWordWithFrequency(word, frequency);
	}
	
	//TODO: a lot of code is duplicated, think how you can improve this
	string decodeMessage(const string& message)
	{
		// initialize variables
		string result = "";
		size_t currentMessagePosition = 0;
		MessageState state = MessageInitialState;
		int tokenIndex = 0; // index of word or punctuation mark
		string wordToDecode = "";
		
		// decode message character by character
		while (currentMessagePosition < message.size())
		{
			char symbolCode = message[currentMessagePosition];
			if (isNextTokenCode(symbolCode))
			{
				assert(MessageInitialState != state); // * cannot be after space
				tokenIndex++;
			}
			else // letter, punctuation or space
			{
				// we are leaving current state, except when encountering one more letter in MessageWordState
				// therefore need to handle state which we are leaving
				if (MessagePunctuationState == state)
				{
					result += punctuationMarkAtIndex(tokenIndex);
				}
				else if ((MessageWordState == state) && (!isLetterCode(symbolCode) || (tokenIndex > 0)))
				{
					assert(wordToDecode.size() > 0); // Should not be in word state with empty word to decode.
					result += wordAtIndex(wordToDecode, tokenIndex);
					wordToDecode.clear();
				}
				
				// set new state
				if (isLetterCode(symbolCode))
				{
					state = MessageWordState;
					wordToDecode += symbolCode;
				}
				else if (isPunctuationMarkCode(symbolCode))
				{
					state = MessagePunctuationState;
				}
				else if (isSpaceCode(symbolCode))
				{
					state = MessageInitialState;
					result += " ";
				}
				else
				{
					assert(false); // Message contains invalid character.
				}
				tokenIndex = 0;
			}
			currentMessagePosition++;
		}
		
		// decode pending token
		//sapsay: could have added and removed space at end, but this will do
		if (MessagePunctuationState == state)
		{
			result += punctuationMarkAtIndex(tokenIndex);
		}
		else if (MessageWordState == state)
		{
			assert(wordToDecode.size() > 0); // Should not be in word state with empty word to decode.
			result += wordAtIndex(wordToDecode, tokenIndex);
			wordToDecode.clear();
		}
		return result;
	}
};

int main(int argc, const char*argv[])
{
	MessageDecoder messageDecoder;
	
	int wordsCount;
	std::cin >> wordsCount;
	//discard newline symbol after number of words in dictionary
	std::cin.get();
	for (int i = 0; i < wordsCount; i++)
	{
		// read word and frequency
		std::stringbuf wordBuffer;
		std::cin.get(wordBuffer, ' ');
		int wordFrequency;
		std::cin >> wordFrequency;
		//discard newline symbol after word frequency
		std::cin.get();
		messageDecoder.addToDictionaryWordWithFrequency(wordBuffer.str(), wordFrequency);
	}
	string message;
	std::getline(std::cin, message);
	std::cout << messageDecoder.decodeMessage(message) << std::endl;
	return 0;
}
