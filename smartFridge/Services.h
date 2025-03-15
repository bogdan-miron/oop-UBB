#pragma once
#include "Repository.h"
#include <stack>

class Services {
private:

	Repository& repo;
	std::stack< std::pair<int, Product> > undoStack; // int is for the code, 0 -> add new entry, 1 -> add to q, -1 - remove from q, 2 remove entry
	std::stack< std::pair<int, Product> > redoStack;
	

public:
	Services(Repository& r) : repo(r) {}
	
	void displayRepo();

	void filterByName(const std::string& name);

	void addProduct(Product& newProduct);

	void removeProduct(const std::string& name, const std::string& category);

	void displayByCategory(const std::string& category);

	void Undo();

	void Redo();

	void mockData();

};
