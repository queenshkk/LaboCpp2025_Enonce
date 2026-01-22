#ifndef XMLFILESERIALIZEREXCEPTION_H
#define XMLFILESERIALIZEREXCEPTION_H

#include <string>
#include "Exception.h"

class XmlFileSerializerException:public Exception{
private:
	int code;

public:
	static const int NOT_ALLOWED;
	static const int FILE_NOT_FOUND;
	static const int END_OF_FILE;

	XmlFileSerializerException();
	XmlFileSerializerException(std::string msg, int c);
	XmlFileSerializerException(const XmlFileSerializerException &xml);
	~XmlFileSerializerException() override;

	void setCode(int c);
	int getCode() const;



};
#endif