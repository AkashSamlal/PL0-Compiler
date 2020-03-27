CC=gcc
TARGET=compile
SAVE=$(wildcard	*.txt)
TEXT=$(patsubst	%.txt,%.txt,	$(SAVE),	$(TARGET))

compile:	compilerDriver.o	lexicalAnalyzer.o	parserCodeGen.o	VM.o
	$(CC)	compilerDriver.c	lexicalAnalyzer.c	parserCodeGen.c	VM.c	-o	$(TARGET)

clean:
	rm	*.o	$(TEXT)
	#Compile
    #1  Run 'make'
    #2  Run './compile' view    output  txt file
    #3  Finish? Run 'make   clean'