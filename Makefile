#sheblamo

#Same as saying CXX
CC = g++
CPPFLAGS = -Wall -Werror -std=c++0x I
OBJ = main.o functions.o
OUTPUT = main.o
ODIR = ./bin
PROJ_DIR = $(HOME)/home/aetas/gitrepos/project_8/project8

vpath = %.h  $(PROJ_DIR)/include
vpath = %.cpp $(PROJ_DIR)/src

#JSON_C_DIR=/usr/lib64
#CPPFLAGS += -I$(JSON_C_DIR)/include/json-c
#LDFLAGS+= -L$(JSON_C_DIR)/lib -ljson-c

program: $(OBJ)
	$(CC) $(OBJ) -o $(ODIR)/$(OUTPUT) $(LDFLAGS)

main.o : ./src/Assignment8.cpp ./include/Graph.h
	$(CC) -c

functions.o : ./src/Graph.cpp ./include/Graph.h
	$(CC) -c

.PHONY : clean
clean :
	rm program $(OBJ)

# Creates a log to keep track of things changed
log : Assignment8.cpp $(OBJ)
	lpt -p $?
	touch log

