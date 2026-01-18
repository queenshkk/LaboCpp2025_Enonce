#include "Employee.h"
#include "PasswordException.h"


// ***************** Constructeurs Employee ****************
Employee::Employee():Actor(){
	#ifdef DEBUG
		std::cout << "On est dans le constructeur par défaut (Employee)" << std::endl;
	#endif

	password=nullptr;

	setLogin("/");
	setRole("/");

}

Employee::Employee(std::string ln, std::string fn, std::string log, std::string r):Actor(ln, fn){
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
	
	password=nullptr;

	setLogin(e.getLogin());
	setRole(e.getRole());


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
    password = nullptr;
}

// ***************** Setters Employee ****************
void Employee::setLogin(const std::string log){
	login=log;
}

void Employee::setPassword(const std::string mdp){
	delete password;  
	int i,lettre=0, chiffre=0, taille;
	taille=mdp.length();

	if(taille<6){
		throw PasswordException("Erreur mdp", 1);
	}

	for(i=0;i<taille; i++){
		if((mdp[i] >= 'A' && mdp[i] <= 'Z') || (mdp[i] >= 'a' && mdp[i] <= 'z')){
			lettre++;
		}
        
    if(mdp[i] >= '0' && mdp[i] <= '9'){
    	chiffre++;
    }
	}

	if(lettre==0){
		throw PasswordException("Erreur mdp", 2);
	}

	if(chiffre==0){
		throw PasswordException("Erreur mdp", 3);
	}

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
		throw PasswordException("Erreur mdp", 4);
	}
}

std::string Employee::getRole() const{
	return role;
}

void Employee::resetPassword()
{
    delete password;
    password = nullptr;
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
	password = nullptr;

	if(e.password){
		password = new std::string(*e.password);     
	}

	return (*this);
}

std::ostream& operator<<(std::ostream&s, const Employee&e){
	s << "Nom : " << e.getLastName() << "\n";
  s << "Prénom : " << e.getFirstName() << "\n";
  s << "Id : " << e.getId() << "\n";
  if (e.password!=nullptr){
  	s << "Password : " << *(e.password) << "\n";
  }
	else{
    	s << "Pas de mdp\n";

	}
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

const std::string Employee::ADMINISTRATIVE = "Administratif";
const std::string Employee::SELLER = "Vendeur";

int Employee::operator<(const Employee& c) const
{
  return compC(c)==-1;
}

int Employee::compC(const Employee& c) const
{
  if(getId()<c.getId())
  {
    return -1;
  }

  if(getId()>c.getId())
  {
    return 1;
  }
  

  return 0;

}