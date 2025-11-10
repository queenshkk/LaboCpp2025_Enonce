#ifndef CAR_H 
#define CAR_H

#include <iostream> 
#include <string> 
#include "Model.h"
#include "Option.h"

namespace carconfig{


class Car{ // on déclare la classe Car
private:
  std::string name; // variable membre
  Model model; // objet Model
  Option* options[5]; // tableau de 5 pointeurs vers Option

public:
  Car();
  Car(std::string n, Model m);
  Car(const Car &c);
  ~Car();

  void setName(std::string n);
  void setModel(Model m);

  std::string getName() const;
  Model       getModel() const;

  void addOption(const Option &o); // la fonction ne reçoit pas une copie, mais une référence. On regarde l'objet sans le copier
  void removeOption(std::string code);
  float getPrice() const;

  void display() const;
};

}

#endif