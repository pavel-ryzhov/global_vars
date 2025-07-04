#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_LEN 20
#define MAX_WORD_WEIGHT 1000
#define BUTTONS ".,? abc def ghi jkl mno pqrstuv wxyz"

//-----------------------------------------
//--------------------input----------------
//-----------------------------------------
int input_dict(char *words, unsigned short int *w_weight, unsigned short int element_num)
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

    }
	
return 0;
}


//------------------------------------------
//-----------fill content table-------------
//------------------------------------------
void fill_cont_table(char *words, unsigned short int *content_table, unsigned short int element_num)
{
unsigned short int i, button;


*content_table = 0;
for (i = 1; i <= 8; i++)
    *(content_table + i) = 0;

button = 2;
for(i = 3; i < element_num; i++)
    {
    while(*(words + (WORD_LEN + 1) * i) >= BUTTONS[4*button])
        {
        if (button > 8)
            break;
        button++;
        }
    if (*(content_table + (button - 1)) > 0)
        continue;
    *(content_table + (button - 1)) = i;
    if (button == 9)
        break;
    }
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
//---------------detect button--------------
//------------------------------------------
short int detect_button(char letter)
{
unsigned short int button = 2;


if (letter < 'a')
    return (1);

while(letter >= BUTTONS[4*button])
    {
    button++;
    if (button > 8)
        break;
    }
return (button);
}


//------------------------------------------
//-----------------get word-----------------
//------------------------------------------
int select_word(char *dict, char *digi_word, unsigned short int *w_weight, unsigned short int start_pos, unsigned short int stop_pos, unsigned short int variant_need, unsigned short int *variants_found, unsigned short int *dict_index)
{
unsigned short int i, ii;
unsigned short int weight, next_weight;
char tmp_word[21];


weight = MAX_WORD_WEIGHT;
while (1)
    {
    next_weight = 0;
    for(i = start_pos; i <= stop_pos; i++)
        {
        if (*(w_weight + i) == weight)
            {
            //cmp strings
            for (ii = 0; ii <= WORD_LEN ; ii++)
                {
                if ( *(digi_word + ii) == '\0' &&\
                     *(dict + (WORD_LEN + 1) * i + ii) == '\0')
                    {
                    (*variants_found)++;
                    *dict_index = i;
                    break;
                    }
                if ( *(digi_word + ii) - 48 !=\
                     detect_button(*(dict + (WORD_LEN + 1) * i + ii)) )
                    break;
                }
	    //string 1 = string 2
            if (*variants_found >= variant_need)
                {
                if (*(w_weight + *dict_index) < MAX_WORD_WEIGHT)
                    (*(w_weight + *dict_index))++;
 
                //move str on top
		if (*dict_index < 3)
                    break;
                strcpy(&tmp_word[0], (dict + (WORD_LEN + 1) * *dict_index));
                weight = *(w_weight + *dict_index);
                for(i = *dict_index; i > start_pos; i--)
                    {
                    strcpy( (dict + (WORD_LEN + 1) * i),\
                            (dict + (WORD_LEN + 1) * (i - 1)) );
                    *(w_weight + i) = *(w_weight + i - 1);
                    }
                strcpy((dict + (WORD_LEN + 1) * i), &tmp_word[0]);
                *(w_weight + i) = weight;
                *dict_index = i;

                break;
                }
            }
        else
            if (*(w_weight + i) > next_weight && *(w_weight + i) < weight)
                next_weight = *(w_weight + i);
        }
    if (next_weight < 1)
        return (-1);
    weight = next_weight;
    }
return 0;
}


//------------------------------------------
//---------------------main-----------------
//------------------------------------------
int main(int argc, char **argv)
{
unsigned short int index;	//word number
unsigned short int element_num = 0;
unsigned short int *w_weight;	//word weight
char *words;
unsigned short int content_table[9];
  //iterator
unsigned short int i;
unsigned short int variant_num, variants_found;
unsigned short int start_pos, stop_pos;
char digi_word[21];
char one_char;


while(1)
    {
    one_char = getchar();
    if (one_char == '\n')
        break;
    if (one_char >= '0' && one_char <= '9')
        element_num = element_num * 10 + ((int)one_char - 48);
    }

element_num += 3;
if (element_num > 50000)
    return (-1);

w_weight = (unsigned short int *)malloc(element_num * sizeof(short int));
words = (char *)malloc((WORD_LEN + 1) * element_num * sizeof(char));

if (input_dict(words, w_weight, element_num) < 0)
    return (-1);

fill_cont_table(words, &content_table[0], element_num);

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
    start_pos = content_table[digi_word[0] - 49];
    if (start_pos == 0 && digi_word[0] - 48 != 1)
        return (-1);

    stop_pos = element_num - 1;
    for (i = digi_word[0] - 48; i < 9; i++)
        if (content_table[i] > 0)
            {
            stop_pos = content_table[i];
            break;
            }

    variants_found = 0;
    select_word( words, &digi_word[0], &w_weight[0], start_pos, stop_pos,\
                 variant_num + 1, &variants_found, &index );

    fprintf(stdout, "%s", (words + (WORD_LEN + 1) * index));

    }
return 0;
}

