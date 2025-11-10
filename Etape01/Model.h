#ifndef MODEL_H //Créer une constante de pré-compilation, on définit une variable
#define MODEL_H

#include <iostream> //Définition des opérations d'entrée/sorties
#include <cstring> //Permet d'avoir les méthodes qui permettent de manipuler les chaines de caractères




enum Engine { Petrol, Diesel, Electric, Hybrid }; //On définit une énumération


class Model //On définit une classe
{

private: //pas d'accès direct aux différents membres
  char * name; //On déclare les variabels membres de la classe
  int power;
  Engine engine;
  float basePrice;

public: //tout ce qui est publique peut être accessible en dehors de la classe
  Model(); //On rajoute les méthodes qu'on va définir pour cette classe
  Model(const  char*n, int p, Engine e, float bp);//On déclare du constructeur d'initialisation. En plus d'alouer l'espace memmoire, il initialise les valeurs des differents champs
  Model(const Model &m); //passé par référence
  ~Model();//destructeur
  
  void setName(const char *n); //const = recevoir en paramètres des chaines constantes
  //Méthodes SET = donne une valeur aux variables membres.
  void setPower(int p);
  void setEngine(Engine e);
  void setBasePrice(float bp);

  const char *getName() const; //Les méthodes GET retournent la valeur de la variable membre correspondante. On retourne l'adresse de la chaine de caractere.
  //const au début, la méthode ne peut pas modifier la chaine dont on reçoit l'adresse.
  //const derriere =empeche les methodes de modifier les valeurs de la variable membre. on le mettre toujours
  int         getPower() const;
  Engine      getEngine() const;
  float       getBasePrice() const;

  void display() const;//On appelle la méthode qu'on a besoin

};

#endif