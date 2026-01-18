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

  int compC(const Car& c) const;

public:
  Car();
  Car(std::string n, Model m);
  Car(const Car &c);
  ~Car();

  void setName(std::string n);
  void setModel(Model m);

  std::string getName() const;
  Model       getModel() const;
  float getPrice() const;


  void addOption(const Option &o);
  void removeOption(std::string code);

  void display() const;

  Car& operator=(const Car &c); 
  Car operator+ (const Option &o) const; 
  friend Car operator+ (const Option &o, const Car &c); 
  Car operator- (const Option &o) const; 
  Car operator- (std::string code) const; 

  int operator>(const Car& c) const;
  int operator==(const Car& c) const;
  int operator<(const Car& c) const;
  
  friend std::istream &operator>>(std::istream &s, Car &c);
  friend std::ostream &operator<<(std::ostream &s, const Car &c); 
  Option* operator[](int i);

};
}

#endif