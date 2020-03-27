//Akash Samlal - HW3 Parser - Code Generator 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXTABLE 200
#define MAXCODE 500
#define MAXID 12
#define MAXTK 3

//Symbol DataType
typedef struct{
  int kind;
  char name[MAXID];
  int val;
  int level;
  int addr;
} symbol;

//Code DataType
typedef struct{
  int OP; 
  int R;  
  int L;  
  int M;  
} code;

//Token DataType
typedef struct{
  char tkn[MAXTK];   
  char value[MAXID]; 
} token;

//Symbol Table, Code Data Type, Token for each string
symbol symTable[MAXTABLE];
code cd[MAXCODE];
token tok; 

//Global Variables to Keep track of
FILE *ifp;
int index = 0, rp, sp = 1, curlvl = 1, lvl = 1, counter = 0;

//Function for errors
void error(int errorCode){
  printf("Error: ");
  switch(errorCode){
  case 1:
    printf("Use = instead of :=.\n");
    break;
  case 2:
    printf("= must be followed by a number.\n");
    break;
  case 3:
    printf("Identifier must be followed by =.\n");
    break;
  case 4:
    printf("const, var, must be followed by identifier.\n");
    break;
  case 5:
    printf("Semicolon or comma missing.\n");
    break;
  case 7:
    printf("Statement expected.\n");
    break;
  case 8:
    printf("Incorrect symbol after statement part in block.\n");
    break;
  case 9:
    printf("Period expected.\n");
    break;
  case 10:
    printf("Semicolon between statements missing.\n");
    break;
  case 11:
    printf("Undeclared identifier.\n");
    break;
  case 12:
    printf("Assignment to constant is not allowed.\n");
    break;
  case 13:
    printf("Assignment operator expected.\n");
    break;
  case 15:
    printf("Call of a constant or variable is meaningless.\n");
    break;
  case 16:
    printf("then expected.\n");
    break;
  case 17:
    printf("Semicolon or } expected.\n");
    break;
  case 18:
    printf("Do expected.\n");
    break;
  case 19:
    printf("Incorrect symbol following statement.\n");
    break;
  case 20:
    printf("Relational operator expected.\n");
    break;
  case 22:
    printf("Right parenthesis missing.\n");
    break;
  case 23:
    printf("The preceding factor cannot begin with this symbol.\n");
    break;
  case 24:
    printf("Expression cannot begin with this symbol.\n");
    break;
  case 25:
    printf("Number is too large.\n");
    break;
  default:
    printf("Unknown error, please check again");
  }
  fclose(ifp);
  exit(0);
}
//Function to add grammar to the symbol table
void addsymTable(int kind, char name[], int value, int address){
  symTable[counter].kind = kind; //1 for const, 2 for variable
  strcpy(symTable[counter].name, name); //store the string
  symTable[counter].val = value; //store value 
  symTable[counter].addr = address; //store address
  counter++;
}
//Function to fill in each Code for the parserOutput.txt
void emit(int OP, int R, int L, int M){
  //Fill in the current index with the operand, register, lex level, and M
    cd[index].OP = OP;
    cd[index].R = R;
    cd[index].L = L;
    cd[index].M = M;
    index++;
}
//Function to scan each token from the lexicalAnalyzerOutput.txt
void getToken(){
  //Scan the next string in input file
  if(fscanf(ifp, "%s", tok.tkn) != EOF ){
    //If the token type is a variable, scan the next string and store it to value
    if((strcmp(tok.tkn, "2") == 0)) 
      fscanf(ifp, "%s", tok.value); 
    //Unless the token type is a number, scan next string and store it to value 
    else if((strcmp(tok.tkn, "3") == 0))
          fscanf(ifp, "%s", tok.value); 
    //If neither a variable or number insert null terminators     
    else
        tok.value[0] = '\0';
  }
  //If no more strings, insert null terminators
  else{
    tok.tkn[0] = '\0';
    tok.value[0] = '\0';
  }
}
//Factor is defined either an ident factor or number
void factor(){
  int i, temp = 0, j = 0;
  //Identifier
  if(strcmp(tok.tkn, "2") == 0){
    //Search for previous declarations in table
    for(i = counter - 1; i >= 0; i--)
      if(strcmp(tok.value, symTable[i].name) == 0){
        temp = 1; 
        j = i; 
      }
    //Error for not declared 
    if(temp == 0) 
        error(11);
        //Variables 
    if(symTable[j].kind == 2) 
        emit(3, rp, curlvl - symTable[j].level, symTable[j].addr - 1);
        //Constant
    else if(symTable[j].kind == 1) 
        emit(1 , rp, 0, symTable[j].val);
    rp++;
    getToken();
  }
  //Number
  else if(strcmp(tok.tkn, "3") == 0) {
    emit(1, rp, 0, atoi(tok.value));  
    rp++;
    getToken();
  }
  //( left parathesis
  else if(strcmp(tok.tkn, "15") == 0){
    getToken();
    expression();
    //For closing brace ')', if there's none, error
    if(strcmp(tok.tkn, "16") != 0 ) 
        error(22);
    getToken();
  }
  else
    error(23);
}
//Term is defined as factor
void term(){
  //Factor [* or /] Factor
  char tmp[3];
  factor();
  //Searches through multiplication or division operators
  while((strcmp(tok.tkn, "6") == 0) || (strcmp(tok.tkn, "7") == 0)){
    strcpy(tmp, tok.tkn);
    getToken();
    factor();
    //If it's Multiplication Operand 
    if(strcmp(tmp, "6") == 0) {
       emit(15, rp - 2, rp - 2, rp - 1); //Multiplication to table
       rp--;
    }
    //If it's Division Operand
    else{
        emit(16, rp - 2, rp - 2, rp - 1); //Division to table
        rp--;
    }
  }
}
//Expression is defined as term
void expression(){
  //[+ or -] term [+ or -] and term
  char temp[3];
  // Addition or Subtraction get either
  if((strcmp(tok.tkn, "4") == 0) || (strcmp(tok.tkn, "5") == 0)) {
    strcpy(temp, tok.tkn);
    getToken();
    term();
    //If Negative
    if(strcmp(temp, "5") == 0)
        emit(12, rp - 1, rp - 1, 0); //Negative
  }
  else term();
  // Continue copying additional operands 
  while((strcmp(tok.tkn, "4") == 0) || (strcmp(tok.tkn, "5") == 0)) {
    strcpy(temp, tok.tkn);
    getToken();
    term();
    //If addition add to code table
    if(strcmp(temp, "4") == 0){
        emit(13, rp - 2, rp - 2, rp - 1); //Addition
        rp--;
    }
    //Unless subtraction add to code table 
    else{
        emit(14, rp - 2, rp - 2, rp - 1 ); //Subtraction
        rp--;
    }
  }
}
//Relational Operator is defined as the relational operators
int rel_op(){ 
    // =
  if(strcmp(tok.tkn, "9") == 0)
    return 19;
    // <>
  else if(strcmp(tok.tkn, "10") == 0)
    return 20;
    // <
  else if(strcmp(tok.tkn, "11") == 0)
    return 21;
    // <=
  else if(strcmp(tok.tkn, "12") == 0)
    return 22;
    // >
  else if(strcmp(tok.tkn, "13") == 0)
    return 23;
    // >=
  else if(strcmp(tok.tkn, "14") == 0)
    return 24;
  else
    return 0;
}
//Condition id defined as expression rel-op
void condition() {
  if(strcmp(tok.tkn, "8") == 0){
    //Searches for Odd 
    getToken();
    expression();
    emit(17, rp - 1, rp - 1, 0); //odd
  }
  else{ //expression rel-op expression
    //Add relational operators into the table 
    int temp;
    expression();
    temp = rel_op();

    if(temp == 0)
      error(20);

    getToken();
    expression();
    emit(temp, rp - 2, rp - 2, rp - 1); //Emit to what the relational expression is 
    rp--;
  }
}
//Statement is defined as expressions
void statement(){
  int i, ax = 0, temp;
  //Search for variable 
  if(strcmp(tok.tkn, "2") == 0) {
    for(i = counter - 1; i >= 0; i--) { 
        if(strcmp(tok.value, symTable[i].name) == 0){
            if(symTable[i].kind == 1) //Error for Const
                error(12);
            else if(symTable[i].kind == 2){
                ax = 1;
                temp = i;
            }
        }
    }
    //Undeclared Identifier
    if(ax == 0) 
        error(11);
    getToken();
    //Should be an equal sign, not becomesym
    if(strcmp(tok.tkn, "20") != 0 ) 
        error(3);

    getToken();
    expression();
    //Add to Code for output: Store
    emit(4, rp - 1, curlvl - symTable[temp].level, symTable[temp].addr - 1);
    rp--;
  }
  //Check for begin
  else if(strcmp(tok.tkn, "21") == 0){
    getToken();
    statement();
    //check until statement ends
    while(strcmp(tok.tkn, "18") == 0){
      getToken();
      statement();
    }
    getToken();
  }
  //check for if
  else if(strcmp(tok.tkn, "23") == 0){
    int in1;
    getToken();
    condition();
    //Seeking for else sym, not a thensym
    if(strcmp(tok.tkn, "24") != 0) 
        error(16);
    getToken();
    in1 = index;
    emit(8, rp - 1, 0, 0);
    statement();
    getToken();
    //Search for else statement 
    if(strcmp( tok.tkn, "33") == 0){
        int in2 = index;
        emit(7, 0, 0, 0);//Jump
        cd[in1].M= index;
        getToken();
        statement();
        cd[in2].M = index;
        rp--;
    }
    else{
        cd[in1].M = index;
        rp--;
    }
  }
  //Search for While statement
  else if(strcmp(tok.tkn, "25") == 0){
    int fI = index;
    getToken();
    condition();
    int fS = index;
    emit(8, rp - 1, 0, 0);
    if(strcmp(tok.tkn, "26") != 0) 
        error(18);
    getToken();
    statement();
    emit(7, 0, 0, fI); //Jump
    cd[fS].M = index;
    rp--;
  }
  //Search for Readsym
  else if(strcmp(tok.tkn, "32") == 0){
    getToken();
    if(strcmp(tok.tkn, "2") != 0)
         error(29);
    for(i = counter - 1; i >= 0; i--)
        if(strcmp(tok.value, symTable[i].name) == 0){
            ax = 1;
            temp = i;
        }
    if(ax == 0) 
        error(11);
     emit(10, rp, 0, 2); //Read 
     if(symTable[temp].kind == 2) 
        emit(4, rp, curlvl - symTable[temp].level, symTable[temp].addr - 1); 
     else if(symTable[temp].kind == 1)
        error(12);
     getToken();
  }
  //Seach for Writing
  else if(strcmp(tok.tkn, "31") == 0){
    getToken();
    if(strcmp(tok.tkn, "2") != 0) 
        error(29);
    for(i = counter - 1; i >= 0; i--) {
        if(strcmp(tok.value, symTable[i].name) == 0){
            if((symTable[i].kind == 1) || (symTable[i].kind == 2)){
                ax = 1;
                temp = i;
            }
        }
    }
    if(ax == 0)
         error(11);
      //Insert variables into code table 
     if(symTable[temp].kind == 2){
        emit(3, rp, curlvl - symTable[temp].level, symTable[temp].addr - 1); 
        emit(9, rp, 0, 1); //Write to console
     }
     //Insert Constants into code table
     else if(symTable[temp].kind == 1){
        emit(1, rp, 0, symTable[temp].val); //First Load
        emit(9, rp, 0, 1); //Write 
     }
     getToken();
  }
}
//Helper Function for Defining Constants 
void constantDecl(char * name, int space, int val) {
      if(strcmp(tok.tkn, "2") != 0) 
        error(4);
      strcpy(name, tok.value);
      getToken();
      if((strcmp(tok.tkn, "9") == 0) || (strcmp(tok.tkn, "20") == 0)){
          if((strcmp(tok.tkn, "20") == 0)) error(1);
        getToken();
        if((strcmp(tok.tkn, "3") == 0)) {
            val = atoi(tok.value);
            addsymTable(1, name, val, 0); //constant
            getToken();
        }
    }
}
//Helper Function for Defining Variables
void varDecl(char *name, int space) {
      if(strcmp(tok.tkn, "2") != 0) 
        error(4);
      strcpy(name, tok.value);
      addsymTable(2, name, 0, sp); /*variable*/
      symTable[counter - 1].level = lvl; //-1
	  space++;
      sp++;
     getToken();
}
//Block is defined as a const-declaration, var-declaration, and statement
void block(){
  char tmp[12];
  int v, jmp, gp = 4;
  jmp = index;
  sp = 3; 
  emit(7, 0, 0, 0);
  do {
     //Constant Declaration
    //-----------------------------------------------
    if(strcmp(tok.tkn, "28") == 0) {
      getToken();
      do{
        constantDecl(tmp, gp, v); 
        while(strcmp(tok.tkn, "17") == 0) {
            getToken();
            constantDecl(tmp, gp, v);
        }
        if(strcmp(tok.tkn, "18") != 0) //semicolon
             error(5);
         getToken();
       }while(strcmp(tok.tkn, "2") == 0); //comma
    }
    //-------------------------------------------
  //Var-Declaration
  if(strcmp(tok.tkn, "29") == 0) {
    getToken();
     do{
      varDecl(tmp, gp);
      while(strcmp(tok.tkn, "17") == 0) { //comma
            getToken();
            varDecl(tmp, gp);
        }
        if(strcmp(tok.tkn, "18") != 0) //semicolon
             error(5);
         getToken();
      }while(strcmp(tok.tkn, "2") == 0);
    }
    //-----------------------------------------------
  }while((strcmp(tok.tkn, "28") == 0) || (strcmp(tok.tkn, "29") == 0));

  cd[jmp].M = index;
  emit(6, 0, 0, gp); //Increment 
  statement();
  curlvl--;
}
//Program is defined as a Block
void program(){
  getToken();
  block();
  if(strcmp(tok.tkn, "19") != 0) error(9);
  emit(11, 0, 0, 3); //period
}
//Print Parser Output
void printParser(FILE *ofp) {
  int i;
  for(i = 0; i < index; i++) {
      printf("%d %d %d %d\n", cd[i].OP, cd[i].R, cd[i].L, cd[i].M);
    fprintf(ofp, "%d %d %d %d\n", cd[i].OP, cd[i].R, cd[i].L, cd[i].M);
  }
}
//Main Function to Run the Parser
int main(){
    FILE *ofp;
    ifp = fopen("lexicalAnalyzerOutput.txt", "r");
    ofp = fopen("parserOutput.txt", "w");
    program();
    printParser(ofp); 
    fclose(ifp);
    fclose(ofp);
    return 0;
}