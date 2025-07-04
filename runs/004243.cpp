#include <iostream>
#include <algorithm>

#include<vector>
using std::vector;

#include<string>
using std::string;

#include<map>
using std::map;

struct Word {
    string Letters;
    int Probability;

    Word (): Probability(0) {}
    Word (string letters): Letters(letters), Probability(0) {}
};

bool Priorited (const Word& lhs, const Word& rhs) {
    return (lhs.Probability > rhs.Probability) || 
        ((lhs.Probability == rhs.Probability) && (lhs.Letters < rhs.Letters));
}

std::istream& operator >> (std::istream& i, Word& word) {
    return i >> word.Letters >> word.Probability;
}

struct Vertex {
    char Digit;
    vector<Word> Words;
    vector<int> SonIndices;

    Vertex (char digit): Digit(digit) {}
};

class Trie {
private:
    vector<Vertex> vertices;
    map<char, char> telephone;

    vector<char> Transform(const string& str) {
        vector<char> digit_sequence;
        for (int i = 0; i < str.length(); ++i) {
            digit_sequence.push_back(telephone[str[i]]);
        }
        return digit_sequence;
    }

    bool HasNeededSon (int index, char digit) const {
        for (int  i = 0; i < vertices[index].SonIndices.size(); ++i) {
            if (vertices[vertices[index].SonIndices[i]].Digit == digit) {
                return true;
            }
        }
        return false;
    }

    int GetSonIndex (int index, char digit) const {
        for (int  i = 0; i < vertices[index].SonIndices.size(); ++i) {
            if (vertices[vertices[index].SonIndices[i]].Digit == digit) {
                return vertices[index].SonIndices[i];
            }
        }
        return -1;
    }

    void AddSon (int index, char digit) {
        Vertex newVertex(digit);
        vertices.push_back(newVertex);
        vertices[index].SonIndices.push_back(static_cast<int>(vertices.size()) - 1);
    }

    void Add (const Word& word) {
        vector<char> digit_sequence = Transform(word.Letters);
        int count = 0;
        int currentIndex = 0;
        while (count != digit_sequence.size()) {
            if (!HasNeededSon(currentIndex, digit_sequence[count])) {
                AddSon(currentIndex, digit_sequence[count]);
                currentIndex = static_cast<int>(vertices.size()) - 1;
            } else {
                currentIndex = GetSonIndex(currentIndex, digit_sequence[count]);
            }
            ++count;
        }
        vertices[currentIndex].Words.push_back(word);
        std::sort(vertices[currentIndex].Words.begin(), vertices[currentIndex].Words.end(), Priorited);
    }

    void AddPunctuation () {
        AddSon(0, '1');
        int currentIndex = static_cast<int>(vertices.size()) - 1;
        
        Word dot(".");
        Word coma(",");
        Word question("?");
        
        vertices[currentIndex].Words.push_back(dot);
        vertices[currentIndex].Words.push_back(coma);
        vertices[currentIndex].Words.push_back(question);
    }

    void UpdateVertex (int vertexIndex, int wordIndex) {
        ++vertices[vertexIndex].Words[wordIndex].Probability;
        int i = wordIndex;
        while ((i > 0) && (vertices[vertexIndex].Words[i].Probability >= vertices[vertexIndex].Words[i - 1].Probability)) {
                std::swap(vertices[vertexIndex].Words[i], vertices[vertexIndex].Words[i - 1]);
                --i;
        }
    }

public:
    Trie () {
        Vertex root(-1);
        vertices.push_back(root);

        telephone['a'] = '2';
        telephone['b'] = '2';
        telephone['c'] = '2';

        telephone['d'] = '3';
        telephone['e'] = '3';
        telephone['f'] = '3';

        telephone['g'] = '4';
        telephone['h'] = '4';
        telephone['i'] = '4';

        telephone['j'] = '5';
        telephone['k'] = '5';
        telephone['l'] = '5';

        telephone['m'] = '6';
        telephone['n'] = '6';
        telephone['o'] = '6';

        telephone['p'] = '7';
        telephone['q'] = '7';
        telephone['r'] = '7';
        telephone['s'] = '7';

        telephone['t'] = '8';
        telephone['u'] = '8';
        telephone['v'] = '8';

        telephone['w'] = '9';
        telephone['x'] = '9';
        telephone['y'] = '9';
        telephone['z'] = '9';

    }

    void Grow (const vector<Word>& dictionary) {
        for (int  i = 0; i < dictionary.size(); ++i) {
            Add(dictionary[i]);
        }

        AddPunctuation();
    }

    int Find (const string& digits) const {
        int count = 0;
        int currentIndex = 0;
        while (count != digits.size()) {
            currentIndex = GetSonIndex(currentIndex, digits[count]);
            ++count;
        }
        return currentIndex;
    }

    string GetWord (const string& digits, int wordIndex) {
        if (digits == "") {
            return "";
        }
        int vertexIndex = Find(digits);
        wordIndex = wordIndex % vertices[vertexIndex].Words.size();
        string target = vertices[vertexIndex].Words[wordIndex].Letters;
        if (digits != "1") {
            UpdateVertex(vertexIndex, wordIndex);
        }
        return target;
    }
};

class Processor {
private:

    Trie Dictionary;
    string Encoded;
    string Decoded;

    string currentWord;
    int triesAmount;

    void Read (char symbol) {
        if (symbol == '*') {
            ++triesAmount;
        } else if (symbol == '1') {
            Decoded += Dictionary.GetWord(currentWord, triesAmount);
            currentWord = "1";
            triesAmount = 0;
        } else if (symbol == ' ') {
            Decoded += Dictionary.GetWord(currentWord, triesAmount) + ' ';
            currentWord = "";
            triesAmount = 0;
        } else {
            currentWord += symbol;
        }
    }

public:
    Processor (Trie dictionary, string encoded): Dictionary(dictionary), Encoded(encoded), triesAmount(0) {}

    string Decode () {
        for (int i = 0; i < Encoded.length(); ++i) {
            Read(Encoded[i]);
        }
        if ((Encoded.length() > 0) && (Encoded[static_cast<int>(Encoded.length()) - 1] != ' ')) {
            Decoded += Dictionary.GetWord(currentWord, triesAmount);
        }
        return Decoded;
    }

};

void Process (string* result, const Trie& trie, const string& sentence) {
    Processor processor(trie, sentence);
    *result = processor.Decode();
}

void Input (vector<Word>* dictionary, string* sentence) {
    int size;
    std::cin >> size;
    dictionary->resize(size);
    for (int  i = 0; i < dictionary->size(); ++i) {
        std::cin >> dictionary->at(i);
    }
    scanf("\n");
    
    std::getline(std::cin, *sentence);
}

void Output (const string& str) {
    std::cout << str << std::endl;
}

int main() {
    Trie trie;
    vector<Word> dictionary;
    string sentence;
    
    Input(&dictionary, &sentence);
    trie.Grow(dictionary);
    
    string result;
    Process(&result, trie, sentence);
    
    Output(result);

    return 0;
}