    //Akash Samlal
//COP 3402 - HW 2
//Standard Libraries for C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include <ctype.h>
#include "header.h"
#define MAX_CHARACTER_LENGTH  11 //Maximum character length for identifiers
#define MAX_NUMBER_LENGTH   5 //Maximum digit length for identifier
#define SPECIAL_SYMBOL_LENGTH 13
#define MAX_SIZE 2000 //Maximum Table Size for Lexeme Table
 
//Declaration of Token Types
typedef enum { 
nulsym = 1, identsym, numbersym, plussym, minussym,
multsym,  slashsym, oddsym, eqsym, neqsym, lessym, leqsym,
gtrsym, geqsym, lparentsym, rparentsym, commasym, semicolonsym,
periodsym, becomessym, beginsym, endsym, ifsym, thensym, 
whilesym, dosym, callsym, constsym, varsym, procsym, writesym,
readsym , elsesym } token_type;

//Token data structure
typedef struct {
    char identifier[MAX_CHARACTER_LENGTH]; //String name 
    int num; //Numerical value of token
    token_type type; //Determines token string or numerical 
}token;
 
//Special Symbols: Key Identifiers for the compiler
 const char specialSymbols[]={'+', '-', '*', '/', '(', ')', '=', ',' , '.', '<', '>',  ';' , ':'};
//Reserved Words: Words reserved for the compiler
 const char* reservedWords[]={"const", "var", "procedure", "call", "begin", "end", "if", "then", "else", "while", "do", "read", "write", "odd"};

//Index counter to maintain position and size of the symbol table
 int pos = 0;
//Symbol Table to maintain reserved words and symbols
 token table_lex[MAX_SIZE];

//Determine if the input file was unable to open - part 1
void checkFile(FILE *ifp) {
    //Check if input file is nonexistent
    if(ifp == NULL) {
     //print to console to user, file is unable to be able to open
        printf("File couldn't open, please check the name of the input text file");
        //Exit the program for failure case if input file is unable to open
        exit(EXIT_FAILURE);
    }
}
//Reprints the Input Program, Source code - part 1
void reprintSourceProgram(FILE* ifp, FILE* ofp) {
    char temp;
    //Prints Header to output file
     fprintf(ofp, "Source Program:\n");
     //Retrieves the first character in the input file
     temp = fgetc(ifp);
     //Continuosly loops through file until termination
     while(temp != EOF) {
        //Prints the current character in output file
        fprintf(ofp, "%c", temp);
        //Retrieves the next character in input file
        temp = fgetc(ifp);
    }
}
//Search for reserved word in string
int searchForReservedWord(char wordString[]) {
     int i, wordPos = -1;
     //Determine if the string is a reserved word
      for(i=0; i < MAX_CHARACTER_LENGTH;i++) 
          if(strcmp(wordString, reservedWords[i])==0)
                wordPos=i; //Save location of the reserved word
     return wordPos;           
}
//If an alphabet, the string is copied into the table
void lexicalAssign(char wordString[]) {
    //Search for reserved word in string
      int wordPos = searchForReservedWord(wordString);
           //Find the reserved word location if there is a reserved word in the character string
           //In order of reservedWord Array List 
            switch(wordPos){
                //Assign 'const' from ReservedWord Array to Symbol Table
                case 0:
                    table_lex[pos].type = constsym;
                    strcpy(table_lex[pos].identifier, wordString);
                    break;
                //Assign 'var' from ReservedWord Array to Symbol Table
                case 1:
                    table_lex[pos].type = varsym;
                    strcpy(table_lex[pos].identifier, wordString);
                    break;
                //Assign 'procedure' from ReservedWord Array to Symbol Table
                case 2:
                    table_lex[pos].type = procsym;
                    strcpy(table_lex[pos].identifier, wordString);
                    break;
                //Assign 'call' from ReservedWord Array to Symbol Table
                case 3:
                    table_lex[pos].type = callsym;
                    strcpy(table_lex[pos].identifier, wordString);
                    break;
                //Assign 'begin' from ReservedWord Array to Symbol Table
                case 4:
                    table_lex[pos].type = beginsym;
                    strcpy(table_lex[pos].identifier,wordString);
                    break;
                //Assign 'end' from ReservedWord Array to Symbol Table
                case 5:
                    table_lex[pos].type = endsym;
                    strcpy(table_lex[pos].identifier, wordString);
                    break;
                //Assign 'if' from ReservedWord Array to Symbol Table
                case 6:
                    table_lex[pos].type = ifsym;
                    strcpy(table_lex[pos].identifier, wordString);
                    break;
                //Assign 'then' from ReservedWord Array to Symbol Table
                case 7:
                    table_lex[pos].type = thensym;
                    strcpy(table_lex[pos].identifier, wordString);
                    break;
                //Assign 'else' from ReservedWord Array to Symbol Table
                case 8:
                    table_lex[pos].type = elsesym;
                    strcpy(table_lex[pos].identifier, wordString);
                    break;
                //Assign 'while' from ReservedWord Array to Symbol Table
                case 9:
                    table_lex[pos].type = whilesym;
                    strcpy(table_lex[pos].identifier, wordString);
                    break;
                //Assign 'do' from ReservedWord Array to Symbol Table
                case 10:
                    table_lex[pos].type = dosym;
                    strcpy(table_lex[pos].identifier, wordString);
                    break;
                //Assign 'read' from ReservedWord Array to Symbol Table
                case 11:
                    table_lex[pos].type = readsym;
                    strcpy(table_lex[pos].identifier,wordString);
                    break;
                //Assign 'write' from ReservedWord Array to Symbol Table
                case 12:
                    table_lex[pos].type = writesym;
                    strcpy(table_lex[pos].identifier,wordString);
                    break;
                //Assign 'odd' from ReservedWord Array to Symbol Table
                case 13:
                    table_lex[pos].type = oddsym;
                    strcpy(table_lex[pos].identifier,wordString);
                    break;
               //If no reserved word was found in string,assign the ident to table, and copy character string to symbol.name
                default:
                    table_lex[pos].type = identsym;
                    strcpy(table_lex[pos].identifier,wordString);
                    break;
            }
            //Increment the the size of lexeme Table
            pos++;
}
 //Determine if the number is too long
int checkNumberTooLong(FILE *ifp, int num, char temp,  int flag) {
     int digit, loc = 1;
     //Go through input file to determine each character is a digit
     temp = fgetc(ifp);
     while(isdigit(temp)){
       //Determine if the number is longer than the maximum requirement
       if(loc > MAX_NUMBER_LENGTH) { 
            flag = 1; //Flag an error
            break;
        }
        digit = temp -'0'; //Convert to int
        num = (10 * num) + digit; //Convert to number
        loc++; //Increment index of character
        temp = fgetc(ifp); //retrieve next character
    }
        return num; //return num
}
//Print out the Special Symbol in the array
int printSpecialSymbol(FILE *ifp, FILE *ofp, int loc, char temp, char wordString[]) {
    int i, commentFlag=0;
    loc=0;
            int sym = -1;
            //Determine if the character is a special symbol
            for(i = 0; i < SPECIAL_SYMBOL_LENGTH; i++){
                if(temp == specialSymbols[i])
                    sym = i; //Reserved the location of the special symbol that was found
            }

           //Assign the SymbolTable number to the symbol location
            switch(sym){
                //Assign the table of the Addition symbol '+'
                case 0:
                    table_lex[pos].type = plussym;
                    strcpy(table_lex[pos].identifier, wordString); 
                    break;
               //Assign the table of the Subraction symbol '-'
                case 1:
                    table_lex[pos].type = minussym;
                    strcpy(table_lex[pos].identifier, wordString); 
                    break;
               //Assign the table of the Multiplication symbol '*'
                case 2:
                    table_lex[pos].type = multsym;
                    strcpy(table_lex[pos].identifier, wordString); 
                    break;
               //Determine if the '/' leads to a comment
                case 3:
                    //Check if the next character is truly a comment, '*'
                    temp =fgetc(ifp);
                    loc=1;
                    //If a comment, ignore the remaining words since a comment
                    if(temp =='*'){
                        commentFlag = 1 , loc=0;
                        temp = fgetc(ifp); //Retireve next character to reinsure it's a comment
                        //Go through, ignore lines until comments are gone
                        while(commentFlag == 1){
                          //Loop thorugh until machine reads the third part of the comment
                            if(temp =='*'){
                                temp =fgetc(ifp);
                                //Once last component of the comment is met, turn off comment flag
                                if(temp =='/')
                                    commentFlag=0;
                            }
                            else{
                             //Keep retrieving each character until comment flag is 0
                                temp =fgetc(ifp);
                            }
                        }
                    }
                    else{
                        //Simply a '/', assign to table
                        table_lex[pos].type = slashsym;
                        strcpy(table_lex[pos].identifier, wordString); 
                    }
                    break;
               //Assign the table of the Left Parenthesis symbol '('
                case 4:
                    table_lex[pos].type = lparentsym;
                    strcpy(table_lex[pos].identifier, wordString); 
                    break;
               //Assign the table of the Right Parenthesis symbol ')'
                case 5:
                    table_lex[pos].type = rparentsym;
                    strcpy(table_lex[pos].identifier, wordString); 
                    break;
               //Assign the table of the Equal symbol '='
                case 6:
                    table_lex[pos].type = eqsym;
                    strcpy(table_lex[pos].identifier, wordString); 
                    break;
               //Assign the table of the Comma symbol ','
                case 7:
                    table_lex[pos].type = commasym;
                    strcpy(table_lex[pos].identifier, wordString); 
                    break;
               //Assign the table of the Period symbol '.'
                case 8:
                    table_lex[pos].type = periodsym;
                    strcpy(table_lex[pos].identifier, wordString); 
                    break;
               //Assign the table of either the Less than, Greater than, or Equal to symbol 
                case 9:
                    temp =fgetc(ifp);
                    loc=1;
                    if(temp =='>'){
                        table_lex[pos].type = neqsym;
                        strcpy(table_lex[pos].identifier, wordString); 
                        loc=0;
                    }

                    else if(temp =='='){
                        table_lex[pos].type = leqsym;
                        strcpy(table_lex[pos].identifier, wordString); 
                        loc=0;
                    }

                    else{
                        table_lex[pos].type = lessym;
                        strcpy(table_lex[pos].identifier, wordString); 
                    }
                    break;
               //Assign the table of the Greater than symbol '>'or Equal to
                case 10:
                    temp =fgetc(ifp);
                    loc=1;
                    if(temp =='='){
                        table_lex[pos].type = geqsym;
                        strcpy(table_lex[pos].identifier, wordString); 
                        loc=0;
                    }

                    else{
                        table_lex[pos].type = gtrsym;
                        strcpy(table_lex[pos].identifier, wordString); 
                    }
                    break;
               //Assign the table of the SemiColon symbol ';'
                case 11:
                    table_lex[pos].type = semicolonsym;
                    strcpy(table_lex[pos].identifier, wordString); 
                    break;
               //Assign the table of the becomessym symbol ':='
                case 12:
                    temp = fgetc(ifp);
                    if(temp == '='){
                        table_lex[pos].type = becomessym;
                        wordString = ":="; 
                        strcpy(table_lex[pos].identifier, wordString); 
                    }
                    break;
                default:
                    fprintf(ofp,"Symbols are Invalid\n");
                    break;
            }
          //Increment the the size of lexeme Table
           pos++;
        return loc;
}
//Goes through each character in the file and perform the Lexical Analyzer Function - part 2
void lexicalAnalyzer(FILE *ifp, FILE *ofp) {
   int i, flag, letter, tn =0;
   fseek(ifp, 0, SEEK_SET); //reset file pointer to begining of input file
   letter = fgetc(ifp);
    //Reads each character until end of file
    while(letter != EOF){
        //-----------------------------------------------------------------------
        //Invisible Characters - don't tokenize 
        if(letter ==' '|| letter =='\t'|| letter =='\n') {
            letter = fgetc(ifp);
            tn =0;
            continue;
        }
       //-----------------------------------------------------------------------
        //If character is a letter
        if(isalpha(letter)){
            int index = 0;
            char wordString[MAX_CHARACTER_LENGTH] = {0}; //temp
           //Initalize the first index for name array
            wordString[index] = letter;
            index ++;
            tn = 1;
            //Determine if the character has a digit in the string
           while(isalpha(letter =fgetc(ifp))||isdigit(letter)){
            //If the character exceeds the limit 
             if(index > MAX_CHARACTER_LENGTH) { 
                flag =1; //flag as error
                break;
            }
                //loop through until string is filled up with word
                wordString[index]= letter;
                index++;
            }
            if(flag == 1) {
                flag = 0;
                continue;
            }
           //assign reserved words into lexical table
           lexicalAssign(wordString);
        }
        //---------------------------------------------------
         //If character is a number
        else if(isdigit(letter)){
           int number = letter -'0'; //convert ascii character to actual number
           char temp[5] = {0}; //number max
           int i = 0;
           //Determine if the digit exceeds the limit  
           number = checkNumberTooLong(ifp, number, letter, flag);

            //loop through until digit is fully in string 
            while(isdigit(letter)){
                temp[i]= letter;
                ++i;
               letter = fgetc(ifp); 
            }
            
            //Converts int to string
            sprintf(temp, "%d", number);
            strcpy(table_lex[pos].identifier, temp);
            //copies the digit into lexical table identifier 
            table_lex[pos].num = number;
            table_lex[pos].type = numbersym;
            pos++;
        }
        //---------------------------------------------------
        //If not alphabet, nor digit, has to be a symbol
        else {
            int symbolIndex = 0; 
            char temp[SPECIAL_SYMBOL_LENGTH] = {0}; 
            //Retrieves the current symbol
            temp[symbolIndex]= letter; 
            symbolIndex++;
            //Assign the correct symbol to the lexical list
            tn = printSpecialSymbol(ifp, ofp, tn, letter, temp);
        }
        if(tn == 0){
            letter = fgetc(ifp);
        }
    }
}
//Print the Lexeme Table - part 2
void printTable(FILE *ifp, FILE *ofp) {
    int i;
    char temp;
    fseek(ifp, 0, SEEK_SET); //reset file pointer to begining of input file
    //Print Header
    fprintf(ofp, "\nLexeme Table:\nlexeme\t\ttoken type\n");
    for(i = 0; i < pos; i++) { //pos
        fprintf(ofp, "%s", table_lex[i].identifier); //Print Lexeme token
        fprintf(ofp, "\t\t%d", table_lex[i].type); //Print Token Type
        fprintf(ofp, "\n");
    }
}
//Prints the Lexical List - part 3
void printLexeme(FILE *ofp) {
    int i;
    //fprintf(ofp, "\nLexeme List:\n");
    for(i = 0; i < pos; i++){
        //Prints the character numerical representation
        fprintf(ofp,"%d ", table_lex[i].type);
        
        //Prints the variable
        if(table_lex[i].type==2)
            fprintf(ofp,"%s ", table_lex[i].identifier);
        
        //Prints number
        else if(table_lex[i].type == 3)
            fprintf(ofp,"%d ",table_lex[i].num);
        
    }
}
void lexical(int lexFlag){
    FILE* ifp; //input file
    FILE* ofp; //output file 

    ifp = fopen("input.txt", "r"); //reads input file 
    ofp = fopen("lexicalAnalyzerOutput.txt", "w"); //write to output file 
    
    //part 1
    checkFile(ifp); //Determine if file is able to open 
    //reprintSourceProgram(ifp, ofp); //Reprint Source Program
    
    //part 2
    lexicalAnalyzer(ifp, ofp); //Conduct the main task of lexical analyzer 
    //printTable(ifp, ofp); //Print the Lexeme Table 

    //part 3
    printLexeme(ofp); //Print the Lexeme List 
    //Close input and output file
    fclose(ifp);
    fclose(ofp);

    if(lexFlag) {
        char temp; 
        ofp = fopen("lexicalAnalyzerOutput.txt", "r");
        fseek(ofp, 0, SEEK_SET);
        printf("Lexeme List:\n");
        temp = fgetc(ofp);
        while(temp != EOF) {
             printf("%c", temp); 
             temp = fgetc(ofp);
        }
        printf("\n\n");
        fclose(ofp);
    }
    
}