#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <cassert>

#include <iostream>
#include <stdexcept>

using std::vector;
using std::string;
using std::pair;
using std::map;
using std::sort_heap;
using std::make_heap;

typedef pair<string, size_t> StrUIntPair;
typedef map<string, vector<StrUIntPair> > DigVectMap;

const int unity_key_capacity = 3; //number of outputs that answers pressing "1" on keyboard (".", ",", "?")

bool ComparePairs(const StrUIntPair& first_pair, 
                  const StrUIntPair& second_pair) {
  if (first_pair.second < second_pair.second) {
    return false;
  } else if (first_pair.second > second_pair.second) {
    return true;
  } else {
    return (first_pair.first < second_pair.first);
  }
}

inline string LettersToDigits(const string& input_letters) {
  string result = "";
  size_t input_letters_count = input_letters.length();

  for (size_t letter_index = 0; 
      letter_index < input_letters_count; 
      ++letter_index) {
    int replace_digit;

    if (input_letters.at(letter_index) <= 'r') {
      replace_digit = (input_letters.at(letter_index) - 'a') / 3 + 2;
    } else if (input_letters.at(letter_index) == 's') {
      replace_digit = 7;
    } else if (input_letters.at(letter_index) <= 'v') {
      replace_digit = 8;
    } else if (input_letters.at(letter_index) <= 'z') {
      replace_digit = 9;
    }

    result += (replace_digit + '0');
  }

  return result;
}

string GetWordFromVocab(const string& digits, size_t star_count, DigVectMap& sorted_vocab)
{
  string result = "";

  if (digits == "1") {
    //handling multiple star pressing
    star_count %= unity_key_capacity;

    switch (star_count) {
      case 0: {
        result += ".";
        break;
      }
      case 1: {
        result += ",";
        break;
      }
      case 2: {
        result += "?";
        break;
      }
      default: {
        assert(false);
      }
    }
  } else {
    //handling multiple star pressing
    if (sorted_vocab[digits].size()) {
      star_count %= sorted_vocab[digits].size();
    }

    try {

    result += sorted_vocab[digits].at(star_count).first;
    ++sorted_vocab[digits].at(star_count).second;

    //changing words order
    StrUIntPair updated_word(sorted_vocab[digits].at(star_count));

    for (; star_count > 0; --star_count) {
      if (updated_word.second >= 
          sorted_vocab[digits].at(star_count - 1).second) {
        sorted_vocab[digits].at(star_count) = 
          sorted_vocab[digits].at(star_count - 1);
      } else {
        break;
      }
    }

    sorted_vocab[digits].at(star_count) = updated_word;

    } catch (std::out_of_range& oor) {
      std::cerr << "GetWordFromVocab --> Out of Range error: " << oor.what() << "\n";
    }
  }

  return result;
}

string GetTextFromT9String(const string& t9_string, DigVectMap& sorted_vocab)
{
  string result = "";

  size_t t9_string_length = t9_string.length();
  size_t letter_index = 0;
  size_t stars_count = 0;

  string current_digit_sequence = "";

  while (letter_index < t9_string_length)
  {
    char current_char = t9_string.at(letter_index);

    if (current_char == ' ') {
      if (!current_digit_sequence.empty()) {
        result += GetWordFromVocab(current_digit_sequence, 
                      stars_count, sorted_vocab);
      }
      result += " ";
      current_digit_sequence.clear();
      stars_count = 0;
    } else if (current_char == '*') {
      ++stars_count;
    } else if (current_char == '1') {
      if (!current_digit_sequence.empty()) {
        result += GetWordFromVocab(current_digit_sequence, 
                      stars_count, sorted_vocab);
      }
      current_digit_sequence.clear();
      current_digit_sequence += "1";
      stars_count = 0;
    } else {
      current_digit_sequence += current_char;
    }
    ++letter_index;
  }

  if (!current_digit_sequence.empty()) {
    result += GetWordFromVocab(current_digit_sequence, 
                  stars_count, sorted_vocab);
  }

  return result;
}

int main()
{
//  FILE* input = fopen("Input.txt", "r");

  size_t vocab_size;
  scanf("%d", &vocab_size);
//  fscanf(input, "%d", &vocab_size);

  //reading vocabulary data from stdin
  char* word_buffer = new char[121];
  memset(word_buffer, 0, 121);
  DigVectMap digit_sequences;

  for (size_t word_index = 0; word_index < vocab_size; ++word_index) {
    size_t word_frequency;
    scanf("%s %d", word_buffer, &word_frequency);
//    fscanf(input, "%s %d", word_buffer, &word_frequency);

    string input_word(word_buffer);
    string word_digit_form = LettersToDigits(input_word);
    digit_sequences[word_digit_form].push_back(
        StrUIntPair(input_word, word_frequency));
  }

  delete [] word_buffer;

  //sorting digit occurences
  DigVectMap::iterator digit_seq_iter;
  for (digit_seq_iter = digit_sequences.begin(); 
       digit_seq_iter != digit_sequences.end(); 
       ++digit_seq_iter) {
    make_heap((*digit_seq_iter).second.begin(), 
              (*digit_seq_iter).second.end(),
              ComparePairs);
    sort_heap((*digit_seq_iter).second.begin(), 
              (*digit_seq_iter).second.end(),
              ComparePairs);
  }

  char* t9_buffer = new char[100001];
  memset(t9_buffer, 0, 100001);

  while ((t9_buffer[0] < '1' || t9_buffer[0] > '9') && t9_buffer[0] != ' ') {
    gets(t9_buffer);
//    fgets(t9_buffer, 100000, input);
  }

  string input_t9_string(t9_buffer);
  delete [] t9_buffer;

  //getting original text message
  string output_text_message = GetTextFromT9String(input_t9_string, digit_sequences);

  printf("%s", output_text_message.c_str());

  return 0;
}