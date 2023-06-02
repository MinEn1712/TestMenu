#include "Laptop.h"

Laptop::Laptop() {
	this->_id = "000";
	this->_name = " ";
	this->_price = 0;
}
Laptop::Laptop(string id, string name, int price) {
	this->_id = id;
	this->_name = name;
	this->_price = price;
}
Laptop::Laptop(const Laptop& other) {
	this->_id = other._id;
	this->_name = other._name;
	this->_price = other._price;
}
void Laptop::operator= (const Laptop& other) {
	this->_id = other._id;
	this->_name = other._name;
	this->_price = other._price;
}
Laptop Laptop::newLaptop(int id, string name, int price) {
	stringstream stringID;
	if (id < 10) stringID << "00" << id;
	else if (id < 100) stringID << "0" << id;

	Laptop lap(stringID.str(), name, price);
	return lap;
}
void Laptop::outputLaptop() {
	cout << _id << " " << _name << " " << _price << endl;
}
