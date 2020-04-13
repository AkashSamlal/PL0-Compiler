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

typedef enum {
    nulsym = 1, identsym, numbersym, plussym, minussym,
    multsym,  slashsym, oddsym, eqsym, neqsym, lessym, leqsym,
    gtrsym, geqsym, lparentsym, rparentsym, commasym, semicolonsym,
    periodsym, becomessym, beginsym, endsym, ifsym, thensym,
    whilesym, dosym, callsym, constsym, varsym, procsym, writesym,
    readsym , elsesym
} token_type;

//Token data structure
typedef struct {
 char identifier[MAX_CHARACTER_LENGTH]; //String name
 int num; //Numerical value of token
 token_type type; //Determines token string or numerical
}token;

token table_lex[MAX_SIZE];
int lexListIndex = 0;

//For Reserved Words
const char* reservedWords[]={"const", "var", "procedure", "call", "begin", "end", "if", "then", "else", "while", "do", "read", "write", "odd"};

//For Reserved Special Symbols
const char specialSymbols[]={'+', '-', '*', '/', '(', ')', '=', ',' , '.', '<', '>',  ';' , ':'};

void lexical(int lexFlag){
    FILE* ifp;
    FILE* ofp;

    ifp = fopen("input.txt", "r");
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
                    printf("Error 3: Name too long.\n");
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
                    table_lex[lexListIndex].type = constsym;
                    break;
                //Case for var
                case 1:
                    table_lex[lexListIndex].type = varsym;
                    break;
                //Case for procedure
                case 2:
                    table_lex[lexListIndex].type = procsym;
                    break;
                //Case for call
                case 3:
                    table_lex[lexListIndex].type = callsym;
                    break;
                //Case for begin
                case 4:
                    table_lex[lexListIndex].type = beginsym;
                    break;
                //Case for end
                case 5:
                    table_lex[lexListIndex].type = endsym;
                    break;
                //Case for if
                case 6:
                    table_lex[lexListIndex].type = ifsym;
                    break;
                //Case for then
                case 7:
                    table_lex[lexListIndex].type = thensym;
                    break;
                //Case for else
                case 8:
                    table_lex[lexListIndex].type = elsesym;
                    break;
                //Case for while
                case 9:
                    table_lex[lexListIndex].type = whilesym;
                    break;
                //Case for do
                case 10:
                    table_lex[lexListIndex].type = dosym;
                    break;
                //Case for read
                case 11:
                    table_lex[lexListIndex].type = readsym;
                    break;
                //Case for write
                case 12:
                    table_lex[lexListIndex].type = writesym;
                    break;
                //Case for odd
                case 13:
                    table_lex[lexListIndex].type = oddsym;
                    break;

                default:
                    table_lex[lexListIndex].type = identsym;
                    strcpy(table_lex[lexListIndex].identifier,string);
                    break;
            }
            lexListIndex++;
        }
 //---------------------------------------------------------------------------------       
        //If a number
        else if(isdigit(tok)){
            int nm = tok - '0', fae, digSize = 1;

            forward = 1;
            //Num max
            while(isdigit(tok = fgetc(ifp))){
                if(digSize > 4){
                    printf("Error 2: Number too long.\n");
                    while (isdigit(tok = fgetc(ifp))) { }
                    flag=1;
                    break;
                }
                fae = tok - '0';
                nm = 10 * nm + fae;
                digSize++;
            }
            if(isalpha(tok)){
                printf("Error 1: Variable does not start with letter.\n");
                while(isalpha(tok = fgetc(ifp))||isdigit(tok)){ }
                continue;
             }
            //Continue w/ error
            if(flag == 1) {
                flag=0;
                continue;
            }
            table_lex[lexListIndex].type = numbersym;
            table_lex[lexListIndex].num = nm;
            lexListIndex++;
        }
//--------------------------------------------------------------------------------------------        
        //Other: Symbols
        else {
            forward=0;
            int spec=-1;
            for(i = 0; i < 13; i++){
                if(tok == specialSymbols[i]){
                    spec = i;
                }
            }
            //If it is a special symbol, print out the correct tokentype
            switch(spec){
                //Case for +
                case 0:
                    table_lex[lexListIndex].type = plussym;
                    lexListIndex++;
                    break;
                //Case for -
                case 1:
                    table_lex[lexListIndex].type = minussym;
                    lexListIndex++;
                    break;
                //Case for *
                case 2:
                    table_lex[lexListIndex].type = multsym;
                    lexListIndex++;
                    break;

                //Case for comments
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
                    else{
                        table_lex[lexListIndex].type = slashsym;
                        lexListIndex++;
                    }
                    break;
                //Case for (
                case 4:
                    table_lex[lexListIndex].type = lparentsym;
                    lexListIndex++;
                    break;
                //Case for )
                case 5:
                    table_lex[lexListIndex].type = rparentsym;
                    lexListIndex++;
                    break;
                //Case for =
                case 6:
                    table_lex[lexListIndex].type = eqsym;
                    lexListIndex++;
                    break;
                //Case for ,
                case 7:
                    table_lex[lexListIndex].type = commasym;
                    lexListIndex++;
                    break;
                //Case for .
                case 8:
                    table_lex[lexListIndex].type = periodsym;
                    lexListIndex++;
                    break;
                //Case for <>
                case 9:
                    tok =fgetc(ifp);
                    forward=1;
                    if(tok =='>'){
                        table_lex[lexListIndex].type = neqsym;
                        forward=0;
                    }
                    //Case for <=
                    else if(tok =='='){
                        table_lex[lexListIndex].type = leqsym;
                        forward=0;
                    }
                    //Case for <
                    else{
                        table_lex[lexListIndex].type = lessym;
                    }
                    lexListIndex++;
                    break;
                //Case for >=
                case 10:
                    tok = fgetc(ifp);
                    forward=1;
                    if(tok =='='){
                        table_lex[lexListIndex].type = geqsym;
                        forward=0;
                    }
                    //Case for >
                    else{
                        table_lex[lexListIndex].type = gtrsym;
                    }
                    lexListIndex++;
                    break;
                //Case for ;
                case 11:
                    table_lex[lexListIndex].type = semicolonsym;
                    lexListIndex++;
                    break;
                //Case for :=
                case 12:
                    tok =fgetc(ifp);
                    if(tok == '='){
                        table_lex[lexListIndex].type = becomessym;
                        lexListIndex++;
                    }
                    //Prints Error 4 for invalid symbols
                    else{
                        printf("Error 4: Invalid symbols.\n");
                    }
                    break;
                    //Prints Error 4 for invalid symbols
                default:
                    printf("Error 4: Invalid symbols.\n");
                    break;
            }
        }
//----------------------------------------------------------------------------------------
        //Get Next Character
        if(forward==0){
            tok = fgetc(ifp);
        }
    }

    //Print to Lexeme List
    for(i = 0;i < lexListIndex; i++){
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
        ifp = fopen("input.txt", "r"); 
        ofp = fopen("lexemeList.txt", "r");
        fseek(ofp, 0, SEEK_SET);
        printf("Lexeme List:\n");
        temp = fgetc(ofp);
        while(temp != EOF) {
             printf("%c", temp); 
             temp = fgetc(ofp);
        }
        printf("\n\n");

      //Print lexical List
       for(i = 0;i < lexListIndex; i++){
            printf("%d ", table_lex[i].type);
         if(table_lex[i].type== 2){
              printf("%s ", table_lex[i].identifier);
          }
         else if(table_lex[i].type== 3){
              printf("%d ",table_lex[i].num);
         }
        printf("\n\n");

        char temp;
        temp = fgetc(ifp); 
        
        while(temp != EOF) { 
           if(temp == '.') {
              printf("No errors, program is syntactically correct\n\n\n"); 
            break;
           }
            else 
              temp = fgetc(ifp);
          }
   
        if(temp != '.')
           printf("***** Error number #9, period expected \n\n\n"); 

        fseek(ifp, 0, SEEK_SET);
        fclose(ofp);
     }
   }
}