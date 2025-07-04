#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_LEN 20
#define MAX_WORD_WEIGHT 1000
#define MAX_DICT_LEN 60000
#define BUTTONS ".,? abc def ghi jkl mno pqrstuv wxyz"


//------------------------------------------
//---------------detect button--------------
//------------------------------------------
short int detect_button(char *letter)
{
unsigned short int button = 2;


if (*letter < 'a')
    return (1);

while(*letter >= BUTTONS[4*button])
    {
    button++;
    if (button > 8)
        break;
    }
return (button);
}


//------------------------------------------
//------------word from poinfer-------------
//------------------------------------------
inline char * wd_point(char *words, unsigned short int *pointer_table, unsigned short int element)
{
return ((words + (WORD_LEN + 1) * *(pointer_table + element)));
}


//------------------------------------------
//-----------weight from pointer------------
//------------------------------------------
inline unsigned short int * wh_point(unsigned short int *w_weight, unsigned short int *pointer_table, unsigned short int element)
{
return ((w_weight + *(pointer_table + element)));
}	


//------------------------------------------
//-------------detect start stop------------
//------------------------------------------
int detect_start_stop(char *digi_word, unsigned short int *content_table, unsigned short int *start_pos, unsigned short int *stop_pos, unsigned short int element_num)
{
unsigned short int i, start_index = 0;


if (*digi_word == '1')
    {
    *start_pos = 0;
    *stop_pos = 2;
    }
else
    {
    if(strlen(digi_word) >= 3)
        start_index = (*(digi_word + 1) - 49) * 9 + *(digi_word + 2) - 49;
    else if(strlen(digi_word) == 2)
        start_index = (*(digi_word + 1) - 49) * 9;

    start_index += (*digi_word - 50) * 81;

    if (*(content_table + start_index) == 0)
        return (-1);

    *stop_pos = element_num - 1;

    for (i = start_index + 1; i < 648; i++)
        if (*(content_table + i) > 0)
            {
            *stop_pos = *(content_table + i);
            break;
            }
    *start_pos = *(content_table + start_index);
    }

return 0;
}


//------------------------------------------
//------refresh content table (sort)--------
//------------------------------------------
void refresh_ct(char *words, unsigned short int *w_weight, unsigned short int *pt, unsigned short int start, unsigned short int stop, unsigned short int *element)
{
unsigned short int word_len, i;
unsigned short int tmp_point;


word_len = strlen(wd_point(words, pt, *element));

for(;start <= stop; start++)
    {
      //knopo4nost`
    if ( *wh_point(w_weight, pt, *element) <\
         *wh_point(w_weight, pt, start))
        continue;
    for(i = 0; i <= 2; i++)
        {
        if (*(wd_point(words, pt, *element) + i) == '\0')
                {
                i = 3;
                break;
                }
        else if (*(wd_point(words, pt, start) + i) == '\0')
            break;

        if( detect_button(wd_point(words, pt, *element) + i) <\
            detect_button(wd_point(words, pt, start) + i) )
            {
            i = 3;
            break;
            }
	else if( detect_button(wd_point(words, pt, *element) + i) !=\
                 detect_button(wd_point(words, pt, start) + i) )
            break;
        }
    if (i > 2)
        break;
    }

if (start < *element)
    {
    tmp_point = *(pt + *element);

    for (; start < *element; (*element)--)
        *(pt + *element) = *(pt + *element - 1);

    *(pt + *element) = tmp_point;
    }
}


//------------------------------------------
//-----------fill content table-------------
//------------------------------------------
void fill_cont_table(char *words, unsigned short int *w_weight, unsigned short int *content_table, unsigned short int *pt, unsigned short int element_num)
{
short int i;
unsigned short int element, new_pos, addr, start, stop, max_ct_addr;


for (element = 3; element < element_num; element++)
    {
    addr = (detect_button(wd_point(words, pt, element)) - 2) * 81;

    if (strlen(wd_point(words, pt, element)) >= 3)
        addr += (detect_button(wd_point(words, pt, element) + 1) - 1) * 9\
                 + (detect_button(wd_point(words, pt, element) + 2) - 1);
    else if (strlen(wd_point(words, pt, element)) == 2)
        addr += (detect_button(wd_point(words, pt, element) + 1) - 1) * 9;

      //detect end 4 refresh_ct
    stop = element - 1;
    start = *(content_table + addr);
    max_ct_addr = (detect_button(wd_point(words, pt, element)) - 1) * 81 - 1;
    max_ct_addr = max_ct_addr > 647 ? 647 : max_ct_addr;
    for (i = max_ct_addr; i > addr; i--)
        if (*(content_table + i) != 0)
            {
            if (start < *(content_table + i))
                stop = *(content_table + i) - 1;
            (*(content_table + i))++;
            }

    if (start == 0)
        {
        start = 3;
        for (i = addr - 1; i > 0; i--)
            if (*(content_table + i) > 0)
                {
                start = *(content_table + i) + 1;
                break;
                }
        }
      //refresh dictionary
    (*(w_weight + element))--;
    new_pos = element;
    refresh_ct(words, w_weight, pt, start, stop, &new_pos);
    (*(w_weight + element))++;

      //add record in content table if need
    if (*(content_table + addr) == 0)
        *(content_table + addr) = new_pos;
    }
}


//-----------------------------------------
//--------------------input----------------
//-----------------------------------------
int input_dict(char *words, unsigned short int *w_weight, unsigned short int element_num, unsigned short int *content_table, unsigned short int *pt)
{
unsigned short int i, ii;
char one_char;

  //button 1
*words = '.'; *(words + 1) = '\0'; *w_weight = MAX_WORD_WEIGHT;
*(pt) = 0;

*(words + WORD_LEN + 1) = ','; *(words + WORD_LEN + 2) = '\0';
*(w_weight + 1) = MAX_WORD_WEIGHT;
*(pt + 1) = 1;

*(words + (WORD_LEN + 1) * 2) = '?'; *(words + (WORD_LEN + 1) * 2 + 1) = '\0';
*(w_weight + 2) = MAX_WORD_WEIGHT;
*(pt + 2) = 2;

  //buttons 2..9
for(ii = 3; ii < element_num; ii++)
    {
    for(i = 0; i <= WORD_LEN; i++)
        {
        one_char = getchar();
        if (one_char == ' ')
            {
            *(words + (WORD_LEN + 1) * ii + i) = '\0';
            break;
            }
        if (i == WORD_LEN)
            return (-1);
        if (one_char >= 'a' && one_char <= 'z')
            *(words + (WORD_LEN + 1) * ii + i) = one_char;
        else
            return (-1);
        }

    *(w_weight + ii) = 0;

    for(i = 0; i <= 5; i++)
        {
        one_char = getchar();
        if (one_char == '\n')
            break;
        if (i == 5)
            return (-1);	//to long weight value
        if (one_char >= '0' && one_char <= '9')
            *(w_weight + ii) = *(w_weight + ii) * 10 + (one_char - 48);
        else
            return (-1);
        }
    

    if (*(w_weight + ii) < 1 || *(w_weight + ii) > MAX_WORD_WEIGHT)
        return (-1);

    *(pt + ii) = ii;
    }
	
return 0;
}


//------------------------------------------
//-------------input buttons----------------
//------------------------------------------
int input_buttons(char *previous_char, char *digi_word, unsigned short int *variant_num)
{
unsigned short int i;


i = 0;
*variant_num = 0;
  //input word formula
while (1)
    {
      //word
    if ( *previous_char == '\0' || *previous_char == '\n' ||\
         *previous_char == ' ' )
        {
        *(digi_word + i) = '\0';
        return 0;
        }
      //star counter
    if (*previous_char == '*')
        {
	if (i == 0)
            return (-1);
        while (*previous_char == '*')
            {
            (*variant_num)++;
            *previous_char = getchar();
            }
        *(digi_word + i) = '\0';
        return 0;
        }
      //button 1
    if (*previous_char == '1')
        if (i == 0)
            {
            *previous_char = getchar();
            if (*previous_char == '*' || *previous_char == ' ' ||\
                *previous_char == '\0' || *previous_char == '\n')
                {
                *(digi_word + i) = '1';
                i++;
                continue;
                }
            *(digi_word + i) = '1';
            *(digi_word + i + 1) = '\0';
            return 0;
            }
        else
            {
            *(digi_word + i) = '\0';
            return 0;
            }

    if (*previous_char >= '2' && *previous_char <= '9' && i < WORD_LEN)
        {
        *(digi_word + i) = *previous_char;
        *previous_char = getchar();
	i++;
        continue;
        }
    return (-1);
    }
}


//------------------------------------------
//--------------select word-----------------
//------------------------------------------
int select_word(char *dict, char *digi_word, unsigned short int *w_weight, unsigned short int *pt, unsigned short int start_pos, unsigned short int stop_pos, unsigned short int variant_need, unsigned short int *variants_found, unsigned short int *dict_index)
{
unsigned short int i, ii;
unsigned short int word_len;
char tmp_word[21];


*variants_found = 0;
word_len = strlen(digi_word);
for(i = start_pos; i <= stop_pos; i++)
    {
      //cmp strings
    for (ii = 3; ii < word_len ; ii++)
        if ( detect_button((wd_point(dict, pt, i) + ii)) !=\
             (*(digi_word + ii) - 48) )
            break;

    if (ii >= word_len)
        {
        if (ii == word_len && *(wd_point(dict, pt, i) + ii) != '\0')
            continue;
        (*variants_found)++;
        if (*variants_found >= variant_need)
            {
            *dict_index = i;
            return 0;
            }
        }
    }

return (-1);
}


//------------------------------------------
//---------------------main-----------------
//------------------------------------------
int main(int argc, char **argv)
{
unsigned short int index = 0;	//word number
unsigned short int element_num = 0;
unsigned short int *w_weight;	//word weight
char *words;
unsigned short int content_table[8][9][9]; //2, 22, 222, 223, 224, ..., 229,
                                           //0, 23, 232, 233, ...
unsigned short int *pointer_table;	//index -> word

  //iterator
unsigned short int i, ii, iii;
unsigned short int variant_num, variants_found;
unsigned short int start_pos, stop_pos;
char digi_word[21];
char one_char;

  //exit status
//0 - Ok
//100 - to long dictionary
//101 - input dict error
//102 - input button error
//103 - detect start, stop error
//104 - variant of word not found


for(i = 0; i < 648; i++)
    *(&content_table[0][0][0] + i) = 0;
  //get dictionary size
while(1)
    {
    one_char = getchar();
    if (one_char == '\n')
        break;
    if (one_char >= '0' && one_char <= '9')
        element_num = element_num * 10 + ((int)one_char - 48);
    }

element_num += 3;	//+ '.', ',', '?'
if (element_num > MAX_DICT_LEN)
    return (100);

w_weight = (unsigned short int *)malloc(element_num * sizeof(short int));
words = (char *)malloc((WORD_LEN + 1) * element_num * sizeof(char));
pointer_table = (unsigned short int *)malloc(element_num * sizeof(short int));

  //get dictionare from stdin
if (input_dict( words, w_weight, element_num, &content_table[0][0][0],\
                pointer_table) < 0 )
    return (101);

fill_cont_table( words, w_weight, &content_table[0][0][0], pointer_table,\
                 element_num );
  //get sting formula(digital) & print analog str
one_char = getchar();
while (1)
    {
    //get word by word from last line
    if (one_char == ' ')
        {
        fprintf(stdout, " ");
        one_char = getchar();
	continue;
        }
    if (one_char == '\0' || one_char == '\n')
        {
        fprintf(stdout, "\n");
        break;
        }
    if (input_buttons(&one_char, &digi_word[0], &variant_num) < 0)
        return (102);

        //define startt & stop
    if ( detect_start_stop(&digi_word[0], &content_table[0][0][0],\
         &start_pos, &stop_pos, element_num) < 0 )
        return (103);

        //find word
    if ( select_word(words, &digi_word[0], w_weight, pointer_table, start_pos,\
                     stop_pos, variant_num + 1, &variants_found, &index) < 0 )
        return (104);

    fprintf(stdout, "%s", wd_point(words, pointer_table, index));

        //check weight & refresh dictionary
    if (*wh_point(w_weight, pointer_table, index) < MAX_WORD_WEIGHT)
        {
        (*wh_point(w_weight, pointer_table, index))++;
        refresh_ct( words, &w_weight[0], pointer_table, start_pos,\
                    index - 1, &index );
        }
    }
return 0;
}

