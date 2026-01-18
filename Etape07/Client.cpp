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


std::istream& operator>>(std::istream& s, Client &c){
	std::string balise, ln, fn, i_d, gsm;
	int id;

	s >> balise; 
	s >> balise; 
	s >> ln;
	s >> balise; 
	s >> balise; 
	s >> fn;
	s >> balise; 
	s >> balise; 
	s >> i_d;
	id=std::stoi(i_d);
	s >> balise; 
	s >> balise; 
	s >> gsm;
	s >> balise; 
	s >> balise; 

	c.setLastName(ln);
	c.setFirstName(fn);
	c.setId(id);
	c.setGsm(gsm);

	return s;

}


std::ostream& operator<<(std::ostream& s, const Client &c){
	
    s << "<Client>\n";
    s << "<lastName>\n";
    s << c.lastName << "\n";
    s << "</lastName>\n";
    s << "<firstName>\n";
    s << c.firstName << "\n";
    s << "</firstName>\n";
    s << "<id>\n";
    s << c.getId() << "\n";
    s << "</id>\n";
    s << "<gsm>\n";
    s << c.getGsm() << "\n";
    s << "</gsm>\n";
    s << "</Client>\n";

	return s;
}

std::string Client::tuple() const {
    return std::to_string(getId()) + ";" + getLastName() + ";" + getFirstName() + ";" + gsm;
}

std::string Client::toString() const {
    return "[C" + std::to_string(getId()) + "]" + getLastName() + " " + getFirstName() + " " + std::to_string(getId()) + " " + getGsm();
}
