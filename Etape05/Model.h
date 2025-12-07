#ifndef MODEL_H 
#define MODEL_H

#include <iostream> 
#include <cstring> 


namespace carconfig{

enum Engine {Petrol, Diesel, Electric, Hybrid}; 


class Model{

private: 
  char* name;
  int power;
  Engine engine;
  float basePrice;

public: 
  Model(); 
  Model(const char*n, int p, Engine e, float bp);
  Model(const Model &m); 
  ~Model(); 
  
  void setName(const char *n); 
  void setPower(int p);
  void setEngine(Engine e);
  void setBasePrice(float bp);


  const char* getName() const; 
  int         getPower() const;
  Engine      getEngine() const;
  float       getBasePrice() const;

  void display() const;

  friend std::istream& operator>>(std::istream& s, Model &m); // cin >> m, friend permet d'accéder les variables vu qu'ils sont en private
  friend std::ostream& operator<<(std::ostream& s, const Model &m); // cout << m

};
}


#endif