#Lab6

all : testavl 

testavl: testavl.cpp arbreavl.h
	g++ -o testavl testavl.cpp

clean :
	rm -f testavl


