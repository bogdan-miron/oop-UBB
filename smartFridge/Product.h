#pragma once
#include <iostream>
#include <cassert>

class Product {
private:
	std::string name;
	std::string category;
	size_t quantity;
	size_t expirationDate;

public:
	Product();

	Product(const std::string& name, const std::string& category, const int& quantity, const int& expirationDate);

	std::string getName();

	std::string getCategory();

	int getQuantity();

	int getExpirationDate();

	void setName(const std::string& newName);

	void setCategory(const std::string& newCategory);

	void setQuantity(const size_t& newQuantity);

	void setExpirationDate(const size_t& newExpirationDate);

	void displayProduct();

};
