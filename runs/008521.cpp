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
void completeWord(unsigned short button, vector<unsigned short> *index, string *output_line);
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

void completeWord(unsigned short button, vector<unsigned short> *index, string *output_line)
{
    if (!index->empty())
    {
        if (index->at(0) > 0)
        {
            while (vocabulary[button][index->at(1)].name.length() != index->at(0))
                index->erase(index->begin() + 1);
            output_line->append(vocabulary[button][index->at(1)].name);
            vocabulary[button][index->at(1)].frequency++;
            for (unsigned short i = index->at(1); (i > 0) && (vocabulary[button][i] >= vocabulary[button][i - 1]); i--)
                swap(vocabulary[button][i], vocabulary[button][i - 1]);
        }
        else
            *output_line += symbol(index->at(1));
        index->clear();
    }
}

const string outputLine(const string input_line)
{
    vector<unsigned short> index;
    unsigned short button, temp_button;
    string output_line;

    for (unsigned long i = 0; i < input_line.length(); i++)
        switch (input_line[i])
        {
        case ' ':
            completeWord(button, &index, &output_line);
            output_line.append(" ");
            break;

        case '*':
            if (index[0] > 0)
                for (unsigned short j = 1; j < index.size(); j++)
                    if (vocabulary[button][index[j]].name.length() != index[0])
                        index.erase(index.begin() + j--);
            index.push_back(index[1]);
            index.erase(index.begin() + 1);
            break;

        case '1':
            completeWord(button, &index, &output_line);
            for (short j = 0; j <= 3; j++)
                index.push_back(j);
            break;

        default:
            temp_button = ctoi(input_line[i]);
            if (index.empty())
            {
                index.push_back(1);
                button = temp_button - 2;
                for (unsigned short j = 0; j < vocabulary[button].size(); j++)
                    if (buttonNumber(vocabulary[button][j].name[0]) == temp_button)
                        index.push_back(j);
            }
            else
            {
                if (index[0] > 0)
                {
                index[0]++;
                for (unsigned short j = 1; j < index.size(); j++)
                    if ((vocabulary[button][index[j]].name.length() < index[0]) || (buttonNumber(vocabulary[button][index[j]].name[index[0] - 1]) != temp_button))
                        index.erase(index.begin() + j--);
                }
                else
                {
                    output_line += symbol(index[1]);
                    index.clear();
                    index.push_back(1);
                    button = temp_button - 2;
                    for (unsigned short j = 0; j < vocabulary[button].size(); j++)
                        if (buttonNumber(vocabulary[button][j].name[0]) == temp_button)
                            index.push_back(j);
                }
            }
        }
    if (!index.empty())
    {
        if (index[0] > 0)
        {
            while (vocabulary[button][index[1]].name.length() != index[0])
                index.erase(index.begin() + 1);
            output_line.append(vocabulary[button][index[1]].name);
        }
        else
            output_line += symbol(index[1]);
    }
    return output_line;
}
