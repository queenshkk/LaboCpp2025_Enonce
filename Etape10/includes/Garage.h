#ifndef GARAGE_H 
#define GARAGE_H 

#include <iostream>
#include <string>
#include <set>
#include <list>
#include "Model.h"
#include "Option.h"
#include "Client.h"
#include "Employee.h"
#include "Car.h"
#include "OptionException.h"
#include <sstream>

using carconfig::Model;
using carconfig::Option;
using carconfig::Car;

class Garage{
private:
	std::set<Employee> employees;
	std::set<Client> clients;
	std::list<Model> models;
	std::list<Option> options;

	static Garage instance;
	static Car currentProject;
	Garage();

	Garage(const Garage &g)=delete;
	Garage &operator=(const Garage &g)=delete;
public:
	
	~Garage() = default;

	void addModel(const Model & m);
	void displayAllModels() const;
	Model getModel(int index) const;
	int getNbModels() const;

	void addOption(const Option & o);
	void displayAllOptions() const;
	Option getOption(int index);
	int getNbOptions() const;

	int addClient(std::string lastName, std::string firstName, std::string gsm);
	void displayClients() const;
	void deleteClientByIndex(int index);
	void deleteClientById(int id);
	Client findClientByIndex(int index) const;
	Client findClientById(int id) const;

	int addEmployee(std::string lastName, std::string firstName, std::string login, std::string role);
	void displayEmployees() const;
	void deleteEmployeeByIndex(int index);
	void deleteEmployeeById(int id);
	Employee findEmployeeByIndex(int index) const;
	Employee findEmployeeById(int id) const;

	static Garage& getInstance();
	static Car& getCurrentProject();
	static void resetCurrentProject();

	void importModelsFromCsv(std::string filename);
	void importOptionsFromCsv(std::string filename);


};

#endif