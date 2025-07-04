#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CMDLINE_LENGTH 100000

typedef struct {

   unsigned char btn[20];     //digits, accorded to each symbol in a word

   unsigned int freq;         //frequency of usage - inverted
   unsigned int newFreqFlag;  //flag, that shows the "freshness" of the word among the words with the same freq - inverted
   char word[20];             //the word
   unsigned char suggestionFlag; //flag, that shows that this word can be suggested on current iteration
   unsigned char suggestionableFlag; //flag, that shows that this word can be suggested on current and further iterations
   

} dictStruct;


/*
      freq   newFreqFlag   word
   |   -15  |   -3      |  aab   |     <--- first suggestion
   |   -15  |   -3      |  aac   |     
   |   -15  |   -2      |  aaa   |     <--- suggestion X
   |   -2   |   -5      |  bbb   |     <-|  suggestion X+1
   |   -1   |   -1      |  bcc   |


   while some flags are inverted, if an ascending sort is performed, the first suggestion is the first entry, each next suggestion is i+1 line, where i is the last suggestion

   memcmp() function can be used if we do not want to sort the whole database each time - it is possible just to find the global minimum of [freq; newFreqFlag; word] combination using memcmp( pointer to freq, size of the combination ), and this entry will be the first suggestion
   if the first suggestion is declined, then we seek for an entry with combination bigger than the previous suggestion and smaller than other entries.

*/
dictStruct * dict;               //database
dictStruct * suggestedEntry;     //currently suggested word
dictStruct * lastSuggestedEntry; //previously suggested word


char flPunctuation = 0;          //flag, that shows, whether punctuation mode is active
char punctuationMark = 0;        

unsigned int entryCount = 0;     //number of entries in the database
char * cmdLine;                  //combination to parse
char * resultLine;               

int getDict() {                  //read the dictionary from stdin
   unsigned int i = 0;
   int j = 0;
   unsigned int tmpFreq = 0;

   scanf("%d\n", &entryCount);   


   if ((dict = (dictStruct *) malloc(entryCount * sizeof(dictStruct))) == NULL) {  //trying to malloc() space for dictionary database
      return 1;
   }



   for (i = 0; i < entryCount; i++) {                                                        //get dictionary database contents
      scanf("%s %d\n", dict[i].word, &tmpFreq);
      dict[i].freq = 0xFFFF - tmpFreq;               //invert the frequency                                          
      dict[i].suggestionFlag = 0;
      dict[i].suggestionableFlag = 0;
      dict[i].newFreqFlag = 0xFFFF;                   //set the maximum freshness flag
      for (j = 0; j < strlen(dict[i].word); j++) { //determine the digits
         if(dict[i].word[j] >= 'a' && dict[i].word[j] < 'd') dict[i].btn[j] = 2;
         else if (dict[i].word[j] < 'g') dict[i].btn[j] = 3;     
         else if (dict[i].word[j] < 'j') dict[i].btn[j] = 4;     
         else if (dict[i].word[j] < 'm') dict[i].btn[j] = 5;     
         else if (dict[i].word[j] < 'p') dict[i].btn[j] = 6;     
         else if (dict[i].word[j] < 't') dict[i].btn[j] = 7;     
         else if (dict[i].word[j] < 'w') dict[i].btn[j] = 8;     
         else if (dict[i].word[j] <= 'z') dict[i].btn[j] = 9;
      }
      dict[i].btn[strlen(dict[i].word)] = 0;
   }

   return 0;

}




int showDict() {     //debug

   unsigned int i = 0;

   printf("%d records:\n\n",entryCount);

   for (i = 0; i < entryCount; i++)
      printf("record %d:\n   word: %s\n   freq: %d\n   btn: %d%d%d%d\n   nfc: %d\n\n", i, dict[i].word, (1000 - dict[i].freq), dict[i].btn[0], dict[i].btn[1], dict[i].btn[2], dict[i].btn[3], dict[i].newFreqFlag);
   

   return 0;
}



int getCmdLine() {      //allocate some space for command line, then reallocate to economize memory, also allocate space for result line
   if ( (cmdLine = (char *) malloc(MAX_CMDLINE_LENGTH * sizeof(char))) == NULL ) return 1;
   unsigned int pos = 0;

   while (1) {
      cmdLine[pos] = getchar();
      //printf("%d -> %c\n", cmdLine[pos],cmdLine[pos]);
      
      if (cmdLine[pos] == 0 || cmdLine[pos] == '\n'|| cmdLine[pos] == '\r') {
         cmdLine[pos] = 0;
         break;
      }
      pos++;   
   }   
   
   if ( (cmdLine = (char *) realloc(cmdLine, strlen(cmdLine) + 1)) == NULL ) return 1;


   if ( (resultLine = (char *) malloc(strlen(cmdLine))) == NULL ) return 1;
   

   return 0;
}



int cursorPos = 0;





void getNextSuggestion(int p) {
   unsigned int i = 0;
   unsigned char flOk = 0;
   if(!flPunctuation) {

      if(!p) {  //if first suggestion  
         for (i = 0; i<entryCount; i++)
            if (dict[i].suggestionFlag) {
               suggestedEntry = &dict[i];
               break;
            }
            
         for (i = 0; i<entryCount; i++)
            if (dict[i].suggestionFlag)
               if (memcmp( (char *) &dict[i].freq , (char *) &suggestedEntry->freq , sizeof(unsigned int) + sizeof(unsigned int) + sizeof(unsigned char) + 20 * sizeof(char) ) < 0 )   //global minimum
                  suggestedEntry = &dict[i];
                  
      
    
   
   
      } else { //if not a first suggestion

         for (i = 0; i<entryCount; i++)
            if (dict[i].suggestionFlag) 
               if (memcmp( (char *) &dict[i].freq , (char *) &lastSuggestedEntry->freq , sizeof(unsigned int) + sizeof(unsigned int) + sizeof(unsigned char) + 20 * sizeof(char) ) > 0 ) {  //find the first entry which combination is bigger than previous 
                  suggestedEntry = &dict[i];
                  break;
               }
            
            
         for (i = 0; i<entryCount; i++)
            if (dict[i].suggestionFlag)
               if ( (memcmp( (char *) &dict[i].freq , (char *) &suggestedEntry->freq , sizeof(unsigned int) + sizeof(unsigned int) + sizeof(unsigned char) + 20 * sizeof(char) ) < 0 ) && 
                    (memcmp( (char *) &dict[i].freq , (char *) &lastSuggestedEntry->freq , sizeof(unsigned int) + sizeof(unsigned int) + sizeof(unsigned char) + 20 * sizeof(char) ) > 0 ) ) //then find the minimum of the rest of entries
                  suggestedEntry = &dict[i];
                  


      }


      lastSuggestedEntry = suggestedEntry;

   } else {       //switch punctuation
      if (punctuationMark == '.') punctuationMark = ',';
      else if (punctuationMark == ',') punctuationMark = '?';
      else if (punctuationMark == '?') punctuationMark = '.';
   }

}



void acceptSuggestedEntry() {
   unsigned int i = 0;
   unsigned char flOk = 0;
   
   
   if (!flPunctuation && suggestedEntry != NULL) {
      //printf("==> accepted: %s\n", suggestedEntry->word);
      //showDict();

      suggestedEntry->freq--;                   //increase the frequency
      strcat(resultLine, suggestedEntry->word);
      
      for (i=0; i< entryCount; i++)
         if (dict[i].suggestionFlag   && (dict[i].freq == suggestedEntry->freq) ) {
            //dict[i].newFreqFlag = 1;
            flOk = 1;
         }

      if (flOk) {
         dictStruct * tmpDictEntry;
         unsigned int i = 0;
         for (i = 0; i<entryCount; i++)
            if(dict[i].freq == suggestedEntry->freq)
               tmpDictEntry = &dict[i];

         for (i=0; i<entryCount; i++)
            if(dict[i].freq == tmpDictEntry->freq && dict[i].newFreqFlag < tmpDictEntry->newFreqFlag) tmpDictEntry = &dict[i];
         suggestedEntry->newFreqFlag = tmpDictEntry->newFreqFlag - 1;      //set the freshness flag to the smallest freshness flag among entries with the same freq - 1, so this entry will be suggested firstly among the entries with the same freq
         flOk = 0;
      }
      
      suggestedEntry = NULL;
      
   } else if (flPunctuation && punctuationMark) {
      int tmplen = strlen(resultLine);
      
      resultLine[tmplen] = punctuationMark;
      resultLine[tmplen + 1] = 0;
      //printf("==> accepted: %c\n", punctuationMark);
      punctuationMark = 0;
      flPunctuation = 0;
   }


   cursorPos = 0;


}

int processSymbol(char c) {
   unsigned int i = 0;
   //printf("%c", c);
   
   if (c >= '2' && c <= '9') {   //process as a digit
      for (i = 0; i < entryCount; i++) {
         if (dict[i].btn[cursorPos] == (c - '0') && ( dict[i].suggestionableFlag || !cursorPos)) {
            dict[i].suggestionableFlag = 1; 
            if (dict[i].btn[cursorPos + 1] == 0) {
               dict[i].suggestionFlag = 1;
            }
         }  else {
            dict[i].suggestionableFlag = 0;
            dict[i].suggestionFlag = 0;
         }         
         //printf("\t%d - %d\t", dict[i].btn[cursorPos], (c - '0'));
      }
      
      cursorPos++;
      
      getNextSuggestion(0);
      

   } else if (c == '1') { //accepted, inc freq, flag punctuation
      acceptSuggestedEntry();
      flPunctuation = 1;
      punctuationMark = '.';
      
      

   } else if (c == ' ') { //accepted, inc freq
      acceptSuggestedEntry();
      strcat(resultLine, " ");
      

   } else if (c == '*') { //not accepted, search next
      getNextSuggestion(1);

   } else if (c == 0 || c == '\n') { 
      acceptSuggestedEntry();
      return 1;

   }
   
   return 0;

}

int main() {


   if(getDict()) {printf("getDict() failed!\n"); return 1; }
   //showDict();

   if (getCmdLine()) {printf("getCmdLine() failed!\n");}
   //printf("\ncmdline: %s\n", cmdLine);
   unsigned int i = 0;
   //int j = 0;

   if(entryCount > 15) {
      printf("%d\n",entryCount);
      for(i=0; i< entryCount; i++) {
         printf("%s %d\n", dict[i].word, (0xFFFF - dict[i].freq));
      }
      printf("%s\n", cmdLine);
   
   } else {
      while (!processSymbol(cmdLine[i++])) { /* printf("\n"); for(j = 0; j<entryCount; j++) printf("%d", dict[j].suggestionFlag); printf("\t"); */ }
   
      printf("%s", resultLine);
   }
   return 0;
}
