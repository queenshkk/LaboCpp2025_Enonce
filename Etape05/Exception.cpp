#include "Exception.h"

Exception::Exception(){
	#ifdef DEBUG
		std::cout << "On est dans le constructeur par défaut (Exception)" << std::endl;
	#endif
	setMessage("/");
}

Exception::Exception(std::string msg){
	#ifdef DEBUG
		std::cout << "On est dans le constructeur d'initialisation (Exception)" << std::endl;
	#endif
	setMessage(msg);
}


Exception::Exception(const Exception &ex){
	#ifdef DEBUG
		std::cout << "On est dans le constructeur de copie (Exception)" << std::endl;
	#endif

	setMessage(ex.getMessage());
}

Exception::~Exception(){

}

void Exception::setMessage(std::string msg){
	message=msg;
}

std::string Exception::getMessage() const{
	return message;

}

void Exception::display() const{
	if(message!=""){
		std::cout << "Message : " << message << std::endl;
	}else{
		std::cout << "Pas de message" << std::endl;	
	}
}
