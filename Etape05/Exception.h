#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include <string>

//namespace carconfig{


class Exception{
protected:
	std::string message;

public:

	Exception();
	Exception(std::string msg);
	Exception(const Exception &ex);
	virtual ~Exception();

	void setMessage(std::string msg);
	std::string getMessage() const;

	virtual void display() const;

};
//}
#endif