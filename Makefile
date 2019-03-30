# Makefile

CARGS= -lm -O2 -std=c++11 -g
DATE = $(shell date +Modif:\ %a\ %-d\ %b\ %Y\ à\ %T)
.PHONY: default tp2 clean save

default: tp2 
tp2: tp2.cpp arbreavl.h type.h fonctor.h pile.h
	@g++ -o $@ $< $(CARGS)

clean :
	@rm -f tp2 

save:
	@git commit -q -am "$(DATE)"	



