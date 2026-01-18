#include "Employee.h"


// ***************** Constructeurs Employee ****************
Employee::Employee():Actor(){
	#ifdef DEBUG
		std::cout << "On est dans le constructeur par défaut (Employee)" << std::endl;
	#endif

	password=nullptr;

	setLogin("/");
	setRole("/");
}

Employee::Employee(std::string ln, std::string fn, int i_d, std::string log, std::string r):Actor(ln, fn, i_d){
	#ifdef DEBUG
		std::cout << "On est dans le constructeur d'initialisation (Employee)" << std::endl;
	#endif

	password=nullptr;

	setLogin(log);
	setRole(r);
}

Employee::Employee(const Employee &e):Actor(e){
	#ifdef DEBUG
		std::cout << "On est dans le constructeur de copie (Employee)" << std::endl;
	#endif

	setLogin(e.getLogin());
	setRole(e.getRole());

	delete password;
	password=nullptr;

	if(e.password){
		password=new std::string(*e.password);
	}

}

// ***************** Destructeur Employee ****************
Employee::~Employee(){
	#ifdef DEBUG
		std::cout << "On est dans le destructeur (Employee)" << std::endl;
	#endif

	delete password;
    password=nullptr;
}

// ***************** Setters Employee ****************
void Employee::setLogin(const std::string log){
	login=log;
}

void Employee::setPassword(const std::string mdp){
	delete password;  
	password=new std::string(mdp);
}

void Employee::setRole(const std::string r){
	role=r;
}


// ***************** Getters Employee ****************
std::string Employee::getLogin() const{
	return login;
}

std::string Employee::getPassword() const{
	if(password!=nullptr){ 
		return *password; 
	}
	else{
		return "";
	}
}

std::string Employee::getRole() const{
	return role;
}

void Employee::resetPassword()
{
    delete password;
    password=nullptr;
}

// ***************** Méthodes d'instance Employee ****************
void Employee::display() const{
	Actor::display();
	std::cout << "Login : " << login << std::endl;
	std::cout << "Role : " << role << std::endl;
}


// ***************** Opérateurs de surcharge ****************
Employee& Employee::operator=(const Employee&e){
	if(this==&e) return (*this);

	Actor::operator=(e);
	setLogin(e.getLogin());
	setRole(e.getRole());

	delete password;
	password=nullptr;

	if(e.password){
		password=new std::string(*e.password);     
	}

	return (*this);
}

std::ostream& operator<<(std::ostream&s, const Employee&e){
	s << "Nom : " << e.getLastName() << "\n";
    s << "Prénom : " << e.getFirstName() << "\n";
    s << "Id : " << e.getId() << "\n";
    s << "Password : " << e.getPassword() << "\n";
	s << "Login : " << e.login << "\n";
	s << "Role : " << e.role << "\n";

	return s;
}

std::string Employee::tuple() const {
     return std::to_string(getId()) + ";" + getLastName() + ";" + getFirstName() + ";" + role;
	
}

std::string Employee::toString() const {
    if(role=="Vendeur" || role=="vendeur"){
		return "[V" + std::to_string(getId()) + "] " + getLastName() + " " + getFirstName();
	}
	else{
		return "[A" + std::to_string(getId()) + "] " + getLastName() + " " + getFirstName();
	}
}

const std::string Employee::ADMINISTRATIVE="Administratif";
const std::string Employee::SELLER="Vendeur";

