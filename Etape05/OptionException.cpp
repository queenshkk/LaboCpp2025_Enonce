#include "OptionException.h"

	
OptionException::OptionException():Exception("Erreur option"){
	#ifdef DEBUG
		std::cout << "On est dans le constructeur par défaut (OptionException)" << std::endl;
	#endif
}

OptionException::OptionException(std:: string msg):Exception(msg){
	#ifdef DEBUG
		std::cout << "On est dans le constructeur d'initialisation (OptionException)" << std::endl;
	#endif
}

OptionException::OptionException(const OptionException &oe):Exception(oe){
	#ifdef DEBUG
		std::cout << "On est dans le constructeur de copie (OptionException)" << std::endl;
	#endif

}


OptionException::~OptionException(){
	#ifdef DEBUG
		std::cout << "On est dans le destructeur (OptionException)" << std::endl;
	#endif
}

	




