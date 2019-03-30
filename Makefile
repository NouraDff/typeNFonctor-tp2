# Makefile

CARGS= -std=c++11 
DATE = $(shell date +Modif:\ %a\ %-d\ %b\ %Y\ à\ %T)
.PHONY: default tp2 clean save

default: tp2 
tp2: tp2.cpp arbreavl.h type.h foncteur.h pile.h
	@g++ -o $@ $< $(CARGS)

clean :
	@rm -f tp2 

save:
	@git commit -q -am "$(DATE)"	



