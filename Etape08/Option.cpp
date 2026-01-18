#include "Option.h"
#include "OptionException.h"

#include <iostream>

namespace carconfig{

// ***************** Constructeurs  ****************
Option::Option(){
	#ifdef DEBUG
		std::cout << "On est dans le constructeur par défaut (Option)" << std::endl;
	#endif

	setCode("abcd");
	setLabel ("Peinture métallisée");
	setPrice(7.5);
}

Option::Option(std::string c, std::string l, float fp){
	#ifdef DEBUG
		std::cout << "On est dans le constructeur d'initialisation (Option)" << std::endl;
	#endif

	setCode(c);
	setLabel(l);
	setPrice(fp);

}

Option::Option(const Option &o){
	#ifdef DEBUG
		std::cout << "On est dans le constructeur de copie (Option)" << std::endl;
	#endif

	setCode(o.getCode());
	setLabel(o.getLabel());
	setPrice(o.getPrice());
}

// ***************** Destructeur  ****************
Option::~Option(){
	#ifdef DEBUG
		std::cout << "On est dans le destructeur (Option)" << std::endl;
	#endif
}

// ***************** SETTERS ****************
void Option::setCode(std::string c){
	
	if(c.size()!=4){
		throw OptionException("Le code doit comporter 4 caractères");
	}

	code=c;
}

void Option::setLabel(std::string l){
	if(l==""){
		throw OptionException("L'intitulé ne peut pas être vide");
	}

	label=l;
}

void Option::setPrice(float p){
	if(p<=0.0){
		throw OptionException("Le prix doit être positif");
	}

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
	if(code!=""){
		std::cout << "Code : " << code << std::endl; 

	}
	else{
		std::cout << "Pas de code";
	}

	if(label!=""){
		std::cout << "Label : " << label << std::endl; 
	}
	else{
		std::cout << "Pas de label";
	}

	std::cout << "Prix option : " << price << std::endl;


}

// ***************** Surcharge d'opérateurs flux (<<, >>) ****************

std::istream& operator>>(std::istream& s, Option &o){ 
	std::string code, label, balise, prix;
	float price;

	std::getline(s, balise); 
	std::getline(s, balise); 
	std::getline(s, code);
	std::getline(s, balise); 
	std::getline(s, balise); 
	std::getline(s, label);
	std::getline(s, balise); 
	std::getline(s, balise); 
	std::getline(s, prix);
	price=std::stof(prix);
	std::getline(s, balise); 
	std::getline(s, balise); 

	o.setCode(code);
	o.setLabel(label);
	o.setPrice(price);

	return s;
}


std::ostream& operator<<(std::ostream& s,const Option &o){ 

	s << "<Option>\n";


    s << "<code>\n";
    s << o.code << "\n";
    s << "</code>\n";

    s << "<label>\n";
    s << o.label << "\n";
    s << "</label>\n";

    s << "<price>\n";
    s << o.price << "\n";
    s << "</price>\n";

    s << "</Option>\n";

    return s;

} 

// ***************** Surcharge d'opérateurs de pré/post-incrémentation (++, --) ****************

Option Option::operator--(){ 
	if(price-50<0.0){
		throw OptionException("Impossible, prix ne peut pas être négatif");
	}
	else{
		price=price-50; 

	}
	
	

	return (*this);
}

Option Option::operator--(int){ 
	Option op2(*this); 

	if(price-50<0.0){
		throw OptionException("Impossible, prix ne peut pas être négatif");
	}
	else{
		price=price-50; 

	}
	return op2;
}


std::string Option::toString() const {
    return getCode() + " " + getLabel() + " " + std::to_string(getPrice());
}

}