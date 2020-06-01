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

**Original Instructions**
![image](https://user-images.githubusercontent.com/43329669/83373586-e58f0a00-a396-11ea-961c-ff9e7ce6a374.png)
![image](https://user-images.githubusercontent.com/43329669/83373604-fb043400-a396-11ea-9e7b-ad8a8e0136a5.png)
![image](https://user-images.githubusercontent.com/43329669/83373664-26871e80-a397-11ea-8762-2d18098a299a.png)
![image](https://user-images.githubusercontent.com/43329669/83373703-4585b080-a397-11ea-9aac-f9954b4edfcc.png)
![image](https://user-images.githubusercontent.com/43329669/83373756-71a13180-a397-11ea-8142-d0b7ecbd731c.png)
![image](https://user-images.githubusercontent.com/43329669/83373820-b927bd80-a397-11ea-9b26-e68790e3b0cf.png)
![image](https://user-images.githubusercontent.com/43329669/83373921-fab86880-a397-11ea-91a7-a148cc4cc7f7.png)
