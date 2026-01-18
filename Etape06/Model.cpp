#include "Model.h"
#include <cstring> 

namespace carconfig{

// ***************** Constructeurs du Modèle ****************
Model::Model()
{
  #ifdef DEBUG
    std::cout << "On est dans le constructeur par défaut (Model)" << std::endl;
  #endif

  name=NULL; 

  setName("/");
  setPower(0);
  setEngine(Engine::Petrol);
  setBasePrice(0.0);
}

Model::Model(const  char*n, int p, Engine e, float bp)
{
  #ifdef DEBUG
    std::cout << "On est dans le constructeur d'initialisation (Model)" << std::endl;
  #endif

  name=NULL;

  setName(n);
  setPower(p);
  setEngine(e);
  setBasePrice(bp);
}

Model::Model(const Model &m){ 
    #ifdef DEBUG
      std::cout << ">>> On est dans le constructeur de copie (Model)" << std::endl;
    #endif

    name=NULL;

    setName(m.getName());
    setPower(m.getPower());
    setEngine(m.getEngine());
    setBasePrice(m.getBasePrice());
}


// ***************** Destructeur du Modèle ****************
Model::~Model()
{
  #ifdef DEBUG
    std::cout << "On est dans le destructeur (Model)" << std::endl;
  #endif

  if(name) delete [] name;
}




// ***************** SETTLERS du Modèle****************
void Model::setName(const char *n){ 
  if (n==NULL) return; 
  if (name==n) return;
  if (name) delete [] name; 

  name=new char[strlen(n)+1]; 
  strcpy(name, n); 
}

void Model::setPower(int p){
  if(p<0) return;
  power=p; 
}

void Model::setEngine(Engine e){
  engine=e; 
}

void Model::setBasePrice(float bp){
  if(bp<0.0) return;
  basePrice=bp;
}


// ***************** GETTERS du Modèle ****************
const char* Model::getName() const{
  return name;
}

int Model::getPower() const{
  return power;
}

Engine   Model::getEngine() const{
  return engine;
}

float Model::getBasePrice() const{
  return basePrice;
}



// ***************** Méthodes d'instance du Modèle ****************
void Model::display() const
{
  std::cout << "Model : ";
  if(name){
    std::cout << name;
  }
  else{
    std::cout << "Pas de nom ";
   
  }
    
  std::cout << "( " << power << " Ch, ";
   
  switch(engine)
  {
    case Engine::Petrol:
        std::cout << "Essence, " ;
      break;
    case Engine::Diesel:
        std::cout << "Diesel, ";
      break;
    case Engine::Electric:
        std::cout << "Electrique, ";
      break;
    case Engine::Hybrid:
        std::cout << "Hybride ";
      break;
  }

  std::cout << basePrice << " euro)" << std::endl;
}

// ***************** Surcharge d'opérateurs flux (<<, >>) ****************

std::istream& operator>>(std::istream& s,Model &m){ 
  std::string balise, name, puissance, engine, price;
  int power;
  float basePrice;
  Engine e;

  std::getline(s, balise); 

  std::getline(s, balise); 
  std::getline(s, name);
  std::getline(s, balise); 


  std::getline(s, balise); 
  std::getline(s, puissance);
  power=std::stoi(puissance);
  std::getline(s, balise); 

  std::getline(s, balise); 
  std::getline(s, engine);
  if(engine=="essence"){
    e=Petrol;
  }else if(engine=="diesel"){
    e=Diesel;
  }else if(engine=="electrique"){
    e=Electric;
  }else{
    e=Hybrid;
  }
  std::getline(s, balise); 

  std::getline(s, balise); 
  std::getline(s, price);
  basePrice=std::stof(price);
  std::getline(s, balise); 


  std::getline(s, balise); 

  m.setName(name.c_str()); 
  m.setPower(power);
  m.setEngine(e);
  m.setBasePrice(basePrice);

  return s;
} 


std::ostream& operator<<(std::ostream& s, const Model &m){ 
  s << "<Model>\n";

  s << "<name>\n";
  s << m.name << "\n";
  s << "</name>\n";


  s << "<power>\n";
  s << m.power << "\n";
  s << "</power>\n";

  s << "<engine>\n";
  switch(m.engine)
  {
    case Petrol:
      s << "essence\n" ;
      break;
    case Diesel:
      s << "diesel\n";
      break;
    case Electric:
      s << "electrique\n";
      break;
    case Hybrid:
      s << "hybride\n";
      break;
  }
  s << "</engine>\n";

  s << "<basePrice>\n";

  s << m.basePrice << "\n";
  s << "</basePrice>\n";

  s << "</Model>\n";
  return s;
} 

std::string Model::toString() const{
  std::string moteur;

  switch (getEngine()){
    case Petrol:
      moteur = "Essence";
      break;
    case Diesel:
      moteur = "Diesel";
      break;
    case Electric:
      moteur = "Electrique";
      break;
    case Hybrid:
      moteur = "Hybride";
      break;
  }

  return std::string(getName()) + " " + std::to_string(getPower()) + " " + moteur + " " + std::to_string(getBasePrice());
}

}