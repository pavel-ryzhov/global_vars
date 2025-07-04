#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_LEN 20
#define MAX_WORD_WEIGHT 1000
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
//-------------detect start stop------------
//------------------------------------------
int detect_start_stop(char *digi_word, unsigned short int *content_table, unsigned short int *start_pos, unsigned short int *stop_pos, unsigned short int element_num)
{
unsigned short int i, start_index = 0;


if (*digi_word - 48 == 1)
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
void refresh_ct(char *words, unsigned short int *w_weight, unsigned short int start, unsigned short int stop, unsigned short int *element)
{
unsigned short int word_len, i;
unsigned short int tmp_weight;
char tmp_word[WORD_LEN + 1];



word_len = strlen((words + (WORD_LEN + 1) * *element));

for(;start <= stop; start++)
    {
    //knopo4nost`
    for(i = 0; i <= word_len; i++)
        {
        if (*(words + (WORD_LEN + 1) * *element + i) == '\0')
            if (*(words + (WORD_LEN + 1) * start + i) != '\0')
                {
                i = word_len + 1;
                break;
                }
            else if(*(w_weight + *element) >= *(w_weight + start))
                {
                i = word_len + 1;
                break;
                }
            else
                break;
        else if (*(words + (WORD_LEN + 1) * start + i) == '\0')
            break;

        if( detect_button((words + (WORD_LEN + 1) * *element + i)) <\
            detect_button((words + (WORD_LEN + 1) * start + i)) )
            {
            i = word_len + 1;
            break;
            }
	else if( detect_button((words + (WORD_LEN + 1) * *element + i)) !=\
            detect_button((words + (WORD_LEN + 1) * start + i)) )
            break;
        }
    if ( i > word_len )
        break;
    }

if (start < *element)
    {
    strcpy(tmp_word, (words + (WORD_LEN + 1) * *element));
    tmp_weight = *(w_weight + *element);

    for (; start < *element; (*element)--)
        {
        strcpy( (words + (WORD_LEN + 1) * *element),\
                (words + (WORD_LEN + 1) * (*element - 1)) );
        *(w_weight + *element) = *(w_weight + *element - 1);
        }

    strcpy((words + (WORD_LEN + 1) * *element), tmp_word);
    *(w_weight + *element) = tmp_weight;
    }
}


//------------------------------------------
//-----------fill content table-------------
//------------------------------------------
void fill_cont_table(char *words, unsigned short int *w_weight, unsigned short int *content_table, unsigned short int element)
{
unsigned short int i, addr, start, stop, max_ct_addr;

addr = (detect_button((words + (WORD_LEN + 1) * element)) - 2) * 81;

if (strlen((words + (WORD_LEN + 1) * element)) >= 3)
    addr += (detect_button((words + (WORD_LEN + 1) * element + 1)) - 1) * 9\
             + (detect_button((words + (WORD_LEN + 1) * element + 2)) - 1);
else if (strlen((words + (WORD_LEN + 1) * element)) == 2)
    addr += (detect_button((words + (WORD_LEN + 1) * element + 1)) - 1) * 9;


  //edit content table
if (*(content_table + addr) == 0)
    *(content_table + addr) = element;
    {
    //detect end 4 refresh_ct
    stop = element - 1;
    start = *(content_table + (detect_button((words + (WORD_LEN + 1) * element)) - 2) * 81);
    max_ct_addr = (detect_button((words + (WORD_LEN + 1) * element)) - 1) * 81 - 1;
    max_ct_addr = max_ct_addr > 647 ? 647 : max_ct_addr;
    for (i = max_ct_addr; i > addr; i--)
        if (*(content_table + i) != 0)
            {
            if (start < *(content_table + i) - 1)
                stop = *(content_table + i) - 1;
            (*(content_table + i))++;
            }

    (*(w_weight + element))--;
    refresh_ct(words, w_weight, start, stop, &element);
    (*(w_weight + element))++;
    }
}


//-----------------------------------------
//--------------------input----------------
//-----------------------------------------
int input_dict(char *words, unsigned short int *w_weight, unsigned short int element_num, unsigned short int *content_table)
{
unsigned short int i, ii;
char one_char;

  //button 1
*words = '.'; *(words + 1) = '\0';
*w_weight = MAX_WORD_WEIGHT;
*(words + WORD_LEN + 1) = ','; *(words + WORD_LEN + 2) = '\0';
*(w_weight + 1) = MAX_WORD_WEIGHT;
*(words + (WORD_LEN + 1) * 2) = '?'; *(words + (WORD_LEN + 1) * 2 + 1) = '\0';
*(w_weight + 2) = MAX_WORD_WEIGHT;

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
            return (-1);
        if (one_char >= '0' && one_char <= '9')
            *(w_weight + ii) = *(w_weight + ii) * 10 + (one_char - 48);
        else
            return (-1);
        }

    if (*(w_weight + ii) < 1 || *(w_weight + ii) > MAX_WORD_WEIGHT)
        return (-1);

    fill_cont_table(words, w_weight, content_table, ii);

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
while (1)
    {
    if (*previous_char == '\0' || *previous_char == '\n' || *previous_char == ' ')
        {
        *(digi_word + i) = '\0';
        return 0;
        }
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
//-----------------get word-----------------
//------------------------------------------
int select_word(char *dict, char *digi_word, unsigned short int *w_weight, unsigned short int start_pos, unsigned short int stop_pos, unsigned short int variant_need, unsigned short int *variants_found, unsigned short int *dict_index)
{
unsigned short int i, ii, z, zz;
unsigned short int word_len, dict_word_len;
char tmp_word[21];


*variants_found = 0;
word_len = strlen(digi_word);
for(i = start_pos; i <= stop_pos; i++)
    {
    dict_word_len = strlen(dict + (WORD_LEN + 1) * i);
    if (dict_word_len == word_len)
        {
        //cmp strings
        for (ii = 0; ii < word_len ; ii++)
            {
            
            if ( detect_button((dict + (WORD_LEN + 1) * i + ii)) !=\
                 (*(digi_word + ii) - 48) )
                break;
            }

        if (ii == word_len)
            {
            (*variants_found)++;
            if (*variants_found >= variant_need)
                {
                *dict_index = i;
                return 0;
                }
            }
        }
    else
        if (dict_word_len > word_len)
            return (-1);
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
unsigned short int content_table[8][9][9];	//2, 22, 222, 223, 224, ..., 229,
                                          	//0, 23, 232, 233, ...
//iterator
unsigned short int i;
unsigned short int variant_num, variants_found;
unsigned short int start_pos, stop_pos;
char digi_word[21];
char one_char;


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
if (element_num > 50000)
    return (-1);

w_weight = (unsigned short int *)malloc(element_num * sizeof(short int));
words = (char *)malloc((WORD_LEN + 1) * element_num * sizeof(char));

if (input_dict(words, w_weight, element_num, &content_table[0][0][0]) < 0)
    return (-1);

	
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
        return (-1);

        //define startt & stop
    if ( detect_start_stop(&digi_word[0], &content_table[0][0][0],\
         &start_pos, &stop_pos, element_num) < 0 )
        return (-1);


    select_word( words, &digi_word[0], w_weight, start_pos, stop_pos,\
                 variant_num + 1, &variants_found, &index );

    if (*(w_weight + index) < MAX_WORD_WEIGHT)
        {
        (*(w_weight + index))++;
        refresh_ct(words, &w_weight[0], start_pos, index - 1, &index);
        }

    fprintf(stdout, "%s", (words + (WORD_LEN + 1) * index));
    }

return 0;
}

