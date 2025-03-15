#include "Services.h"
#include <algorithm>

void Services::displayRepo() {
	std::cout << "Contents of the repo:\n";
	std::cout << "=====================\n";
	for (auto& it : repo.products) {
		it.displayProduct();
		std::cout << '\n';
	}
	std::cout << "=====================\n";
}

void Services::filterByName(const std::string& name) {
	bool noFilter = false;
	if (name == "no_filter") {
		noFilter = true;
	}
	Vector<Product> temp;
	for (auto& it : repo.products) {
		if (noFilter) {
			temp.PushBack(it);
		}
		else if (it.getName() == name) {
			temp.PushBack(it);
		}
	}
	//std::sort(temp.begin(), temp.end(), [](Product& a, Product& b) {return a.getQuantity() > b.getQuantity(); });
	// nu stau acum sa implementez random access iterator si ce ii mai trebuie pentru std::sort
	if (temp.Size() != 0) {
		for (int i = 0; i < temp.Size() - 1; ++i) {
			for (int j = i + 1; j < temp.Size(); ++j) {
				if (temp[i].getQuantity() > temp[j].getQuantity()) {
					Product aux = temp[j];
					temp[j] = temp[i];
					temp[i] = aux;
				}
			}
		}
	}
	std::cout << "Filter results: \n";
	std::cout << "=====================\n";
	for (auto& it : temp) {
		it.displayProduct();
		std::cout << '\n';
	}
	std::cout << "=====================\n";
}

void Services::addProduct(Product& newProduct) {
	bool found = false;
	for (auto& it : repo.products) {
		if (it.getName() == newProduct.getName() && it.getCategory() == newProduct.getCategory()) {
			it.setQuantity(it.getQuantity() + newProduct.getQuantity());
			it.setExpirationDate(newProduct.getExpirationDate());
			found = true;

			undoStack.push({ -1, newProduct }); // if we do undo, we want to subtract from quantity
		}
	}
	if (!found) {
		repo.products.PushBack(newProduct);

		undoStack.push({ 2, newProduct }); // if we undo, we want to remove the object
	}
}

void Services::removeProduct(const std::string& name, const std::string& category) {
	Vector<Product> temp;
	bool found = false;
	Product f;
	for (auto& it : repo.products) {
		if (it.getName() == name && it.getCategory() == category) {
			found = true;
			f = it; // for undo purposes
		}
		else {
			temp.PushBack(it);
		}
	}
	if (found) {
		for (int i = 0; i < temp.Size(); ++i) {
			repo.products[i] = temp[i];
		}
		repo.products.PopBack();

		undoStack.push({ 0, f });
	}
}

void Services::displayByCategory(const std::string& category) {
	std::cout << "Filter results: \n";
	std::cout << "=====================\n";
	for (auto& it : repo.products) {
		if (it.getCategory() == category) {
			it.displayProduct();
			std::cout << '\n';
		}
	}
	std::cout << "=====================\n";
}

void Services::Undo() {
	if (undoStack.empty()) {
		throw std::out_of_range("Nothing to undo...");
	}
	else if (undoStack.top().first == 0) {
		repo.addProduct(undoStack.top().second);
		redoStack.push({ 2, undoStack.top().second });
		undoStack.pop();
	}
	else if (undoStack.top().first == 2) {
		repo.removeProduct(undoStack.top().second.getName(), undoStack.top().second.getCategory());
		redoStack.push({ 0, undoStack.top().second });
		undoStack.pop();
	}
	else if (undoStack.top().first == 1) {
		repo.addProduct(undoStack.top().second);
		redoStack.push({ -1, undoStack.top().second });
		undoStack.pop();
	}
	else if (undoStack.top().first == -1) {
		for (auto& it : repo.products) {
			if (it.getName() == undoStack.top().second.getName() && it.getCategory() == undoStack.top().second.getCategory()) {
				it.setQuantity(it.getQuantity() - undoStack.top().second.getQuantity());
			}
		}
		redoStack.push({ 1, undoStack.top().second });
		undoStack.pop();
	}
}

void Services::Redo() {
	if (redoStack.empty()) {
		throw std::out_of_range("Nothing to redo...");
	}
	else if (redoStack.top().first == 0) {
		repo.addProduct(redoStack.top().second);
		undoStack.push({ 2, redoStack.top().second });
		redoStack.pop();
	}
	else if (redoStack.top().first == 2) {
		repo.removeProduct(redoStack.top().second.getName(), redoStack.top().second.getCategory());
		undoStack.push({ 0, redoStack.top().second });
		redoStack.pop();
	}
	else if (redoStack.top().first == 1) {
		repo.addProduct(redoStack.top().second);
		undoStack.push({ -1, redoStack.top().second });
		redoStack.pop();
	}
	else if (redoStack.top().first == -1) {
		for (auto& it : repo.products) {
			if (it.getName() == redoStack.top().second.getName() && it.getCategory() == redoStack.top().second.getCategory()) {
				it.setQuantity(it.getQuantity() - redoStack.top().second.getQuantity());
			}
		}
		undoStack.push({ 1, redoStack.top().second });
		redoStack.pop();
	}
}

void Services::mockData() {

	Vector<Product> prod;
	
	prod.EmplaceBack("Chicken Breast", "meat", 3, 20221220);
	prod.EmplaceBack("Salmon Fillet", "meat", 5, 20231115);
	prod.EmplaceBack("Milk", "dairy", 2, 20240210);
	prod.EmplaceBack("Cheese", "dairy", 4, 20240525);
	prod.EmplaceBack("Apple", "fruit", 1, 20240712);
	prod.EmplaceBack("Banana", "fruit", 2, 20240330);
	prod.EmplaceBack("Chocolate Cake", "sweets", 6, 20240105);
	prod.EmplaceBack("Gummy Bears", "sweets", 2, 20241018);
	prod.EmplaceBack("Beef Steak", "meat", 7, 20231222);
	prod.EmplaceBack("Yogurt", "dairy", 1, 20240605);
	prod.EmplaceBack("Orange", "fruit", 3, 20241120);
	prod.EmplaceBack("Strawberries", "fruit", 4, 20240514);
	prod.EmplaceBack("Ice Cream", "sweets", 5, 20240901);
	prod.EmplaceBack("Pork Chop", "meat", 6, 20240228);
	prod.EmplaceBack("Butter", "dairy", 3, 20240809);
	prod.EmplaceBack("Grapes", "fruit", 2, 20241225);
	prod.EmplaceBack("Muffin", "sweets", 3, 20240322);
	prod.EmplaceBack("Lamb", "meat", 8, 20240417);
	prod.EmplaceBack("Cottage Cheese", "dairy", 2, 20240630);
	prod.EmplaceBack("Blueberries", "fruit", 5, 20240915);

	for (auto& it : prod) {
		repo.addProduct(it);
	}

}
