#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector <pair <string, unsigned int> > matching_words;
pair <string, unsigned int> temp;
vector <vector <string> > frequency;

struct Node
{
    char letter;
    unsigned int freq;
    struct List* children;
};

struct List
{
    struct Node* son;
    struct List* next;
};

List* create_list()
{
    List* new_list = (struct List*) malloc(sizeof(struct List));
    new_list->son = NULL;
    new_list->next = NULL;
    return new_list;
};

List* last(List* curr)
{
    while ((curr->next)!= NULL)
        curr = (curr->next);
    return curr;
};

void add_list(List* curr, List* new_list)
{
    new_list->next = curr->next; 
    curr->next = new_list;
};

Node* create_node(char key, unsigned int value)
{
    Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->letter = key;
    new_node->freq = value;
    new_node->children = create_list();
    return new_node;
};

int add_node(Node* curr, char key, unsigned int value)
{
    Node* new_node = create_node(key, value);
    List* new_list = create_list();
    new_list->son = new_node;
    if (curr->children->son == NULL)
        curr->children = new_list;
    else
        add_list(last(curr->children), new_list);
    return 0;
};

// Обход дерева, нужен для проверки, в программе не используется

void walk (Node* curr)
{
    List* step;
    cout << curr->letter << "," << curr->freq << endl;
    
    if (curr->children->son != NULL)
    {
        step = curr->children;
        while (step != NULL)
        {
              walk(step->son);
              step = step->next;
        }
    } 

}

// По считанному словарю создаем дерево

void create_tree(Node* root, vector < pair<string, unsigned int> > words)
{
    
    char curr_letter;
    bool node_found;    
    string::iterator iter;
    Node* curr_node;
    Node* tmp_node;
    List* step;
    unsigned int curr_freq;
    
    for (size_t i = 0; i < words.size(); i++)
    {     
        curr_node = root;
        int run_count = 0;        
       
        for (iter = words[i].first.begin(); iter < words[i].first.end(); iter++)
        {
            curr_letter = *iter;        
            node_found = false;         
            step = curr_node->children;  
           // Проходим по сыновьям, выходим если нашли вершину           
            while(step->next != NULL)
            {
                  if ( step->son->letter == curr_letter)
                  {    
                       node_found = true;
                       curr_node = step->son;
                       break;
                  }
                  step = step->next;
            }
            // Если только один сын
            if ( (step->next == NULL) && (step->son != NULL))
            {
                 if ( step->son->letter == curr_letter)
                 {
                    node_found = true;
                    curr_node = step->son;
                 }
            }
            
            if (!node_found)
            {                
                if ( (iter + 1) == (words[i].first.end() ) )
                {
                    curr_freq = words[i].second;
                } else {
                    curr_freq = 0;            
                }
      
                add_node(curr_node, curr_letter, curr_freq);     
                curr_node = (last(curr_node->children))->son;
            }
         }
     }
}

// Определяет каким буквам соответствует данная клавиша

string cmd_to_str(char key)
{
    switch (key)
    {
        case '2':
             return "abc";
             
        case '3':
             return "def";
             
        case '4':
             return "ghi"; 
                 
        case '5':
             return "jkl"; 
              
        case '6':
             return "mno"; 
              
        case '7':
             return "pqrs";  
             
        case '8':
             return "tuv";  
             
        case '9':
             return "wxyz"; 
                                                                                           
        default: ;
    }            
}
 
// Ищет в дереве все слова, подходящие для данной команды ввода comm,
// и записывает их в массив matching_words 

 
void find_words(Node* curr, int pos, string comm, string word)
{
     List* step;
     string s;     
     // Если вершина - не лист
     
     if ( (curr->children->son != NULL) && (comm.size() != word.size()) )
     {
        step = curr->children;
        while (step != NULL)
        {
              // Если уже прошли все цифры            
              if (pos >= comm.size())
                 break;
              s = cmd_to_str(comm[pos]);
       
              for (size_t i = 0; i < s.size(); i++)              
                  if (step->son->letter == s[i])                                      
                     find_words(step->son, pos+1, comm, word + s[i]);                  
                                    
              step = step->next;
        }
     } else if (comm.size() == word.size() ){
         temp.first = word;
         temp.second = curr->freq;
         matching_words.push_back(temp);
     } 
}

// Проверяет, является ли данная клавиша клавишей для ввода букв

bool is_a_num (char key)
{
     switch (key)
     {
            case '2':
                 return true;
            case '3':
                 return true;
            case '4':
                 return true;
            case '5':
                 return true;
            case '6':
                 return true;
            case '7':
                 return true;
            case '8':
                 return true;
            case '9':
                 return true;
            default:
                 return false;
     }
}
                 
// Получаем позицию последнего символа в строке-команде, соответствующего букве

int get_last_pos (string s)
{
     int i;
     for (i = 0; i < s.size(); i++)
         if(!is_a_num(s[i]))
              break;
     return i;
}

// Обновление частоты встречаемости заданного слова в дереве

void update_frequency (Node* tree, string word)
{
    Node* curr = tree;
    List* step;
    
    for(size_t i = 0; i < word.size(); i++)
    {
        step = curr->children;
        while (step != NULL)
        {
              //cout << "Curr letter " << step->son->letter << endl;
              if (step->son->letter == word[i])
              {
                  curr = step->son;
                  break;
              }
              step = step->next;
        }
    }
    if (curr->freq < 1000)
        (curr->freq)++;
     //cout << "Finish node: " << curr->letter << "," << curr->freq << endl;
}

// Сортировка для массива matching_words

void bubble_sort(vector < pair <string, unsigned int> > &v)
{
     bool swapped = true;
     int temp;
     while(swapped)
     {
         swapped = false;
         for (size_t i = 0; i < v.size()-1; i++)
         {
             if (v[i].second < v[i+1].second)
             {
  
                 //temp = v[i+1];
                 //v[i+1] = v[i];
                 //v[i] = temp; 
                 swap (v[i].second, v[i+1].second);
                 swap (v[i].first, v[i+1].first);    
                
                 swapped = true;
             } else if (v[i].second == v[i+1].second)
             {
                 
                 size_t index1, index2;
                 for (size_t j = 0; j < frequency[v[i].second].size(); j++)
                     if  (frequency[v[i].second][j] == v[i].first)
                     {
                         index1 = j;
                         break;
                     }
                 for (size_t j = 0; j < frequency[v[i+1].second].size(); j++)
                     if  (frequency[v[i+1].second][j] == v[i+1].first)
                     {
                         index2 = j;
                         break;
                     }
                 if (index1 > index2)
                 {
                    swap (v[i].second, v[i+1].second);
                    swap (v[i].first, v[i+1].first);    
                    swapped = true;
                 }
             }
         }
     }
}
 
string punctuation (string input)
{
    string output;
    string marks = ".,?";
    size_t pos;
    size_t i = 0;
    char curr_sign;
    while (i < input.size()) 
    {
        pos = 0;
        if ( input[i] == '1' )
        {
           if (curr_sign == '1')
              output += marks[0];
           curr_sign = input[i];
           i++;
        }
           
        else
        {
              

            size_t n = i;
            for (n; n < input.size(); n++)
            {
  
                if (input[n] == '*')
                   pos++;
                else break;
            }  

            pos = pos % marks.size();
            output += marks[pos];
            curr_sign = ' ';
            i = n;
        }
    }
    if (curr_sign == '1')
              output += marks[0];
    return output;    
         
} 


void word_proc (Node* root, string input)
{
     string command;
     size_t posit;
     string punct_marks;
     unsigned int fr_count;
     unsigned int index;
     unsigned int space_count = 0;
     string w;     

     
     // Получаем индекс последней буквы слова в команде
     posit = get_last_pos(input);
     fr_count = 0;
     
     // Формируем команду для поиска слов
     for (size_t n = 0; n < posit; n++)
            command += input[n];
            
     // Считываем число звезд для выбора нужного слова            
     for (size_t n = posit; n < input.size(); n++)
         if (input[n] != '*')
               break;
         else
         {
             fr_count++; 
             posit++;
         }

     // Считываем часть, соответствующую знакам препинания     
     for (size_t n = posit; n < input.size(); n++)
         if (input[n] == ' ')
            break;
         else
         {
            punct_marks += input[n];
            posit++;
         } 
     
     // Считываем число пробелов в конце
     for (size_t n = posit; n < input.size(); n++)
         space_count++;
     

     
     // Ищем подходящие слова
     
     if (command.size() != 0)
     {               
      
     find_words(root, 0, command, w);  

     if (matching_words.size())
         fr_count = fr_count % matching_words.size();
         


                 
     bubble_sort(matching_words);
     

     
     cout << matching_words[fr_count].first;
     index = matching_words[fr_count].second;
     
     for (size_t i = 0; i < frequency[index].size(); i++)
              if (frequency[index][i] == matching_words[fr_count].first)
              {    
                   if (index < 1000)
                   {
                      frequency[index + 1].insert( frequency[index + 1].begin(), matching_words[fr_count].first);
                      frequency[index].erase( frequency[index].begin() + i);
                   } else 
                   {
                      frequency[index].insert( frequency[index].begin(), matching_words[fr_count].first);
                      frequency[index].erase( frequency[index].begin() + i + 1);
                   }
                   
              }
          // Обновление дерева
     update_frequency(root, matching_words[fr_count].first);
     }
     
     cout << punctuation(punct_marks);
     
     for (unsigned int i = 0; i < space_count; i++)
         cout << " ";              
    
     matching_words.clear();       

}



int main(int argc, char *argv[])
{
    vector < pair<string, unsigned int> > vocabulary;
    vector <string> cmd_list;
    unsigned int word_count;
	unsigned int curr_freq;
    string curr_word, buf;
 
   
    Node* root = create_node('-', 0);
   
    cin >> word_count;
	
	for (unsigned int i = 0; i < word_count; i++)
	{
        cin >> curr_word >> curr_freq;
        temp.first = curr_word;
        temp.second = curr_freq;
        vocabulary.push_back(temp);
    }
		
    getline(cin, curr_word);
	getline(cin, curr_word);
	
	bool space = false;
	
	for (size_t i = 0; i < curr_word.size(); i++)
	{
        
        if (curr_word[i] != ' ')
        {
           if (!space)
               buf += curr_word[i];
           else
           {
               cmd_list.push_back(buf);
               buf.clear();
               buf += curr_word[i];
               space = false;
           }
        } else {
           buf += curr_word[i];
           space = true;
        }
    }
    cmd_list.push_back(buf);

    frequency.resize(1001);

    for (size_t i = 0; i < vocabulary.size(); i++)
    {
        curr_freq = vocabulary[i].second;
        curr_word = vocabulary[i].first;
        frequency[curr_freq].push_back(curr_word);
    }   

    // Ввод слов в дерево

    create_tree(root, vocabulary);    
     
     
    curr_word.clear();
    string command;
    size_t posit;
    string punct_marks;
    unsigned int fr_count;
    unsigned int index;
    
    for (size_t j = 0; j < cmd_list.size(); j++)
    {          
        word_proc(root, cmd_list[j]);
      
    }
     
    return 0;
}
