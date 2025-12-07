.SILENT :

COMP= g++ -Wall 

Test4 : Test4.o Person.o Actor.o Client.o Employee.o 
	echo Création de compilation de Test4.o
	$(COMP) Test4.cpp Person.o Actor.o Client.o Employee.o -o Test4

Person.o : Person.cpp Person.h
	echo Création de compilation Person.o 
	$(COMP) Person.cpp -c

Actor.o : Actor.cpp Actor.h
	echo Création de compilation Actor.o 
	$(COMP) Actor.cpp -c

Client.o : Client.cpp Client.h
	echo Création de compilation Client.o 
	$(COMP) Client.cpp -c

Employee.o : Employee.cpp Employee.h
	echo Création de compilation Employee.o 
	$(COMP) Employee.cpp -c
	
clean :
	rm -f *.o Test4

clobber:
	clean
