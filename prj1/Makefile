CC=g++
CFLAGS=-std=c++11

all: executable
debug: CFLAGS += -DEBUG -g -Wall
debug: executable

executable:
	$(CC) $(CFLAGS) wu_p1.cpp -o wu_p1

clean:
	rm wu_p1
