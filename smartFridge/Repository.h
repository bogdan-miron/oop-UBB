#pragma once
#include "Vector.h"
#include "Product.h"


class Repository {

	friend class Services;

private:
	Vector<Product> products;

public:
	Repository();
	void addProduct(Product& newProduct);
	void removeProduct(const std::string& name, const std::string& category);
	void displayRepo();
};
