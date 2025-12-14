#include "PasswordException.h"


PasswordException::PasswordException():Exception("Erreur mdp\n"){
	#ifdef DEBUG
		std::cout << "On est dans le constructeur par défaut (PasswordException)" << std::endl;
	#endif

	setCode(0);
}

PasswordException::PasswordException(std::string msg, int c):Exception(msg){
	#ifdef DEBUG
		std::cout << "On est dans le constructeur d'initilisation (PasswordException)" << std::endl;
	#endif

	setCode(c);

}

PasswordException::PasswordException(const PasswordException &pe):Exception(pe){
	#ifdef DEBUG
		std::cout << "On est dans le constructeur d'initilisation (PasswordException)" << std::endl;
	#endif

	setCode(pe.getCode());
}

PasswordException::~PasswordException() noexcept{
	#ifdef DEBUG
		std::cout << "On est dans le destructeur (PasswordException)" << std::endl;
	#endif
}

void PasswordException::setCode(int c) noexcept{
	
	code=c;
}

int PasswordException::getCode() const noexcept{
	return code;
}

void PasswordException::display() const{

    Exception::display();

	switch(code)
  	{
	    case 1:
	        std::cout << "Taille du mdp doit être supérieur à 6" ;
	      break;
	    case 2:
	        std::cout << "Le mdp doit contenir une lettre";
	      break;
	    case 3:
	        std::cout << "Le mdp doit contenir un chiffre";
	      break;
	    case 4:
	        std::cout << "Pas de mdp entré";
	      break;
  	}

}
