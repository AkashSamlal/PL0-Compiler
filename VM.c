//Akash Samlal
//HW 1 PM/0 Virtual Machine Assignment
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_HEIGHT 40
#define MAX_CODE_LENGTH 200
#define MAX_LEX_LEVELS 3
#define REGISTER_FILE_LENGTH 8
//Prototype for Instruction Register
struct instruction {
    int OP;
    int R;
    int L;
    int M;
};
//P-Machine: 2 Memory Stores
int stack[MAX_STACK_HEIGHT] = {0}; //Contains data to be used by the CPU
struct instruction text[MAX_CODE_LENGTH]; //Contains the instructions for the VM

//Register File for P-Machine to computer arithmetic
int registerFile[REGISTER_FILE_LENGTH] = {0};

//PM/0 CPU Four Registers: Handles the stack and text segments
int BP = 1; //base pointer
int SP = 0; //stack pointer
int PC = 0; //program counter
struct instruction IR = {0}; //instruction register

//Input File to read the sequence code for virtual machine PM/0
FILE *ifp;
//Output File to print out the program in interpreted assembly language
FILE *ofp;
//Halt Flag currently set to 0
int HALTFLAG = 0;
//Find variable in a different Activation Record some L levels down
int base(int L, int base) {
    int b1;
    b1 = base;
    while(L > 0) {
        b1 = stack[b1 + 1];
        L--;
    }
    return b1;
}
//PM/0 Instruction Cycle - Fetch & Execute Cycle
void fetch() {  //Fetch Cycle: Retrieves the current instruction and prepare it for the ALU
  IR = text[PC]; //Instruction is fetched from the "text" array, and store it in the "IR" Register
  PC++; //Increments Program Counter to point to the next instruction
  return; //Continue to the code
}
void execute() { //Execute Cycle: Executes the fetched instruction by the VM
    switch(IR.OP) {
        //LIT
        case 1:
            registerFile[IR.R] = IR.M;
            break;
        //RTN
        case 2:
            SP = BP - 1;
            BP = stack[SP+3];
            PC = stack[SP+4];
            break;
        //LOD
        case 3:
            registerFile[IR.R] = stack[base(IR.L, BP) + IR.M];
            break;
        //STO
        case 4:
            stack[base(IR.L, BP) + IR.M] = registerFile[IR.R];
            break;
        //CAL
        case 5:
            stack[SP+1] = 0;
            stack[SP+2] = base(IR.L, BP);
            stack[SP+3] = BP;
            stack[SP+4] = PC;
            BP = SP + 1;
            PC = IR.M;
            break;
        //INC
        case 6:
            SP = SP + IR.M;
            break;
        //JMP
        case 7:
            PC = IR.M;
            break;
        //JPC
        case 8:
            if(registerFile[IR.R] == 0)
                PC = IR.M;
            break;
        //SIO
        case 9:
            fprintf(ofp, "%d\n", registerFile[IR.R]);
            break;
        //SIO
        case 10:
            printf("Enter Number to store in register.\n");
            scanf("%d", &registerFile[IR.R]);
            break;
        //SIO
        case 11:
            HALTFLAG = 1;
            break;
        //NEG
        case 12:
            registerFile[IR.R] = -registerFile[IR.R];
            break;
        //ADD
        case 13:
            registerFile[IR.R] = registerFile[IR.L] - registerFile[IR.M];
            break;
        //SUB
        case 14:
            registerFile[IR.R]= registerFile[IR.L] - registerFile[IR.M];
            break;
        //MUL
        case 15:
            registerFile[IR.R]= registerFile[IR.L] * registerFile[IR.M];
            break;
        //DIV
        case 16:
            registerFile[IR.R]= ((registerFile[IR.L])/(registerFile[IR.M]));
            break;
        //ODD
        case 17:
            registerFile[IR.R] = (registerFile[IR.R]%2);
            break;
        //MOD
        case 18:
            registerFile[IR.R] = ((registerFile[IR.L]) % (registerFile[IR.M]));
            break;
        //EQL
        case 19:
            if(registerFile[IR.L] == registerFile[IR.M])
                registerFile[IR.R] = 1;
            break;
        //NEQ
        case 20:
              if(registerFile[IR.L] != registerFile[IR.M])
                registerFile[IR.R] = 1;
            break;
        //LSS
        case 21:
             if(registerFile[IR.L] < registerFile[IR.M])
                registerFile[IR.R] = 1;
            break;
        //LEQ
        case 22:
              if(registerFile[IR.L] <= registerFile[IR.M])
                registerFile[IR.R] = 1;
            break;
        //GTR
        case 23:
              if(registerFile[IR.L] > registerFile[IR.M])
                registerFile[IR.R] = 1;
            break;
        //GEQ
        case 24:
              if(registerFile[IR.L] >= registerFile[IR.M])
                registerFile[IR.R] = 1;
            break;
        //If IR.OP isn't recognized, break from execute
        default:
            fprintf(ofp, "Error: Operand isn't recognized\n");
            break;
    }
   return;
}
//Print the Interpreted Assembly Language
void printAssembly(char ** line, int index) {
    fprintf(ofp,"Line\tOP\tR\tL\tM\n");

    //Print the Line Numbering
    for(int i = 0; i < index; i++) {
        fprintf(ofp, "%d\t", i);

    //Print the Operand of each OP
        switch(text[i].OP) {
             case 1: //lit
                strcpy(line[i], "lit");
                fprintf(ofp, "lit\t");
                break;
             case 2: //rtn
                strcpy(line[i], "rtn");
                fprintf(ofp, "rtn\t");
                break;
             case 3: //lod
                strcpy(line[i], "lod");
                fprintf(ofp, "lod\t");
                break;
             case 4: //sto
                strcpy(line[i], "sto");
                fprintf(ofp, "sto\t");
                break;
             case 5: //cal
                strcpy(line[i], "cal");
                fprintf(ofp, "cal\t");
                break;
             case 6: //inc
                strcpy(line[i], "inc");
                fprintf(ofp, "inc\t");
                break;
             case 7: //jmp
                strcpy(line[i], "jmp");
                fprintf(ofp, "jmp\t");
                break;
             case 8: //jpc
                strcpy(line[i], "jpc");
                fprintf(ofp, "jpc\t");
                break;
             case 9: //sio
                strcpy(line[i], "sio");
                fprintf(ofp, "sio\t");
                break;
             case 10: //sio
                strcpy(line[i], "sio");
                fprintf(ofp, "sio\t");
                break;
             case 11: //sio
                strcpy(line[i], "sio");
                fprintf(ofp, "sio\t");
                break;
             case 12: //neg
                strcpy(line[i], "neg");
                fprintf(ofp, "neg\t");
                break;
             case 13: //add
                strcpy(line[i], "add");
                fprintf(ofp, "add\t");
                break;
             case 14: //sub
                strcpy(line[i], "sub");
                fprintf(ofp, "sub\t");
                break;
             case 15: //mul
                strcpy(line[i], "mul");
                fprintf(ofp, "mul\t");
                break;
             case 16: //div
                strcpy(line[i], "div");
                fprintf(ofp, "div\t");
                break;
             case 17: //odd
                strcpy(line[i], "odd");
                fprintf(ofp, "odd\t");
                break;
             case 18: //mod
                strcpy(line[i], "mod");
                fprintf(ofp, "mod\t");
                break;
             case 19: //eql
                strcpy(line[i], "eql");
                fprintf(ofp, "eql\t");
                break;
             case 20: //neq
                strcpy(line[i], "neq");
                fprintf(ofp, "neq\t");
                break;
             case 21: //lss
                strcpy(line[i], "lss");
                fprintf(ofp, "lss\t");
                break;
             case 22: //leq
                strcpy(line[i], "leq");
                fprintf(ofp, "leq\t");
                break;
             case 23: //gtr
                strcpy(line[i], "gtr");
                fprintf(ofp, "gtr\t");
                break;
             case 24: //geq
                strcpy(line[i], "geq");
                fprintf(ofp, "geq\t");
                break;
            default: break;
          }
        //Print the Register
        fprintf(ofp, "%d\t", text[i].R);
       //Print the Lexicographical Level
        fprintf(ofp, "%d\t", text[i].L);
        //Print the M Operator
        fprintf(ofp, "%d\n", text[i].M);
    }
    //Print New Line
     fprintf(ofp, "\n");
}
//Print the Exection of the program in Virtual Machine: Depict the stack and registers PC, BP, SP
void printInitialExecution() {
    int i; //Use for "For-Loop"
    //Print Header
    fprintf(ofp,"\t\tpc\tbp\tsp\tregisters\n");
    //Print PC, BP, SP
    fprintf(ofp, "Initial Values\t%d\t%d\t%d\t", PC, BP, SP);
    //Print Register File
    for(i = 0; i < REGISTER_FILE_LENGTH; i++)
        fprintf(ofp, "%d ", registerFile[i]);
    //Print Stack Header
    fprintf(ofp, "\nStack: ");
    //Print Stack Contents
    for(i = 0; i < MAX_STACK_HEIGHT; i++)
        fprintf(ofp, "%d ", stack[i]);
    //Print new lines
    fprintf(ofp, "\n\n");
}
//Print Contents of the Program during Execution
void printExecution(int temp, char **line, int index) {
    int i; //Use for "For-Loop"
    //Print Header
    fprintf(ofp, "\t\tpc\tbp\tsp\tregisters\n");
    //Print Contents of Instruction Register
    fprintf(ofp, "%d %s %d %d %d", temp, line[index], IR.R, IR.L, IR.M);
    fprintf(ofp, "\t%d\t%d\t%d\t", PC, BP, SP);
    //Print Register File Contents
    for(i = 0; i < REGISTER_FILE_LENGTH; i++)
        fprintf(ofp, "%d ", registerFile[i]);
    //Print Stack Header
    fprintf(ofp, "\nStack: ");
    //Print Stack Contents
    for(i = 0; i < MAX_STACK_HEIGHT; i++)
       fprintf(ofp, "%d ", stack[i]);
   //Print new lines
   fprintf(ofp, "\n\n");
}
//Main Function
int main() {
    //Use for "for-loop"
    int i;
    char ** line; //String for storing current Operand
    //Open the Input File and Read it
    ifp = fopen("parserOutput.txt", "r");
    //Create Output File and Write it
    ofp = fopen("VMOutput.txt", "w");
    //If Input File doesn't exist ouput an error
    if(ifp == NULL) {
        printf("File couldn't open, please check name of the input text file\n");
        exit(EXIT_FAILURE);
    }
    //Increment initalizer
    int index = 0;
    //Read input file and save in text memory
    while(!feof(ifp)) {
        fscanf(ifp, "%d", &text[index].OP); //save operand
        fscanf(ifp, "%d", &text[index].R); //save register
        fscanf(ifp, "%d", &text[index].L); //save lexicographical level
        fscanf(ifp, "%d", &text[index].M); //save M component
        index++;
    }
    //Dynamically Allocated an array of strings to save Operands
    line = malloc(sizeof(char*)*(index));
    //Error Check if no memory left to allocate
    if(line == NULL) {
        printf("Unable to allocate Memory, please restart Machine and try again.\n");
        exit(EXIT_FAILURE); //exit gracefully
     }
    //Dynamically Allocated each string
    for(i = 0; i < index; i++)
        line[i] = (char*)malloc(sizeof(char)*3);
    //Print the Interpreted Assembly Language
    printAssembly(line, index);
    //Print the Initial Exection of the program in Virtual Machine: Depict the stack and registers PC, BP, SP
    printInitialExecution();
    //Restart Index to print each execution
    index = 0;
    //Execute the P-Machine Cycle
    while(HALTFLAG == 0) {
        int temp = PC; //stores previous PC
        fetch(); //fetch instruction
        execute(); //execute instruction
        printExecution(temp, line, index); //display output after execution
        index++; //increment to next operand
        //Halt program when program ends
        if(((PC == 0) && (BP == 0)) && (SP == 0))
            HALTFLAG == 1;
        //Print after state of program
        if(HALTFLAG == 1)
            printExecution(temp, line, index);
       }
    //Free Dynamic1ally Allocated String Array
    free(line);
    //Close Input File
    fclose(ifp);
    //Close Output File
    fclose(ofp);
    exit(EXIT_SUCCESS); //Exit gracefully
    return 0;
}
