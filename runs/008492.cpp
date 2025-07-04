#include <fstream>
#include <stdlib.h>
#include <vector>

using namespace std;

class word
{
public:
    string name;
    unsigned short frequency;
    void operator =(const word other);
    bool operator <(const word other);
    bool operator >=(const word other);
};

const char buttonNumber(const char letter);
const char symbol(const short number);
void swapWords(word *first, word *other);
void input(vector<word> *vocabulary, string *input_line);
void sortVocabulary(vector<word> *vocabulary);
void completeWord(vector<word> *vocabulary, vector<unsigned short> *index, string *output_line);
const string outputLine(vector<word> vocabulary, const string input_line);

int main()
{
    string input_line;
    vector<word> vocabulary;

    input(&vocabulary, &input_line);
    sortVocabulary(&vocabulary);
    printf("%s", outputLine(vocabulary, input_line).c_str());

    return 0;
}

void word::operator =(const word other)
{
    this->name = other.name;
    this->frequency = other.frequency;
}

bool word::operator <(const word other)
{
    return this->frequency < other.frequency;
}

bool word::operator >=(const word other)
{
    return this->frequency >= other.frequency;
}

const char buttonNumber(const char letter)
{
    if (letter <= 'c')
        return '2';
    else if (letter <= 'f')
        return '3';
    else if (letter <= 'i')
        return '4';
    else if (letter <= 'l')
        return '5';
    else if (letter <= 'o')
        return '6';
    else if (letter <= 's')
        return '7';
    else if (letter <= 'v')
        return '8';
    else
        return '9';
}

const char symbol(const short number)
{
    switch (number)
    {
    case 1:
        return '.';
    case 2:
        return ',';
    case 3:
        return '?';
    }
}

void swapWords(word *first, word *other)
{
    word *temp_word = new word;
    *temp_word = *first;
    *first = *other;
    *other = *temp_word;
    delete temp_word;
}

void input(vector<word> *vocabulary, string *input_line)
{
    char str[20], input_str[100000];
    word temp_word;
    unsigned short words_quantity;

    scanf("%hu", &words_quantity);
    for (unsigned short i = 0; i < words_quantity; i++)
    {
        scanf("%s %hu", str, &temp_word.frequency);
        temp_word.name = str;
        vocabulary->push_back(temp_word);
    }
    getchar();
    gets(input_str);
    *input_line = input_str;
}

void sortVocabulary(vector<word> *vocabulary)
{
    bool not_sorted;
    unsigned short words_quantity = vocabulary->size();

    do {
        not_sorted = false;
        for (unsigned short i = 0; i < words_quantity - 1; i++)
            if (vocabulary->at(i) < vocabulary->at(i + 1))
            {
                swapWords(&(vocabulary->at(i)), &(vocabulary->at(i + 1)));
                not_sorted = true;
            }
    } while (not_sorted);
}

void completeWord(vector<word> *vocabulary, vector<unsigned short> *index, string *output_line)
{
    if (!index->empty())
    {
        if (index->at(0) > 0)
        {
            while (vocabulary->at(index->at(1)).name.length() != index->at(0))
                index->erase(index->begin() + 1);
            output_line->append(vocabulary->at(index->at(1)).name);
            vocabulary->at(index->at(1)).frequency++;
            for (unsigned short i = index->at(1); (i > 0) && (vocabulary->at(i) >= vocabulary->at(i - 1)); i--)
                swapWords(&(vocabulary->at(i)), &(vocabulary->at(i - 1)));
        }
        else
            *output_line += symbol(index->at(1));
        index->clear();
    }
}

const string outputLine(vector<word> vocabulary, const string input_line)
{
    vector<unsigned short> index;
    unsigned short words_quantity = vocabulary.size();
    string output_line;

    for (unsigned long i = 0; i < input_line.length(); i++)
        switch (input_line[i])
        {
        case ' ':
            completeWord(&vocabulary, &index, &output_line);
            output_line.append(" ");
            break;

        case '*':
            if (index[0] > 0)
                for (unsigned short j = 1; j < index.size(); j++)
                    if (vocabulary[index[j]].name.length() != index[0])
                    {
                        index.erase(index.begin() + j);
                        j--;
                    }
            index.push_back(index[1]);
            index.erase(index.begin() + 1);
            break;

        case '1':
            completeWord(&vocabulary, &index, &output_line);
            for (short j = 0; j <= 3; j++)
                index.push_back(j);
            break;

        default:
            if (index.empty())
            {
                index.push_back(1);
                for (unsigned short j = 0; j < words_quantity; j++)
                    if (buttonNumber(vocabulary[j].name[0]) == input_line[i])
                        index.push_back(j);
            }
            else
            {
                index[0]++;
                for (unsigned short j = 1; j < index.size(); j++)
                    if ((vocabulary[index[j]].name.length() < index[0]) || (buttonNumber(vocabulary[index[j]].name[index[0] - 1]) != input_line[i]))
                    {
                        index.erase(index.begin() + j);
                        j--;
                    }
            }
        }
    if (!index.empty())
    {
        if (index[0] > 0)
        {
            while (vocabulary[index[1]].name.length() != index[0])
                index.erase(index.begin() + 1);
            output_line.append(vocabulary[index[1]].name);
        }
        else
            output_line += symbol(index[1]);
    }
    return output_line;
}
