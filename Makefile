# Makefile for ex1-q1 spring 2021B
CFLAGS = -Wall
LDFLAGS = -lm # not really needed for this exercise
CC = gcc -std=c99
ECHO = echo "going to compile for target $@"
PROG = ex1_q1
OBJFILES = ex1_q1_func.o ex1_q1.o

all: test

ex1_q1_func.o: ex1_q1_func.c ex1_q1.h
	$(ECHO)
	$(CC) $(CFLAGS) -c ex1_q1_func.c 

ex1_q1.o: ex1_q1.c ex1_q1_func.o 
	$(ECHO)
	$(CC) $(CFLAGS) -c ex1_q1.c

$(PROG): $(OBJFILES)
	echo 'going to build (link) ex1_q1...'
	$(CC) -o ex1_q1 -Wall $(OBJFILES) $(LDFLAGS)

clean:
	rm -vf *.o ${PROG} *.log 

test:$(PROG)
	@echo going to run test...
	./$(PROG) < in.txt > out.log
