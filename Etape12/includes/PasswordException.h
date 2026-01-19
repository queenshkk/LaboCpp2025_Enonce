#ifndef PASSWORDEXCEPTION_H
#define PASSWORDEXCEPTION_H

#include <iostream>
#include <string>
#include "Exception.h"

#define INVALID_LENGTH 1
#define ALPHA_MISSING 2
#define DIGIT_MISSING 3
#define NO_PASSWORD 4


class PasswordException:public Exception{
private:
	int code;

public:
	PasswordException();
	PasswordException(std::string msg, int c);
	PasswordException(const PasswordException &pe);
	~PasswordException() noexcept override;

	void setCode(int c) noexcept;
	int getCode() const noexcept;

	void display() const override;


};

#endif