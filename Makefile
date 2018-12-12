CC=gcc
DIR_OBJ=bin
DIR_LIB=lib
CPPFLAGS=-Iinclude
#On récupère tous les fichiers .c (qui ne sont pas des tests)
#de manière récursive dans les sous répertoires
SRC = $(shell find ./src -name '*.c' ! -name 'test*.c' )
TEST_HISTO = ./src/test_histogram.o
HISTO = ./src/histogram.o
#On récupère également les .h qui sont dans le sous dossier include
HEADERS = $(shell find ./include -name '*.h')
#Les fichiers objets sont les mêmes que les fichiers c, mais l'extension est remplacée par .o 
OBJS = $(SRC:.c=.o)


all : main

main : $(OBJS) 
	$(CC) -o $@ $(OBJS)

testhisto : $(TEST_HISTO) $(HISTO)
	$(CC) -o $@ $^ $(CPPFLAGS)

%.o : %.c $(HEADERS)
	$(CC) -o $@ -c $< $(CPPFLAGS)

clean :
	find . -name '*o' -delete

doc :
	doxygen

.PHONY: all clean


