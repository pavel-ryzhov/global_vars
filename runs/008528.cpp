#include <fstream>
#include <vector>
#include <deque>

using namespace std;

struct word
{
    string name;
    unsigned short frequency;
};

vector< deque<word> > vocabulary;
deque<unsigned short> index;
string input_line, output_line;

unsigned short buttonNumber(const char letter);
char symbol(unsigned short number);
bool checkWord(const string what_word, const string temp_word);
void completeWord(unsigned short button, const string temp_word);
void input();
void outputLine();

int main()
{
    vocabulary.resize(8);
    input();
    outputLine();

    return 0;
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

void input()
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
    input_line = input_str;
}

bool checkWord(string what_word, string temp_word)
{
    unsigned short i = what_word.length();
    for (unsigned short j = 0; j < i; j++)
        if (buttonNumber(what_word[j]) != (int)temp_word[j] - 48)
            return false;
    return true;
}

void completeWord(unsigned short button, string temp_word)
{
    if (!index.empty())
    {
        if (index[0] > 0)
        {
            unsigned short i;
            if (index.size() > 1)
                i = index[1];
            else
            {
                i = 0;
                unsigned short temp_length = temp_word.length();
                while (!(vocabulary[button][i].name.length() == temp_length && checkWord(vocabulary[button][i].name, temp_word)))
                    i++;
            }
            output_line.append(vocabulary[button][i].name);
            vocabulary[button][i].frequency++;
            if (i != 0)
            {
                long j = i - 1;
                unsigned short temp_frequency = vocabulary[button][i].frequency;
                while ((j >= 0) && (vocabulary[button][j].frequency <= temp_frequency))
                    j--;
                if (j >= 0)
                    vocabulary[button].insert(vocabulary[button].begin() + j + 1, 1, vocabulary[button][i]);
                else
                    vocabulary[button].push_front(vocabulary[button][i]);
                vocabulary[button].erase(vocabulary[button].begin() + i + 1);
            }
        }
        else
            output_line += symbol(index[1]);
        index.clear();
    }
}

void outputLine()
{
    unsigned short button, temp_length, temp_size;
    string temp_word;
    bool change_finished = false;

    for (unsigned long i = 0; i < input_line.length(); i++)
    {
        if (input_line[i] >= '2' && input_line[i] <= '9')
        {
            temp_word += input_line[i];
            if (!index.empty())
            {
                if (index[0] > 0)
                    index[0]++;
                else
                {
                    output_line += symbol(index[1]);
                    index.clear();
                    index.push_back(1);
                    button = (int)input_line[i] - 50;
                }
            }
            else
            {
                index.push_back(1);
                button = (int)input_line[i] - 50;
            }
        }
        else if (input_line[i] == ' ')
        {
            completeWord(button, temp_word);
            temp_word.clear();
            change_finished = false;
            output_line.append(" ");
        }
        else if (input_line[i] == '1')
        {
            completeWord(button, temp_word);
            temp_word.clear();
            change_finished = false;
            for (short j = 0; j <= 3; j++)
                index.push_back(j);
        }
        else
        {
            if (index[0] > 0 && !change_finished)
            {
                temp_length = temp_word.length();
                temp_size = vocabulary[button].size();
                long j;
                if (index.size() > 1)
                {
                    j = index[1];
                    index.push_back(index[1]);
                }
                else
                    j = -1;
                do
                    j++;
                while ((j < temp_size) && !(vocabulary[button][j].name.length() == temp_length && checkWord(vocabulary[button][j].name, temp_word)));
                if (j < temp_size)
                {
                    if (index.size() == 1)
                    {
                        index.push_back(j);
                        do
                            j++;
                        while ((j < temp_size) && !(vocabulary[button][j].name.length() == temp_length && checkWord(vocabulary[button][j].name, temp_word)));
                        if (j < temp_size)
                        {
                            index.push_back(index[1]);
                            index[1] = j;
                        }
                        else
                        {
                            index.erase(index.begin() + 1);
                            change_finished = true;
                        }
                    }
                    else
                        index[1] = j;
                }
                else
                {
                    index.erase(index.begin() + 1);
                    change_finished = true;
                }
            }
            else
            {
                index.push_back(index[1]);
                index.erase(index.begin() + 1);
            }
        }
    }
    if (!index.empty())
    {
        if (index[0] > 0)
        {
            unsigned short i;
            if (index.size() > 1)
                i = index[1];
            else
            {
                i = 0;
                unsigned short temp_length = temp_word.length();
                while (!(vocabulary[button][i].name.length() == temp_length && checkWord(vocabulary[button][i].name, temp_word)))
                    i++;
            }
            output_line.append(vocabulary[button][i].name);
        }
        else
            output_line += symbol(index[1]);
    }
    printf("%s", output_line.c_str());
}
