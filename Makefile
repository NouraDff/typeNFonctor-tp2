#Lab6
CARGS= -lm -std=c++11
.PHONY: all default testavl clean

all : testavl tp2 

default: tp2 arbreavl.h fonctor.h type.h
tp2:
	@g++ tp2.cpp $(CARGS)

test: testavl.cpp arbreavl.h
	@g++ -o testavl testavl.cpp $(CARGS)

clean :
	@rm -f testavlls
	


