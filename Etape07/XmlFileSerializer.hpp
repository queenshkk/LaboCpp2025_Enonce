#ifndef XMLFILESERIALIZER_H
#define XMLFILESERIALIZER_H

#include <iostream>
#include <string>
#include <fstream>
//#include "XmlFileSerializerException.h"

template<typename T>

class XmlFileSerializer{
private:
	std::fstream file;
	std::string filename;
	char mode;
	std::string collectionName;

public:
	XmlFileSerializer() = delete;
	XmlFileSerializer(const std::string &fn, char m, std::string &cn = "entities");
	XmlFileSerializer (const XmlFileSerializer<T>&) = delete;
	~XmlFileSerializer();


	std::string getFileName() const;
	std::string getCollectionName() const;
	bool isReadible();
	bool isWritable();

	void write(const T & val);
	T read();

	//XmlFileSerializer<T>&operator=(const XmlFileSerializerException<T>&)=delete;
	static const char READ;
	static const char WRITE ;
};


#include XmlFileSerializer.ipp
#endif