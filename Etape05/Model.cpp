#include "Model.h"
#include <cstring> 

namespace carconfig{

// ***************** Constructeurs du Modèle ****************
Model::Model()
{
  #ifdef DEBUG
    std::cout << "On est dans le constructeur par défaut (Model)" << std::endl;
  #endif

  name=NULL; // initialiser le pointeur à "pas d'adresses"

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

  if(name) delete [] name; // on vérifie que le pointeur de name n'est pas nul et on libère la mếmoire, on supprime le tableau de char
  // les int, float ne réservent rien en mémoire donc rien à libérer
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
  if (bp<0.0) return;
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

std::istream& operator>>(std::istream& s,Model &m){ // cin >> m

  char name[30]; // on remet des variables car les variables de la classe sont en private donc pas accès pour les modifier 
  int power;
  int engine;
  float basePrice;

  std::cout << "Nom : ";
  s.getline(name, 30);

  std::cout << "Puissance : ";
  s >> power;

  std::cout << "Engin (1 = Essence, 2 = Diesel, 3 = Electrique, 4 = Hybride) : ";
  s >> engine;

  std::cout << "Prix : ";
  s >> basePrice;

  m.setName(name); // on transmet ce que l'utilisateur a saisi par des setters
  m.setPower(power);

  switch(engine)
  {
    case 1: 
      m.setEngine(Petrol);
      break;
    case 2:
      m.setEngine(Diesel);
      break;
    case 3: 
      m.setEngine(Electric);
      break;
    case 4:
      m.setEngine(Hybrid);
      break;
    
  }
  
  m.setBasePrice(basePrice);

  return s;
} 


std::ostream& operator<<(std::ostream& s, const Model &m){ // cout << m

  s << "Model : ";
  if(m.name){
    s << m.name;
  }
  else{
    s << "Pas de nom ";
  }
  

  s << "( " << m.power<< " Ch, ";

  switch(m.engine)
  {
    case Petrol:
      s << "Essence, " ;
      break;
    case Diesel:
      s << "Diesel, ";
      break;
    case Electric:
      s << "Electrique, ";
      break;
    case Hybrid:
      s << "Hybride ";
      break;
  }

  s << m.basePrice << " euro)";

  return s;
} 

}
