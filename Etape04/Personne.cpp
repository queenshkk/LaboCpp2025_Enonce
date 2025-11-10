#include "Personne.h"

namespace carconfig {

// ***************** Constructeurs de Personne ****************

Personne::Personne(){
	std::cout << "On est dans le constructeur par défaut (Personne)" << std::endl;

	setLastName("Nom");
	setName("Prenom");
	
}

Personne::Personne(std::string ln, std::string n){
	std::cout << "On est dans le constructeur d'initialisation (Personne)" << std::endl;

	setLastName(ln);
	setName(n);
}


Personne::Personne(const Personne &p){
	std::cout << "On est dans le constructeur de copie (Personne)" << std::endl;

	setLastName(p.getLastName());
	setName(p.getName());
}

// ***************** Destructeur de Personne ****************

Personne::~Personne(){
	std::cout << "On est dans le destructeur (Personne)" << std::endl;

} // on ne fait rien car string gère tout

// ***************** Setters de Personne ****************
void Personne::setLastName(std::strng ln){	
	lastName=ln;
}

void Personne::setName(std::strng n){	
	name=n;
}

// ***************** Getters de Personne ****************
std::string Personne::getLastName() const{
	return lastname;
}

std::string Personne::getName() const{
	return name;
}


// ***************** Méthodes d'instance de Personne ****************
void display const(){
	if(lastName!=""){
		std::cout << "Nom : " << lastName << std::endl;
	}
	else{
		std::cout << "Pas de nom" << std::endl;
	}

	if(name!=""){
		std::cout << "Prénom : " << name << std::endl;
	}
	else{
		std::cout << "Pas de prénom" << std::endl;
	}
	
}

// ***************** Surcharge d'opérateurs ****************
friend std::istream operator>>(std::istream &s, Personne p){
	std::string name, lastName;

	std::cout << "Nom : ";
	s >> lastName;
	std::cout << "Prénom";
	s >> name;

	setLastName(ln);
	setName(n);

	return s;
}

friend std::ostream operator<<(std::ostream &s, const Personne &p){
	if(p.lastName!=""){
		s << "Nom : " << p.lastName << "\n";
	}
	else{
		s << "Pas de nom" << "\n";
	}

	if(p.name!=""){
		s << "Prénom : " << p.name << "\n";
	}
	else{
		s << "Pas de prénom\n";
	}
	

	return s;
}


Personne& Personne::operator=(const Personne &p){
	if(this==&p) return (*this);

	setLastName(p.getLastName());
	setName(p.getName());

	return (*this);
}




}