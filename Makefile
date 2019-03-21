# Makefile

CARGS= -lm -std=c++11 -g
DATE = $(shell date +Modif:\ %a\ %-d\ %b\ %Y\ à\ %T)
.PHONY: all default testavl clean save

all : testavl tp2 

default: tp2 arbreavl.h type.h fonctor.h
tp2:
	@g++ tp2.cpp $(CARGS)

test: testavl.cpp arbreavl.h
	@g++ -o testavl testavl.cpp $(CARGS)

clean :
	@rm -f testavl a.out

save:
	@git commit -q -am "$(DATE)"	



