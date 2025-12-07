#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include "Actor.h"



class Client: public Actor{
private:
	std::string gsm;

public:
	Client();
	Client(std::string ln, std::string fn, int i_d, std::string numtel);
	Client(const Client& c);
	~Client() override;


	void setGsm(std::string numtel);
	std::string getGsm() const;

	std::string tuple() const override;
    std::string toString() const override;

	void display() const override;

	Client& operator=(const Client &c);
	
	friend std::ostream& operator<<(std::ostream& s, const Client &c);

};




#endif