#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CMDLINE_LENGTH 100001

typedef struct {

   char btn[21];     //digits, accorded to each symbol in a word

   unsigned int freq;         //frequency of usage - inverted
   unsigned int newFreqFlag;  //flag, that shows the "freshness" of the word among the words with the same freq - inverted
   unsigned int index;
   char word[21];             //the word






} dictStruct;


/*

   while some flags are inverted, if an ascending sort is performed, the first suggestion is the first entry, each next suggestion is i+1 line, where i is the last suggestion

   memcmp() function can be used if we do not want to sort the whole database each time - it is possible just to find the global minimum of [freq; newFreqFlag; index] combination using memcmp( pointer to freq, size of the combination ), and this entry will be the first suggestion
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
unsigned int maxNewFreqFlag = 0xFFFF;     

char btns[21];



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
      dict[i].index = i;
      dict[i].freq = 0xFFFF - tmpFreq;               //invert the frequency                                          
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
      dict[i].btn[j] = 0;
   }

   return 0;

}






int getCmdLine() {      //allocate some space for command line, then reallocate to economize memory, also allocate space for result line
   if ( (cmdLine = (char *) malloc(MAX_CMDLINE_LENGTH * sizeof(char))) == NULL ) return 1;

   gets(cmdLine);
      
   if ( (cmdLine = (char *) realloc(cmdLine, strlen(cmdLine) + 1)) == NULL ) return 1;


   if ( (resultLine = (char *) malloc(strlen(cmdLine))) == NULL ) return 1;
   

   return 0;
}



unsigned int cursorPos = 0;


void getNextSuggestion() {
   unsigned int i = 0;
   unsigned char flOut = 0; 
   if(!flPunctuation) {

      if(suggestedEntry == NULL) {  //if first suggestion  
         for (i = 0; i<entryCount; i++)
            if (!strcmp(btns, dict[i].btn)) {
               suggestedEntry = &dict[i];
               break;
            }
            
         for (; i<entryCount; i++)
            if (!strcmp(btns, dict[i].btn)) {
               if (memcmp( (char *) &dict[i].freq , (char *) &suggestedEntry->freq , sizeof(unsigned int) * 3 ) < 0 )   //global minimum
                  suggestedEntry = &dict[i];
               flOut = 1;
            } else if (flOut) break;
         flOut = 0;
      
    
   
   
      } else { //if not a first suggestion

         for (i = 0; i<entryCount; i++)
            if (!strcmp(btns, dict[i].btn)) 
               if (memcmp( (char *) &dict[i].freq , (char *) &lastSuggestedEntry->freq , sizeof(unsigned int) * 3 ) > 0 ) {  //find the first entry which combination is bigger than previous 
                  suggestedEntry = &dict[i];
                  break;
               }
            
            
         for (; i<entryCount; i++)
            if (!strcmp(btns, dict[i].btn)) {
               if (memcmp( (char *) &dict[i].freq , (char *) &suggestedEntry->freq , sizeof(unsigned int) * 3 ) < 0 ) 
                  if (memcmp( (char *) &dict[i].freq , (char *) &lastSuggestedEntry->freq , sizeof(unsigned int) * 3 ) > 0 ) //then find the minimum of the rest of entries
                     suggestedEntry = &dict[i];
                     flOut = 1;
            } else if (flOut) break;
         flOut = 0;
                  


      }


      lastSuggestedEntry = suggestedEntry;

   } else {       //switch punctuation
      if (punctuationMark == '.') punctuationMark = ',';
      else if (punctuationMark == ',') punctuationMark = '?';
      else if (punctuationMark == '?') punctuationMark = '.';
   }

}




void acceptSuggestedEntry() {


   
   
   if (!flPunctuation && btns[0] != 0) {
      if (suggestedEntry == NULL) getNextSuggestion();

      suggestedEntry->freq--;                   //increase the frequency
      strcat(resultLine, suggestedEntry->word);

      suggestedEntry->newFreqFlag = maxNewFreqFlag - 1;      //set the freshness flag to the smallest freshness flag among other entries - 1, so this entry will be suggested firstly among the entries with the same freq


      maxNewFreqFlag--;      


      suggestedEntry = NULL;
      cursorPos = 0;
      btns[0] = 0;
      
   } else if (flPunctuation && punctuationMark) {
      unsigned int tmplen = strlen(resultLine);
      resultLine[tmplen] = punctuationMark;
      resultLine[tmplen + 1] = 0;
      flPunctuation = 0;
   }

}





int processSymbol(char c) {
   //printf("%c", c);
   
   if (c >= '2' && c <= '9') {   //process as a digit
      if(flPunctuation) {
         acceptSuggestedEntry();
         //flPunctuation = 0;
      }
      

      btns[cursorPos] = c - '0';
      btns[cursorPos + 1] = 0;
      
      cursorPos++;
      
      

   } else if (c == '1') { //accepted, inc freq, flag punctuation
      acceptSuggestedEntry();
      flPunctuation = 1;
      punctuationMark = '.';
      
      

   } else if (c == ' ') { //accepted, inc freq

      acceptSuggestedEntry();
      strcat(resultLine, " ");
      

   } else if (c == '*') { //not accepted, search next
      if(suggestedEntry == NULL && !flPunctuation) getNextSuggestion();
      getNextSuggestion();

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


   while (!processSymbol(cmdLine[i++])) { /* printf("\n"); for(j = 0; j<entryCount; j++) printf("%d", dict[j].suggestionFlag); printf("\t"); */ }
 
   printf("%s", resultLine);
   
   
   return 0;
}
