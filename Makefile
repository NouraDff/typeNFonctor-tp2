#Lab6
CARGS= -lm -std=c++11
.PHONY: all default testavl clean

all : testavl 

default: tp2
tp2:
	@g++ tp2.cpp $(CARGS)

testavl: testavl.cpp arbreavl.h
	@g++ -o testavl testavl.cpp $(CARGS)

clean :
	@rm -f testavl


