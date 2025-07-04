#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALLOCATE_SIZE_STRING  100
#define MAX_WORD_SIZE         21
#define MAX_NUMBER_OF_LETTERS_ON_DIGIT  5

struct word
{
  char *w;
  unsigned int q;

  word ()
  {
    w = 0;
    q = 0;
  }

  word (const word &from)
  {
    w = from.w;
    q = from.q;
  }

  ~word ()
  {
    delete [] w;
  }
};

int reallocate_string (char *&str, unsigned int size, unsigned int new_size)
{
  if (new_size <= size)
    return 1;

  char *temp = new char [new_size];
  if (!temp)
    return 2;

  memset (temp, '\0', new_size);
  memcpy (temp, str, size * sizeof (char));
  delete [] str;
  str = temp;
  return 0;
}

static inline bool true_symbol (char c)
{
  return (c == ' ') || (c == '*') || ((c >= '1') && (c <= '9'));
}

int read_string (char *&str)
{
  char c;       // input
  char *curr;   // current char in str
  unsigned int str_size = 0;

  for (c = getc (stdin); !true_symbol (c) || (c == ' '); c = getc (stdin)) ;
  for ( ;true_symbol (c); c = getc (stdin))
    {
      if (!(str_size % ALLOCATE_SIZE_STRING)) // its time to allocate memory
        {
          reallocate_string (str, str_size, str_size + ALLOCATE_SIZE_STRING);
          curr = str + str_size;
        }

      str_size++;
      *curr++ = c;
    }

  return str_size;
}

void read_word (struct word &r)
{
  r.w = new char [MAX_WORD_SIZE];
  scanf ("%s %u", r.w, &r.q);
}

int read_input_data (struct word *&dictionary, unsigned int &dictionary_size, char *&str)
{
  scanf ("%ui", &dictionary_size);
  if (!dictionary_size)
    return 1;

  dictionary = new struct word [dictionary_size];
  for (unsigned int i = 0; i < dictionary_size; i++)
    read_word (dictionary[i]);

  int n = read_string (str);
  fclose (stdin);
  return n;
}

unsigned int move (struct word *&dictionary, unsigned int i, unsigned int to = 0)  // to keep sorting, returns new position
{
  unsigned int j;
  if (to == 0)  // we need to found position
    for (j = 0; (j < i) && (dictionary[j].q > dictionary[i].q); j++);
  else
    j = to;

  if (i == j)
    return i;

  // moving from i to j
  char *w = dictionary[i].w;
  unsigned int q = dictionary[i].q;

  for (unsigned int k = i; k > j; k--)
    dictionary[k] = dictionary [k - 1];
  dictionary[j].w = w;
  dictionary[j].q = q;

  return j;
}

void sort_by_freq (struct word *dictionary, unsigned int dictionary_size)
{
  unsigned int i, j;
  unsigned int index;

  for (i = 0; i < dictionary_size - 1; i++)
    {
      index = i;
      for (j = i + 1; j < dictionary_size; j++)
        {
          if (dictionary[j].q > dictionary[index].q)
            index = j;
        }
      move (dictionary, index, i);
    }
}

static inline bool letter_match (const char *coding[10], const char digit, const char letter) // 0 < digit < 9
{
  for (int i = 0; i < MAX_NUMBER_OF_LETTERS_ON_DIGIT; i++)
    if (coding[(int) digit][i] == letter)
      return true;
  return false;
}

static inline bool word_match (const char *coding[10], char *digit_word, char *word)
{
  char *curr_digit  = digit_word,
       *curr_letter = word;
  for ( ; (*curr_digit != '\0') && (*curr_letter != '\0'); curr_digit++, curr_letter++)
    if (!letter_match (coding, *curr_digit - '0', *curr_letter))
      return false;

  return ((*curr_digit == '\0') && (*curr_letter == '\0'));
}

char *find_word (const char *coding[10], struct word *&dictionary, unsigned int dictionary_size, char *word)
{
  unsigned int k = 0;
  char *c = word + strlen (word) - 1;

  for ( ; (*c == '*') && (c != word); c--, k++)
    *c = '\0';

  for (unsigned int i = 0; i < dictionary_size; i++)
    {
      if (word_match (coding, word, dictionary[i].w))
        {
          if (k == 0)
            {
              dictionary[i].q++;
              return dictionary[move (dictionary, i)].w;
            }
          else
            k--;
        }
    }
  return 0;
}

void parse_word (struct word *&dictionary, unsigned int dictionary_size, char *word, char *&result)
{
  const char *coding[10] =
  {
    "*   ",  //  0 - just for offset
    ".,? ",  //  1
    "abc ",  //  2
    "def ",  //  3
    "ghi ",  //  4
    "jkl ",  //  5
    "mno ",  //  6
    "pqrs",  //  7
    "tuv ",  //  8
    "wxyz"   //  9
  };

  if (*word == '1') // sign
    *result++ = coding[1][strlen (word) - 1];
  else
    {
      char *found_word;
      unsigned int found_word_size = 0;

      found_word = find_word (coding, dictionary, dictionary_size, word);

      if (!found_word)
        return;
      found_word_size = strlen (found_word);
      memcpy (result, found_word, found_word_size);
      result += found_word_size;
    }
}

int parse_string (struct word *&dictionary, unsigned int dictionary_size, char *str, char *&result)
{
  char *c = str;            // current char in str
  char *word = new char [MAX_WORD_SIZE];
  char *c_word = word;      // current char in word
  char *c_result = result;  // current char in result

  memset (word, '\0', MAX_WORD_SIZE);
  for (; ; c++)
    {
      if (((*c >= '2') && (*c <= '9')) || (*c == '*'))
        *c_word++ = *c;
      else
        {
          if (c_word != word)
            {
              parse_word (dictionary, dictionary_size, word, c_result);
              c_word = word;
              memset (word, '\0', MAX_WORD_SIZE);
            }

          if (*c == ' ')
            *c_result++ = *c;
          else if (*c == '1')  // sign
            *c_word++ = *c;
          else if (*c == '\0') // end of source string
            break;
        }
    }

  delete [] word;
  return 0;
}

int main (void)
{
  char *str = 0;
  char *result_str = 0;
  struct word *dictionary = 0;
  unsigned int dictionary_size = 0;

  int str_size = read_input_data (dictionary, dictionary_size, str);

  sort_by_freq (dictionary, dictionary_size);

  result_str = new char [str_size + 1];
  memset (result_str, '\0', str_size + 1);

  parse_string (dictionary, dictionary_size, str, result_str);

  printf ("%s", result_str);

  delete [] str;
  delete [] result_str;
  delete [] dictionary;

  return 0;
}
