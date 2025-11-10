.SILENT: 
COMP= g++ -Wall -D DEBUG

Test1 : Test1.o Model.o
	echo "Création compilation Test1"
	$(COMP) Test1.cpp Model.o -o Test1

Model.o : Model.cpp Model.h 
	echo "Création compilation Model"
	$(COMP) Model.cpp -c

