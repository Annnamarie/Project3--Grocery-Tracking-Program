#include <iostream>
#include <fstream>
#include <set>

#include "GroceryItem.h"

using namespace std;

//method to read the Inventory.txt file
set<GroceryItem> readInventoryFile(const string& fileName) {
	
	//declaring grocery items set
	set<GroceryItem> items;

	ifstream file(fileName);
	
	//reading and openning file
	if (file.is_open()) {
		string itemName;

		//adding items into the GroceryItem set
		while (getline(file, itemName)) {
			GroceryItem newItem(itemName);
			auto existingItem = items.find(newItem);

			if (existingItem != items.end()) {
				//getting the quanity for items that are listed multiple times in the file
				int existingQuantity = existingItem->getQuantity();
				newItem.addItem();
				//erasing existing item from the set
				items.erase(existingItem);
			}

			//Increment quanity for the new or existing item
			newItem.addItem();
			items.insert(newItem);
		}
		//closing file
		file.close();
	}

	return items;
}


int main() {

	try {

		set<GroceryItem> items = readInventoryFile("Inventory.txt");

		int userChoice;
		string itemName;

		//creating back up data
		ofstream outFile("frequency.dat");

		if (outFile.is_open()) {
			for (const GroceryItem& item : items) {
				outFile << item.getName() << " " << item.getQuantity() << endl;
			}
			outFile.close();
		}

		do {
			//output menu
			cout << endl << "Menu" << endl;
			cout << "1. Search for an item." << endl;
			cout << "2. Display all frequencies" << endl;
			cout << "3. Print histogram." << endl;
			cout << "4. Exit" << endl;
			cout << "Enter your choice: ";

			//input validation when input is a character or string
			while (!(cin >> userChoice)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid. Please enter a number: ";
			}

			//menu
			switch (userChoice) {
			case 1: {
				//Searching for an item
				cout << "Enter the grocery item you would like to search: ";
				cin >> itemName;

				GroceryItem searchItem(itemName);
				auto foundItem = items.find(searchItem);

				//if item is found
				if (foundItem != items.end()) {
					cout << "Item found. Quantity: " << foundItem->getQuantity() << endl;
				}
				//if item is not found
				else {
					cout << "Item not found." << endl;
				}
				break;
			}

			case 2: {
				//Implement display for all frequencies
				for (const GroceryItem& item : items) {
					cout << "Item: " << item.getName() << ", Quantity: " << item.getQuantity() << endl;
				}
				break;
			}
			case 3: {
				//print histogram (quantity displayed as *)
				for (const GroceryItem& item : items) {
					cout << item.getName() << " ";
					for (int i = 0; i < item.getQuantity(); ++i) {
						cout << "*";
					}
					cout << endl;
				}
				break;
			}
			case 4: {
				//Exiting program
				cout << "Goodbye!" << endl;
				break;
			}
			default:
				cout << "Invalid input. Please try again (1-4): " << endl;
			}
		} while (userChoice != 4);
	}
	catch (const std::bad_exception& e) {
		cout << "Error: " << e.what() << endl;
	}

	return 0;
}