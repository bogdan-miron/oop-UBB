#include "Product.h"

Product::Product() {}

Product::Product(const std::string& name, const std::string& category, const int& quantity, const int& expirationDate) {
	if (!(category == "dairy" || category == "sweets" || category == "meat" || category == "fruit")) {
		throw std::invalid_argument("Category not valid.");
	}
	if (quantity < 0) {
		throw std::invalid_argument("Quantity must be positive and an integer.");
	}
	if (expirationDate <= 0) {
		throw std::invalid_argument("Expiration date must be positive.");
	}
	this->name = name;
	this->category = category;
	this->quantity = quantity;
	this->expirationDate = expirationDate;
}

std::string Product::getName() {
	return name;
}

std::string Product::getCategory() {
	return category;
}

int Product::getQuantity() {
	return quantity;
}

int Product::getExpirationDate() {
	return expirationDate;
}

void Product::setName(const std::string& newName) {
	name = newName;
}

void Product::setCategory(const std::string& newCategory) {
	if (!(newCategory == "dairy" || newCategory == "sweets" || newCategory == "meat" || newCategory == "fruit")) {
		throw std::invalid_argument("Category not valid.");
	}
	category = newCategory;
}

void Product::setQuantity(const size_t& newQuantity){
	if (newQuantity <= 0) {
		throw std::invalid_argument("Quantity must be positive and integer.");
	}
	quantity = newQuantity;
}

void Product::setExpirationDate(const size_t& newExpirationDate){
	if (newExpirationDate <= 0) {
		throw std::invalid_argument("Expiration date must be positive.");
	}
	expirationDate = newExpirationDate;
}

void Product::displayProduct() {
	std::cout << "Name: " << name << ", Category: " << category << ", Quantity: " << quantity << ", Expiration Date: " << expirationDate;
}
