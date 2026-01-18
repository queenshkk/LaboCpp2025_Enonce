#ifndef ACTOR_H
#define ACTOR_H

#include <iostream>
#include <string>
#include "Person.h"

class Actor : public Person{

private:
	int id;
	static int currentId;
	
protected:
	void setId(const int i_d); 
	
public:

	Actor();
	Actor(std::string ln, std::string fn);
	Actor(const Actor &a);

	~Actor() override;

	int getId() const;

	virtual std::string tuple() const =0;
	virtual std::string toString() const =0;



	void display() const override;

	Actor &operator=(const Actor &a);


};


#endif