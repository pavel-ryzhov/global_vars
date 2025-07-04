#include <map>
#include <string>
#include <list>
#include <functional>
#include <algorithm>
#include <iostream>
#include <fstream>

// ��������-����������
// ������ ����������� '������' -> '������� ��������'
class Keyboard {
// ���������������/����������
private:
	Keyboard();
// �������� �������-�����
public:
	// ��������� ������ �� ������
	static Keyboard& Instance() {
		static Keyboard keyb;
		return keyb;
	}
	// ��������� ������� �������� ��� ������
	std::string GetSymbol(char inSym) {
		return m_Symbols[inSym];
	}
// �������� ������-�����
private:
	// ����������� ������ �� ������� ��������
	std::map<char, std::string > m_Symbols;
};

// ������-���������� ��� ��������� ������� ������� �� �����
template<typename T>
struct word_less : public std::binary_function<T, T, bool> {
	bool operator()(const T& lhs, const T& rhs) {
		return lhs.first < rhs.first;
	}
};

// ������-���������� ��� ��������� ������� ������� �� ���������� ��������
template<typename T>
struct prio_greater : public std::binary_function<T, T, bool> {
	bool operator()(const T& lhs, const T& rhs) {
		return lhs.second > rhs.second;
	}
};

// ��������� �������� ����:
// ������ ���� �������� � ����������� �� ����� -
// ������� �������� ������
// ��������� �������� - ��� ���������� �� ������ ��������
template<typename T>
struct Wordmap {
	// ������ ����� ���� - '����� - ��������� ��������'
	typedef std::pair<std::string, T> entry_type;
	// ������ ���� � �������
	typedef typename std::list<entry_type> bucket_type;
	// �������� ������
	typedef typename bucket_type::iterator bucket_it;
	// ��� �����������
	typedef std::map<std::string, bucket_type> map_type;
	// �������� �����������
	typedef typename map_type::iterator map_it;
	Wordmap();
	// ������� ����
	std::map<std::string, bucket_type> buckets;
};

/*
������ �������: T - ��� ���������� �� ������ �������� (����� - ���������),
WordComp - ���������� ������� �� ��������,
PrioComp - ���������� ������� �� ����������
C���� ����������� � ������������� �� ����������, �
��� ��������� �� ���������� - � ������������������ �������.
���������� ���������� �������� ������������������ ������� ���������� ������� ����������
*/
template<typename T = unsigned, typename WordComp = word_less<typename Wordmap<T>::entry_type>, typename PrioComp = prio_greater<typename Wordmap<T>::entry_type> >
class Dictionary {
// �������� ����������� �����
public:
	// �������� ��������� ������ � ����� ���� �������
	typedef typename Wordmap<T>::bucket_it word_it;
	// �������� ����� ����
	typedef typename Wordmap<T>::map_it wordmap_it;
// �������� �������-�����
public:
	// �������� ����� � �������
	void AddWord(const std::string& inWord, T inPrio);
	// �������� ��������� ����� (������ ��������������� �� ������� ��� ���������� �����������)
	void IncreasePriority(typename Wordmap<T>::bucket_it inIt);
	// �������� ������ � ����� ������� ����
	std::pair<word_it, word_it> GetBucket(const std::string& inWord) {
		wordmap_it it = m_Dict.buckets.find(inWord);
		return std::make_pair<word_it, word_it>(it->second.begin(), it->second.end());
	}
// �������� �������-�����
private:
	// ��������� ��������� ����� ����, ���������������� �������
	wordmap_it FindBucket(const std::string& inWord) {
		wordmap_it it = m_Dict.buckets.lower_bound(inWord);
		// ��������, �������� lower_bound, ������������� ������� �������
		//if(it->first[p] < inWord[0])
		if(!Contains(it, inWord[0]))
			--it;
		return it;
	}
	bool Contains(const wordmap_it& inIt, char inSym) {
		if(inIt == m_Dict.buckets.end())
			return false;
		for(std::string::const_iterator it = inIt->first.begin(); it != inIt->first.end(); ++it) {
			if((*it) == inSym)
				return true;
		}
		return false;
	}
// �������� ������-�����
private:
	// ����� ����
	Wordmap<T> m_Dict;
};

// ������ �������
void ReadDictionary(std::basic_istream<char>& inStream, Dictionary<>& inDict);

/*
���������� ����������������� �����:
��� ����� ������ ����� �������� ��� �����
�� ������� ������� �������, ������ �� ��� ���������� ������
(�������� � ���� ��������� ����� ���� ���������� �������)
� ������������ ������ (��������������� ������);
��� ����� ����������� �������� ����������� ���������� � ������������ �������
*/
class Parser {
	// ��� ��������� ������������� �������: '�������� ����� � ������� - ���������'
	typedef std::pair<Wordmap<unsigned>::bucket_it, unsigned> dictionary_ind;
// ���������������/����������
public:
	Parser(Dictionary<>& inDict) : m_Dict(&inDict), m_Index(NULL), m_PrioIndex(NULL) {
		Reset();
	}
// �������� �������-�����
public:
	// ��������� ���������� ������� � ������������
	// ������������� �����������
	std::string OnNewInput(char inSym);
// �������� �������-�����
private:
	// ����� ���������� ����� ����������
	void SelectNewPreposition();
	// ���������� ��������
	void UpdateIndex(const std::string& inSymbol);
// �������� ������-�����
private:
	// ���������� ������ - ����� �������
	// � ���������� '������� - �������� ����� � �������'
	Wordmap<Dictionary<>::word_it>* m_Index;
	// ������������ ������
	std::list<dictionary_ind>* m_PrioIndex;
	// ����� ���������
	void Reset();
	// ���������� �������� ��������
	unsigned m_AsteriskCounter;
	// ���������� �������� ������ ����������
	unsigned m_PrepositionCounter;
	// ���������� �������� ����
	unsigned m_NumberCounter;
	// �������
	Dictionary<>* m_Dict;
	// ������������ �����
	std::string m_Text;
};

int main(int argc, char* argv[]) {
	Dictionary<> dict;
	ReadDictionary(std::cin, dict);
	std::string instr = "";
        Parser p(dict);
	// ������ ����� �������
	// ������ ������ �����������
		while(std::cin >> instr) {
		for(unsigned i = 0; i < instr.length(); ++i)
			p.OnNewInput(instr[i]);
		std::string outstr = p.OnNewInput(' ');
		std::cout << outstr;
	}
	return 0;
}


// ���������� Keyboard
////////////////////////////////////////////////////////////////

Keyboard::Keyboard() {
	m_Symbols['1'] = ".,?";
	m_Symbols['2'] = "abc";
	m_Symbols['3'] = "def";
	m_Symbols['4'] = "ghi";
	m_Symbols['5'] = "jkl";
	m_Symbols['6'] = "mno";
	m_Symbols['7'] = "pqrs";
	m_Symbols['8'] = "tuv";
	m_Symbols['9'] = "wxyz";
}

////////////////////////////////////////////////////////////////

// ���������� Wordmap
////////////////////////////////////////////////////////////////
template<typename T>
Wordmap<T>::Wordmap() {
	// ������������� �������� ������� ��������
	buckets.insert(typename map_type::value_type("abc", bucket_type(0)));
	buckets.insert(typename map_type::value_type("def", bucket_type(0)));
	buckets.insert(typename map_type::value_type("ghi", bucket_type(0)));
	buckets.insert(typename map_type::value_type("jkl", bucket_type(0)));
	buckets.insert(typename map_type::value_type("mno", bucket_type(0)));
	buckets.insert(typename map_type::value_type("pqrs", bucket_type(0)));
	buckets.insert(typename map_type::value_type("tuv", bucket_type(0)));
	buckets.insert(typename map_type::value_type("wxyz", bucket_type(0)));
	// "������" ������ ����������� ��� ���������� ������� ��������
	// � ������� (Parser::UpdateIndex)
	buckets.insert(typename map_type::value_type("", bucket_type(0)));
}

////////////////////////////////////////////////////////////////

// ���������� Dictionary
////////////////////////////////////////////////////////////////
// ���������� ����� � �������
template<typename T, typename WordComp, typename PrioComp>
void Dictionary<T, WordComp, PrioComp>::AddWord(const std::string& inWord, T inPrio) {
	// ��������� �������
	wordmap_it it = FindBucket(inWord);
	typedef typename std::pair<word_it, word_it> bucketpair;
	typedef typename Wordmap<T>::bucket_type::value_type word_type;
	// ��������� ��������� ���� � ������������, ������ ������� �� �������
	bucketpair prio_its = std::equal_range(it->second.begin(), it->second.end(), word_type(inWord, inPrio - 1), PrioComp());
	// ����� � ���� ��������� ����� �� ��������
	word_it final_it = std::lower_bound(prio_its.first, prio_its.second, word_type(inWord, inPrio), WordComp());
	it->second.insert(final_it, word_type(inWord, inPrio));
}

// ���������� ����������
template<typename T, typename WordComp, typename PrioComp>
void Dictionary<T, WordComp, PrioComp>::IncreasePriority(typename Wordmap<T>::bucket_it inIt) {
	wordmap_it it = FindBucket(inIt->first);
	typedef typename std::pair<word_it, word_it> bucketpair;
	typedef typename Wordmap<T>::bucket_type::value_type word_type;
	T prio = inIt->second;
	std::string word = inIt->first;
	it->second.erase(inIt);
	// ������� ����� ����� ���������� ���� � �����������, ������ ������� ��������
	bucketpair prio_its = std::equal_range(it->second.begin(), it->second.end(), word_type(word, prio + 1), PrioComp());
	it->second.insert(prio_its.first, word_type(word, prio + 1));
}

////////////////////////////////////////////////////////////////

// ���������� Parser
////////////////////////////////////////////////////////////////

// ���������� ��������
void Parser::UpdateIndex(const std::string& inSymbol) {

	std::list<dictionary_ind>* temp_prio = new std::list<dictionary_ind>;
	// ���� ������� ������ �����
	if(!m_NumberCounter) {
		m_Index = new Wordmap<Dictionary<>::word_it>;

		// ��������� ������� ������� �������
		std::pair<Dictionary<>::word_it, Dictionary<>::word_it> bucket = m_Dict->GetBucket(inSymbol);
		// ����������� ��������� ���� ����� ������� � ���������� ������,
		// ����������� - � ������������ ������
		for(;bucket.first != bucket.second; ++bucket.first) {
			// ����������� �������� ������
			std::string suffix(bucket.first->first.begin() + 1, bucket.first->first.end());
			// ��������� ������� � �������
			Wordmap<Dictionary<>::word_it>::map_it it = m_Index->buckets.lower_bound(suffix);
			if(it->first[0] != suffix[0])
				--it;

			// (�������, ��������.��������)
			it->second.insert(it->second.end(), Wordmap<Dictionary<>::word_it>::entry_type(suffix, bucket.first));

			// (��������.��������, ��������.��������->���������)
			dictionary_ind
				ind1(bucket.first, bucket.first->second),
				ind2(bucket.first, bucket.first->second - 1);
			temp_prio->insert(std::lower_bound(temp_prio->begin(), temp_prio->end(), ind2, prio_greater<dictionary_ind>()), ind1);
		}
	}

	// ����� �� ������, ��������������
	// ������ ��� ������ - ���������� ����������� �������
	// �� ������ ��� ����������
	else {
		Wordmap<Dictionary<>::word_it>* temp_ind = new Wordmap<Dictionary<>::word_it>;

		// �������� �������� � ����� ������
		Wordmap<Dictionary<>::word_it>::bucket_type b_temp = m_Index->buckets[inSymbol];

		for(Wordmap<Dictionary<>::word_it>::bucket_it b_ind = b_temp.begin(); b_ind != b_temp.end(); ++b_ind) {
			// ����������� �������� ������
			std::string suffix(b_ind->first.begin() + 1, b_ind->first.end());
			// ������ ������� ���� ����������
			Wordmap<Dictionary<>::word_it>::map_it it = temp_ind->buckets.lower_bound(suffix);
			if(it->first[0] != suffix[0])
				--it;

			// (�������, ��������.��������)
			it->second.insert(it->second.end(), Wordmap<Dictionary<>::word_it>::entry_type(suffix, b_ind->second));

			// (��������.�������, ��������.��������->���������)
			dictionary_ind
				ind1(b_ind->second, b_ind->second->second - 1),
				ind2(b_ind->second, b_ind->second->second);
			temp_prio->insert(std::lower_bound(temp_prio->begin(), temp_prio->end(), ind1, prio_greater<dictionary_ind>()), ind2);
		}
		// �������� ������ ��������
		delete m_PrioIndex;
		delete m_Index;

		m_Index = temp_ind;
	}

	m_PrioIndex = temp_prio;
}

// ��������� ������ �������
std::string Parser::OnNewInput(char inSym) {
	// ������ �� ������ �����������:
	// ��������� ���������� ����� � �������,
	// ���������� � ��������� ����� �������,
	// ����� ���������
	if(inSym == ' ') {
		std::list<dictionary_ind>::iterator it = m_PrioIndex->begin();
		m_Dict->IncreasePriority(it->first);
		std::string res = m_Text;
		res = m_Text + inSym;
		Reset();
		return res;
	}

	if(inSym == '*') {
		// ���������� ������� �����������
		if(!m_PrepositionCounter)
		{
			m_PrioIndex->erase(m_PrioIndex->begin());
			m_Text = m_PrioIndex->begin()->first->first;
		}
		// ����� ���������� ����� ����������
		else
			SelectNewPreposition();
	}
	// ����� ����� ����������
	else if(inSym == '1') {
		SelectNewPreposition();
	}
	// inSym == 2 -- 9
	else {
		// ������� �������� � ����������
		std::string str = Keyboard::Instance().GetSymbol(inSym);
		// ���������� ��������
		UpdateIndex(str);
		// ���������� ��������
		m_NumberCounter++;
		// ���������� ��������� �����
		m_Text = m_PrioIndex->begin()->first->first;
	}
	return m_Text;
}

// ����� ���������� ����� ����������
void Parser::SelectNewPreposition() {
	// �� ����� ���������� �� ����
	if(m_PrepositionCounter) {
		unsigned u = m_Text.length();
		// ���������� � ����� ������� ����� ���������� ����������
		m_Text[m_Text.length() - 1] = Keyboard::Instance().GetSymbol('1')[m_PrepositionCounter++];
	}
	// ���� ���������� ��� �������
	else {
		// ������ ���������� ������� ����� ����� ������
		std::string sym = Keyboard::Instance().GetSymbol('1');
		m_Text += sym[m_PrepositionCounter++];
	}
}

// ����� ��������, ��������� � ��������� �����
void Parser::Reset() {
	m_Text = "";
	m_PrepositionCounter = 0;
	m_AsteriskCounter = 0;
	m_NumberCounter = 0;
	delete m_PrioIndex;
	delete m_Index;
}
////////////////////////////////////////////////////////////////


// ������ �������
void ReadDictionary(std::basic_istream<char>& inStream, Dictionary<>& inDict) {
	// ���������� ����
	unsigned N = 0;
	inStream >> N;
	for(unsigned i = 0; i < N; ++i) {
		unsigned priority = 0;
		std::string wrd = "";
		char c = 0;
		// �����-���������
		inStream >> wrd;
		inStream >> priority;
		// ����������
		inDict.AddWord(wrd, priority);
	}
}