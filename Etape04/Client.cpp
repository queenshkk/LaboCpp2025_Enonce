#include "Client.h"


// ***************** Constructeurs Client ****************
Client::Client():Actor(){
	#ifdef DEBUG
		std::cout << "On est dans le constructeur par défaut (Client)" << std::endl;
	#endif
	setGsm("/");
}

Client::Client(std::string ln, std::string fn, int i_d, std::string numtel):Actor(ln, fn, i_d){
	#ifdef DEBUG
		std::cout << "On est dans le constructeur d'initialisation (Client)" << std::endl;
	#endif
	setGsm(numtel);
}

Client::Client(const Client &c):Actor(c){
	#ifdef DEBUG
		std::cout << "On est dans le constructeur de copie (Client)" << std::endl;
	#endif
	setGsm(c.getGsm());
}

// ***************** Destructeur Client ****************
Client::~Client(){
	#ifdef DEBUG
		std::cout << "On est dans le destructeur (Client)" << std::endl;
	#endif

}

// ***************** Setters Client ****************
void Client::setGsm(const std::string numtel){
	gsm=numtel;
}


// ***************** Getters Client ****************
std::string Client::getGsm() const{
	return gsm;
}

// ***************** Méthodes d'instance Client ****************
void Client::display() const{
	Actor::display();
	std::cout << "Gsm : " << gsm << std::endl;
}




// ***************** Opérateurs de surcharge ****************
Client& Client::operator=(const Client &c){
	if(this==&c) return (*this);

	Actor::operator=(c);
	setGsm(c.getGsm());
	
	return (*this);
}

std::ostream& operator<<(std::ostream& s, const Client &c){
	
    s << "Nom : " << c.getLastName() << "\n";
    s << "Prénom : " << c.getFirstName() << "\n";
    s << "Id : " << c.getId() << "\n";
    s << "Gsm : " << c.gsm << "\n";
	
	return s;
}

std::string Client::tuple() const {
    return std::to_string(getId()) + ";" + getLastName() + ";" + getFirstName() + ";" + gsm;
}

std::string Client::toString() const {
    return "[C" + std::to_string(getId()) + "]" + getLastName() + " " + getFirstName() + " ";
}

