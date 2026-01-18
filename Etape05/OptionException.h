#ifndef OPTIONEXCEPTION_H
#define OPTIONEXCEPTION_H

#include <iostream>
#include <string>
#include "Exception.h"

class OptionException: public Exception{
private:

public:

	OptionException();
	OptionException(std:: string msg);
	OptionException(const OptionException &oe);
	 ~OptionException() override;
};

#endif