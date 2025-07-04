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


//inline void printSign(){
//	switch (star){
//		case 0:
//			std::cout << ".";
//			break;
//		case 1:
//			std::cout << ",";
//			break;
//		case 2:
//			std::cout << "?";
//			break;
//	}
//}


struct TWord{
	std::string symbols;
	int cost;
} current;

class TCombi{
	TCombi* offsprings[keys];
	std::vector <TWord> words;		//��������������. ����� ����������� ������ ������� ������������ ������
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
	int iFree; //����� ������ ��������� ���������� � �������.
public:
	TCombi *getFree() {return &(table[iFree++]);}
	TTable(int size);
	~TTable();
};

inline TCombi::TCombi(){  //��������������. ����� ���������������� ������ ������� ��������� ������
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
			words.push_back(current);	//��������������. ���������� ������� � �����, � ��������� �� ������(�� ���� �������� �� �������)
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
	const std::string &temp = word.symbols; //��������� ���������� ��� ���������. 
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
	address.clear();
	for (int i = 0; i < sequence.size(); i++){
		if (sequence[i] == ' '){
			address.push_back(0);
			offsprings[address[level]]->decipher(address);
			std::cout << " ";
			star = 0;
			address.clear();	//��������������. ������ �� ���� �������. ���� ������� ����������, ������� ����� ���������� �� ������� ������������ � �������� �� � ������ ������
		}
		else if (sequence[i] == '1'){
			if (! address.empty()){
				address.push_back(0);
				offsprings[address[level]]->decipher(address);
				star = 0;
				address.clear();
			}
			if (sequence[i + 1] != '*'){
				std::cout << '.';
			}
			else if (sequence[i + 1] == '*' && sequence[i + 2] != '*'){
				std::cout << ',';	
				i++;
			}
			else{
				std::cout << '?';
				i = i + 2;
			}
		}
		else if (sequence[i] == '*')
			star++;
		else //��������������. ��� ������� ���� ������� ������ �� ����, �� ��� ���� �����������
			address.push_back(keyTable[sequence[i]]);
	}
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
	while (sequence.size() == 0){
		std::getline(std::cin, sequence);
		//-----------------
		//std::getline(testFile, sequence);
		//-----------------
	}
	root.decipher(sequence);


	//---------------
	//system("pause");
	//---------------
	return 0;
}