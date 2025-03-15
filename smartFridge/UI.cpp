#include "UI.h"

void UI::printMenu()
{
	std::cout << "1. Add or update product.\n";
	std::cout << "2. Remove a product.\n";
	std::cout << "3. Display all products by name, no_filter to display all. The items are sorted in ascending order of quantity.\n";
	std::cout << "4. Display all products of a given category.\n";
	std::cout << "5. Undo last performed operation.\n";
	std::cout << "6. Redo last performed operation.\n";
	std::cout << "0. Exit\n";
	std::cout << "Your option: ";
}

void UI::Run() {
	while (1) {
		printMenu();
		int choice;
		try {
			std::cin >> choice;
		}
		catch (std::exception& e) {
			std::cout << e.what() << '\n';
		}
		if (choice == 0) {
			break;
		}
		else if (choice == 1) {
			try {
				std::cout << "Enter name, category, quantity and expiration date (yyyymmdd): ";
				std::string name, category;
				int quantity, expirationDate;
				std::cin >> name >> category >> quantity >> expirationDate;
				Product p(name, category, quantity, expirationDate);
				serv.addProduct(p);
			}
			catch (const std::exception& e){
				std::cout << e.what() << '\n';
				std::cout << "No operation performed.\n";
			}
		}
		else if (choice == 2) {
			std::string name, category;
			std::cout << "Enter name, category: ";
			std::cin >> name >> category;
			serv.removeProduct(name, category);
		}
		else if (choice == 3) {
			std::string name;
			std::cout << "Enter name (no_filter to display all). This sorts the items in ascending order of quantity: ";
			std::cin >> name;
			serv.filterByName(name);
		}
		else if (choice == 4) {
			std::string category;
			std::cout << "Enter category: ";
			std::cin >> category;
			serv.displayByCategory(category);
		}
		else if (choice == 5) {
			try {
				serv.Undo();
			}
			catch (std::exception& e) {
				std::cout << e.what() << '\n';
			}
		}
		else if (choice == 6) {
			try {
				serv.Redo();
			}
			catch (std::exception& e) {
				std::cout << e.what() << '\n';
			}
		}
		else {
			std::cout << "Invalid choice!\n";
		}
	}
}
