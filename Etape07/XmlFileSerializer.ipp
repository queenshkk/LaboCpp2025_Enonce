#include "XmlFileSerializer.hpp"

namespace carconfig{

XmlFileSerializer::XmlFileSerializer(const std::string &fn, char m, std::string &cn = "entities"){
	
	filebuf fichier;

	if(mode==WRITE){
		ofstream fichier(nf, ios::out);
		if(!fichier){
			std::cout << "Erreur d'ouverture" << std::endl;
			exit(1);
		}
		<?xml version="1.0" encoding="UTF-8"?>
<clients>

	fichier.write(())

	fichier.close();
	}

	if(mode==READ){
		ifstream fichier(nf, ios::in);
		if(!fichier.rdbuf()->is_open()){
			std::cout << "Erreur d'ouverture" << std::endl;
			exit(1);
		}

		fichier.read((std::string) cn, sizeof(cn));

		fichier.close();
	}
}

}