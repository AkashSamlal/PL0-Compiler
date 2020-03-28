//Akash Samlal
//HW 1 PM/0 Virtual Machine Assignment
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "header.h"
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
    char name[6];
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
  fprintf(ofp, "%d\t", PC);
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
            registerFile[IR.R] = registerFile[IR.L] + registerFile[IR.M];
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
            else
                registerFile[IR.R]=0;
            break;
        //NEQ
        case 20:
              if(registerFile[IR.L] != registerFile[IR.M])
                registerFile[IR.R] = 1;
              else
                registerFile[IR.R]=0;  
            break;
        //LSS
        case 21:
             if(registerFile[IR.L] < registerFile[IR.M])
                registerFile[IR.R] = 1;
            else
                registerFile[IR.R]=0;
            break;
        //LEQ
        case 22:
              if(registerFile[IR.L] <= registerFile[IR.M])
                registerFile[IR.R] = 1;
              else
                registerFile[IR.R]=0;  
            break;
        //GTR
        case 23:
              if(registerFile[IR.L] > registerFile[IR.M])
                registerFile[IR.R] = 1;
             else
                registerFile[IR.R]=0;
            break;
        //GEQ
        case 24:
              if(registerFile[IR.L] >= registerFile[IR.M])
                registerFile[IR.R] = 1;
              else
                registerFile[IR.R]=0;
            break;
        //If IR.OP isn't recognized, break from execute
        default:
            fprintf(ofp, "Error: Operand isn't recognized\n");
            break;
    }
   return;
}   
    //Print Table
    void printAssembly(int index){
        int i;
        fprintf(ofp, "\nLine\tOP\tR\tL\tM");
        for(i = 0; i < index; i++){
            int op = text[i].OP;
            //Interpret the operation.
            switch(op){
            case 1: 
            strcpy(text[i].name, "lit");
            fprintf(ofp, "\n%d\t", i); 
            fprintf(ofp, "\tlit\t"); 
            break;

            case 2: 
            strcpy(text[i].name, "rtn");
            fprintf(ofp, "\n%d\t", i); 
            fprintf(ofp, "\trtn\t"); 
            break;

            case 3: 
            strcpy(text[i].name, "lod");
            fprintf(ofp, "\n%d\t", i); 
            fprintf(ofp, "\tlod\t"); 
            break;

            case 4:
            strcpy(text[i].name, "sto");
            fprintf(ofp, "\n%d\t", i); 
            fprintf(ofp, "\tsto\t");
            break;

            case 5: 
            strcpy(text[i].name, "cal");
            fprintf(ofp, "\n%d\t", i);
            fprintf(ofp, "\tcal\t");
            break;

            case 6: 
            strcpy(text[i].name, "inc");
            fprintf(ofp, "\n%d\t", i); 
            fprintf(ofp, "\tinc\t");
            break;

            case 7:
            strcpy(text[i].name, "jmp");
            fprintf(ofp, "\n%d\t", i); 
            fprintf(ofp, "\tjmp\t"); 
            break;

            case 8:
            strcpy(text[i].name, "jpc");
            fprintf(ofp, "\n%d\t", i); 
            fprintf(ofp, "\tjpc\t"); 
            break;

            case 9: 
            strcpy(text[i].name, "sio");
            fprintf(ofp, "\n%d\t", i); 
            fprintf(ofp, "\tsio\t"); 
            break;

            case 10:
            strcpy(text[i].name, "sio");
            fprintf(ofp, "\n%d\t", i); 
            fprintf(ofp, "\tsio\t");
            break;

            case 11:
            strcpy(text[i].name, "sio");
            fprintf(ofp, "\n%d\t", i); 
            fprintf(ofp, "\tsio\t"); 
            break;

            case 12:
            strcpy(text[i].name, "neg");
            fprintf(ofp, "\n%d\t", i); 
            fprintf(ofp, "\tneg\t"); 
            break;

            case 13:
            strcpy(text[i].name, "add");
            fprintf(ofp, "\n%d\t", i); 
            fprintf(ofp, "\tadd\t"); 
            break;

            case 14:
            strcpy(text[i].name, "sub");
            fprintf(ofp, "\n%d\t", i); 
            fprintf(ofp, "\tsub\t"); 
            break;

            case 15:
            strcpy(text[i].name, "mul");
            fprintf(ofp, "\n%d\t", i); 
            fprintf(ofp, "\tmul\t"); 
            break;

            case 16:
            strcpy(text[i].name, "div");
            fprintf(ofp, "\n%d\t", i); 
            fprintf(ofp, "\tdiv\t");
            break;

            case 17:
            strcpy(text[i].name, "odd");
            fprintf(ofp, "\n%d\t", i); 
            fprintf(ofp, "\todd\t"); 
            break;

            case 18:
            strcpy(text[i].name, "mod");
            fprintf(ofp, "\n%d\t", i); 
            fprintf(ofp, "\tmod\t"); 
            break;

            case 19:
            strcpy(text[i].name, "eql");
            fprintf(ofp, "\n%d\t", i); 
            fprintf(ofp, "\teql\t"); 
            break;

            case 20:
            strcpy(text[i].name, "neq");
            fprintf(ofp, "\n%d\t", i); 
            fprintf(ofp, "\tneq\t"); 
            break;

            case 21:
            strcpy(text[i].name, "lss");
            fprintf(ofp, "\n%d\t", i); 
            fprintf(ofp, "\tlss\t"); 
            break;

            case 22:
            strcpy(text[i].name, "leq");
            fprintf(ofp, "\n%d\t", i); 
            fprintf(ofp, "\tleq\t"); 
            break;

            case 23:
            strcpy(text[i].name, "gtr");
            fprintf(ofp, "\n%d\t", i); 
            fprintf(ofp, "\tgtr\t"); 
            break;

            case 24:
            strcpy(text[i].name, "geq");
            fprintf(ofp, "\n%d\t", i); 
            fprintf(ofp, "\tgeq\t"); 
            break;

            default: 
                return;
            }
            fprintf(ofp, "%d\t", text[i].R);
            fprintf(ofp, "%d\t", text[i].L);
            fprintf(ofp, "%d\t", text[i].M);
        }
        return;
    }
//Print the Exection of the program in Virtual Machine: Depict the stack and registers PC, BP, SP
void printInitialExecution() {
    int i; //Use for "For-Loop"
    //Print Header
    fprintf(ofp,"\n\n\t\t\t\tpc\tbp\tsp\tregisters\n");
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
void printExecution(int temp, int index) {
     int i; //Use for "For-Loop"
    //Print Header
    fprintf(ofp, "\t\tpc\tbp\tsp\tregisters\n");
    //Print Contents of Instruction Register
    fprintf(ofp, "%d %s %d %d %d", temp, text[index].name , IR.R, IR.L, IR.M);
    fprintf(ofp, "\t%d\t%d\t%d\t", PC, BP, SP);
    printf("%d\n", index);
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

//Main function -----------------------------------------------------------------------------------
void VM(int lexFlag, int parseFlag, int vmFlag){
     ifp =   fopen("parserOutput.txt", "r");
     ofp =   fopen("VMOutput.txt", "w");
     //If the file isn't there or could not open properly, end the program.
     if(ifp == NULL){
        printf("Input File could not open\n");
      }
    //Keep track of number of instructions the input file.
    int index = 0;
    //Read in the lines from the input file.
    while(!feof(ifp)) { 
        fscanf(ifp, "%d", &text[index].OP);
        fscanf(ifp, "%d", &text[index].R);
        fscanf(ifp, "%d", &text[index].L);
        fscanf(ifp, "%d", &text[index].M);
        index++;
    }
    printAssembly(index);
    printInitialExecution();
    index = 0;
    //Fetch - Execute Cycle. Runs until the halt flag is set to stop the loop.
    while(HALTFLAG == 0){
        int temp = PC; 
        fetch();
        execute();
        printExecution(temp, index);
        index++;
        if(((PC==0) && (BP==0) && (SP==0)))
            HALTFLAG = 1;

        if(HALTFLAG == 1)
            printExecution(temp, index);
    }

    //Close files.
    fclose(ifp);
    fclose(ofp);

 if(vmFlag) {
      char temp; 
      ofp = fopen("VMOutput.txt", "r");
      fseek(ofp, 0, SEEK_SET);
      printf("Virtual Machine:\n");
      temp = fgetc(ofp);
      while(temp != EOF) {
         printf("%c", temp); 
         temp = fgetc(ofp);
        }
        printf("\n\n");
        fclose(ofp);
    }
    if((lexFlag == 0) && (parseFlag == 0) && (vmFlag == 0)) {
        ifp = fopen("input.txt", "r"); 
        ofp = fopen("VMOutput.txt", "r"); 
        char temp; 
        fseek(ifp, 0, SEEK_SET);
        printf("Input File:\n"); 
        temp = fgetc(ifp);
        while(temp != EOF) {
             printf("%c", temp); 
             temp = fgetc(ifp);
        }
        printf("\n\n");

        fseek(ofp, 0, SEEK_SET);
        printf("Output File:\n"); 
        temp = fgetc(ofp);
        while(temp != EOF) {
             printf("%c", temp); 
             temp = fgetc(ofp);
        }
        printf("\n\n");
        fclose(ifp); 
        fclose(ofp);
    }
    }//---------------------------------------------------------------------------------------------------

    