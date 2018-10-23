// ConsoleApplication25.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

const int LIST_SIZE = 100;

void showMenu() {
	system("CLS");  // clears the screan (console)
	cout << "Welcome to my Grocery Shop Application." << endl;
	cout << "-----------------------------------------" << endl;
	cout << "Please select an option:" << endl;
	cout << "l : List all fruits." << endl;
	cout << "g : List of fruits more expensive than x." << endl;
	cout << "k : List of fruits cheaper than x." << endl;
	cout << "s : Sum of all prices" << endl;
	cout << "q : Quit." << endl;
	cout << endl;
}

char getOption() {
	char option;
	// bool wrongOption = false;
	do {
		cout << "Your option: ";
		cin >> option;
		switch (tolower(option))
		{
		case 'l':
		case 'g':
		case 'k':
		case 's':
		case 'q':
			//wrongOption = false;
			return option;
		default:
			cout << "Please enter one of the valid options!" << endl;
			//wrongOption = true;
			break;
		}
	} while (1);

	return option;
}

void listAllFruits(const string fruitList[][2], int fruitsCount) {
	ofstream outFile("results.txt");

	if (outFile.is_open()) {
		for (int row = 0; row < fruitsCount; row++) {
			outFile << setw(12) << left << fruitList[row][0] << setw(10) << fruitList[row][1] << endl;
			cout << setw(12) << left << fruitList[row][0] << setw(10) << fruitList[row][1] << endl;
		}
	}
	else {
		cout << "Opening results.txt file was not successful." << endl;
	}
	outFile.close();
}
int getFruits(string fruitList[][2]) {
	int fruitsCount;
	ifstream inFile("fruits.txt");
	int row = 0;
	if (inFile.is_open()) {
		while (!inFile.eof()) {
			inFile >> fruitList[row][0] >> fruitList[row][1];
			if (!fruitList[row][0].empty() || !fruitList[row][1].empty() ) 
				row++;  // increases row counter if the row is not empty.
		}

		//getline(inFile, fruitList[0][0],' ');
	}
	else {
		cout << "Opening the file was not successful." << endl;
	}
	fruitsCount = row;

	return fruitsCount;
}

void listGreaterThanFruits(string fruitList[][2], int fruitsCount, float limit) {
	for (int row = 0; row < fruitsCount; row++) {
		if (stof(fruitList[row][1]) >= limit) {
			cout << setw(12) << left << fruitList[row][0] << setw(10) << fruitList[row][1] << endl;
		}
	}
}

void listCheaperThanFruits(string fruitList[][2], int fruitsCount, float limit) {
	for (int row = 0; row < fruitsCount; row++) {
		if (stof(fruitList[row][1]) <= limit) {
			cout << setw(12) << left << fruitList[row][0] << setw(10) << fruitList[row][1] << endl;
		}
	}
}

float sumAllPrices(string fruitList[][2], int fruitsCount) {
	float sum = 0;

	for (int row = 0; row < fruitsCount; row++) {
		sum += stof(fruitList[row][1]);
	}

	return sum;
}

float getUserInput(string message, int lowerLimit, int upperLimit) {
	int userInput;
	bool validInput = true;

	do {
		cout << message;
		cin >> userInput;
		if (userInput < lowerLimit || userInput > upperLimit) {
			cout << "The input is not between " << lowerLimit << " and " << upperLimit << "! Try again." << endl;
			validInput = false;
		}
	} while (!validInput);

	return userInput;
}

int processTheOption(char option) {
	int success = 1;
	static int fruitsCount; // it is defined as static as we need to define it once and use it many times.
	float sum;
	int priceLimit;
	float userInput;

	static string fruitList[LIST_SIZE][2]; // fruitList array is defined as static, means it is defined only once, the first time function processThe Option is called.
	if (fruitList[0][0].empty()) // getFruits function is called if the fruitList array is empty, means it is the first time that processTheOption function is called. 
		fruitsCount = getFruits(fruitList);
	switch (option)
	{
	case 'l':
		listAllFruits(fruitList, fruitsCount);
		break;
	case 'g':
		userInput = getUserInput("Enter the desired price: ", 0, 10);
		listGreaterThanFruits(fruitList, fruitsCount, userInput);
		break;
	case 'k':
		userInput = getUserInput("Enter the desired price: ", 0, 10);
		listCheaperThanFruits(fruitList, fruitsCount, userInput);
		break;
	case 's':
		sum = sumAllPrices(fruitList, fruitsCount);
		cout << "The sum is: " << sum << endl;
		break;
	case 'q':
		success = 0;
		break;
	default:
		break;
	}

	return success;
}
int main()
{
	char option;
	int success;
	do {
		showMenu();
		option = getOption();
		success = processTheOption(option);
		system("pause");
	} while (option != 'q');

	return 0;
}

