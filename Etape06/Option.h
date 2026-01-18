#ifndef OPTION_H
#define OPTION_H
#include <iostream> 
#include <string> 

namespace carconfig{

class Option{

private:
	std::string code;
	std::string label;
	float price;

public:
	Option();
	Option(std::string c, std::string l, float fp);
	Option(const Option &o);

	~Option();

	void setCode(std::string c);
	void setLabel(std::string l);
	void setPrice(float p);

	std::string getCode() const;
	std::string getLabel() const;
	float 		getPrice() const;

	void display() const;

	friend std::istream& operator>>(std::istream& s, Option &o); 
	friend std::ostream& operator<<(std::ostream& s,const Option &o); 

	Option operator--();
	Option operator--(int);

};
}
#endif