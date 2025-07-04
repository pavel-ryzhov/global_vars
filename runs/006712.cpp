#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALLOCATE_SIZE_STRING  100
#define MAX_WORD_SIZE         21
#define MAX_NUMBER_OF_LETTERS_ON_DIGIT  5

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

struct word
{
  char *w;
  char *d;
  unsigned int q;
  bool copy;

  word ()
  {
    w = 0;
    q = 0;
    d = 0;
    copy = false;
  }

  word (const word &from)
  {
    w = from.w;
    q = from.q;
    d = from.d;
    copy = true;
  }

  ~word ()
  {
    if (!copy)
      {
        delete [] w;
        delete [] d;
      }
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
  memcpy (temp, str, size);
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

static inline char to_digit (const char c)
{
  int i, j;
  for (i = 1; i < 10; i++)
    for (j = 0; j < MAX_NUMBER_OF_LETTERS_ON_DIGIT; j++)
      if (coding[i][j] == c)
        return i + '0';
  return 0;
}

void read_word (struct word &r)
{
  char *c_w, *c_d;
  r.w = new char [MAX_WORD_SIZE];
  r.d = new char [MAX_WORD_SIZE];
  memset (r.w, '\0', MAX_WORD_SIZE);
  memset (r.d, '\0', MAX_WORD_SIZE);

  scanf ("%s %u", r.w, &r.q);
  for (c_w = r.w, c_d = r.d; *c_w != '\0'; c_w++, c_d++)
    *c_d = to_digit (*c_w);
}

int read_input_data (struct word *&dictionary, unsigned int &dictionary_size, char *&str)
{
  scanf ("%ui", &dictionary_size);
  if (!dictionary_size)
    return 1;

  dictionary = new struct word [dictionary_size];
  for (unsigned int i = 0; i < dictionary_size; i++)
    read_word (dictionary[i]);

  return read_string (str);
}

unsigned int move (struct word *&dictionary, unsigned int i)  // to keep sorting, returns new position
{
  unsigned int j;

  for (j = 0; (j < i) && (strcmp (dictionary[j].d, dictionary[i].d) < 0); j++) ;
  for (; (j < i) && (strcmp (dictionary[j].d, dictionary[i].d) == 0) && (dictionary[j].q > dictionary[i].q); j++) ;

  if (i == j)
    return i;

  // moving from i to j
  struct word temp = dictionary[i];

  for (unsigned int k = i; k > j; k--)
    dictionary[k] = dictionary [k - 1];
  dictionary[j] = temp;
  dictionary[j].copy = false;

  return j;
}

static inline int compare (const struct word a, const struct word b)
{
  int cmp = strcmp (a.d, b.d);
  if (cmp)
    return cmp;
  else if (a.q != b.q)
    {
      if (a.q < b.q)
        return 1;
      else
        return -1;
    }
  else
    return strcmp (a.w, b.w);
}

void replace (struct word &a, struct word &b)
{
  struct word temp = a;
  a = b;
  b = temp;
  b.copy = false;
}

int find_position_and_reverse (struct word *dictionary, unsigned int dictionary_size, const struct word x)
{
  struct word *a, *b;
  unsigned int i, j;

  a = dictionary;          // borders
  b = dictionary + dictionary_size - 1;

  i = 0;
  j = dictionary_size - 1;

  while (i <= j)
    {
      while ((i < dictionary_size - 1) && (compare (*a, x) < 0))
        {
          a++;
          i++;
        }
      while ((j > 0) && (compare (*b, x) > 0))
        {
          b--;
          j--;
        }
      if (i <= j)
        {
          replace (*a, *b);
          a++;
          i++;
          b--;
          j--;
        }
    }
  return i;
}

void quick_sort (struct word *dictionary, unsigned int dictionary_size)
{
  int i, p, k;

  k = dictionary_size;
  while (k > 2)
    {
      p = (unsigned int) k >> 1;
      i = find_position_and_reverse (dictionary, k, dictionary[p]);

      if (i == k)
        {
          replace (dictionary[p], dictionary[k - 1]);
          i--;
        }

      if (i > k - i)
        {
          quick_sort (dictionary + i, k - i);
          k = i;
        }
      else
        {
          quick_sort (dictionary, i);
          k = k - i;
          dictionary = dictionary + i;
        }
    }

    if (k == 2)
      {
        if (compare (dictionary[0], dictionary[1]) > 0)
          replace (dictionary[0], dictionary[1]);
      }
}

void sort (struct word *dictionary, unsigned int dictionary_size)
{
  quick_sort (dictionary, dictionary_size);
}

static inline bool letter_match (const char digit, const char letter) // 0 < digit < 9
{
  for (int i = 0; i < MAX_NUMBER_OF_LETTERS_ON_DIGIT; i++)
    if (coding[(int) digit][i] == letter)
      return true;
  return false;
}

static inline bool word_match (char *digit_word, char *word)
{
  char *curr_digit  = digit_word,
       *curr_letter = word;
  for ( ; (*curr_digit != '\0') && (*curr_letter != '\0'); curr_digit++, curr_letter++)
    if (!letter_match (*curr_digit - '0', *curr_letter))
      return false;

  return ((*curr_digit == '\0') && (*curr_letter == '\0'));
}

char *find_word (struct word *&dictionary, const unsigned int dictionary_size, char *word, int k)
{
  unsigned int a = 0,
               b = dictionary_size - 1,
               m = 0,
               i;
  int cmp;

  while (1)
    {
      m = (b + a) >> 1;

      if (strcmp (dictionary[a].d, word) == 0)
        {
          i = a;
          break;
        }
      if (strcmp (dictionary[b].d, word) == 0)
        {
          i = b;
          break;
        }

      cmp = strcmp (dictionary[m].d, word);
      if (cmp < 0)
        a = m;
      else if (cmp > 0)
        b = m + 1;
      else
        {
          i = m;
          break;
        }
    }

  for (; (i > 0) && (strcmp (dictionary[i].d, word) == 0) && (strcmp (dictionary[i - 1].d, word) == 0); i--) ;
  i += k;

  dictionary[i].q++;
  return dictionary[move (dictionary, i)].w;
}

void parse_word (struct word *&dictionary, unsigned int dictionary_size, char *word, char *&result, int k)
{
  if (*word == '1') // sign
    *result++ = coding[1][k];
  else
    {
      char *found_word;
      unsigned int found_word_size = 0;

      found_word = find_word (dictionary, dictionary_size, word, k);

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
  int k = 0;                // * count
  int z = 0;

  memset (word, '\0', MAX_WORD_SIZE);
  for (; ; c++)
    {
      if ((c_word != word) && (*word == '1') && (*c != '*'))
        {
          parse_word (dictionary, dictionary_size, word, c_result, k);
          c_word = word;
          memset (word, '\0', MAX_WORD_SIZE);
          k = 0;
          c--;
        }
      else if ((*c >= '2') && (*c <= '9'))
        *c_word++ = *c;
      else if (*c == '*')
        k++;
      else
        {
          if (c_word != word)
            {
              parse_word (dictionary, dictionary_size, word, c_result, k);
              c_word = word;
              memset (word, '\0', MAX_WORD_SIZE);
              k = 0;
            }

          if (*c == ' ')
            *c_result++ = *c;
          else if (*c == '1')  // sign
            *c_word++ = *c;
          else if (*c == '\0') // end of source string
            break;
        }
      z++;
      if (z % 1000 == 0)
        fprintf (stderr, "%i ", z);
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

  fprintf (stderr, "begin\n");
  int str_size = read_input_data (dictionary, dictionary_size, str);
  fprintf (stderr, "data readed\n");
  sort (dictionary, dictionary_size);
  fprintf (stderr, "dictionary sorted\n");

  result_str = new char [str_size + 1];
  memset (result_str, '\0', str_size + 1);

  parse_string (dictionary, dictionary_size, str, result_str);
  fprintf (stderr, "parsed\n");

  printf ("%s", result_str);

  delete [] str;
  delete [] result_str;
  delete [] dictionary;
  fprintf (stderr, "end\n");

  return 0;
}
