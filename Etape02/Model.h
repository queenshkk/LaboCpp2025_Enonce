#ifndef MODEL_H 
#define MODEL_H

#include <iostream> // pour le std::cout dans le display
#include <cstring> // pour le strlen, strcpy, strcmp... avec le char*


namespace carconfig{
enum Engine { Petrol, Diesel, Electric, Hybrid }; 


class Model // on déclare la classe Model
{

private: 
  char * name; // pointeur vers une chaîne de caractère
  int power;
  Engine engine;
  float basePrice;

public: 
  Model(); // constructeur par défaut
  Model(const  char*n, int p, Engine e, float bp); // constructeur d'initialisation
  Model(const Model &m); // constructeur de copie
  ~Model(); // destructeur
  
  void setName(const char *n); // le const : permet de ne pas modifier la chaîne passée en paramètre
  void setPower(int p);
  void setEngine(Engine e);
  void setBasePrice(float bp);


  const char *getName() const; // permet de ne pas modifier l'objet (const derrière) ni la chaîne renvoyée (const devant)
  int         getPower() const;
  Engine      getEngine() const;
  float       getBasePrice() const;

  void display() const;

};
}


#endif