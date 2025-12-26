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
  

  Car& operator=(const Car &c); // c1=c2
  Car operator+ (const Option &o) const; // c3=c2+op1
  friend Car operator+ (const Option &o, const Car &c); // c3=op2 + c3
  Car operator- (const Option &o) const; // c3=c3-op1
  Car operator- (std::string code) const; // c3=c3- "ZH75"

  int operator>(const Car& c) const;
  int operator==(const Car& c) const;
  int operator<(const Car& c) const;
  
  friend std::istream &operator>>(std::istream &s, Car &c);
  friend std::ostream &operator<<(std::ostream &s, const Car &c); // cout << "Projet de Mr Dugenou :” << c1 << endl;
  Option* operator[](int i);

};
}

#endif