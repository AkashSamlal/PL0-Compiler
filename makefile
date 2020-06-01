CC=gcc
TARGET=compile
SAVE	:=	$(wildcard	*.txt)
TEXT	:=	$(patsubst	%.txt,%.txt,	$(SAVE),	$(TARGET))

compile:	hw4compiler.o	lexicalAnalyzer.o	parserCodeGen.o	VM.o
	$(CC)	hw4compiler.c	lexicalAnalyzer.c	parserCodeGen.c	VM.c	-o	$(TARGET)

clean:
	rm	*.o	$(TEXT)
	#Compile
    #1  Run 'make'
    #2  Run './compile' view    output  txt file
    #3  Finish? Run 'make   clean'