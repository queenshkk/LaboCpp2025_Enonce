#include "Person.h"


// ***************** Constructeurs de Personne ****************

Person::Person(){
	#ifdef DEBUG
		std::cout << "On est dans le constructeur par défaut (Personne)" << std::endl;
	#endif

	setLastName("/");
	setFirstName("/");
	
}

Person::Person(std::string ln, std::string fn){
	#ifdef DEBUG
		std::cout << "On est dans le constructeur d'initialisation (Personne)" << std::endl;
	#endif

	setLastName(ln);
	setFirstName(fn);
}


Person::Person(const Person &p){
	#ifdef DEBUG
		std::cout << "On est dans le constructeur de copie (Personne)" << std::endl;
	#endif

	setLastName(p.getLastName());
	setFirstName(p.getFirstName());
}

// ***************** Destructeur de Personne ****************

Person::~Person(){
	#ifdef DEBUG
	std::cout << "On est dans le destructeur (Personne)" << std::endl;
	#endif

} 

// ***************** Setters de Personne ****************
void Person::setLastName(std::string ln){	
	lastName=ln;
}

void Person::setFirstName(std::string fn){	
	firstName=fn;
}

// ***************** Getters de Personne ****************
std::string Person::getLastName() const{
	return lastName;
}

std::string Person::getFirstName() const{
	return firstName;
}


// ***************** Méthodes d'instance de Personne ****************
void Person::display()const{
	if(lastName!=""){
		std::cout << "Nom : " << lastName << std::endl;
	}
	else{
		std::cout << "Pas de nom" << std::endl;
	}

	if(firstName!=""){
		std::cout << "Prénom : " << firstName << std::endl;
	}
	else{
		std::cout << "Pas de prénom" << std::endl;
	}
	
}

// ***************** Surcharge d'opérateurs ****************
std::istream& operator>>(std::istream &s, Person &p){
	
	std::string firstName, lastName;
	
	std::cout << "Nom : ";
	getline(s, lastName);

	std::cout << "Prénom : ";
	getline(s, firstName);

	p.setLastName(lastName);
	p.setFirstName(firstName);

	return s;
}

std::ostream& operator<<(std::ostream &s, const Person &p){
	if(p.lastName!=""){
		s << "Nom : " << p.lastName << "\n";
	}
	else{
		s << "Pas de nom" << "\n";
	}

	if(p.firstName!=""){
		s << "Prénom : " << p.firstName << "\n";
	}
	else{
		s << "Pas de prénom\n";
	}
	

	return s;
}


Person& Person::operator=(const Person &p){
	if(this==&p) return (*this);
	
	setLastName(p.getLastName());
	setFirstName(p.getFirstName());



	return (*this);
}
