#include "Garage.h"
#include "Credentials.h"
#include "PasswordException.h"
#include "XmlFileSerializer.hpp"
#include "XmlFileSerializerException.h"

Garage::Garage(){
	#ifdef DEBUG
		std::cout << "On est dans le constructeur par défaut (Garage)" << std::endl;
	#endif

	int id=addEmployee("admin (ln)", "admin (fn)", "ADMIN", "administratif");
	Employee e=findEmployeeById(id);
	if(e.getLogin() == "") return; 

  	e.setPassword("admin123"); 
      
    updateEmployee(e);
    

}

void Garage::addModel(const Model & m){
	models.push_back(m); 
}

void Garage::displayAllModels() const{
	std::list<Model>::const_iterator it;  

	for(it=models.cbegin(); it!=models.cend(); it++){ 
		std::cout << (*it).toString() << std::endl; 
	}
}

Model Garage::getModel(int index) const{
	std::list<Model>::const_iterator it; 
	it=models.cbegin(); 
	int i;

	if(index<0) return Model();

	for(i=0; i<index; i++, it++){
		if(it==models.cend()){
			return Model();
		}
	}

	if(it==models.cend()){
		return Model();
	}

	return *it; 
}

int Garage::getNbModels() const{
	return models.size();
}


void Garage::addOption(const Option & o){
	options.push_back(o);
}

void Garage::displayAllOptions() const{
	std::list<Option>::const_iterator it;

	for(it=options.cbegin(); it!=options.cend(); it++){
		std::cout << (*it).toString()<< std::endl;
	}
}

Option Garage::getOption(int index){
	std::list<Option>::iterator it;
	it=options.begin();
	int i;

	if(index<0){
		throw OptionException("Indice option invalide");
	}

	for(i=0; i<index; i++, it++){
		if(it==options.end()){
			throw OptionException("Indice option invalide");
		}
	}

	if(it==options.end()){
		throw OptionException("Indice option invalide");
	}

	return *it;
}

int Garage::getNbOptions() const{
	return options.size();
}


int Garage::addClient(std::string lastName, std::string firstName, std::string gsm){
	Client c(lastName, firstName, gsm);
	int id;

	id=c.getId();
	clients.insert(c);  

	return id; 
}

void Garage::displayClients() const{
	std::set<Client>::const_iterator it;

	for(it=clients.cbegin(); it!=clients.cend(); it++){
		std::cout << (*it).toString() << std::endl;
	}
}



void Garage::deleteClientByIndex(int index){
	std::set<Client>::iterator it;
	it=clients.begin();

	int i;

	if(index<0) return;

	for(i=0; i<index; i++, it++){
		if(it== clients.end()){
			return;
		}
	}

	if(it!= clients.end()){
		clients.erase(it);
	}

}

void Garage::deleteClientById(int id){
	std::set<Client>::iterator it;

	for(it=clients.begin(); it!=clients.end(); it++){
		if(it->getId()==id){
			clients.erase(it);
			return;
		}
	}

}

Client Garage::findClientByIndex(int index) const{
	std::set<Client>::const_iterator it;
	it=clients.cbegin();
	int i;

	if(index<0) return Client();

	for(i=0; i<index; i++, it++){
		if(it==clients.cend()){
			return Client();
		}
	}

	if(it==clients.cend()){
		return Client();
	}

	return *it;

}

Client Garage::findClientById(int id) const{
	std::set<Client>::const_iterator it;


	for(it=clients.cbegin(); it!=clients.cend(); it++){
		if(it->getId()==id){
			return *it;
		}
	}

	return Client(); 

}

int Garage::getNbClients() const{
	return clients.size();
}



int Garage::addEmployee(std::string lastName, std::string firstName, std::string login, std::string role){
	Employee e (lastName, firstName, login, role);
	int id;

	id=e.getId();
	employees.insert(e);

	return id;
}

void Garage::displayEmployees() const{
	std::set<Employee>:: const_iterator it;

	for(it=employees.cbegin(); it!=employees.cend(); it++){
		std::cout << (*it).toString() << std::endl; 
	}
}



void Garage::updateEmployee(const Employee &e){
	deleteEmployeeById(e.getId());
    employees.insert(e);
}

void Garage::deleteEmployeeByIndex(int index){
	std::set<Employee>::iterator it;
	it=employees.begin();
	int i;

	if(index<0) return;

	for(i=0; i<index; i++, it++){
		if(it==employees.end()){
			return;
		}
	}

	if(it!=employees.end()){
		employees.erase(it);
	}	

}

void Garage::deleteEmployeeById(int id){
	std::set<Employee>::iterator it;

	for(it=employees.begin(); it!=employees.end(); it++){
		if(it->getId()==id){
			employees.erase(it);
			return;
		}
	}
}

Employee Garage::findEmployeeByIndex(int index) const{
	std::set<Employee>::const_iterator it;
	it=employees.cbegin();
	int i;

	if(index<0) return Employee();

	for(i=0; i<index;i++, it++){
		if(it==employees.cend()){
			return Employee();
		}
	}

	if(it==employees.cend()){
			return Employee();
	}

	return *it;
}

Employee Garage::findEmployeeById(int id) const{
	std::set<Employee>:: const_iterator it;

	for(it=employees.cbegin(); it!=employees.cend(); it++){
		if(it->getId()==id){
			return *it;
		}
	}

	return Employee();
}

int Garage::getNbEmployees() const{
	return employees.size();


}
Employee Garage::findEmployeeLogin(const std::string &login) const
{
	std::set<Employee>::const_iterator it;

    for(it=employees.cbegin(); it!=employees.cend(); it++)
    {
        if(it->getLogin()==login){
        	return *it;
        }
    }
    return Employee(); 
}

Garage Garage::instance; 

Car Garage::currentProject;


Garage& Garage::getInstance(){
	return instance;
}

Car& Garage::getCurrentProject(){
	return currentProject;
}

void Garage::resetCurrentProject(){
	currentProject=Car(); 
}

void Garage::importModelsFromCsv(std::string filename){
	std::ifstream file(filename);
	std::string line;

    char sep=';';
    int i;


	if(!file.is_open()){
		std::cout << "Erreur ouverture fichier en mode lecture" << std::endl;
     	std::exit(1);
	}

	std::getline(file, line);
	std::getline(file, line);

	for(i=0; i<line.size(); i++){
        if(line[i]==';' || line[i]==':' || line[i]==',') {
            sep=line[i];
            break;
        }
    }

	do{
		std::istringstream iss(line);
    	std::string nom, power, engine, img, bp;
    	Model m;

		std::getline(iss, nom, sep);
        std::getline(iss, power, sep);
        std::getline(iss, engine, sep);
        std::getline(iss, img, sep);
        std::getline(iss, bp, sep);
    

	    m.setName(nom.c_str());
	    m.setPower(std::stoi(power));
	    if(engine=="essence"){
	    	m.setEngine(Engine::Petrol);
	    }
	    else if(engine=="diesel"){
	    	m.setEngine(Engine::Diesel);
	    }
	    else if(engine=="electrique"){
	    	m.setEngine(Engine::Electric);
	    } 
	    else{
	    	m.setEngine(Engine::Hybrid);	
	    }
	    m.setBasePrice(std::stof(bp));
	    m.setImage(img);

	    addModel(m);

	}while(std::getline(file, line));

	file.close();

}
	
void Garage::importOptionsFromCsv(std::string filename){
	std::ifstream file(filename);
	std::string line;
    char sep=';';
    int i;

	if(!file.is_open()){
		std::cout << "Erreur ouverture fichier en mode lecture" << std::endl;
     	std::exit(1);
	}

	std::getline(file, line);
	std::getline(file, line);

	for(i=0; i<line.size(); i++){
        if(line[i]==';' || line[i]==':' || line[i]==',') {
            sep=line[i];
            break;
        }
    }

	do{
		std::istringstream iss(line);
    	std::string code, label, price;
    	Option o;

		std::getline(iss, code, sep);
        std::getline(iss, label, sep);
        std::getline(iss, price, sep);
    
        o.setCode(code);
        o.setLabel(label);
        o.setPrice(std::stof(price));

	 	addOption(o);
	}while(std::getline(file, line));

	file.close();
}


int Garage::idLoggedEmployee=-1;

void Garage::save(){

	int currentId, nbEmp, i;

	XmlFileSerializer<Employee> emp("employees.xml", XmlFileSerializer<Employee>::WRITE, "Employees");

    std::set<Employee>::const_iterator itE;
    for(itE=employees.begin(); itE!=employees.end(); itE++){
        emp.write(*itE);
    }

    XmlFileSerializer<Client> cl("clients.xml", XmlFileSerializer<Client>::WRITE, "Clients");

    std::set<Client>::const_iterator itC;
    for(itC=clients.begin(); itC!=clients.end(); itC++){
        cl.write(*itC);
    }

    std::ofstream file;
    file.open("config.dat", std::ios::binary);
    if(!file.is_open())
    {
        std::cout << "Erreur ouverture en écriture" << std::endl;
        std::exit(1);
    }

    currentId=Actor::getCurrentId();
    file.write((char*)&currentId, sizeof(int));

   	nbEmp=(int)employees.size();
    file.write((char*)&nbEmp, sizeof(int));

    for(itE=employees.begin(); itE!=employees.end(); itE++)
    {
        Credentials c;
        memset(&c, 0, sizeof(Credentials));
        std::strcpy(c.login, itE->getLogin().c_str());

        try
        {
            std::strcpy(c.password, itE->getPassword().c_str());
        }
        catch(const PasswordException &pe)
        {
        	pe.display();
        	c.password[0] = '\0';
        }

        c.crypt();
        file.write((char*)&c, sizeof(Credentials));
    }

    file.close();
}

void Garage::load(){

	int currentId=0, nbEmp=0, i;


	employees.clear();
    clients.clear();

    try
    {
        XmlFileSerializer<Employee> emp("employees.xml",XmlFileSerializer<Employee>::READ, "");

        while(emp.isReadable())
        {
            try
            {
            	Employee e = emp.read();

                employees.insert(emp.read());
            }
            catch(const XmlFileSerializerException &xml)
            {
                if(xml.getCode()==XmlFileSerializerException::END_OF_FILE){

                    break;      
                }
                else{
                    throw;
                }
            }
        }
    }
    catch(const XmlFileSerializerException &)
    {

    }

    try
    {
        XmlFileSerializer<Client> cl("clients.xml",XmlFileSerializer<Client>::READ,"");

        while(cl.isReadable())
        {
            try
            {
                Client c =cl.read();
                clients.insert(c);
            }
            catch(const XmlFileSerializerException &ex)
            {
                if(ex.getCode()==XmlFileSerializerException::END_OF_FILE)
                    break;
                else
                    throw;
            }
        }
    }
    catch(const XmlFileSerializerException &)
    {
    }

    // ===================== 3) Charger config.dat =====================
    std::ifstream file("config.dat", std::ios::binary);
    if(!file.is_open())
    {
        return;
    }

    
    file.read((char*)&currentId, sizeof(int));
    file.read((char*)&nbEmp, sizeof(int));

    Actor::setCurrentId(currentId);

    for(i=0; i<nbEmp; i++)
    {
        Credentials c;
        file.read((char*)&c, sizeof(Credentials));

        c.decrypt();

        Employee e=findEmployeeLogin(std::string(c.login));

        if(e.getLogin()!="") 
        {
            if(c.password[0] != '\0') 
            {
                try
                {
                    e.setPassword(std::string(c.password));
                    updateEmployee(e);
                }
                catch(const PasswordException &)
                {
                }
            }
        }
    }

    file.close();
}