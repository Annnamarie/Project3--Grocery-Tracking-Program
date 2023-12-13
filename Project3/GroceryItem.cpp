#include "GroceryItem.h"

//setters
GroceryItem::GroceryItem(std::string& name)
	:name(name), quantity(0) {}

//setters
GroceryItem::GroceryItem(std::string& name, int quantity)
	:name(name), quantity(quantity) {}


std::string GroceryItem::getName() const
{
	//get grocery item name
	return std::string(name);
}

int GroceryItem::getQuantity() const
{
	//get quantity for repeated items in the inventory.txt
	return quantity;
}

void GroceryItem::addItem()
{
	//add quantity if a new item is added
	quantity = quantity + 1;
}

void GroceryItem::removeItem()
{
	// decreasing the quantity if an item is removed
	quantity = quantity - 1;
}

bool GroceryItem::operator<(const GroceryItem& other) const {
	return name.compare(other.getName()) < 0;
}

