CC=gcc
TARGET=compile

compile:	main.o	testHW2.o
	$(CC)	main.c	testHW2.c	-o	$(TARGET)

clean:
	rm	*.o	$(TARGET)
	#Compile
    #1  Run 'make'
    #2  Run './compile' view    output  txt file
    #3  Finish? Run 'make   clean'