#include "Option.h"
#include <iostream>

namespace carconfig{

// ***************** Constructeurs  ****************
Option::Option(){
	std::cout << "On est dans le constructeur par défaut (Option)" << std::endl;
	setCode("abcd");
	setLabel ("Peinture métallisée");
	setPrice(7.5);
}

Option::Option(std::string c, std::string l, float fp){
	std::cout << "On est dans le constructeur d'initialisation (Option)" << std::endl;
	setCode(c);
	setLabel(l);
	setPrice(fp);

}

Option::Option(const Option &o){
	std::cout << "On est dans le constructeur de copie (Option)" << std::endl;
	setCode(o.getCode());
	setLabel(o.getLabel());
	setPrice(o.getPrice());
}

// ***************** Destructeur  ****************
Option::~Option(){
	std::cout << "On est dans le destructeur (Option)" << std::endl;
	// rien à delete car les string gère leur propre mémoire
}

// ***************** SETTERS ****************
void Option::setCode(std::string c){
	/*if(c=="") return; // si la chaine est vide, on ne fait rien
	if(code==c) return;*/ // pas besoin de faire ça car string gère lui même

	code = c;
}

void Option::setLabel(std::string l){
	/*if(l=="") return;
	if(label==l) return;*/ // pas besoin de faire ça car string gère lui même

	label= l;
}

void Option::setPrice(float p){
	if(p<0.0) return;
	price=p;
}

// ***************** GETTERS ****************
std::string Option::getCode() const{
	return code;
}


std::string Option::getLabel() const{
	return label;
}

float 		Option::getPrice() const{
	return price;
}


// ***************** Méthodes d'instance du Modèle ****************
void Option::display() const{
	if (code!=""){
		std::cout << "Code : " << code << std::endl; 
	}
	else{
		std::cout << "Pas de code";
	}

	if (label!=""){
		std::cout << "Label : " << label << std::endl; 
	}
	else{
		std::cout << "Pas de label";
	}

	std::cout << "Prix l'option : " << price << std::endl;


}
}