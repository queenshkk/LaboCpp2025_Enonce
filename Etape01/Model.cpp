#include "Model.h" 
#include <cstring> 
using namespace std;

// ***************** Constructeurs ****************
Model::Model()
{
  cout << "On est dans le constructeur du Model" << endl; 
  name=NULL; 
  setName("Nom");
  setPower(0);
  setEngine(Engine::Petrol);
  setBasePrice(0.0);
}

Model::Model(const  char* n, int p, Engine e, float bp)
{
  cout<< ">>> On est dans le constructeur d'initialisation <<<" << endl;
  name=NULL; 

  setName(n);
  setPower(p);
  setEngine(e);
  setBasePrice(bp);
}

Model::Model(const Model &m){
  cout << ">>> On est dans le constructeur de copie <<<" << endl;
  name=NULL;
  setName(m.getName());
  setPower(m.getPower());
  setEngine(m.getEngine());
  setBasePrice(m.getBasePrice());
}


// ***************** Destructeur ****************
Model::~Model()
{
  cout << "On est dans le destructeur du Model" << endl;
  if(name) delete [] name; 
}



// ***************** SETTLERS ****************
void Model::setName(const char * n){ 
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




// ***************** GETTERS ****************
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



// ***************** Méthodes d'instance ****************
void Model::display() const 
{
  cout << "Model : ";
  
  if(name){ 
    cout << name;
  }
  else{
    cout << "Pas de nom ";
  }
  
  cout << "( " << power << " Ch, ";

  switch(engine)
  {
    case Engine::Petrol:
      cout << "Essence, " ;
      break;
    case Engine::Diesel:
      cout << "Diesel, ";
      break;
    case Engine::Electric:
      cout << "Electrique, ";
      break;
    case Engine::Hybrid:
      cout << "Hybride ";
      break;
  }

  cout << basePrice << " euro)" << endl;

}

