.SILENT :

Test4 : Test4.cpp Personne.o 
	echo Création de compilation de Test4.o
	g++ Test4.cpp Personne.o -c -o Test4

Personne.o : Personne.cpp Personne.h
	echo Création de compilation Personne.o 
	g++ Personne.cpp -c

clean :
	rm -f *.o Test4

clobber:
	clean