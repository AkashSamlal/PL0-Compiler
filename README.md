## PL0 Compiler Steps:
**Step 1:** Run "make" on the command line where the file is saved, 
        If this command line don't work, enter: "gcc -o compile compilerDriver.c lexicalAnalyzer.c parserCodeGen.c VM.c"
        Hit enter 

**Step 2:** Run "./compile [Name of the input fileName]" (Prints only the input source program and the output)
            "./compile -l [Name of the input fileName]" (Prints only the lexeme list)
            "./compile -a [Name of the input fileName]" (Prints only the parser)
            "./compile -v [Name of the input fileName]" (Prints only the VM)
             "./compile -l -a -v [Name of the input fileName]" (Prints all three, the lexeme list, parser, and VM)
             
**Step 3:** After you are done, enter in the terminal, "make clean", this will erase all object files, and generated text files, besides the input text file 
        Ignore the error about "Couldn't delete input text file", we wanted to not delete the input text file
