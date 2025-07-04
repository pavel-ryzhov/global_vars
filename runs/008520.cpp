/* The test task, part C.

First, excuse me, but I don't wish to have sex with the UTF-8<->CP1251/KOI8-R
translation, neither I want you to puzzle over my transliterations. That's why
I've got to write my comments explaining the core of my code in pure english.
I swear my comments are absolutely "Promt" free and are written exclusively
using my own mind with a very slight lexical help from Yandex.Dictionaries.*/

#include <stdlib.h>
#include <stdio.h>
struct el { //elements of the word list;
   char* word;
   int freq;
   struct el* next;
};
struct dn { //data nodes;
   struct dn* ii;
   struct dn* iii;
   struct dn* iv;
   struct dn* v;
   struct dn* vi;
   struct dn* vii;
   struct dn* viii;
   struct dn* ix;
   struct el* val;
};
int main (int argc, char* argv [] ) {
   FILE* fd;
   fpos_t pos;
   int i, m, freq, ch;
   char one [] = ".,?";
   struct dn* root; //The root node of the tree.
   struct dn* cdn; //The current node of the tree.
   struct el* ael; //An auxilliary element of the list.
   struct el* cel; //The current element of the list.
   struct el* from; //The former parent of the element.
   struct el* to; //The new parent of the element.
   if (argc != 2) {
      printf ("Invalid input string!\n");
      return -1;
   }
   if ( (fd = fopen (argv [1], "r") ) == NULL) {
      printf ("Invalid or absent input file!\n");
      return -1;
   }
   root = (struct dn*) malloc (sizeof (struct dn) );
   fscanf (fd, "%i", &m);
   while (m > 0) {
      cdn = root;
      fgetpos (fd, &pos);
      ch = fgetc (fd);
      i = 0;
      while (ch != ' ') {
         switch (ch) {
            case 'a':
            case 'b':
            case 'c': {
               if (cdn->ii == NULL)
                  cdn->ii = (struct dn*) malloc (sizeof (struct dn) );
               cdn = cdn->ii;
               break;
            }
            case 'd':
            case 'e':
            case 'f': {
               if (cdn->iii == NULL)
                  cdn->iii = (struct dn*) malloc (sizeof (struct dn) );
               cdn = cdn->iii;
               break;
            }
            case 'g':
            case 'h':
            case 'i': {
               if (cdn->iv == NULL)
                  cdn->iv = (struct dn*) malloc (sizeof (struct dn) );
               cdn = cdn->iv;
               break;
            }
            case 'j':
            case 'k':
            case 'l': {
               if (cdn->v == NULL)
                  cdn->v = (struct dn*) malloc (sizeof (struct dn) );
               cdn = cdn->v;
               break;
            }
            case 'm':
            case 'n':
            case 'o': {
               if (cdn->vi == NULL)
                  cdn->vi = (struct dn*) malloc (sizeof (struct dn) );
               cdn = cdn->vi;
               break;
            }
            case 'p':
            case 'q':
            case 'r':
            case 's': {
               if (cdn->vii == NULL)
                  cdn->vii = (struct dn*) malloc (sizeof (struct dn) );
               cdn = cdn->vii;
               break;
            }
            case 't':
            case 'u':
            case 'v': {
               if (cdn->viii = NULL)
                  cdn->viii = (struct dn*) malloc (sizeof (struct dn) );
               cdn = cdn->viii;
               break;
            }
            case 'w':
            case 'x':
            case 'y':
            case 'z': {
               if (cdn->ix == NULL)
                  cdn->ix = (struct dn*) malloc (sizeof (struct dn) );
               cdn = cdn->ix;
               break;
            }
         }
         ch = fgetc (fd);
         i ++;
      } //Now I've obtained the length of the word; it is $i.
      //Not really, though. The experiment has shown that I must use $i - 1.
      //I guess the happening is due to the usage of fseek.
      //Now I am to get the value of the word's frequency.

      while (ch == ' ') {
         ch = fgetc (fd);
      }
      fseek (fd, -1, SEEK_CUR);
      fscanf (fd, "%i", &freq);//Now $freq is the frequency of the word.
      fsetpos (fd, &pos); //Now $fd points to the first character of the string.
      fseek (fd, 1, SEEK_CUR);
      ael = (struct el*) malloc (sizeof (struct el) );
      ael->freq = freq;
      ael->word = (char*) malloc (21 * sizeof (char) );
      fread (ael->word, 1, i - 1, fd);
      //Now I have to find a place for the new element.
      if ( (cdn->val == NULL) || (cdn->val->freq < freq) ) {
         ael->next = cdn->val;
         cdn->val = ael;
      } else {
         cel = cdn->val;
         while (1) {
            if ( (cel->next == NULL) || (cel->next->freq < freq) ){
               ael->next = cel->next;
               cel->next = ael;
               break;
            }
            cel = cel->next;
         } //The element has been successfully inserted.
      }
      m --;
      while ( (ch = fgetc (fd) ) == ' ');
   }
   ch = fgetc (fd);
   ch = fgetc (fd);
   while (ch != 10) {
      cdn = root;
      while ( (ch != ' ') && (ch != '1') ) {
         switch (ch) {
            case '2': {
               cdn = cdn->ii;
               cel = cdn->val;
               break;
            }
            case '3': {
               cdn = cdn->iii;
               cel = cdn->val;
               break;
            }
            case '4': {
               cdn = cdn->iv;
               cel = cdn->val;
               break;
            }
            case '5': {
               cdn = cdn->v;
               cel = cdn->val;
               break;
            }
            case '6': {
               cdn = cdn->vi;
               cel = cdn->val;
               break;
            }
            case '7': {
               cdn = cdn->vii;
               cel = cdn->val;
               break;
            }
            case '8': {
               cdn = cdn->viii;
               cel = cdn->val;
               break;
            }
            case '9': {
               cdn = cdn->ix;
               cel = cdn->val;
               break;
            }
            case '*': {
               cel = cel->next;
               break;
            }
         }
         ch = fgetc (fd);
      }
      cel->freq ++;
      to = NULL;
      from = cdn->val;
      while (from->next != cel) {
         if ( (from->next->freq <= cel->freq) && (to == NULL) )
            to = from;
         from = from->next;
      }
      if (to != NULL) {
         from->next = cel->next;
         cel->next = to->next;
         to->next = cel;
      }
      printf ("%s", cel->word);
      switch (ch) {
         case ' ': {
            printf (" ");
            ch = fgetc (fd);
            break;
         }
         case '1': {
            i = 0;
            while ( (ch = fgetc (fd) ) == '*')
               i ++;
            printf ("%c", one [i] );
         }
      }
   }
   fclose (fd);
   //НЕ ЗАБУДЬ ПРОПИСАТЬ ВЕЗДЕ free, MOTHERFUCKER!!!
   //cel = root->ii->ii->ii->val;
   //for (i = 0; i < 5; i ++) {
   //   printf ("%s: %i\n", cel->word, cel->freq);
   //   cel = cel->next;
   //}
   return 0;
}
