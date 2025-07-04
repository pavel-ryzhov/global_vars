#include <cstdio>
#include <vector>
#include <string>
#include <iostream>

using std::string;
using std::vector;
using std::cout;

const int SIGN = 1;
const int DIGIT = 2;
const int NOTHING = 0;

struct SamePriorityWords {
  SamePriorityWords* previous;
  SamePriorityWords* next;
  string word;
};

struct ElementOfSameDigitArray {
  int number_of_words;
  int priority;
  SamePriorityWords* head;
  SamePriorityWords* tail;
};

//TODO:: private fields
class Node {
public:
  Node* two;
  Node* three;
  Node* four;
  Node* five;
  Node* six;
  Node* seven;
  Node* eight;
  Node* nine;
  vector< ElementOfSameDigitArray* > same_digit_words;
  Node() {
    two = NULL;
    three = NULL;
    four = NULL;
    five = NULL;
    six = NULL;
    seven = NULL;
    eight = NULL;
    nine = NULL;
  }
};

class Dictionary {
private:
  Node *root;
  void InsertToList(SamePriorityWords*& head, string& word);
  void InsertToListEnd(SamePriorityWords*& tail, string& word);
  void DeleteFromList(SamePriorityWords*& head, SamePriorityWords*& word_pointer);
  int FindListToWord(int first_index, int last_index, int priority,
    const vector< ElementOfSameDigitArray* >& same_digit_words);
  ElementOfSameDigitArray* MakeNewSameDigitElement(int priority, const string& word);
public:
  Dictionary();
  void InsertWord(string& word, int priority);
  string FindWord(const string& digits, int sequence_number);
};

Dictionary::Dictionary() {
  root = new Node;
}

ElementOfSameDigitArray* Dictionary::MakeNewSameDigitElement(int priority, const string& word) {
   ElementOfSameDigitArray* new_element = new ElementOfSameDigitArray;
      new_element->priority = priority;
      new_element->number_of_words = 1;
      new_element->head = new SamePriorityWords;
      new_element->tail = new_element->head;
      new_element->head->word = word;
      new_element->head->next = NULL;
      new_element->head->previous = NULL;
      return new_element;
}

void Dictionary::InsertToList(SamePriorityWords*& head, string& word) {
  head->previous = new SamePriorityWords;
  head->previous->next = head;
  head = head->previous;
  head->word = word;
  head->previous = NULL;
}

void Dictionary::InsertToListEnd(SamePriorityWords*& tail, string& word) {
  tail->next = new SamePriorityWords;
  tail->next->previous = tail;
  tail = tail->next;
  tail->word = word;
  tail->next = NULL;
}


int Dictionary::FindListToWord(int first_index, int last_index, int priority,
                               const vector< ElementOfSameDigitArray* >& same_digit_words) {
  int result;
  
  int middle_index = first_index + (last_index - first_index) / 2;
  if (same_digit_words[middle_index]->priority >= priority) {
    if (middle_index != 0) {
      if (same_digit_words[middle_index - 1]->priority < priority) {
        return middle_index;
      }
      else {
        result = FindListToWord(first_index, middle_index, priority, same_digit_words);
      }
    }
    else {
      return 0;
    }
  }
  else {
    if (middle_index != (int) same_digit_words.size() - 1) {
      if (same_digit_words[middle_index + 1]->priority >= priority) {
        return middle_index + 1;
      }
      else {
         result = FindListToWord(middle_index + 1, last_index, priority, same_digit_words);
      }
    }
    else {
      return middle_index + 1;
    }
  }
}

void Dictionary::InsertWord(std::string &word, int priority) {
  Node *node = root;
  for (int index = 0; index < (int)word.size(); ++index) {
    switch(word[index]) {
      case 'a':case'b':case'c':
        if (node->two == NULL) {
          node->two = new Node;
        }
        node = node->two;
        break;
      case 'd':case'e':case'f':
        if (node->three == NULL) {
          node->three = new Node;
        }
        node = node->three;
        break;
      case 'g':case'h':case'i':
        if (node->four == NULL) {
          node->four = new Node;
        }
        node = node->four;
        break;
      case 'j':case'k':case'l':
        if (node->five == NULL) {
          node->five = new Node;
        }
        node = node->five;
        break;
      case 'm':case'n':case'o':
        if (node->six == NULL) {
          node->six = new Node;
        }
        node = node->six;
        break;
      case 'p':case'q':case'r':case's':
        if (node->seven == NULL) {
          node->seven = new Node;
        }
        node = node->seven;
        break;
        case 't':case'u':case'v':
          if (node->eight == NULL) {
          node->eight = new Node;
        }
        node = node->eight;
        break;
      case 'w':case'x':case'y':case'z':
        if (node->nine == NULL) {
          node->nine = new Node;
        }
        node = node->nine;
        break;
    }
  }
  int words_size = (int)node->same_digit_words.size();
    if (words_size == 0) {
      ElementOfSameDigitArray* new_element = MakeNewSameDigitElement(priority, word);
      node->same_digit_words.push_back(new_element);
    }
    else {
      int index = FindListToWord(0, words_size - 1, priority, node->same_digit_words);
      if (index == words_size) {
        ElementOfSameDigitArray* new_element = MakeNewSameDigitElement(priority, word);
        node->same_digit_words.push_back(new_element);
      }
      else if (node->same_digit_words[index]->priority == priority) {
        InsertToListEnd(node->same_digit_words[index]->tail, word);
        ++node->same_digit_words[index]->number_of_words;
      }
      else {
        node->same_digit_words.push_back(node->same_digit_words[words_size - 1]);
        int row;
        for (row = words_size; row > index; --row) {
          node->same_digit_words[row] = node->same_digit_words[row - 1];
        }
        ElementOfSameDigitArray* new_element = new ElementOfSameDigitArray;
        new_element = MakeNewSameDigitElement(priority, word);
        node->same_digit_words[index] = new_element;
      }
    }
}


string Dictionary::FindWord(const std::string &digits, int sequence_number) {
  Node* node = root;
  for (int index = 0; index < (int)digits.size(); ++index) {
     switch(digits[index]) {
      case '2':
        node = node->two;
        break;
      case '3':
        node = node->three;
        break;
      case '4':
        node = node->four;
        break;
      case '5':
        node = node->five;
        break;
      case '6':
        node = node->six;
        break;
      case '7':
        node = node->seven;
        break;
      case '8':
        node = node->eight;
        break;
      case '9':
        node = node->nine;
        break;
    }
  }
  
  int same_digits_words_size = (int)node->same_digit_words.size();
  for (int row = same_digits_words_size - 1; row >= 0; --row) {
    if (sequence_number > node->same_digit_words[row]->number_of_words) {
      sequence_number -= node->same_digit_words[row]->number_of_words;
      if (row == 0) {
        row = same_digits_words_size;
        continue;
      }
    }
    else {
      int counter = 1;
      SamePriorityWords* word_pointer = node->same_digit_words[row]->head;
      while (counter != sequence_number) {
        word_pointer = word_pointer->next;
        ++counter;
      }
      string current_word = word_pointer->word;
      if (node->same_digit_words[row]->number_of_words == 1) {
        if (row == same_digits_words_size - 1) {
          ++node->same_digit_words[row]->priority;
        }
        else if (node->same_digit_words[row + 1]->priority != node->same_digit_words[row]->priority + 1) {
          ++node->same_digit_words[row]->priority;
        }
        else {
          SamePriorityWords* new_word = new SamePriorityWords;
          *new_word = *node->same_digit_words[row]->head;
          new_word->next = node->same_digit_words[row + 1]->head;
          node->same_digit_words[row + 1]->head->previous = new_word;
          node->same_digit_words[row + 1]->head = new_word;
          ++node->same_digit_words[row + 1]->number_of_words;
          delete node->same_digit_words[row]->head;
          for (int index = row; index < same_digits_words_size - 1; ++index) {
            node->same_digit_words[index] = node->same_digit_words[index + 1];
          }
          node->same_digit_words.pop_back();
        }
      }
      else { 
        if (row == same_digits_words_size - 1) {
          node->same_digit_words.push_back(MakeNewSameDigitElement(node->same_digit_words[row]->priority + 1,
           current_word));
          DeleteFromList(node->same_digit_words[row]->head, word_pointer);
          --node->same_digit_words[row]->number_of_words;
        }
        else if (node->same_digit_words[row + 1]->priority == node->same_digit_words[row]->priority + 1) {
          InsertToList(node->same_digit_words[row + 1]->head, current_word);
          ++node->same_digit_words[row + 1]->number_of_words;
          DeleteFromList(node->same_digit_words[row]->head, word_pointer);
          --node->same_digit_words[row]->number_of_words;
        }
        else {
         ElementOfSameDigitArray* new_element = 
           MakeNewSameDigitElement(node->same_digit_words[row]->priority + 1, word_pointer->word);
         node->same_digit_words.push_back(node->same_digit_words[(int)node->same_digit_words.size() - 1]);
         for (int index = (int)node->same_digit_words.size() - 2; index > row + 1; --index) {
           node->same_digit_words[index] = node->same_digit_words[index - 1];
         }
         node->same_digit_words[row + 1] = new_element;
         DeleteFromList(node->same_digit_words[row]->head, word_pointer);
         --node->same_digit_words[row]->number_of_words;
        }
      }

      return current_word;
    }
  }
  string a = " ";
  return a;
}

void Dictionary::DeleteFromList(SamePriorityWords *&head, SamePriorityWords *&word_pointer) {
  if (word_pointer->previous == NULL) {
    head = head->next;
    head->previous = NULL;
    delete word_pointer;
  }
  else if (word_pointer->next == NULL) {
    word_pointer->previous->next = NULL;
    delete word_pointer;
  }
  else {
    word_pointer->previous->next = word_pointer->next;
    word_pointer->next->previous = word_pointer->previous;
    delete word_pointer;
  }
}

void ReadWords(Dictionary& dictionary) {
  int dictionary_size;
  scanf("%d", &dictionary_size);
  for (int index = 0; index < dictionary_size; ++index) {
    char word[20];
    int priority;
    scanf("%s%d", &*word, &priority);
    string _word = (string)word;
    dictionary.InsertWord(_word, priority);
  }
}

void ParseString(Dictionary& dictionary) {
  char letter = getchar();
  while (letter == '\n') {
    letter = getchar();
  }
  int priority = 1;
  int current_state = NOTHING;
  string word = "";

  while ((letter != '\n') && (letter != EOF)) {
    switch(letter) {
      case '*':
        ++priority;
        break;
      case '1':
        if (current_state == SIGN) {
          if (priority == 1) {
            printf(".");
          }
          else if (priority == 2) {
            printf(",");
          }
          else if (priority == 3) {
            printf("?");
          }
          priority = 1;
        }
        else if (current_state == DIGIT) {
          if (word != "") {
            cout << dictionary.FindWord(word, priority);
            priority = 1;
           word = "";
          }
        }

        current_state = SIGN;
        break;
      case ' ':
        if (current_state == SIGN) {
          if (priority == 1) {
            printf(".");
          }
          else if (priority == 2) {
            printf(",");
          }
          else if (priority == 3) {
            printf("?");
          }
        }
        else if (current_state == DIGIT) {
          cout << dictionary.FindWord(word, priority);
          word = "";
        }
        priority = 1;
        current_state = NOTHING;
        printf(" ");
        break;
      case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':
        if (current_state == SIGN) {
          if (priority == 1) {
            printf(".");
          }
          else if (priority == 2) {
            printf(",");
          }
          else if (priority == 3) {
            printf("?");
          }
          priority = 1;
        }
        else if ((current_state = DIGIT) && (priority > 1)) {
           cout << dictionary.FindWord(word, priority);
           word = "";
           priority = 1;
        }
          

        word.push_back(letter);
        current_state = DIGIT;
        break;
    }
    letter = getchar();
  }
  if (current_state == SIGN) {
    if (priority == 1) {
      printf(".");
    }
    else if (priority == 2) {
      printf(",");
    }
    else if (priority == 3) {
      printf("?");
    }
  }
  else if (current_state == DIGIT) {
    cout << dictionary.FindWord(word, priority);
    word = "";
  }
}


int main() {
  Dictionary dictionary;
  ReadWords(dictionary);
  ParseString(dictionary);
  return 0;
}
            
          
