#include "Car.h"
#include "OptionException.h"

namespace carconfig {

// ***************** Constructeurs de Car ****************
Car::Car(){
  int i;

  #ifdef DEBUG
    std::cout << "On est dans le constructeur par défaut (Car)" << std::endl;
  #endif

  setName("Nom projet");
  // pas de setmodel car Car appele directement le constructeur par défaut Model
  
  // on initialise les 5 pointeurs d'option à null
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

  #ifdef DEBUG
    std::cout << "On est dans le destructeur du Car" << std::endl;
  #endif

 for (i = 0; i < 5; ++i)
 {
  delete options[i]; // on supprime toutes les options allouées dynamiquement
  options[i] = nullptr; // on remet le pointeur à null car sinon le pointeur garde l'ancienne adresse mémoire qui n'est plus valable
 }

}

// ***************** SETTLERS de Car **************** 
void Car::setName(std::string n){ 
  name=n; 
}

void Car::setModel(Model m) { 
  // on copie champ par champ
    model.setName(m.getName());
    model.setPower(m.getPower());
    model.setEngine(m.getEngine());
    model.setBasePrice(m.getBasePrice());
    model.setImage(m.getImage());
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

  for (i=0; i<5; i++){
      if (options[i] != nullptr &&
          options[i]->getCode() == o.getCode()){
          throw OptionException("Option déja présente");
      }
  }


  for(i=0; i<5; i++){
    if(options[i]==nullptr){ // on cherche la première case libre dans la tableau
      options[i]=new Option(o); // on lui donne un pointeur vers un objet Option qu'on loue dynamiquement

      return; // on quitte quand on a ajouté une option
    }
  }

  
  throw OptionException("Impossible d'avoir plus de 5 options");

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

  throw OptionException("Option non présente");

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


void Car::save(){
  std::string fileName;
  std::fstream file;


  fileName = name + ".xml";
  file.open(fileName, std::ios::out);
  if(!file.is_open()){
      std::cout << "Erreur ouverture fichier en mode écriture" << std::endl;
      std::exit(1);
  }
  
  file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";

  file << (*this);

  file.close();
}

void Car::load(std::string projectName){
  std::string fileName, balise;
  std::fstream file;

  fileName = projectName + ".xml";

  file.open(fileName, std::ios::in);
  if(!file.is_open()){
      std::cout << "Erreur ouverture fichier en mode lecture" << std::endl;
      std::exit(1);
  }
  
  std::getline(file, balise); // en tête XML
  file >> (*this);
  file.close();
}



// ***************** Surcharges d'opérateurs (-, +, =) ****************
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
    if (c.options[i] != nullptr){ 
      options[i] = new Option(*(c.options[i])); 
    }
    else{
      options[i] = nullptr; 
    }
  }

  return (*this);
}

Car Car::operator+ (const Option &o) const{ // c3=c2+op1
  Car c2(*this); // on crée un objet temporaire à partir de l’objet courant car celui-ci ne doit pas être modifié

  c2.addOption(o);

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

std::istream &operator>>(std::istream &s, Car&c){
  std::string balise, name, model, option;
  Model m;
  Option o;
  std::streampos pos;
  int i;

  std::getline(s, balise); //"<Car>"
  std::getline(s, balise); //"<name>"
  std::getline(s, name);
  std::getline(s, balise); //"<name>"
  std::getline(s, balise); //"<model>"
  s >> m;
  std::getline(s, balise); //"</model>"
  std::getline(s, balise); //"<options>"

  for (i = 0; i < 5; ++i) // il faut d'abord supprimer les anciennes options
  {
      delete c.options[i];
      c.options[i]=nullptr;
  }

  for(i=0; i<5; i++){

    pos=s.tellg(); // on sauvegarde la position du flux
    std::getline(s, option); // on lit une ligne pour voir si on est arrivé à la fin
    if(option=="</options>"){ // si oui, on arrête car plus d'options
      break;
    }

    s.seekg(pos); // on revient avant la ligne qu'on a lu pour relire l'option correctement
    s >> o;
    c.addOption(o);
  }

  std::getline(s, balise); //"</options>"
  std::getline(s, balise); //"</Car>"

  c.setName(name);
  c.setModel(m);
  return s;
}

// ***************** Surcharge d'opérateurs flux (<<, >>) ****************
std::ostream &operator<<(std::ostream &s, const Car &c){ // cout << "Projet de Mr Dugenou :” << c1 << endl;

  int i;

  s << "<Car>\n";
  s << "<name>\n";
  s << c.name << "\n";
  s << "</name>\n";
  s << "<model>\n";  
  s << c.model;
  s << "</model>\n";  
  s << "<options>\n";

  for(i=0; i<5; i++){
    if(c.options[i]!=nullptr){
      s << *c.options[i];

    }
  }
  
  s << "</options>\n";
  s << "</Car>\n";

  return s;
}

// ***************** Opérateurs []****************
Option* Car::operator[](int i){
  return options[i];
}

}