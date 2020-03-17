testData: compilerDriver.o testHW2.o testData.o
    gcc -o testData compilerDriver.o testHW2.o testData.o

compilerDriver.o: compilerDriver.c testData.h 
    gcc -c compilerDriver.c 

testHW2.o: testHW2.c testData.h 
    gcc -c testHW2.c 
    

