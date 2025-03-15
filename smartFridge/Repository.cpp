#include "Repository.h"
#include <iostream>

Repository::Repository() {}

void Repository::addProduct(Product& newProduct) {
	bool found = false;
	for (auto& it : products) {
		if (it.getName() == newProduct.getName() && it.getCategory() == newProduct.getCategory()) {
			it.setQuantity(it.getQuantity() + newProduct.getQuantity());
			it.setExpirationDate(newProduct.getExpirationDate());
			found = true;
		}
	}
	if (!found) {
		products.PushBack(newProduct);
	}
}

void Repository::removeProduct(const std::string& name, const std::string& category) {
	Vector<Product> temp;
	bool found = false;
	for (auto& it : products) {
		if (it.getName() == name && it.getCategory() == category) {
			found = true;
		}
		else {
			temp.PushBack(it);
		}
	}
	if (found) {
		for (int i = 0; i < temp.Size(); ++i) {
			products[i] = temp[i];
		}
		products.PopBack();

	}
}

void Repository::displayRepo() {
	std::cout << "Contents of the repo:\n";
	std::cout << "=====================\n";
	for (auto& it : products) {
		it.displayProduct();
		std::cout << '\n';
	}
	std::cout << "=====================\n";
}



