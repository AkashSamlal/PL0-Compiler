//Akash Samlal
//COP 3402 - HW 2
//Standard Libraries for C
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "header.h"
#define MAX_CHARACTER_LENGTH 11 //Maximum character length for identifiers
#define MAX_SIZE 5000 //Maximum Table Size for Lexeme Table
#define MAX_DIGIT_SIZE 5

typedef enum {
    nulsym = 1, identsym, numbersym, plussym, minussym,
    multsym,  slashsym, oddsym, eqlsym, neqsym, lessym, leqsym,
    gtrsym, geqsym, lparentsym, rparentsym, commasym, semicolonsym,
    periodsym, becomessym, beginsym, endsym, ifsym, thensym,
    whilesym, dosym, callsym, constsym, varsym, procsym, writesym,
    readsym , elsesym
} token_type;

//Token data structure
typedef struct {
 char identifier[MAX_CHARACTER_LENGTH]; //String name
 char symbolicRep[MAX_CHARACTER_LENGTH]; //Symbolic Rep
 int num; //Numerical value of token
 token_type type; //Determines token string or numerical
}token;

token table_lex[MAX_SIZE];
int counterLexical = 0;

//For Reserved Words
const char* reservedWords[]={"const", "var", "procedure", "call", "begin", "end", "if", "then", "else", "while", "do", "read", "write", "odd"};

//For Reserved Special Symbols
const char specialSymbols[]={'+', '-', '*', '/', '(', ')', '=', ',' , '.', '<', '>',  ';' , ':'};

void lexical(int lexFlag, char inputName[]){
    FILE* ifp;
    FILE* ofp;

    ifp = fopen(inputName, "r");
    ofp = fopen("lexemeList.txt", "w");

    int i = 0, j = 0, k = 0, tok, flag, comFlag = 0, forward = 0;
//---------------------------------------------------------------------
    //Initalize List
    for(i = 0; i < 5000; i++){
        table_lex[i].type = 0;
    }
//--------------------------------------------------------------------------
    //Grab first character
    tok = fgetc(ifp);
//---------------------------------------------------------
    //Ignores spaces, tabs, and newlines 
    while(tok != EOF){
        if(tok == ' ' || tok =='\t' || tok =='\n'){
            tok = fgetc(ifp);
            forward = 0;
            continue;
        }
 //---------------------------------------------------------       
        //If a letter
        if(isalpha(tok)) {
            int tmp = 0;
            char string[12];
            memset(string, 0, sizeof string);
            string[tmp]= tok;
            tmp++;
            forward = 1;

            while(isalpha(tok =fgetc(ifp)) || isdigit(tok)){
                if(tmp > 10){
                    printf("Error 26: Identifier too long.\n");
                    while (isalpha(tok=fgetc(ifp))||isdigit(tok)) { }
                    flag =1;
                    break;
                }
                string[tmp]= tok;
                tmp++;
            }
            if(flag==1) {
                flag=0;
                continue;
            }
            int flagReserved = -1;
            for(i = 0; i < 14;i++){
                if(strcmp(string, reservedWords[i]) == 0){
                    flagReserved = i;
                }
            }
         //Find the reserved word location if there is a reserved word in the character string
            switch(flagReserved){
                //Case for const
                case 0:
                    table_lex[counterLexical].type = constsym;
                    strcpy(table_lex[counterLexical].symbolicRep, "constsym"); 
                    break;
                //Case for var
                case 1:
                    table_lex[counterLexical].type = varsym;
                    strcpy(table_lex[counterLexical].symbolicRep, "varsym"); 
                    break;
                //Case for procedure
                case 2:
                    table_lex[counterLexical].type = procsym;
                    strcpy(table_lex[counterLexical].symbolicRep, "procsym"); 
                    break;
                //Case for call
                case 3:
                    table_lex[counterLexical].type = callsym;
                    strcpy(table_lex[counterLexical].symbolicRep, "callsym"); 
                    break;
                //Case for begin
                case 4:
                    table_lex[counterLexical].type = beginsym;
                    strcpy(table_lex[counterLexical].symbolicRep, "beginsym"); 
                    break;
                //Case for end
                case 5:
                    table_lex[counterLexical].type = endsym;
                    strcpy(table_lex[counterLexical].symbolicRep, "endsym"); 
                    break;
                //Case for if
                case 6:
                    table_lex[counterLexical].type = ifsym;
                    strcpy(table_lex[counterLexical].symbolicRep, "ifsym"); 
                    break;
                //Case for then
                case 7:
                    table_lex[counterLexical].type = thensym;
                    strcpy(table_lex[counterLexical].symbolicRep, "thensym"); 
                    break;
                //Case for else
                case 8:
                    table_lex[counterLexical].type = elsesym;
                    strcpy(table_lex[counterLexical].symbolicRep, "elsesym"); 
                    break;
                //Case for while
                case 9:
                    table_lex[counterLexical].type = whilesym;
                    strcpy(table_lex[counterLexical].symbolicRep, "whilesym"); 
                    break;
                //Case for do
                case 10:
                    table_lex[counterLexical].type = dosym;
                    strcpy(table_lex[counterLexical].symbolicRep, "dosym"); 
                    break;
                //Case for read
                case 11:
                    table_lex[counterLexical].type = readsym;
                    strcpy(table_lex[counterLexical].symbolicRep, "readsym"); 
                    break;
                //Case for write
                case 12:
                    table_lex[counterLexical].type = writesym;
                    strcpy(table_lex[counterLexical].symbolicRep, "writesym"); 
                    break;
                //Case for odd
                case 13:
                    table_lex[counterLexical].type = oddsym;
                    strcpy(table_lex[counterLexical].symbolicRep, "oddsym"); 
                    break;

                default:
                    table_lex[counterLexical].type = identsym;
                    strcpy(table_lex[counterLexical].identifier,string);
                        strcpy(table_lex[counterLexical].symbolicRep, "identsym"); 
                    break;
            }
            counterLexical++;
        }
 //---------------------------------------------------------------------------------       
        //If a number
        else if(isdigit(tok)){
            int nm = tok - '0', fae, digSize = 1;

            forward = 1;
            //Num max
            while(isdigit(tok = fgetc(ifp))){
                if(digSize > MAX_DIGIT_SIZE){
                    printf("Error 25: This number too large.\n");
                    while (isdigit(tok = fgetc(ifp))) { }
                    flag=1;
                    break;
                }
                fae = tok - '0';
                nm = 10 * nm + fae;
                digSize++;
            }
            if(isalpha(tok)){
                printf("Error 24: Variable does not start with letter.\n");
                while(isalpha(tok = fgetc(ifp))||isdigit(tok)){ }
                continue;
             }
            //Continue w/ error
            if(flag == 1) {
                flag=0;
                continue;
            }
            table_lex[counterLexical].type = numbersym;
            table_lex[counterLexical].num = nm;
            counterLexical++;
        }
//--------------------------------------------------------------------------------------------        
        //Other: Symbols
        else {
            int symbol =-1;
            forward = 0;
            for(i = 0; i < 13; i++){
                if(tok == specialSymbols[i]){
                    symbol = i;
                }
            }
            //Prints out the correct symbols
            switch(symbol){
                //+
                case 0:
                    table_lex[counterLexical].type = plussym;
                    strcpy(table_lex[counterLexical].symbolicRep, "plussym");    
                    counterLexical++;
                    break;
                //-
                case 1:
                    table_lex[counterLexical].type = minussym;
                    strcpy(table_lex[counterLexical].symbolicRep, "minussym"); 
                    counterLexical++;
                    break;
                //*
                case 2:
                    table_lex[counterLexical].type = multsym;
                    strcpy(table_lex[counterLexical].symbolicRep, "multsym"); 
                    counterLexical++;
                    break;

                //Comments
                case 3:
                    tok = fgetc(ifp);
                    forward=1;
                    if(tok =='*'){
                        comFlag=1;
                        forward=0;
                        tok =fgetc(ifp);
                        while(comFlag==1){
                            if(tok =='*'){
                                tok =fgetc(ifp);
                                if(tok =='/'){
                                    comFlag=0;
                                }
                            }
                            else{
                                tok =fgetc(ifp);
                            }
                        }
                    }
                    // /
                    else{
                        table_lex[counterLexical].type = slashsym;
                        strcpy(table_lex[counterLexical].symbolicRep, "slashsym"); 
                        counterLexical++;
                    }
                    break;
                //(
                case 4:
                    table_lex[counterLexical].type = lparentsym;
                    strcpy(table_lex[counterLexical].symbolicRep, "lparentsym"); 
                    counterLexical++;
                    break;
                //)
                case 5:
                    table_lex[counterLexical].type = rparentsym;
                    strcpy(table_lex[counterLexical].symbolicRep, "rparentsym"); 
                    counterLexical++;
                    break;
                //=
                case 6:
                    table_lex[counterLexical].type = eqlsym;
                    strcpy(table_lex[counterLexical].symbolicRep, "eqlsym"); 
                    counterLexical++;
                    break;
                //,
                case 7:
                    table_lex[counterLexical].type = commasym;
                    strcpy(table_lex[counterLexical].symbolicRep, "commasym"); 
                    counterLexical++;
                    break;
                //.
                case 8:
                    table_lex[counterLexical].type = periodsym;
                    strcpy(table_lex[counterLexical].symbolicRep, "periodsym"); 
                    counterLexical++;
                    break;
                //<>
                case 9:
                    tok =fgetc(ifp);
                    forward=1;
                    if(tok =='>'){
                        table_lex[counterLexical].type = neqsym;
                        strcpy(table_lex[counterLexical].symbolicRep, "neqsym"); 
                        forward=0;
                    }
                    //<=
                    else if(tok =='='){
                        table_lex[counterLexical].type = leqsym;
                        strcpy(table_lex[counterLexical].symbolicRep, "leqsym"); 
                        forward=0;
                    }
                    //<
                    else{
                        table_lex[counterLexical].type = lessym;
                        strcpy(table_lex[counterLexical].symbolicRep, "lessym"); 
                    }
                    counterLexical++;
                    break;
                //>=
                case 10:
                    tok = fgetc(ifp);
                    forward=1;
                    if(tok =='='){
                        table_lex[counterLexical].type = geqsym;
                        strcpy(table_lex[counterLexical].symbolicRep, "geqsym"); 
                        forward=0;
                    }
                    //>
                    else{
                        table_lex[counterLexical].type = gtrsym;
                        strcpy(table_lex[counterLexical].symbolicRep, "gtrsym"); 
                    }
                    counterLexical++;
                    break;
                //;
                case 11:
                    table_lex[counterLexical].type = semicolonsym;
                    strcpy(table_lex[counterLexical].symbolicRep, "semicolonsym"); 
                    counterLexical++;
                    break;
                //:=
                case 12:
                    tok =fgetc(ifp);
                    if(tok == '='){
                        table_lex[counterLexical].type = becomessym;
                        strcpy(table_lex[counterLexical].symbolicRep, "becomessym"); 
                        counterLexical++;
                    }
                    //If none of the symbols then print error
                    else{
                        printf("Error 27: Invalid symbols are not accepted.\n");
                    }
                    break;
                    //Prints Error 4 for invalid symbols
                default:
                    printf("Error 27: Invalid symbols are not accepted.\n");
                    break;
            }
        }
//----------------------------------------------------------------------------------------
        //Get Next Character
        if(forward==0){
            tok = fgetc(ifp);
        }
    }

    //Print Lexeme List
    for(i = 0;i < counterLexical; i++){
        fprintf(ofp,"%d ", table_lex[i].type);
        if(table_lex[i].type== 2){
            fprintf(ofp,"%s ", table_lex[i].identifier);
        }
        else if(table_lex[i].type== 3){
            fprintf(ofp,"%d ",table_lex[i].num);
        }
    }
    fclose(ifp);
    fclose(ofp);

    if(lexFlag) {
        char temp; 
        ifp = fopen(inputName, "r"); 
        ofp = fopen("lexemeList.txt", "r");
        fseek(ofp, 0, SEEK_SET);
        printf("Lexeme List:\n");
        temp = fgetc(ofp);
        while(temp != EOF) {
             printf("%c", temp); 
             temp = fgetc(ofp);
        }
        printf("\n\n");

      //Print symbolic representation of lexical List
       for(i = 0;i < counterLexical; i++){
            printf("%s ", table_lex[i].symbolicRep);
         if(table_lex[i].type== 2){
              printf("%s ", table_lex[i].identifier);
          }
         else if(table_lex[i].type== 3){
              printf("%d ",table_lex[i].num);
         }
       }  
        printf("\n\n");

        char too;
        too = fgetc(ifp); 
        
        while(too != EOF) { 
           if(too == '.') {
              printf("No errors, program is syntactically correct\n\n\n"); 
            break;
           }
            else 
              too = fgetc(ifp);
          }
   
        if(too != '.')
           printf("***** Error number #9, period expected \n\n\n"); 

        fseek(ifp, 0, SEEK_SET);
        fclose(ofp);
     }
   }