CC=gcc
TARGET=compile

compile:	main.o	testHW2.o
	$(CC)	main.c	testHW2.c	-o	$(TARGET)

clean:
	rm	*.o	$(TARGET)