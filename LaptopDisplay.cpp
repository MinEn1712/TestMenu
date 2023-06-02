#include "LaptopDisplay.h"

HANDLE hStdin;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

LaptopDisplay::LaptopDisplay() {
	this->_numOfItems = 0;
	this->_numOfPages = 1;
	this->_curPage = 1;
	this->_itemsInPage = 0;
	this->_priceBuf = 0;
}
void LaptopDisplay::gotoXY(int x, int y) {
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}
void LaptopDisplay::changeColor(int color) {
	SetConsoleTextAttribute(console, color);
}
void LaptopDisplay::exitMessage() {
	system("cls");
	cout << "Thanks for using our app ^_^" << endl;
}
void LaptopDisplay::testLaptopList() {
	fstream testFile(_productFile);
	string buf;
	string id, name, price;

	getline(testFile, buf);
	this->_numOfItems = stoi(buf);

	while (getline(testFile, buf)) {
		istringstream iss(buf);

		getline(iss, id, '-');
		getline(iss, name, '-');
		getline(iss, price, '\n');

		Laptop bufLap(id, name, stoi(price));
		_laptopList.push_back(bufLap);
	}

	testFile.close();
}
void LaptopDisplay::addLaptopList() {
	//_numOfItems++;
	//if (_numOfItems % 10 != 0) _numOfPages = _numOfItems / 10 + 1;

	//string name;
	//int price;

	cout << "Laptop's name: "; //getline(cin, name);
	cout << endl;
	cout << "Laptop's price: "; //cin >> price;

	//_laptopBuf = _laptopBuf.newLaptop(_numOfItems, name, price);
	//_laptopList.push_back(_laptopBuf);


	//manipulateFile();
}
void LaptopDisplay::outputLaptopList() {
	for (int i = 0; i < _numOfItems; i++) {
		_laptopList[i].outputLaptop();
	}
}
string LaptopDisplay::outputOneProduct(int index) {
	stringstream stringPrice;
	stringPrice << _laptopList[index].getPrice();

	stringstream builder;
	builder << _laptopList[index].getID() << "|";
	for (int i = 0; i < 34 - _laptopList[index].getName().length(); i++) builder << " ";
	builder << _laptopList[index].getName() << "|";
	for (int i = 0; i < 12 - stringPrice.str().length(); i++) builder << " ";
	builder << _laptopList[index].getPrice();
	return builder.str();
}
void LaptopDisplay::selectProductMenu(int y, int color) {
	changeColor(color);
	gotoXY(0, y - 1);

	_itemsInPage = _numOfItems;

	if (_numOfItems > 10) _itemsInPage -= (_curPage - 1) * 10;

	int curItemInPage;

	if (_itemsInPage <= 10) curItemInPage = _itemsInPage;
	else curItemInPage = 10;

	if (y == 7 && curItemInPage >= 1) cout << outputOneProduct(0 + ((_curPage - 1) * 10));
	else if (y == 8 && curItemInPage >= 2) cout << outputOneProduct(1 + ((_curPage - 1) * 10));
	else if (y == 9 && curItemInPage >= 3) cout << outputOneProduct(2 + ((_curPage - 1) * 10));
	else if (y == 10 && curItemInPage >= 4) cout << outputOneProduct(3 + ((_curPage - 1) * 10));
	else if (y == 11 && curItemInPage >= 5) cout << outputOneProduct(4 + ((_curPage - 1) * 10));
	else if (y == 12 && curItemInPage >= 6) cout << outputOneProduct(5 + ((_curPage - 1) * 10));
	else if (y == 13 && curItemInPage >= 7) cout << outputOneProduct(6 + ((_curPage - 1) * 10));
	else if (y == 14 && curItemInPage >= 8) cout << outputOneProduct(7 + ((_curPage - 1) * 10));
	else if (y == 15 && curItemInPage >= 9) cout << outputOneProduct(8 + ((_curPage - 1) * 10));
	else if (y == 16 && curItemInPage >= 10) cout << outputOneProduct(9 + ((_curPage - 1) * 10));

	gotoXY(52, y - 1);
	changeColor(7);
}
void LaptopDisplay::displayProduct() {
	system("cls");

	if (_numOfItems <= 10) _numOfPages = 1;
	else if (_numOfItems % 10 == 0) _numOfPages = _numOfItems / 10;
	else _numOfPages = _numOfItems / 10 + 1;

	cout << "------------------- ALL PRODUCTS ------------------" << endl;
	if (_numOfItems - ((_curPage - 1) * 10) > 10)
		cout << "           Page " << _curPage << "/" << _numOfPages <<
		". Displaying 10/" << _numOfItems << " items" << endl;
	else
		cout << "           Page " << _curPage << "/" << _numOfPages <<
		". Displaying " << _numOfItems - (_curPage - 1) * 10 << "/" << _numOfItems << " items" << endl;

	cout << endl;
	cout << "===================================================" << endl;
	cout << " ID|                              Name|       Price" << endl;
	cout << "===================================================" << endl;

	_itemsInPage = _numOfItems;

	if (_numOfItems <= 10) {
		for (int i = 0; i < _itemsInPage; i++)
			cout << outputOneProduct(i) << endl;
	}
	else {
		_itemsInPage -= (_curPage - 1) * 10;
		if (_itemsInPage <= 10) {
			for (int i = (_curPage - 1) * 10; i < (_curPage - 1) * 10 + _itemsInPage; i++)
				cout << outputOneProduct(i) << endl;
		}
		else {
			for (int i = (_curPage - 1) * 10; i < (_curPage - 1) * 10 + 10; i++)
				cout << outputOneProduct(i) << endl;
		}
	}
	cout << endl;
	gotoXY(0, 17);
	cout << " Use right or left arrow to go to next/previous page" << endl;
	cout << " To delete a row, select then press Del" << endl;
	cout << " To view the detail of a product for editing, press Enter" << endl;
	cout << " Press Esc to go back to main menu" << endl;
}
void LaptopDisplay::nextPage() {
	this->_curPage++;
	if (_curPage > _numOfPages) _curPage--;
	_itemsInPage = _numOfItems % 10;
	if (_itemsInPage > 10) _itemsInPage = 10;
	interactiveProductMenu();
}
void LaptopDisplay::previouPage() {
	this->_curPage--;
	if (_curPage < 1) _curPage++;
	_itemsInPage = 10;
	interactiveProductMenu();
}
void LaptopDisplay::editProduct(int index) {
	system("cls");
	cout << "------ SELECTED PRODUCT ------" << endl;
	cout << "Product's ID: " << _laptopList[index].getID() << endl;
	cout << "Product's Name: " << _laptopList[index].getName() << endl;
	cout << "Product's Price: " << _laptopList[index].getPrice() << endl;
	cout << endl;

	char choice;
	cout << "Do you want to edit? (Y/N)" << endl;
	cout << "Your choice >> "; cin >> choice;

	switch (choice) {
	case 'y': {
		cout << endl;

		cin.ignore();
		cout << "Product's new name: "; getline(cin, _nameBuf);
		cout << "Product's new price: "; cin >> _priceBuf;

		_laptopList[index].setName(_nameBuf);
		_laptopList[index].setPrice(_priceBuf);

		interactiveProductMenu();

		break;
	}
	case 'Y': {
		cout << endl;
		cout << "Product's new name: "; getline(cin, _nameBuf);
		cin.ignore();
		cout << "Product's new price: "; cin >> _priceBuf;

		_laptopList[index].setName(_nameBuf);
		_laptopList[index].setPrice(_priceBuf);

		system("pause");

		interactiveProductMenu();

		break;

		break;
	}
	case 'n': {
		interactiveProductMenu();
		break;
	}
	case 'N': {
		interactiveProductMenu();
		break;
	}
	default:
		interactiveProductMenu();
		break;
	}

}
void LaptopDisplay::deleteProductOnList(int index) {
	system("cls");
	cout << "------ SELECTED PRODUCT ------" << endl;
	cout << "Product's ID: " << _laptopList[index].getID() << endl;
	cout << "Product's Name: " << _laptopList[index].getName() << endl;
	cout << "Product's Price: " << _laptopList[index].getPrice() << endl;
	cout << endl;

	char choice;
	cout << "Do you really want to delete this product? (Y/N)" << endl;
	cout << "Your choice >> "; cin >> choice;

	switch (choice) {
	case 'y': {
		_laptopList.erase(_laptopList.begin() + index);
		_numOfItems--;
		interactiveProductMenu();
		break;
	}
	case 'Y': {
		_laptopList.erase(_laptopList.begin() + index);
		_numOfItems--;
		interactiveProductMenu();
		break;
	}
	case 'n': {
		interactiveProductMenu();
		break;
	}
	case 'N': {
		interactiveProductMenu();
		break;
	}
	default:
		interactiveProductMenu();
		break;
	}
}
int LaptopDisplay::selectProduct(int& y) {
	_itemsInPage = _numOfItems;

	if (_numOfItems > 10) _itemsInPage -= (_curPage - 1) * 10;

	int curItemInPage;

	if (_itemsInPage <= 10) curItemInPage = _itemsInPage;
	else curItemInPage = 10;

	do {
		int key = _getch();
		switch (key) {
		case KEY_UP: {
			int position = y;
			y -= 1;
			if (y < 7) y = 7;
			selectProductMenu(position, 7);
			selectProductMenu(y, 11);
			break;
		}
		case KEY_DOWN: {
			int position = y;
			y += 1;
			if (y > 16 - (10 - curItemInPage)) y = 16 - (10 - curItemInPage);
			selectProductMenu(position, 7);
			selectProductMenu(y, 11);
			break;
		}
		case KEY_RIGHT: {
			nextPage();
			break;
		}
		case KEY_LEFT: {
			previouPage();
			break;
		}
		case KEY_ESC: {
			return 0;
			break;
		}
		case KEY_DELETE: {
			return y + 10;
			break;
		}
		case KEY_ENTER: {
			return y;
			break;
		}
		default: 
			continue;
			break;
		}
	} while (1);

}
void LaptopDisplay::interactiveProductMenu() {
	displayProduct();
	changeColor(7);

	int j = 7;
	selectProductMenu(j, 11);

	do {
		j = selectProduct(j);
		switch (j) {
		case 0: {
			system("cls");
			interactiveMenu();
			break;
		}
		// Edit cases
		case 7: {
			editProduct(0 + ((_curPage - 1) * 10));
			break;
		}
		case 8: {
			editProduct(1 + ((_curPage - 1) * 10));
			break;
		}
		case 9: {
			editProduct(2 + ((_curPage - 1) * 10));
			break;
		}
		case 10: {
			editProduct(3 + ((_curPage - 1) * 10));
			break;
		}
		case 11: {
			editProduct(4 + ((_curPage - 1) * 10));
			break;
		}
		case 12: {
			editProduct(5 + ((_curPage - 1) * 10));
			break;
		}
		case 13: {
			editProduct(6 + ((_curPage - 1) * 10));
			break;
		}
		case 14: {
			editProduct(7 + ((_curPage - 1) * 10));
			break;
		}
		case 15: {
			editProduct(8 + ((_curPage - 1) * 10));
			break;
		}
		case 16: {
			editProduct(9 + ((_curPage - 1) * 10));
			break;
		}
		//Delete cases 
		case 17:{
			deleteProductOnList(0 + ((_curPage - 1) * 10));
			break;
		}
		case 18: {
			deleteProductOnList(1 + ((_curPage - 1) * 10));
			break;
		}
		case 19: {
			deleteProductOnList(2 + ((_curPage - 1) * 10));
			break;
		}
		case 20: {
			deleteProductOnList(3 + ((_curPage - 1) * 10));
			break;
		}
		case 21: {
			deleteProductOnList(4 + ((_curPage - 1) * 10));
			break;
		}
		case 22: {
			deleteProductOnList(5 + ((_curPage - 1) * 10));
			break;
		}
		case 23: {
			deleteProductOnList(6 + ((_curPage - 1) * 10));
			break;
		}
		case 24: {
			deleteProductOnList(7 + ((_curPage - 1) * 10));
			break;
		}
		case 25: {
			deleteProductOnList(8 + ((_curPage - 1) * 10));
			break;
		}
		case 26: {
			deleteProductOnList(9 + ((_curPage - 1) * 10));
			break;
		}
		default:
			system("cls");
			break;
		}
	} while (1);
}
void LaptopDisplay::addProduct() {
	system("cls");
	cout << "------ ADD A PRODUCT ------";
	gotoXY(0, 5);
	cout << "---------------------------";
	gotoXY(0, 2);
	addLaptopList();
	gotoXY(0, 6);
	cout << "  Press Enter to continue  ";

	while (1) {
		int userInput = _getch();
		if (userInput == 13) {
			interactiveProductMenu();
			break;
		}
		else {
			system("cls");
			cout << "   !!! INVALID INPUT !!!" << endl;
			cout << "  Press Enter to continue  ";
		}
	}
}
void LaptopDisplay::deleteProductById() {
	system("cls");
	string bufId;

	cout << "------ DELETE A PRODUCT ------";
	gotoXY(0, 4);
	cout << "------------------------------";
	gotoXY(0, 2);
	cout << "Product's ID: "; cin >> bufId;
	gotoXY(0, 5);
	cout << "    Press Enter to continue   ";

	while (1) {
		int userInput = _getch();
		if (userInput == 13) {
			interactiveProductMenu();
			break;
		}
		else {
			system("cls");
			cout << "   !!! INVALID INPUT !!!" << endl;
			cout << "  Press Enter to continue  ";
		}
	}

}
void LaptopDisplay::selectMenu(int y, int color) {
	changeColor(color);
	gotoXY(3, y - 1);
	if (y == 3) cout << "  1. Display all products    ";
	else if (y == 4) cout << "  2. Add a new product       ";
	else if (y == 5) cout << "  3. Delete a product by ID  ";
	gotoXY(32, y - 1);
	changeColor(7);
}
int LaptopDisplay::selectFunction(int& y) {
	do {
		int key = _getch();
		switch (key) {
		case KEY_UP: {
			int position = y;
			y -= 1;
			if (y < 3) y = 3;
			selectMenu(position, 7);
			selectMenu(y, 11);
			break;
		}
		case KEY_DOWN: {
			int position = y;
			y += 1;
			if (y > 5) y = 5;
			selectMenu(position, 7);
			selectMenu(y, 11);
			break;
		}
		case KEY_ESC: {
			return 0;
			break;
		}
		case KEY_ENTER: {
			return y;
			break;
		}
		default: 
			continue;
			break;
		}
	} while (1);
}
void LaptopDisplay::displayMenu() {
	system("cls");
	cout << "   ------ LAPTOP SHOP APP ------" << endl;
	cout << endl;
	cout << "     1. Display all products  " << endl;
	cout << "     2. Add a new product     " << endl;
	cout << "     3. Delete a product by ID" << endl;
	cout << endl;
	cout << "   -----------------------------" << endl;
	cout << "         Press Esc to quit    " << endl;
}
void LaptopDisplay::interactiveMenu() {
	displayMenu();
	changeColor(7);

	int j = 3;
	selectMenu(j, 11);
	do {
		j = selectFunction(j);
		switch (j) {
		case 3: {
			interactiveProductMenu();
			break;
		}
		case 4: {
			addProduct();
			break;
		}
		case 5: {
			deleteProductById();
			break;
		}
		case 0: {
			exitMessage();
			exit(0);
			break;
		}
		}
	} while (1);
}