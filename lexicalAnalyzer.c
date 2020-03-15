#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>
#define MAX_CHARACTER_LENGTH 11
#define MAX 100

//token value, eg: var -> tok[globalCounter].tkn = varsym
typedef enum { 
nulsym = 1, identsym, numbersym, plussym, minussym,
multsym,  slashsym, oddsym, eqlsym, neqsym, lessym, leqsym,
gtrsym, geqsym, lparentsym, rparentsym, commasym, semicolonsym,
periodsym, becomessym, beginsym, endsym, ifsym, thensym, 
whilesym, dosym, callsym, constsym, varsym, procsym, writesym,
readsym , elsesym = 33
} token_type;

typedef struct {
    char identifier[MAX_CHARACTER_LENGTH]; //Store lexeme string
    char symType[MAX_CHARACTER_LENGTH]; //Store Sym String
    char reservedW[MAX_CHARACTER_LENGTH];//Store reserved Words
    token_type tkn; //token value
}token;

token tok[MAX];
int globalCounter = 0;          //0         1       2           3       4       5       6       7       8       9      10   11      12      13
const char * reservedWords[] = { "const", "var", "procedure", "call", "begin", "end", "if", "then", "else", "while", "do", "read", "write", "odd"};
                                //0     1    2    3    4    5   6     7   8     9   10  11  12
const char * specialSymbols[] = { "+", "-", "*", "/", "(", ")", "=", ",",".", "<", ">", ";" ":"};

void checkProgram(FILE *ifp) {
     if(ifp == NULL) {
        printf("File couldn't open!\n");
        exit(EXIT_FAILURE);
    }
}
void printProgram(FILE *ifp, FILE *ofp) {
    char temp;
    fprintf(ofp, "Source Program:\n");
    temp = fgetc(ifp);
    while(temp != EOF) {
    fprintf(ofp, "%c", temp); 
    temp = fgetc(ifp); 
    }
    fseek(ifp, 0, SEEK_SET);
}
void checkProgramPeriod(FILE *ifp) {
   char temp;
   temp = fgetc(ifp); 
   while(temp != EOF) { 
        if(temp == '.') {
            printf("Code is runnable\n"); 
            break;
        }
        else 
            temp = fgetc(ifp);
   }
   if(temp != '.')
        printf("Does not compile, missing .\n");
    
     fseek(ifp, 0, SEEK_SET);
}
 char printSymbols(char temp, FILE *ifp) {
      if(temp == '+') {
        char *tmp = calloc(2, sizeof(char)); 
        tmp[0] = '+';
        strcpy(tok[globalCounter].identifier, tmp);
       // printf("%s\n", tok[globalCounter].identifier); 
        globalCounter++; 
        free(tmp);
       }
      else if(temp == '-') {
        char *tmp = calloc(2, sizeof(char)); 
        tmp[0] = '-';
        strcpy(tok[globalCounter].identifier, tmp);
        globalCounter++; 
        free(tmp);
       }
       else if(temp == '*') {
        char *tmp = calloc(2, sizeof(char)); 
        tmp[0] = '*';
        strcpy(tok[globalCounter].identifier, tmp);
        globalCounter++; 
        free(tmp);
      }
      else if(temp == '/') {
        char *tmp = calloc(2, sizeof(char)); 
        tmp[0] = '/';
        strcpy(tok[globalCounter].identifier, tmp);
        globalCounter++; 
        free(tmp); 
      }
       else if(temp == '(') {
        char *tmp = calloc(2, sizeof(char)); 
        tmp[0] = '(';
        strcpy(tok[globalCounter].identifier, tmp);
        globalCounter++; 
        free(tmp);
      }
      else if(temp == ')') {
        char *tmp = calloc(2, sizeof(char)); 
        tmp[0] = ')';
        strcpy(tok[globalCounter].identifier, tmp);
        globalCounter++; 
        free(tmp);
      }
       else if(temp == '=') {
        char *tmp = calloc(2, sizeof(char)); 
        tmp[0] = '=';
        strcpy(tok[globalCounter].identifier, tmp);
        globalCounter++; 
        free(tmp);
      }
      else if(temp == ',') {
        char *tmp = calloc(2, sizeof(char)); 
        tmp[0] = ',';
        strcpy(tok[globalCounter].identifier, tmp);
        //printf("%s\n", tok[globalCounter].identifier); 
        globalCounter++; 
        free(tmp);
      }
      else if(temp == '<') {
        char *tmp = calloc(2, sizeof(char)); 
        tmp[0] = '<';
        strcpy(tok[globalCounter].identifier, tmp);
        globalCounter++; 
        free(tmp);
      }
      else if(temp == '>') {
        char *tmp = calloc(2, sizeof(char)); 
        tmp[0] = '>';
        strcpy(tok[globalCounter].identifier, tmp);
        globalCounter++; 
        free(tmp);
      }
      else if(temp == ';') {
        char *tmp = calloc(2, sizeof(char)); 
        tmp[0] = ';';
        strcpy(tok[globalCounter].identifier, tmp);
        globalCounter++; 
        free(tmp);
      }
      else if(temp == '.') {
        char *tmp = calloc(2, sizeof(char)); 
        tmp[0] = '.';
        strcpy(tok[globalCounter].identifier, tmp);
        globalCounter++; 
        free(tmp);
      }
      else {
        //printf("Error!\n");
      }
      temp = fgetc(ifp); 
      return temp; 
 }
void convertAlphaReserved() {
    int i = 0, j = 0;
    int condition = 0;

    for(i = 0; i < globalCounter; i++) {
        for(j = 0; j < 14; j++) {
          condition = strcmp(tok[i].identifier, reservedWords[j]); 
        
      if(condition == 0) {
          int constemp = strcmp(tok[i].identifier,"const");
          int vartemp = strcmp(tok[i].identifier,"var");
          int proceduretemp = strcmp(tok[i].identifier,"procedure");
          int calltemp = strcmp(tok[i].identifier,"call");
          int begintemp = strcmp(tok[i].identifier,"begin");
          int endtemp = strcmp(tok[i].identifier,"end");
          int iftemp = strcmp(tok[i].identifier,"if");
          int thentemp = strcmp(tok[i].identifier,"then");
          int elsetemp = strcmp(tok[i].identifier,"else");
          int whiletemp = strcmp(tok[i].identifier,"while");
          int dotemp = strcmp(tok[i].identifier,"do");
          int readtemp = strcmp(tok[i].identifier,"read");
          int writetemp = strcmp(tok[i].identifier,"write");
          int oddtemp = strcmp(tok[i].identifier,"odd");

        if(constemp == 0) {
            strcpy(tok[i].reservedW, "constsym"); 
            strcpy(tok[i].symType, reservedWords[j]);
            tok[i].tkn = constsym;
          }
        if(vartemp == 0) {
            strcpy(tok[i].reservedW, "varsym"); 
            strcpy(tok[i].symType, reservedWords[j]);
            tok[i].tkn = varsym;
            int strcondition = 1;
            
            while(strcondition != 0) {
                i++;
                int tempSize = strlen(tok[i].identifier);
                char *tempString = malloc(sizeof(char)*tempSize); 
                strcpy(tempString, tok[i].identifier);
                char tmptoken = tempString[0];

                if(isalpha(tmptoken)) {
                   strcpy(tok[i].reservedW, "identsym");
                   tok[i].tkn = identsym;
                }
                strcondition = strcmp(tok[i].identifier, ";");
            }
          }
        if(proceduretemp == 0) {
            strcpy(tok[i].reservedW, "procsym");
            strcpy(tok[i].symType, reservedWords[j]);
            tok[i].tkn = procsym;
          }
        if(calltemp == 0) {
            strcpy(tok[i].reservedW, "callsym"); 
            strcpy(tok[i].symType, reservedWords[j]);
            tok[i].tkn = callsym;
          }
        if(begintemp == 0) {
            strcpy(tok[i].reservedW, "beginsym");
            strcpy(tok[i].symType, reservedWords[j]);
            tok[i].tkn = beginsym; 
          }
        if(endtemp == 0) {
            strcpy(tok[i].reservedW, "endsym"); 
            strcpy(tok[i].symType, reservedWords[j]);
            tok[i].tkn = endsym;
          }
        if(iftemp == 0) {
            strcpy(tok[i].reservedW, "ifsym");
            strcpy(tok[i].symType, reservedWords[j]);
            tok[i].tkn = ifsym; 
          }
        if(thentemp == 0) {
            strcpy(tok[i].reservedW, "thensym"); 
            strcpy(tok[i].symType, reservedWords[j]);
            tok[i].tkn = thensym;
          }
        if(elsetemp == 0) {
            strcpy(tok[i].reservedW, "elsesym");
            strcpy(tok[i].symType, reservedWords[j]);
            tok[i].tkn = elsesym;
          }
        if(whiletemp == 0) {
            strcpy(tok[i].reservedW, "whilesym"); 
            strcpy(tok[i].symType, reservedWords[j]);
            tok[i].tkn = whilesym;
          }
        if(dotemp == 0) {
            strcpy(tok[i].reservedW, "dosym");
            strcpy(tok[i].symType, reservedWords[j]);
            tok[i].tkn = dosym;
          }
        if(readtemp == 0) {
            strcpy(tok[i].reservedW, "readsym"); 
            strcpy(tok[i].symType, reservedWords[j]);
            tok[i].tkn = readsym;
          }
        if(writetemp == 0) {
            strcpy(tok[i].reservedW, "writesym");
            strcpy(tok[i].symType, reservedWords[j]);
            tok[i].tkn = writesym;
          }
        if(oddtemp == 0) {
            strcpy(tok[i].reservedW, "oddsym"); 
            strcpy(tok[i].symType, reservedWords[j]);
            tok[i].tkn = oddsym;
          }
        }
      }
    }
    for(int i = 0; i < globalCounter; i++) {
     for(int k = 0; k < globalCounter; k++) {
        int same = strcmp(tok[i].identifier, tok[k].identifier); 
        if(same == 0) {
          strcpy(tok[k].reservedW, tok[i].reservedW);
          tok[k].tkn = tok[i].tkn;
        }
      }
    }
 }
 void convertDigitReserved() {
    int i; 
    for(i = 0; i < globalCounter; i++) {
              int tempSize = strlen(tok[i].identifier);
              char *tempDigit = malloc(sizeof(char)*tempSize); 
              strcpy(tempDigit, tok[i].identifier);
              char tmptoken = tempDigit[0];
        if(isdigit(tmptoken)) {
            strcpy(tok[i].reservedW, "numbersym");
            tok[i].tkn = numbersym;
        }
    }
 }
 void convertSymbolReserved() {
     int i = 0, j = 0;
      int condition = 0;

    for(i = 0; i < globalCounter; i++) {
         int templen = strlen(tok[i].identifier);
         char * tempchar = calloc(templen, sizeof(char)); 
         strcpy(tempchar, tok[i].identifier);

          if(tempchar[0] == '+') {
            strcpy(tok[i].reservedW, "plussym"); 
            tok[i].tkn = plussym;
          }
         else if(tempchar[0] == '-') {
            strcpy(tok[i].reservedW, "minussym"); 
            tok[i].tkn = minussym;
          }
        else if(tempchar[0] == '*') {
            strcpy(tok[i].reservedW, "multsym"); 
            tok[i].tkn = multsym;
          }
         else if(tempchar[0] == '/') {
            strcpy(tok[i].reservedW, "slashsym"); 
            tok[i].tkn = slashsym;
          } 
         else if(tempchar[0] == '(') {
            strcpy(tok[i].reservedW, "lparentsym"); 
            tok[i].tkn = lparentsym;
          }
         else if(tempchar[0] == ')') {
            strcpy(tok[i].reservedW, "rparentsym"); 
            tok[i].tkn = rparentsym;
          }   
        else if(tempchar[0] == '=') {
            strcpy(tok[i].reservedW, "eqlsym"); 
            tok[i].tkn = eqlsym;
          }
        else if(tempchar[0] == ',') {
            strcpy(tok[i].reservedW, "commasym"); 
            tok[i].tkn = commasym;
          }
        else if(tempchar[0] == '.') {
            strcpy(tok[i].reservedW, "periodsym"); 
            tok[i].tkn = periodsym;
          }
         else if(tempchar[0] == '<') {
            strcpy(tok[i].reservedW, "lessym"); 
            tok[i].tkn = lessym;
          }
         else if(tempchar[0] == '>') {
            strcpy(tok[i].reservedW, "gtrsym"); 
            tok[i].tkn = gtrsym;
          }
        else if(tempchar[0] == ';') {
            strcpy(tok[i].reservedW, "semicolonsym"); 
            tok[i].tkn = semicolonsym;
          }   
         else if(tempchar[0] == ':') {
             if(tempchar[1] == '=') {
            strcpy(tok[i].reservedW, "becomesym"); 
            tok[i].tkn = becomessym;
             }
          }
          else{

          }  
       }
     }
int main() {
    FILE *ifp, *ofp; 
    char temp; 
    ifp = fopen("input.txt", "r");
    ofp = fopen("output.txt", "w"); 

   //Part I  
   checkProgram(ifp);
   printProgram(ifp, ofp); 

   //Part II 
   checkProgramPeriod(ifp); 
   fprintf(ofp, "\nLexeme Table:\nlexeme\ttoken type\n"); 

   int counter = 0; 
   char wordTemp[MAX_CHARACTER_LENGTH] = {0};

   temp = fgetc(ifp); 
   while(temp != EOF) {
       //----------------------------------------------------------
       //Word
       if(isalpha(temp)) {
           wordTemp[counter] = temp; 
           counter++; 
           temp = fgetc(ifp);
           //No longer a Word
           if(!isalpha(temp)) {
             strcpy(tok[globalCounter].identifier, wordTemp);
            // printf("%s\n", tok[globalCounter].identifier); 
             globalCounter++; 
             for(int i = 0; i < counter; i++)
                wordTemp[i] = 0;
              counter = 0;
           }
       }
      //----------------------------------------------------------
       //Anything else than a letter
       else if(!isalpha(temp)) {
           //----------------------------------------------------------
           //Number
           if(isdigit(temp)) {
                wordTemp[counter] = temp; 
                counter++; 
                temp = fgetc(ifp);
               if(!isdigit(temp)) {
                strcpy(tok[globalCounter].identifier, wordTemp); 
                 globalCounter++; 
                for(int i = 0; i < counter; i++)
                      wordTemp[i] = 0;
                counter = 0;
               }
           }
           //----------------------------------------------------------
           //Symbol, Space, or Comment 
           else if(!isdigit(temp)) {
             //----------------------------------------------------------
               //Space
                if((temp == ' ') || (temp == '\t') || (temp == '\n')) {
                    temp = fgetc(ifp); 
                    continue; 
                 }
             //----------------------------------------------------------
             //Symbols
               else if(temp == ':') {
                   temp = fgetc(ifp);
                   if(temp == '='){
                       char *tmp = calloc(2, sizeof(char)); 
                       tmp[0] = ':';
                       tmp[1] = '=';
                       strcpy(tok[globalCounter].identifier, tmp); 
                       globalCounter++; 
                      free(tmp);
                      temp = fgetc(ifp); 
                   }
                   else {
                       temp = fgetc(ifp);
                       continue;
                    }
                }
           //----------------------------------------------------------
           //Comment
             else if(temp == '/'){
                temp = fgetc(ifp); 
                if(temp == '*') {
                   temp = fgetc(ifp);
                    while(temp != '*') {  
                        temp = fgetc(ifp);
                    }
                    if(temp == '*') {
                         temp = fgetc(ifp); 
                        if(temp == '/'){
                          temp = fgetc(ifp);
                          continue; 
                        }
                    }
               } 
                 else 
                   continue; 
              }
             temp = printSymbols(temp, ifp); 
           //----------------------------------------------------------
           } //End of Symbol, Space, or Comment
       } //End of Not a Letter
   } //End of character while loop 

    convertAlphaReserved();
    convertDigitReserved(); 
    convertSymbolReserved(); 

   for(int i = 0; i < globalCounter; i++) {
     int tempsize = strlen(tok[i].identifier); 
     if(tempsize >= 5) {
     fprintf(ofp, "%s\t\t%d\n", tok[i].identifier, tok[i].tkn);
     }
     else 
     fprintf(ofp, "%s\t\t\t%d\n", tok[i].identifier, tok[i].tkn);

     printf("Lexeme: %s\n", tok[i].identifier);
     printf("Token Type: %d\n", tok[i].tkn);
     printf("Reserved Word Sym: %s\n\n", tok[i].reservedW);
   }

    return 0;
} //End of Main