# Makefile
#
# CS 433 homework 1: symbol table

# This is a "Makefile" - a unix tool for program development.  You will
# see many more Makefiles in this class.  A Makefile contains all the
# information necessary to build (compile) all the files in the current
# directory.  To compile, simply type "make".  The program "make" then
# looks at this file to figure out what commands to run to compile the
# whole project.  It is "smart" in that it looks at the file modification
# dates to figure out which files have been edited since the last "make",
# and it only recompiles those files (and all that depend on them).  To
# learn more about "make" and Makefiles, consult some of the books on
# Unix in the library, or type "man make", or click on the "Info" button
# in xemacs and go to the documentation for "Gnu make" (this will involve
# learning how to use the xemacs info system, but it's probably worth it!).

# this defines some variables:
HDR = symtab.h
SRC = main.c symtab.c
OBJ = main.o symtab.o

DBG = -g
OPT = # -O
WARN = -W -Wall
CFLAGS = $(DBG) $(OPT) $(WARN)
CC = gcc
LINK = gcc

# this tells "make" what to make:
all: symtab_test

# the lines below tell "make" how to create "symtab_test".  The first line
# means that in order to create symtab_test, it needs to create $(OBJ)
# first (i.e., main.o and symtab.o).  "make" uses a default rule to create
# .o files from .c files.  In this particular case, it will execute
#
#     gcc -g -W -Wall   -c -o main.o main.c
#     gcc -g -W -Wall   -c -o symtab.o symtab.c
#
# The second line tells "make" what command to run.  It will result in
#
#     gcc -o symtab_test main.o symtab.o
# 
symtab_test: $(OBJ)
	$(LINK) -o symtab_test $(OBJ)


# this is a useful rule for cleaning up (type "make clean")
clean:
	rm -f $(OBJ) *.bak core*

# this is a rule to automatically extract all file dependencies from
# the .c files.  To run it, type "make depend".  To see *all* files
# that get included, including system files, try -M instead of -MM

depend:
	gcc -MM $(CFLAGS) $(SRC)

# for now, we include these dependencies here manually:

main.o: main.c symtab.h
symtab.o: symtab.c symtab.h
