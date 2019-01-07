CC=gcc
DIR_OBJ=bin
DIR_LIB=lib
CPPFLAGS=-Iinclude
TRAITEMENT=./src/traitement.o
HISTO=./src/histogram.o
QUANTIFICATION=./src/quantification.o
TEST_HISTO=./src/test_histogram.o
MAIN=./src/main.o
#On récupère également les .h qui sont dans le sous dossier include
HEADERS = $(shell find ./include -name '*.h')


all : main quantification testhisto

main : $(TRAITEMENT) $(HISTO) $(MAIN)
	$(CC) -o $@ $^ $(CPPFLAGS)

quantification : $(QUANTIFICATION) $(TRAITEMENT) $(HISTO)
	$(CC) -o $@ $^ $(CPPFLAGS)

testhisto : $(TEST_HISTO) $(TRAITEMENT) $(HISTO)
	$(CC) -o $@ $^ $(CPPFLAGS)

%.o : %.c $(HEADERS)
	$(CC) -o $@ -c $< $(CPPFLAGS)

clean :
	find . -name '*o' -delete

doc :
	doxygen

.PHONY: all clean


