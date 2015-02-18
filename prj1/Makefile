CC=g++
CFLAGS=-std=c++11

wu_p1:
debug: CFLAGS += -DEBUG -g -Wall
.PHONY: debug
debug: wu_p1

%:
	$(CC) $(CFLAGS) wu_p1.cpp -o $@

.PHONY: clean
clean:
	rm wu_p1 *.o
