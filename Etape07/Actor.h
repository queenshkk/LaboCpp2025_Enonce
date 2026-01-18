#ifndef ACTOR_H
#define ACTOR_H

#include <iostream>
#include <string>
#include "Person.h"

class Actor:public Person{

private:
	int id;

public:

	Actor();
	Actor(std::string ln, std::string fn, int i_d);
	Actor(const Actor &a);

	~Actor() override;

	void setId(const int i_d);
	int getId() const;

	virtual std::string tuple() const =0;
	virtual std::string toString() const =0;

	void display() const override; 

	Actor &operator=(const Actor &a);

};

#endif