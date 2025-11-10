.SILENT : 
	
COMP= g++ -Wall -D DEBUG

Test3 : Test3.o Car.o Model.o Option.o
	echo Création compilation Test3.o
	$(COMP) Test3.cpp Car.o Model.o Option.o -o Test3

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
	rm -f *.o Test3

clobber : clean

