#ifndef PASSWORDEXCEPTION_H
#define PASSWORDEXCEPTION_H

#include <iostream>
#include <string>
#include "Exception.h"

#define INVALID_LENGTH 1
#define ALPHA_MISSING 2
#define DIGIT_MISSING 3
#define NO_PASSWORD 4

//namespace carconfig {



class PasswordException:public Exception{
private:
	int code;

public:
	PasswordException();
	PasswordException(std::string msg, int c);
	PasswordException(const PasswordException &pe);
	~PasswordException() override;

	void setCode(int c);
	int getCode() const;

	void display() const override;


};
//}
#endif