#include <stdio.h>
#include <stdlib.h>
#include "testData.h"
#define MAX_SYMBOL_TABLE_SIZE 55
#define NUMBER 5
#define RELATION 5
#define CODE_SIZE 5

typedef struct {
    int kind;
    char name[10];
    int val;
    int level;
    int addr;
} symbol; 

int token; 

symbol table[MAX_SYMBOL_TABLE_SIZE] = {0};
instruction code[CODE_SIZE]; 

void factor() {
    if(token == "identsym") {
        get(token); 
    }
    else if(token == NUMBER) {
        get(token);
    }
    else if(token == "(") {
        get(token); 
        expression(); 
        if(token != ")") 
            error(); 
        get(token); 
    }
    else {
        error(); 
    }
}

void term() {
    factor(); 
    while((token == "multsym") || (token == "slashsym")) {
        get(token);
        factor();
    }
}

void expression() {
    if((token == "plussym") || (token == "minussym")) {
        get(token);
    }
    term(token);
    while((token == "plussym") || (token == "minussym")) {
        get(token);
        term();
    }
} 

void condition() {
    if(token == "oddsym") {
        get(token); 
        expression(); 
    }
    else {
        expression();
        if(token != RELATION) 
            error(); 
        get(token);
        expression();
    }
}

void statement() {
    if(token == "identsym") {
        get(token);
        if(token != "becomessym")
            error();
        get(token);
        expression(); 
    }
    else if(token == "callsym") {
        get(token);
        if(token != "identsym")
            error(); 
        get(token);
    }
    else if(token == "beginsym") {
        get(token);
        statement(); 
        while(token == "semicolonsym") {
            get(token); 
            statement(); 
        }
        if(token != "endsym")
            error(); 
        get(token); 
    }
    else if(token == "ifsym") {
        get(token);
        condition(); 
        if(token != "thensym")
            error();
        get(token);
        statement();
    }
    else if(token == "whilesym") {
        get(token);
        condition(); 
        if(token != "dosym")
            error(); 
        get(token); 
        statement();
    }
}

void block() {
    if(token == "constsym") {
        do {
            get(token);
            if(token != "identsym") 
                error();
            if(token != "eqsym")
                error(); 
            if(token != NUMBER)
                error(); 
            get(token); 
        }while(token != "commasym");
        if(token != "semicolomsym")
            error(); 
        get(token);
    }
    if(token == "intsym") {
        do {
            get(token);
            if(token != "identsym")
                error(); 
            get(token);
        } while(token != "commasym"); 
        if(token != "semicolonsym")
            error(); 
        get(token);
    }
    while(token == "procsym") {
        get(token); 
        if(token != "identsym")
            error(); 
        get(token); 
        if(token != "semicolomsym")
            error(); 
        get(token);
        block(); 
        if(token != "semicolomsym")
            error();
        get(token);
    }
    statement();
}

void program() {
    get(token);
    block(); 
    if(token != "periodsym") {
        error();
    }
}
int main() {
    FILE *ifp, *ofp; 

    ifp = fopen("lexoutput.txt", "r");
    ofp = fopen("parserOutput.txt", "w"); 

    program(ifp); 
    return 0;
}