#include "Car.h"

namespace carconfig {

// ***************** Constructeurs de Car ****************
Car::Car(){
  int i;

  #ifdef DEBUG
    std::cout << "On est dans le constructeur par défaut (Car)" << std::endl;
  #endif

  setName("Nom projet\n");
  
  for(i=0; i<5; i++){
    options[i]=nullptr;
  }
  
}

Car::Car(std::string n, Model m){
  int i;

  #ifdef DEBUG
    std::cout << "On est dans le constructeur d'initialisation (Car)" << std::endl;
  #endif

  setName(n);
  setModel(m);

  for(i=0; i<5; i++){
    options[i]=nullptr;
  }
  
}

Car::Car(const Car &c){
  int i;

  #ifdef DEBUG
    std::cout << "On est dans le constructeur de copie (Car)" << std::endl;
  #endif

  setName(c.getName());
  setModel(c.getModel());

  for(i=0; i<5; i++){
    if (c.options[i] != nullptr){ 
      options[i] = new Option(*(c.options[i])); 
    }
    else{
      options[i] = nullptr; 
    }
  }
  
}

// ***************** Destructeurs de Car ****************
Car::~Car(){
  int i;

  #ifdef DEBUG
    std::cout << "On est dans le destructeur du Car" << std::endl;
  #endif

 for(i=0;i<5;i++)
 {
  delete options[i]; 
  options[i]=nullptr; 
 }

}

// ***************** SETTLERS de Car **************** 
void Car::setName(std::string n){ 
  name=n; 
}

void Car::setModel(Model m) { 
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
    if(options[i]==nullptr){ 
      options[i]=new Option(o); 
      return; 
    }
  }
}

void Car::removeOption(std::string code){
  int i;

  for(i=0; i<5; i++){
    if(options[i]!=nullptr && options[i]->getCode()==code){
      delete options[i]; 
      options[i]=nullptr; 
      return; 
    }
  }
}

float Car::getPrice() const{
  int i;
  float somme;

  somme=model.getBasePrice();

  for(i=0; i<5; i++){
    if(options[i]!=nullptr){ 
      somme=somme+options[i]->getPrice();
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



// ***************** Surcharges d'opérateurs (-, +, =) ****************
Car& Car::operator=(const Car &c){
  int i;

  if(this==&c) return (*this);

  for(i=0; i<5; i++){ 
    delete options[i];
    options[i]=nullptr;
  }

  setName(c.getName());
  setModel(c.getModel());


  for(i=0; i<5; i++){
    if(c.options[i]!= nullptr){ 
      options[i]=new Option(*(c.options[i])); 
    }
    else{
      options[i] = nullptr; 
    }
  }

  return (*this);
}

Car Car::operator+ (const Option &o) const{
  Car c2(*this); 

  c2.addOption(o);

  return c2;
}

Car operator+ (const Option &o, const Car &c){
  Car c3(c);
  c3.addOption(o);

  return c3;
}

Car Car::operator- (const Option &o) const{
  Car c3(*this);
  c3.removeOption(o.getCode());

  return c3;
}


Car Car::operator- (std::string code) const{ 
  Car c3(*this);
  c3.removeOption(code);
  return c3;
}


// ***************** Surcharge d'opérateurs comparaison (<, >, ==) ****************
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

// ***************** Surcharge d'opérateurs flux (<<, >>) ****************
std::ostream &operator<<(std::ostream &s, const Car &c){

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
    if(c.options[i]!=nullptr){
      s << *(c.options[i]);
    }
  }

  return s;
}

// ***************** Opérateurs []****************
Option* Car::operator[](int i){
  return options[i];
}

}