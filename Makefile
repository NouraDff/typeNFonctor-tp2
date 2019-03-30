# Makefile

CARGS= -lm -std=c++11 -g
DATE = $(shell date +Modif:\ %a\ %-d\ %b\ %Y\ à\ %T)
.PHONY: all default testavl clean save

all : testavl tp2 

default: tp2 arbreavl.h type.h fonctor.h
tp2: tp2.cpp arbreavl.h type.h fonctor.h
	@g++ -o $@ $< $(CARGS)

test: testavl.cpp arbreavl.h
	@g++ -o $@ $< $(CARGS)

clean :
	@rm -f testavl tp2

save:
	@git commit -q -am "$(DATE)"	



