#pragma once
#include <fstream>
#include <vector>
#include <conio.h>
#include <cmath>
#include <Windows.h>

#include "Laptop.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27
#define KEY_ENTER 13
#define KEY_DELETE 83

class LaptopDisplay {
private:
	vector<Laptop> _laptopList;
	int _numOfPages;
	int _numOfItems;
	int _curPage;
	int _itemsInPage;

	string _nameBuf;
	int _priceBuf;
	Laptop _laptopBuf;

	string _productFile = "Test Products.txt";
	//string _productFile = "All Products.txt";
public:
	LaptopDisplay();
	void addLaptopList();
	void outputLaptopList();
	//void manipulateFile();
	//void laptopFile();
	//void printLaptopFile();
	string outputOneProduct(int index);
public:
	void gotoXY(int x, int y);
	void changeColor(int color);
	void testLaptopList();

	int selectFunction(int& y);
	void selectMenu(int y, int color);
	void displayMenu();
	void interactiveMenu();

	int selectProduct(int &y);
	void selectProductMenu(int y, int color);
	void displayProduct();
	void interactiveProductMenu();
	//int getNumOfItems();
	void nextPage();
	void previouPage();

	void addProduct();
	void editProduct(int index);

	void deleteProductById();
	void deleteProductOnList(int index);

	void exitMessage();
};