PL0 Compiler Steps:
Step 1: Have your input file called "input.txt"

Step 2: Run "make" on the command line where the file is saved, 
        If this command line don't work, enter: "gcc -o compile compilerDriver.c lexicalAnalyzer.c parserCodeGen.c VM.c"
        Hit enter 

Step 3: Run "./compile (any arguments you want), for example 
            "./compile" (Prints only the input source program and the output)
            "./compile -l" (Prints only the lexeme list)
            "./compile -a" (Prints only the parser)
            "./compile -v" (Prints only the VM)
             "./compile -l -a -v" (Prints all three, the lexeme list, parser, and VM)

Step 4:After you are done, enter in the terminal, "make clean", this will erase all object files, and generated text files, besides the input text file 
        Ignore the error about "Couldn't delete input text file", we wanted to not delete the input text file
