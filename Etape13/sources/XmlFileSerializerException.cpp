#include "XmlFileSerializerException.h"


XmlFileSerializerException::XmlFileSerializerException():Exception("Erreur"){
	#ifdef DEBUG
		std::cout << "On est dans le constructeur par défaut (XmlFileSerializerException)" << std::endl;
	#endif

	setCode(0);
}

XmlFileSerializerException::XmlFileSerializerException(std::string msg, int c):Exception(msg){
	#ifdef DEBUG
		std::cout << "On est dans le constructeur d'initialisation (XmlFileSerializerException)" << std::endl;
	#endif

	setCode(c);
}

XmlFileSerializerException::XmlFileSerializerException(const XmlFileSerializerException &xml):Exception(xml){
	#ifdef DEBUG
		std::cout << "On est dans le constructeur de copie (XmlFileSerializerException)" << std::endl;
	#endif

	setCode(xml.getCode());
}

XmlFileSerializerException::~XmlFileSerializerException(){
	#ifdef DEBUG
		std::cout << "On est dans le destructeur (XmlFileSerializerException)" << std::endl;
	#endif
}

void XmlFileSerializerException::setCode(int c){
	code=c;
}

int XmlFileSerializerException::getCode() const{
	return code;
}

const int XmlFileSerializerException::NOT_ALLOWED=1;
const int XmlFileSerializerException::FILE_NOT_FOUND=2;
const int XmlFileSerializerException::END_OF_FILE=3;