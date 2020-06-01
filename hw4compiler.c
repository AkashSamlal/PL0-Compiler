#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main(int argc, char *argv[]) {
    int lexFlag = 0, parseFlag = 0, vmFlag = 0, i; 
    for(i = 0; i < argc; i++) {
        if((strcmp(argv[i], "-l") == 0))
            lexFlag = 1;
        if((strcmp(argv[i], "-a") == 0))
            parseFlag = 1;
        if((strcmp(argv[i], "-v") == 0))
            vmFlag = 1;
    }
    int size = --argc;
    
    lexical(lexFlag, argv[size]);
    parser(parseFlag);
    VM(lexFlag, parseFlag, vmFlag);
    
    return 0; 
}