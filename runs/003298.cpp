#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cstring>

using namespace std;

class dictWord
{
	private:
		string word;
		long rate;
	public:
		dictWord(string word, long rate);
		int operator==(dictWord word2) {return rate == word2.rate;}
		int operator!=(dictWord word2) {return rate != word2.rate;}
		int operator<(dictWord word2) {return rate < word2.rate;}
		int operator>(dictWord word2) {return rate > word2.rate;}
		int operator<=(dictWord word2) {return rate <= word2.rate;}
		int operator>=(dictWord word2) {return rate >= word2.rate;}
		dictWord operator=(dictWord word2);
		dictWord operator++() {rate++; return *this;}
		dictWord operator++(int notUsed) {rate++; return *this;}
		string getWord() {return this->word;}
		long getRate() {return this->rate;}
};

dictWord::dictWord(string word = "", long rate = 0)
{
	this->word = word;
	this->rate = rate;
}

dictWord dictWord::operator=(dictWord word2)
{
	this->word = word2.word;
	this->rate = word2.rate;
	return *this;
}

class node
{
	private:
		node *links[8];
		vector<dictWord> words;
		map<long, long> wordsMap;
	public:
		node();
		void addLink(int num, node *link) {links[num] = link;}
		void addWord(dictWord word);
		node *getLink(int num) {return links[num];}
		long getWordsCount() {return words.size();}
		string getStringAndIncreaseRate(long offset);
		void buildMaps(void);
};

node::node()
{
	for (int i = 0; i < 8; i++) links[i] = NULL;
}

void node::addWord(dictWord word)
{
	long length = words.size();
	if (!length) words.push_back(word);
	else
	{
		vector<dictWord>::iterator bIt = words.begin();
		long b = 0;
		long e = length;
		long step = length == 1?1:length>>1;
		long p = b + step;
		while(true)
		{
			step = step == 1?1:step>>1;
			if (p == e)
			{
				if (words[p-1] >= word)
				{
					words.insert(bIt+e, word);
					break;
				}
				else p -= step;	   
			}
			else if (words[p] < word)
			{
				if (p == b)
				{
					words.insert(bIt+b, word);
					break;
				}
				else if (words[p-1] >= word)
				{
					words.insert(bIt+p, word);
					break;
				}
				else p -= step;
			}
			else
			{
				if (words[p+1] < word)
				{
					words.insert(bIt+p+1, word);
					break;
				}
				else p += step;
			}
		}
	}
}

void node::buildMaps(void)
{
 	 long wordsCount = words.size();
 	 if (wordsCount)
 	 {
      	 long p = 0;
      	 wordsMap[words[0].getRate()] = p;
      	 for (p = 1; p < wordsCount; p++)
      	 {
		  	 long rateCur = words[p].getRate();
		  	 long ratePrev = words[p-1].getRate();
		  	 if (ratePrev > rateCur) wordsMap[rateCur] = p; 
		 }
	 }
 	 for (int i = 0; i < 8; i++)
 	 {
	  	 if (links[i]) links[i]->buildMaps();
	 }
}

string node::getStringAndIncreaseRate(long offset)
{
	dictWord curWord = words[offset];
	long curRate = curWord.getRate();
	string res = words[offset].getWord();
	curWord++;
	map<long, long>::iterator end = wordsMap.end();
	map<long, long>::iterator p;
	vector<dictWord>::iterator bIt = words.begin();
	if ((p = wordsMap.find(curRate + 1)) == end)
	{
	    long curOffset = wordsMap[curRate];
	 	words.erase(bIt + offset);
	 	words.insert(bIt + curOffset, curWord);
		wordsMap[curRate + 1] = curOffset;
		wordsMap[curRate]++;     	   
	}
	else
	{
	 	words.erase(bIt + offset);
	 	words.insert(bIt + wordsMap[curRate + 1], curWord);
	 	wordsMap[curRate]++;
	}
	return res;
}

node *buildTree()
{
	long wordsCount;
	cin >> wordsCount;
	node *tree = new(nothrow) node;
	if (!tree) return NULL;
	for (long i = 0; i < wordsCount; i++)
	{
		string word;
		cin >> word;
		long rate;
		cin >> rate;
		node *temp = tree;
		for (long j = 0; j < word.length(); j++)
		{
		 	 int num;
			 switch (word[j])
			 {
			 	 case 'a': case 'b': case 'c':
				 	   num = 0;
					   break;
			 	 case 'd': case 'e': case 'f':
				 	   num = 1;
					   break;
			 	 case 'g': case 'h': case 'i':
				 	   num = 2;
					   break;
			 	 case 'j': case 'k': case 'l':
				 	   num = 3;
					   break;
			 	 case 'm': case 'n': case 'o':
				 	   num = 4;
					   break;
			 	 case 'p': case 'q': case 'r': case 's':
				 	   num = 5;
					   break;
			 	 case 't': case 'u': case 'v':
				 	   num = 6;
					   break;
			 	 case 'w': case 'x': case 'y': case 'z':
				 	   num = 7;
					   break;
			 	 default:
				 	   return NULL;				 						   					   							   					   					    		
  			 }
			 if (!temp->getLink(num))
			 {
	 	 		node *newNode = new(nothrow) node;
		  		if (!newNode) return NULL;
		  		temp->addLink(num, newNode);
		  		temp = newNode;
			 }
			 else temp = temp->getLink(num);
		}
		temp->addWord(dictWord(word, rate));	  	 
	}
	return tree;
}

void computeT9(node *tree)
{
 	 int ch = getchar();
 	 ch = getchar();
 	 while (true)
 	 {
	  	   if (ch == '\n' || ch == '\0' || ch == EOF) break;
	  	   else if (ch == ' ')
	  	   {
		   		cout << " ";
		   		ch = getchar();
	   	   }
		   else if (ch == '1')
		   {
		   		long astNum = 0;
		   		while ((ch = getchar()) == '*') astNum++;
		   		astNum %= 3;
		   		if (astNum == 0) cout << ".";
		   		else if (astNum == 1) cout << ",";
		   		else cout << "?";
	   	   }
	   	   else if (ch - '0' >= 2 && ch - '0' <= 9)
	   	   {
		   		node *temp = tree->getLink(ch - '0' - 2);
		   		long astNum = 0;
		   		ch = getchar();
		   		while (ch - '0' >= 2 && ch - '0' <= 9)
		   		{
		   		 	temp = temp->getLink(ch - '0' - 2);
		   		 	ch = getchar();
			    }
			    while (ch == '*')
				{
 	  			 	  astNum++;
 	  			 	  ch = getchar();
		        }
  			    astNum %= temp->getWordsCount();
  			    cout << temp->getStringAndIncreaseRate(astNum);
		   }
		   else cout << "[Err] Wrong input";
	 }
	 cout << endl;
}



int main()
{
 	node *tree = buildTree();
 	if (!tree)
 	{
     	cerr << "Memory error" << endl;
     	return 1;
    }
    tree->buildMaps();
    computeT9(tree);
	return 0;
}
