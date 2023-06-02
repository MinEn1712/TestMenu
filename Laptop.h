#pragma once
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Laptop {
private:
	string _id;
	string _name;
	int _price;
public:
	Laptop();
	Laptop(string id, string name, int price);
	Laptop(const Laptop& other);
	void operator= (const Laptop& other);
public:
	void setID(string id) { this->_id = id; }
	void setName(string name) { this->_name = name; }
	void setPrice(int price) { this->_price = price; }
	string getID() { return _id; }
	string getName() { return _name; }
	int getPrice() { return _price; }
	Laptop newLaptop(int id, string name, int price);
	void outputLaptop();
};