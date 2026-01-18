#include "Model.h" // importer les déclarations de la classe Model pour les définir dans .cpp
#include <cstring> 

namespace carconfig{
// ***************** Constructeurs du Modèle ****************
Model::Model()
{
  std::cout << "On est dans le constructeur par défaut (Model)" << std::endl;
  name=NULL; 

  setName("Nom");
  setPower(0);
  setEngine(Engine::Petrol);
  setBasePrice(0.0);
}

Model::Model(const  char*n, int p, Engine e, float bp)
{
  std::cout << "On est dans le constructeur d'initialisation (Model)" << std::endl;
  name=NULL;

  setName(n);
  setPower(p);
  setEngine(e);
  setBasePrice(bp);
}

Model::Model(const Model &m){ // on passe le Model par référence et non par copie
    std::cout << ">>> On est dans le constructeur de copie (Model)" << std::endl;
    name=NULL;

    setName(m.getName());
    setPower(m.getPower());
    setEngine(m.getEngine());
    setBasePrice(m.getBasePrice());
}


// ***************** Destructeur du Modèle ****************
Model::~Model()
{
    std::cout << "On est dans le destructeur (Model)" << std::endl;
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
  if (bp<0.0) return;
  basePrice=bp;
}


// ***************** GETTERS du Modèle ****************
const char * Model::getName() const{
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
}
