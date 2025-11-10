#include "Car.h"

namespace carconfig {

// ***************** Constructeurs de Car ****************
Car::Car(){
  int i;
  std::cout << "On est dans le constructeur par défaut (Car)" << std::endl;
  setName("Nom projet\n");
  // pas de setmodel car Car appele directement le constructure de défaut Model

  // on initialise les 5 pointeurs à null
  for(i=0; i<5; i++){
    options[i]=nullptr;
  }
  
}

Car::Car(std::string n, Model m){
  int i;
  std::cout << "On est dans le constructeur d'initialisation (Car)" << std::endl;
  setName(n);
  setModel(m);

  for(i=0; i<5; i++){
    options[i]=nullptr;
  }
  
}

Car::Car(const Car &c){
  int i;
  std::cout << "On est dans le constructeur de copie (Car)" << std::endl;
  setName(c.getName());
  setModel(c.getModel());

  for(i=0; i<5; i++){
    if (c.options[i] != nullptr){ //Si le pointeur vers une option pointe vers qqch
      options[i] = new Option(*(c.options[i])); // on crée une copie des options
    }
    else{
      options[i] = nullptr; // sinon on met le pointeur à nullptr
    }
  }
  
}

// ***************** Destructeurs de Car ****************
Car::~Car(){
  int i;
  std::cout << "On est dans le destructeur du Car" << std::endl;

 for (i = 0; i < 5; ++i)
 {
  delete options[i]; // on supprime toutes les options allouées dynamiquement
  options[i] = nullptr; // on remet le pointeur à null car sinon le pointeur garde l'ancienne adresse mémoire qui n'est plus valable
 }

}

// ***************** SETTLERS de Car **************** 
void Car::setName(std::string n){ // pour changer le nom du projet de la voiture
  /*if (n=="") return; // si la chaîne est vide, on ne fait rien
  if (name==n) return; // si n est pareil que name, on ne fait rien*/ // // pas besoin de faire ça car string gère lui même

  name=n; // sinon une copie la chaîne n dans name
}

void Car::setModel(Model m) { // pour mettre à jour le modèle de la voiture à partir d'un autre Model
  // on copie champ par champ
    model.setName(m.getName());
    model.setPower(m.getPower());
    model.setEngine(m.getEngine());
    model.setBasePrice(m.getBasePrice());
}

// ***************** GETTERS de Car ****************
std::string Car::getName() const{
    return name;
}

Model Car::getModel() const {
    return model;
}

// ***************** //
void Car::addOption(const Option &o){
  int i;
  for(i=0; i<5; i++){
    if(options[i]==nullptr){ // on cherche la première case libre dans la tableau
      options[i]=new Option(o); // on lui donne un pointeur vers un objet Option qu'on loue dynamiquement
      return; // on quitte quand on a ajouté une option
    }
  }
}

void Car::removeOption(std::string code){
  int i;

  for(i=0; i<5; i++){
    if(options[i]!=nullptr && options[i]->getCode()==code){ // si on trouve une option qui n'est pas nulle et dont le code correspond
      delete options[i]; // on supprime cette option
      options[i]=nullptr; // on remet le pointeur à null
      return; // on quitte après avoir supprimé
    }

  }
}

float Car::getPrice() const{ // calcule le prix total de la voiture
  int i;
  float somme;

  somme=model.getBasePrice(); // prix de base du modèle

  for(i=0; i<5; i++){
    if(options[i]!=nullptr){ // si l'option pointe vers qqch
      somme=somme+options[i]->getPrice(); // on fait la somme des prix de tous les potions
    }
  }


  return somme;
}

// ***************** Méthodes d'instance de Car ****************
void Car::display() const{
  int i;


  if(name!=""){ 
      std::cout << "Projet Car : " << name << std::endl;
  }
  else{
    std::cout << "Pas de nom " << std::endl;
  }

  std::cout << "Modèle : ";
  model.display();

  std::cout << "Option : " << std::endl;

  for(i=0; i<5; i++){
    if(options[i]!=nullptr)
    options[i]->display();
  }
}



// ***************** Opérateurs de surcharge (-, +, =) ****************
Car& Car::operator=(const Car &c){ // c1=c2
  int i;

  if(this==&c) return (*this);

  for(i=0; i<5; i++){ // on doit libérer les options
    delete options[i];
    options[i]=nullptr;
    
  }

  setName(c.getName());
  setModel(c.getModel());

  
  for(i=0; i<5; i++){ // on copie les options
    if (c.options[i] != nullptr){ // Si le pointeur vers une option pointe vers qqch
      options[i] = new Option(*(c.options[i])); // on crée une copie des options
    }
    else{
      options[i] = nullptr; // sinon on met le pointeur à nullptr
    }
  }

  return (*this);
}

Car Car::operator+ (const Option &o) const{ // c3=c2+op1
  Car c2(*this); // on crée un objet temporaire à partir de l’objet courant car celui-ci ne doit pas être modifié

  c2.addOption(o); // on ajoute une option (allouée dynamiquement)

  return c2;
}

Car operator+ (const Option &o, const Car &c){ // c3=op2 + c3
  Car c3(c); // on appelle le constructeur de copie d'un objet Car passé en paramètre
  c3.addOption(o);
  return c3;
}

Car Car::operator- (const Option &o) const{ // c3=c3-op1
  Car c3(*this);
  c3.removeOption(o.getCode());

  return c3;
}


Car Car::operator- (std::string code) const{ // c3=c3- "ZH75"
  Car c3(*this);
  c3.removeOption(code);
  return c3;
}


// ***************** Opérateurs de surcharge comparaison (<, >, ==) ****************
int Car::operator<(const Car& c) const
{
  return compC(c)==-1;
}

int Car::operator>(const Car& c) const
{
  return compC(c)==1;
}

int Car::operator==(const Car& c) const
{
  return compC(c)==0;
}

int Car::compC(const Car& c) const
{
  if(getPrice()<c.getPrice())
  {
    return -1;
  }

  if(getPrice()>c.getPrice())
  {
    return 1;
  }
  

  return 0;

}

// ***************** Opérateurs de surcharge flux (<<, >>) ****************
std::ostream &operator<<(std::ostream &s, const Car &c){ // cout << "Projet de Mr Dugenou :” << c1 << endl;

  int i;

  if(c.name!=""){ 
      s << "Projet Car : " << c.name << "\n";
  }
  else{
    s << "Pas de nom " << "\n";
  }

  s << "Modèle : " << c.model << "\n";
  

  s << "Options : " << "\n";

  for(i=0; i<5; i++){
    if(c.options[i]!=nullptr)
      s << *(c.options[i]);
  }


  return s;
}

// ***************** Opérateurs []****************
Option* Car::operator[](int i){
  return options[i];
}

}