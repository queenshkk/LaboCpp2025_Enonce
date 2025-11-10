.SILENT : 

COMP= g++ -Wall -D DEBUG

all : Test2a Test2b Test2c
	
Test2a : Test2a.o Car.o Model.o Option.o
	echo Création compilation Test2a.o
	$(COMP) Test2a.cpp Car.o Model.o Option.o -o Test2a -D DEBUG


Test2b : Test2b.o Car.o Model.o Car.o Option.o
	echo Création de compilation Test2b.o
	$(COMP) Test2b.cpp Car.o Model.o Option.o -o Test2b -D DEBUG

Test2c : Test2c.o Car.o Model.o Car.o Option.o 
	echo Création de compilation Test2c.o
	$(COMP) Test2c.cpp Car.o Model.o Option.o -o Test2c -D DEBUG

Car.o : Car.cpp Car.h 
	echo Création de compilation Car.o
	$(COMP) Car.cpp -c 

Model.o : Model.cpp Model.h 
	echo Création de compilation Model.o
	$(COMP) Model.cpp -c 

Option.o : Option.h Option.cpp
	echo Création de compilation Option.o
	$(COMP) Option.cpp -c 

clean :
	rm -f *.o Test2a Test2b Test2c

clobber : clean

