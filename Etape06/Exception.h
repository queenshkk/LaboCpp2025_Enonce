#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include <string>



class Exception{
protected:
	std::string message;

public:

	Exception();
	Exception(std::string msg);
	Exception(const Exception &ex);
	virtual ~Exception() noexcept;

	void setMessage(std::string msg);
	std::string getMessage() const noexcept;

	virtual void display() const;

};

#endif