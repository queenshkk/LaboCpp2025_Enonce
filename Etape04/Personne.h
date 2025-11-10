#ifndef PERSONNE_H
#define PERSONNE_H

#include <iostream>
#include <string>


namespace carconfig{

Personne{

private:
	std::string lastName;
	std::string name;

public:
	Personne();
	Personne(std::string ln, std::string n);
	Personne(const Personne &p);
	~Personne();

	void setLastName(std::string ln);
	void setName(std::string n);

	std::string getLastName() const;
	std::string getName() const;


	void display() const;

	friend std::istream operator>>(std::istream &s, Personne &p);
	friend std::ostream operator<<(std::ostream &s, const Personne &p);

	

	Personne& operator=(const Personne &p);

}

};

#endif