CC=g++
CFLAGS=-std=c++11

wu_p1:
debug: CFLAGS += -DEBUG -g -Wall
debug: executable

%:
	$(CC) $(CFLAGS) wu_p1.cpp -o $@

clean:
	rm wu_p1

