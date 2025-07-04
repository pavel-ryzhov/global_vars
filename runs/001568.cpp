#include <iostream>
#include <vector>
#include <string>
#include <fstream>

//const int keys = 8;
const int keys = 10;
const int maxSize = 21;
typedef char tword[maxSize];

struct TWord;
class TCombi;
class TRoot;
class TTable; 

int star;


inline void printMark(){
	switch (star){
		case 0:
			std::cout << ".";
			break;
		case 1:
			std::cout << ",";
			break;
		case 2:
			std::cout << "?";
			break;
	}
}


struct TWord{
	std::string symbols;
	int cost;
} current;

class TCombi{
	TCombi* offsprings[keys];
	std::vector <TWord> words;		//БЫСТРОДЕЙСТВИЕ. можно попробовать вместо вектора использовать список
	TTable *source;
	int level;
public:
	TCombi();
	void process(std::vector <int> & address);
	void initialize(int level, TTable *source);
	void decipher(std::vector <int> & address);
};

class TRoot{
	static const int level = 0;
	TCombi* offsprings[keys];
	std::vector <int> address;
	std::vector <int> keyTable;
	TTable *source;
public:
	TRoot(TTable *source);
	void addWord(const TWord & word);
	void decipher(std::string & sequence);
};

class TTable{
	int size;
	TCombi *table;
	int iFree; //номер первой незанятой комбинации в массиве.
public:
	TCombi *getFree() {return &(table[iFree++]);}
	TTable(int size);
	~TTable();
};

inline TCombi::TCombi(){  //БЫСТРОДЕЙСТВИЕ. можно инициализировать вектор нулевым барьерным словом
	for (int i = 0; i < keys; i++) 
		offsprings[i] = NULL;
}

inline void TCombi::initialize(int level, TTable *source){
	TCombi::level = level;
	TCombi::source = source;
}

inline void TCombi::process(std::vector<int> & address){
	if (address[level] == 0){
		if (words.empty() || current.cost > words.back().cost)
			words.push_back(current);	//БЫСТРОДЕЙСТВИЕ. записывать быстрее в конец, а считывать из начала(не надо отнимать от размера)
		else{
			for (int i = 0; i <= words.size() - 1; i++)
				if (current.cost <= words[i].cost){
					words.insert(words.begin() + i, current);
					break;
				}
		}
	}
	else {
		TCombi **next = &(offsprings[address[level]]);
		if ((*next) == NULL){
			(*next) = source->getFree();
			(*next)->initialize(level + 1, source);
		}	
		(*next)->process(address);
	}
}

inline void TCombi::decipher(std::vector <int> & address){
	if (address[level] == 0){
		int i = words.size() - 1 - star;
		std::cout << words[i].symbols;
		words[i].cost++;
		while (i < words.size() - 1 && words[i].cost >= words[i+1].cost){
			std::swap(words[i], words[i+1]);
			i++;
		}
	}
	else
		offsprings[address[level]]->decipher(address);
}

TRoot::TRoot(TTable *source){
	address.resize(maxSize);
	for (int i = 0; i < keys; i++) 
		offsprings[i] = NULL;
	keyTable.resize(128, 0);
	for (int i = 48; i < 58; i++)
		keyTable[i] = i - 48;
	int shift = 97;
	for (int i = shift; i < 123; i++){
		if (i == 115 || i == 122)
			shift ++;
		keyTable[i] = (i - shift) / 3 + 2; 
	}
	TRoot::source = source;
}

inline void TRoot::addWord(const TWord &word){
	const std::string &temp = word.symbols; //временная переменная для ускорения. 
	for (int i = 0; i < temp.size(); i++){ 
		address[i] = keyTable[temp[i]];
	}
	address[temp.size()] = 0;
	TCombi **next = &(offsprings[address[level]]);
	if ((*next) == NULL){
		(*next) = source->getFree();
		(*next)->initialize(level + 1, source);
	}	
	(*next)->process(address);
}

void TRoot::decipher(std::string & sequence){
	star = 0;
	int pos = 0;
	bool mark = false;
	for (int i = 0; i < sequence.size(); i++){
		if (sequence[i] == '*')
			star++;
		else if (sequence[i] == '1'){
			if (pos != 0){
				address[pos] = 0;
				offsprings[address[level]]->decipher(address);
				pos = 0;
				star = 0;
			}
			if (mark){
				printMark();
				star = 0;
			}
			mark = true;
		}
		else if (sequence[i] == ' '){
			if (pos != 0){
				address[pos] = 0;
				offsprings[address[level]]->decipher(address);
				pos = 0;
				star = 0;
			}
			if (mark){
				printMark();
				star = 0;
				mark = false;
			}
			std::cout << " ";
		}
		else{
			address[pos] = keyTable[sequence[i]];
			pos++;
		}
	}
	if (pos != 0){
		address[pos] = 0;
		offsprings[address[level]]->decipher(address);
	}
	if (mark)
		printMark();
}

TTable::TTable(int size){
	TTable::size = 4 * size;
	iFree = 0;
	table = new TCombi[TTable::size];
}

TTable::~TTable(){
	delete [] table;
}



int main(int argc, char* argv[])
{
	//-----------------
	//std::ifstream testFile;
	//testFile.open("test.txt");
	//-----------------
	int size;
	std::cin >> size;
	//-----------------
	//testFile >> size;
	//-----------------
	TTable table(size);	
	TRoot root(&table);	

	for (int i = 0; i < size; i++){
		std::cin >> current.symbols;
		std::cin >> current.cost;
		//-----------------
		//testFile >> current.symbols;
		//testFile >> current.cost;
		//std::cout << current.symbols << " ";
		//std::cout << current.cost << std::endl;
		//-----------------
		root.addWord(current);
	}
	std::string sequence;
	std::getline(std::cin, sequence);
	std::getline(std::cin, sequence);
	//-----------------
	//std::getline(testFile, sequence);
	//std::getline(testFile, sequence);
	//-----------------
	root.decipher(sequence);
	//---------------
	//system("pause");
	//---------------
	return 0;
}