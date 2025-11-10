#include "Model.h" //Contient le prototype et définition de fonction
#include <cstring> 
using namespace std;

// ***************** Constructeurs ****************
Model::Model()//Définir la méthode qui appartient à la classe Model qui est le constructeur par défaut
{
  cout << "On est dans le constructeur du Model"<< endl; //vu que c'est un constructeur
  name=NULL; //Initialiser toutes les variables membres;
  setName("Nom");
  setPower(0);
  setEngine(Engine::Petrol);
  setBasePrice(0.0);
  //Tout ça c'était notre constructeur par défaut
  

  /*name=new char[strlen("Nom") +1];
  strcpy(name, "Nom");
  power=0;
  engine=Engine::Petrol;
  basePrice=0.0;*/
}

Model::Model(const  char* n, int p, Engine e, float bp)
{
  cout<< ">>> On est dans le constructeur d'initialisation <<<" << endl;
  //on donne les differents valeurs reçues aux différents champs.
  name=NULL;  //J'itinialise l'espace mémoire à nul pour appeler l'espace name pour ne pas qu'il libère un espace mémoire qu'il ne doit pas libérer
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
    
    /*
    name = new char[strlen(m.name) + 1];
    strcpy(name, m.name);
    power = m.power;
    engine = m.engine;
    basePrice = m.basePrice;
    */
}


// *********************************************************
// ***************** Destructeur ****************
Model::~Model() //On définit le destructeur qui doit libérer l'espace mémoire qui est pointé par l'espace name pour autant qu'il ne soit pas nul
{
    cout << "On est dans le destructeur du Model" << endl; //vu que c'est un destructeur
    if(name) delete [] name; //vérifier si la variable name n'est pas null, alors on fait un delete de name. if(name) est equivalent de if name!=NULL
    //[] car name contient l'adresse d'un vecteur de caractères. c'est donc un tableau de caractères.
}



// *********************************************************//Ca empeche de mettre n'importe quoi dans la valeur membre
// ***************** SETTLERS **************** //On fait ça pour la chacune des variables membres (relié au fichier .h)
void Model::setName(const char * n){ 
  if (n==NULL) return;//Regarder si la valeur du paramètre est nulle //Si c'est null, on quitte la méthode
  if (name==n) return;
  if (name) delete [] name; //On regarde si name a une valeur, dans ce cas on va supprimer la valeur

  name=new char[strlen(n)+1];//On re alloue l'espace mémoire. +1 car il y a le \0. 
  strcpy(name, n);
}

void Model::setPower(int p){
  if(p<0) return; //On regarde si c'est negatif, sinon on fait power=p
  power=p; 
}

void Model::setEngine(Engine e){
  engine=e; //On ne doit pas vérifier car c'est déjà vérifié
}

void Model::setBasePrice(float bp){
  if (bp<0.0) return;
  basePrice=bp;
}




// ***************** GETTERS ****************
const char * Model::getName() const{//return la valeur du champ correspondant au nom de la méthode dans lequel on est
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
void Model::display() const //vu qu'on a mis dans le prototype, on doit mettre aussi dans la définition
//afficher la valeur de différent champs
//Si name n'est pas null, je fais un cout, sinon je vais mettre ...
{
  cout << "Model : ";
  if(name){ //if name !=null
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

