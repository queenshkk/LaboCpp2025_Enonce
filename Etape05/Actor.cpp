#include "Actor.h"

//namespace carconfig {


// ***************** Constructeurs Actor ****************
Actor::Actor():Person(){
	#ifdef DEBUG
		std::cout << "On est dans le constructeur par défaut (Actor)" << std::endl;
	#endif
	setId(0);
}

Actor::Actor(std::string ln, std::string fn, int i_d):Person(ln, fn){
	#ifdef DEBUG
		std::cout << "On est dans le constructeur d'initialisation (Actor)" << std::endl;
	#endif
	setId(i_d);
}

Actor::Actor(const Actor &a):Person(a){
	#ifdef DEBUG
		std::cout << "On est dans le constructeur de copie (Actor)" << std::endl;
	#endif
	setId(a.getId());
}

// ***************** Destructeur Actor ****************
Actor::~Actor(){
	#ifdef DEBUG
		std::cout << "On est dans le destructeur (Actor)" << std::endl;
	#endif

}

// ***************** Setters Actor ****************
void Actor::setId(const int i_d){
	if(i_d<0) return;

	id=i_d;
	
}


// ***************** Getters Actor ****************
int Actor::getId() const{
	return id;
}

// ***************** Méthodes d'instance Actor ****************
void Actor::display() const{

	Person::display();

	std::cout << "Id : " << id << std::endl;

}




// ***************** Opérateurs de surcharge ****************

Actor& Actor::operator=(const Actor &a){
	if(this==&a) return (*this);

	Person::operator=(a);
	setId(a.getId());
	
	return(*this);

}

//}


