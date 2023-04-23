/*
 * Grocer.cpp
 *
 *  Date: 04/15/2023
 *  Author: David Hendershot
 */
#include "Grocer.h"

Grocer::Grocer() { // Sets the default input and output files
	setInputFileName("CS210_Project_Three_Input_File.txt");
	setOutputFileName("frequency.dat");

	// Read input file and write output file
	readFile();
	writeFile();
}

Grocer::Grocer(string inputFileName, string outputFileName) {
	// Set user-specified input and output file names
	setInputFileName(inputFileName);
	setOutputFileName(outputFileName);
	// Read input file and write output file
	readFile();
	writeFile();
}

void Grocer::setInputFileName(string fileName) {
	// Set input file name
	inputFileName = fileName;
}

void Grocer::setOutputFileName(string fileName) {
	// Set output file name
	outputFileName = fileName;
}
void Grocer::writeFile() {
	// Open output file
	ofstream outFS;
	outFS.open(outputFileName);

	// Check if file was successfully opened
	if (!outFS.is_open()) {
		cout << "Could not open file." << endl;
	}

	// Iterate over the map and write each key-value pair to the output file
	for (auto itr = grocerMap.begin(); itr != grocerMap.end(); itr++) {
		outFS << itr->first << " " << itr->second << endl;
	}
	outFS.close(); // Close output file
}
void Grocer::readFile() {
	// Open input file
	ifstream inFS;
	inFS.open(inputFileName);

	// Check if file was successfully opened
	if (!inFS.is_open()) {
		cout << "Could not open file";
	}
	string tempString;
	map<string, int> tempMap;

	// Read each word from the input file and count the frequency of each word
	while (!inFS.fail()) {
		inFS >> tempString;
		if (tempMap.count(tempString)) {
			tempMap[tempString] += 1;
		}
		else {
			tempMap.insert(std::pair<std::string, int>(tempString, 1));
		}
	}
	grocerMap = tempMap;
	inFS.close(); // Close input file
}

void Grocer::printGrocerMap() {
	// Iterate over the map and print each key-value pair to the console
	for (auto itr = grocerMap.begin(); itr != grocerMap.end(); itr++) {
		cout << itr->first << " " << itr->second << endl;
	}
}
void Grocer::printMenu() {
	// Print the main menu to the console, with formatting
	cout << "\033[1m----------[ Main Menu ]----------\033[22m" << endl;
	cout << "\033[1m| 1.\033[22m Search For Groccery Item." << endl;
	cout << "\033[1m| 2.\033[22m Show All Grocery Items And Amounts." << endl;
	cout << "\033[1m| 3.\033[22m Show All Grocery Items In Histogram" << endl;
	cout << "\033[1m| 4.\033[22m Exit The Program" << endl;
	int choice = getMenuOption(); // Get user's menu choice
	executeMenuOption(choice); // Execute the user's menu choice
}
void Grocer::run() {
	while (true) { // Continuously print the menu and wait for user input until the program is exited
		printMenu();
	}
}
int Grocer::getMenuOption() {
	int menuOption;
	while (true) {
		// Prompt user for a menu option
		cout << "Choose a option: ";
		cin >> menuOption;
		try {
			// Validate user input and throw an exception if it is invalid
			if (menuOption < 1 || menuOption > 4) {
				throw std::out_of_range("Invalid input. It must be between 1 and 4.");
				menuOption = 0;
			} else {
				break;
			}
		}
		catch (std::out_of_range& e) {
			std::cout << e.what() << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
	return menuOption;
}

void Grocer::executeMenuOption(int choice) {
	// Clear the console screen and execute the user's menu choice
	system("cls");
	if (choice == 1) {
		searchForItem();
	}
	else if (choice == 2) {
		printGrocerMap();
	}
	else if (choice == 3) {
		printGrocerHistogram();
	}
	else if (choice == 4) {
		exit(0);
	}
	// Wait for user to press any key before clearing the console screen again
	system("pause");
	system("cls");
}
void Grocer::searchForItem() {
	string input;
	bool inputIsValid = false;
	while (!inputIsValid) { 
		// Prompt user for an item name to search for
		cout << "Please enter an item name to search for: ";
		cin >> input;
		try {
			// Validate user input and throw an exception if it is invalid
			for (char c : input) {
				if (!isalpha(c)) {
					throw invalid_argument("Input is not a valid string.");
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
			}
			inputIsValid = true;
			// Search for the input string in the map and print the result to the console
			if (grocerMap.find(input) != grocerMap.end()) {
				cout << "There are " << grocerMap[input] << " " << input << " in the system." << endl;
			}
			else {
				cout << "There are no " << input << " in the system." << endl;
			}
		}
		catch (const invalid_argument& e) {
			cout << "Error: " << e.what() << std::endl;
		}
	}
}

void Grocer::printGrocerHistogram() {
	// Iterate over the map and print a histogram of each key-value pair to the console
	for (auto itr = grocerMap.begin(); itr != grocerMap.end(); itr++) {
		cout << itr->first << " ";
		int tempInt = itr->second;
		for (int i = 0; i < tempInt; i++) {
			cout << "*";
		}
		cout << endl;
	}
}