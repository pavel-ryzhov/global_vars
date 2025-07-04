#include <fstream>
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

vector< vector<word> > vocabulary;

int ctoi(const char what);
unsigned short buttonNumber(char letter);
char symbol(unsigned short number);
bool checkWord(string word, string temp_word);
void completeWord(unsigned short button, vector<unsigned short> *index, string *output_line, string temp_word);
void input(string *input_line);
const string outputLine(string input_line);

int main()
{
    string input_line;

    vocabulary.resize(8);
    input(&input_line);
    printf("%s", outputLine(input_line).c_str());

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

int ctoi(const char what)
{
    return (int)what - 48;
}

unsigned short buttonNumber(char letter)
{
    if (letter <= 'c')
        return 2;
    else if (letter <= 'f')
        return 3;
    else if (letter <= 'i')
        return 4;
    else if (letter <= 'l')
        return 5;
    else if (letter <= 'o')
        return 6;
    else if (letter <= 's')
        return 7;
    else if (letter <= 'v')
        return 8;
    else
        return 9;
}

char symbol(unsigned short number)
{
    switch (number)
    {
    case 1:
        return '.';
    case 2:
        return ',';
    default:
        return '?';
    }
}

void input(string *input_line)
{
    char str[20], input_str[100000];
    vector< vector<word> > temp_vocabulary;
    word temp_word;
    unsigned short words_quantity;

    temp_vocabulary.resize(1000);
    scanf("%hu", &words_quantity);
    for (unsigned short i = 0; i < words_quantity; i++)
    {
        scanf("%s %hu", str, &temp_word.frequency);
        temp_word.name = str;
        temp_vocabulary[temp_word.frequency - 1].push_back(temp_word);
    }
    for (short i = 999; i >= 0; i--)
        for (unsigned short j = 0; j < temp_vocabulary[i].size(); j++)
            vocabulary[buttonNumber(temp_vocabulary[i][j].name[0]) - 2].push_back(temp_vocabulary[i][j]);
    getchar();
    gets(input_str);
    *input_line = input_str;
}

bool checkWord(string word, string temp_word)
{
    for (unsigned short i = 0; i < word.length(); i++)
        if (buttonNumber(word[i]) != ctoi(temp_word[i]))
            return false;
    return true;
}

void completeWord(unsigned short button, vector<unsigned short> *index, string *output_line, string temp_word)
{
    if (!index->empty())
    {
        if (index->at(0) > 0)
        {
            unsigned short i;
            if (index->size() > 1)
                i = index->at(1);
            else
            {
                i = 0;
                unsigned short temp_length = temp_word.length();
                while (!(vocabulary[button][i].name.length() == temp_length && checkWord(vocabulary[button][i].name, temp_word)))
                    i++;
            }
            output_line->append(vocabulary[button][i].name);
            vocabulary[button][i].frequency++;
            for (unsigned short j = i; (j > 0) && (vocabulary[button][j] >= vocabulary[button][j - 1]); j--)
                swap(vocabulary[button][j], vocabulary[button][j - 1]);
        }
        else
            *output_line += symbol(index->at(1));
        index->clear();
    }
}

const string outputLine(const string input_line)
{
    vector<unsigned short> index;
    unsigned short button, temp_length, temp_size;
    string output_line, temp_word;

    for (unsigned long i = 0; i < input_line.length(); i++)
        switch (input_line[i])
        {
        case ' ':
            completeWord(button, &index, &output_line, temp_word);
            temp_word.clear();
            output_line.append(" ");
            break;

        case '*':
            if (index[0] > 0 && index.size() == 1)
            {
                temp_length = temp_word.length();
                temp_size = vocabulary[button].size();
                for (unsigned short j = 0; j < temp_size; j++)
                    if (vocabulary[button][j].name.length() == temp_length && checkWord(vocabulary[button][j].name, temp_word))
                        index.push_back(j);
            }
            index.push_back(index[1]);
            index.erase(index.begin() + 1);
            break;

        case '1':
            completeWord(button, &index, &output_line, temp_word);
            temp_word.clear();
            for (short j = 0; j <= 3; j++)
                index.push_back(j);
            break;

        default:
            temp_word += input_line[i];
            if (index.empty())
            {
                index.push_back(1);
                button = ctoi(input_line[i]) - 2;
            }
            else
            {
                if (index[0] > 0)
                    index[0]++;
                else
                {
                    output_line += symbol(index[1]);
                    index.clear();
                    index.push_back(1);
                    button = ctoi(input_line[i]) - 2;
                }
            }
        }
    if (!index.empty())
    {
        if (index[0] > 0)
        {
            unsigned short i = 0, temp_length = temp_word.length();
            while (!(vocabulary[button][i].name.length() == temp_length && checkWord(vocabulary[button][i].name, temp_word)))
                i++;
            output_line.append(vocabulary[button][i].name);
        }
        else
            output_line += symbol(index[1]);
    }
    return output_line;
}
