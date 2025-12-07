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

	code = c;
}

void Option::setLabel(std::string l){
	if(l==""){
		throw OptionException("L'intitulé ne peut pas être vide");
	}

	label= l;
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

	std::cout << "Prix option : " << price << std::endl;


}

// ***************** Surcharge d'opérateurs flux (<<, >>) ****************

std::istream& operator>>(std::istream& s, Option &o){ // cin >> op1
	std::string code, label, balise, prix;
	float price;

	std::getline(s, balise); // <Option>
	std::getline(s, balise); // <code>
	std::getline(s, code);
	std::getline(s, balise); // </code>
	std::getline(s, balise); // <label>
	std::getline(s, label);
	std::getline(s, balise); // </label>
	std::getline(s, balise); // <price>
	std::getline(s, prix);
	price=std::stof(prix); // pour convertir la string en float
	std::getline(s, balise); // </price>
	std::getline(s, balise); // </Option>

	o.setCode(code);
	o.setLabel(label);
	o.setPrice(price);

	return s;
}


std::ostream& operator<<(std::ostream& s,const Option &o){ // cout << op1

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

Option Option::operator--(){ // pré-incrémentation : on baisse le prix avant d'afficher l'option
	
	if(price-50 < 0.0){
		throw OptionException("Impossible, prix ne peut pas être négatif");
	}
	else{
		price = price - 50; 

	}
	
	

	return (*this);
}

Option Option::operator--(int){ // post-incrémentation : on affiche l'option puis on baisse le prix
	Option op2(*this); // on copie l'objet actuel

	if(price-50 < 0.0){
		throw OptionException("Impossible, prix ne peut pas être négatif");
	}
	else{
		price = price - 50; 

	}
	return op2;
}




}