#include <iostream>
#include <algorithm>

#include<vector>
using std::vector;

#include<string>
using std::string;

struct Word {
    string Letters;
    int Probability;

    Word (): Probability(0) {}
    Word (string letters): Letters(letters), Probability(0) {}
};

bool MorePriorited (const Word& lhs, const Word& rhs) {
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
    vector<char> telephone;

    vector<char> Transform(const string& str) {
        vector<char> digit_sequence;
        for (int i = 0; i < str.length(); ++i) {
            digit_sequence.push_back(telephone[str[i] - 97]);
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
        int wordIndex = static_cast<int>(vertices[currentIndex].Words.size()) - 1;
        while ((wordIndex > 0) && (MorePriorited(vertices[currentIndex].Words[wordIndex], vertices[currentIndex].Words[wordIndex - 1]))) {
                std::swap(vertices[currentIndex].Words[wordIndex], vertices[currentIndex].Words[wordIndex - 1]);
                --wordIndex;
        }
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
        while ((wordIndex > 0) && (vertices[vertexIndex].Words[wordIndex].Probability >= vertices[vertexIndex].Words[wordIndex - 1].Probability)) {
                std::swap(vertices[vertexIndex].Words[wordIndex], vertices[vertexIndex].Words[wordIndex - 1]);
                --wordIndex;
        }
    }

public:
    Trie () {
        Vertex root(-1);
        vertices.push_back(root);

        telephone.push_back('2');
        telephone.push_back('2');
        telephone.push_back('2');

        telephone.push_back('3');
        telephone.push_back('3');
        telephone.push_back('3');

        telephone.push_back('4');
        telephone.push_back('4');
        telephone.push_back('4');

        telephone.push_back('5');
        telephone.push_back('5');
        telephone.push_back('5');

        telephone.push_back('6');
        telephone.push_back('6');
        telephone.push_back('6');

        telephone.push_back('7');
        telephone.push_back('7');
        telephone.push_back('7');
        telephone.push_back('7');

        telephone.push_back('8');
        telephone.push_back('8');
        telephone.push_back('8');

        telephone.push_back('9');
        telephone.push_back('9');
        telephone.push_back('9');
        telephone.push_back('9');
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

    Trie* Dictionary;
    string Encoded;
    string Decoded;

    string currentWord;
    int triesAmount;

    void Read (char symbol) {
        if (symbol == '*') {
            ++triesAmount;
        } else if (symbol == '1') {
            Decoded += Dictionary->GetWord(currentWord, triesAmount);
            currentWord = "1";
            triesAmount = 0;
        } else if (symbol == ' ') {
            Decoded += Dictionary->GetWord(currentWord, triesAmount) + ' ';
            currentWord = "";
            triesAmount = 0;
        } else {
            if ((currentWord.length() > 0) &&
                ((currentWord[static_cast<int>(currentWord.length()) - 1] == '1') || (currentWord[static_cast<int>(currentWord.length()) - 1] == '*'))) {
                Decoded += Dictionary->GetWord(currentWord, triesAmount);
                currentWord = "";
                triesAmount = 0;
            }
            currentWord += symbol;
        }
    }

public:
    Processor (Trie* dictionary, string encoded): Dictionary(dictionary), Encoded(encoded), triesAmount(0) {}

    string Decode () {
        for (int i = 0; i < Encoded.length(); ++i) {
            Read(Encoded[i]);
        }
        if ((Encoded.length() > 0) && (Encoded[static_cast<int>(Encoded.length()) - 1] != ' ')) {
            Decoded += Dictionary->GetWord(currentWord, triesAmount);
        }
        return Decoded;
    }

};

void Process (string* result, Trie* trie, const string& sentence) {
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
    char buffer [100001];
    gets(buffer);    
    *sentence = buffer;
}

void Output (const string& str) {
    for (int i = 0; i < str.length(); ++i) {
        printf("%c", str[i]);
    }
}

int main() {
    Trie trie;
    vector<Word> dictionary;
    string sentence;

    Input(&dictionary, &sentence);
    trie.Grow(dictionary);
    
    string result;
    Process(&result, &trie, sentence);

    Output(result);
    return 0;
}