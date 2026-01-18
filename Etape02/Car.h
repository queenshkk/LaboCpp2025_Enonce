#ifndef CAR_H 
#define CAR_H

#include <iostream> 
#include <string> 
#include "Model.h"
#include "Option.h"

namespace carconfig{


class Car{ 
private:
  std::string name; 
  Model model; 
  Option* options[5]; 

public:
  Car();
  Car(std::string n, Model m);
  Car(const Car &c);
  ~Car();

  void setName(std::string n);
  void setModel(Model m);

  std::string getName() const;
  Model       getModel() const;

  void addOption(const Option &o); 
  void removeOption(std::string code);
  float getPrice() const;

  void display() const;
};

}

#endif