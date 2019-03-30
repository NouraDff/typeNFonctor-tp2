# Makefile

CARGS= -lm -std=c++11 -g
DATE = $(shell date +Modif:\ %a\ %-d\ %b\ %Y\ à\ %T)
.PHONY: default testavl clean save

default: tp2 arbreavl.h type.h fonctor.h
tp2:
	@g++ -o $@ tp2.cpp $(CARGS)

test: testavl.cpp arbreavl.h
	@g++ -o testavl testavl.cpp $(CARGS)

clean :
	@rm -f testavl tp2

save:
	@git commit -q -am "$(DATE)"	



