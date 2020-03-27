CC=gcc
TARGET=compile

compile:	compilerDriver.o	lexicalAnalyzer.o	parserCodeGen.o	VM.o
	$(CC)	compilerDriver.c	lexicalAnalyzer.c	parserCodeGen.c	VM.c	-o	$(TARGET)

clean:
	rm	*.o	$(TARGET)
	#Compile
    #1  Run 'make'
    #2  Run './compile' view    output  txt file
    #3  Finish? Run 'make   clean'