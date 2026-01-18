#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <string>
#include "Actor.h"

class Employee:public Actor{
private:
	std::string login;
	std::string* password;
	std::string role;

public:
	Employee();
	Employee(std::string ln, std::string fn, int i_d, std::string log, std::string r);
	Employee(const Employee &e);

	~Employee() override;
	
	void setLogin(std::string log);
	void setPassword(std::string mdp);
	void setRole(std::string r);


	std::string getLogin() const;
	std::string getPassword() const;
	std::string getRole() const;

	void resetPassword();

	std::string tuple() const override;
    std::string toString() const override;

	void display() const override;

	Employee& operator=(const Employee&e);

	friend std::ostream& operator<<(std::ostream&s, const Employee&e);

	static const std::string ADMINISTRATIVE;
    static const std::string SELLER;

};

#endif