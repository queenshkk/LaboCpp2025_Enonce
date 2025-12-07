.SILENT : 
	
COMP= g++ -Wall 

Test6: Test6.o Car.o Model.o Option.o Exception.o OptionException.o PasswordException.o Person.o Actor.o Employee.o Client.o
	echo Création compilation Test6.o
	$(COMP) Test6.cpp Car.o Model.o Option.o Exception.o OptionException.o PasswordException.o Person.o Actor.o Employee.o Client.o -o Test6

Car.o : Car.cpp Car.h 
	echo Création de compilation Car.o
	$(COMP) Car.cpp -c

Model.o : Model.cpp Model.h 
	echo Création de compilation Model.o
	$(COMP) Model.cpp -c

Option.o : Option.cpp Option.h 
	echo Création de compilation Option.o
	$(COMP) Option.cpp -c

Exception.o : Exception.cpp Exception.h 
	echo Création de compilation Exception.o 
	$(COMP) Exception.cpp -c

OptionException.o : OptionException.cpp OptionException.h 
	echo Création de compilation OptionException.o 
	$(COMP) OptionException.cpp -c

PasswordException.o : PasswordException.cpp PasswordException.h 
	echo Création de compilation PasswordException.o 
	$(COMP) PasswordException.cpp -c

Person.o : Person.cpp Person.h
	echo Création de compilation Person.o 
	$(COMP) Person.cpp -c

Actor.o : Actor.cpp Actor.h
	echo Création de compilation Actor.o
	$(COMP) Actor.cpp -c

Employee.o : Employee.cpp
	echo Création de compilation Employee.o 
	$(COMP) Employee.cpp -c 

Client.o : Client.cpp Client.h
	echo Création de compilation Client.o 
	$(COMP) Client.cpp -c

clean :
	rm -f *.o Test5

clobber : clean

