#include "XmlFileSerializer.hpp"
#include <cstdlib> //std::exit

template<typename T>
XmlFileSerializer<T>::XmlFileSerializer(const std::string &fn, char m, const std::string &cn){
	
	filename=fn;
	mode=m;
	collectionName=cn;
	std::string balise, nom;
	char c;


	#ifdef DEBUG
		std::cout << "On est dans le constructeur d'initialisation (XmlFileSerializer)" << std::endl;
	#endif

	if(mode==WRITE){
		file.open(filename, std::ios::out | std::ios::trunc);
		if(!file.is_open()){
			std::cout << "Erreur ouverture fichier en mode écriture" << std::endl;
			std::exit(1);
		}
	
		file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";

		file << "<" << collectionName << "/>\n";
	}

	else{
		file.open(filename, std::ios::in);
		if(!file.is_open()){
			throw XmlFileSerializerException("Erreur ouverture fichier en mode lecture", XmlFileSerializerException::FILE_NOT_FOUND);
		}

		
		std::getline(file, balise); 

		while(file.get(c) && c!='<'){ 

		}

		nom="";

		while(file.get(c) && c!='>'){
			nom=nom+c;
		}
		
		collectionName=nom;
	}
}


template<typename T>
XmlFileSerializer<T>::~XmlFileSerializer(){

	#ifdef DEBUG
		std::cout << "On est dans le destructeur (XmlFileSerializer)" << std::endl;
	#endif

	if (file.is_open()){
		if (mode==WRITE){
			file << "</" << collectionName << "/>\n";
		}

		file.close();
	}
}

template<typename T>
std::string XmlFileSerializer<T>::getFilename() const{
	return filename;
}

template<typename T>
std::string XmlFileSerializer<T>::getCollectionName() const{
	return collectionName;
}

template<typename T>
bool XmlFileSerializer<T>::isReadable(){
	return mode==READ && file.is_open();
}

template<typename T>
bool XmlFileSerializer<T>::isWritable(){
	return mode==WRITE && file.is_open();
}

template<typename T>
void XmlFileSerializer<T>::write(const T & val){
	if(!isWritable()){
		throw XmlFileSerializerException("Impossible --> mode READ",XmlFileSerializerException::NOT_ALLOWED);
	}

	file << val; 
}

template<typename T>
T XmlFileSerializer<T>::read(){
	T objet;
	std::streampos pos;
	std::string ligne, fin;
	fin="</" + collectionName + ">"; 

	if(!isReadable()){
		throw XmlFileSerializerException("Impossible --> mode WRITE", XmlFileSerializerException::NOT_ALLOWED);
	}


	pos=file.tellg(); 
	file >> ligne;

	if(!file){
		throw XmlFileSerializerException("Fin de fichier", XmlFileSerializerException::END_OF_FILE);
	}


	if(ligne==fin){
		throw XmlFileSerializerException("Balise de fin", XmlFileSerializerException::END_OF_FILE);
	}

	file.seekg(pos); 
	file >> objet; 

	return objet;
}

template<typename T>
const char XmlFileSerializer<T>::READ='R';

template<typename T>
const char XmlFileSerializer<T>::WRITE='W';
