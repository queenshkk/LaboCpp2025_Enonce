#ifndef PERSON_H
#define PERSON_H


#include <iostream>
#include <string>


//namespace carconfig {

class Person{

protected: // pour que les membres soient accessibles par la classe qui hérite
	std::string lastName;
	std::string firstName;

public:
	Person();
	Person(std::string ln, std::string fn);
	Person(const Person &p);
	virtual ~Person();

	void setLastName(std::string ln);
	void setFirstName(std::string fn);

	std::string getLastName() const;
	std::string getFirstName() const;


	virtual void display() const; // virtual : uniquement dans la classe mère. Cette fonction peut être modifiée dans les classes dérivées

	friend std::istream& operator>>(std::istream &s, Person &p);
	friend std::ostream& operator<<(std::ostream &s, const Person &p);

	

	Person& operator=(const Person &p);


};
//}

#endif
