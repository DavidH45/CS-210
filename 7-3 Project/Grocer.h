/*
 * Grocer.h
 *
 *  Date: 04/15/2023
 *  Author: David Hendershot
 */
#pragma once
#include<iostream>
#include<string>
#include<map>
#include<fstream>
#include <cstdlib>
using namespace std;
class Grocer
{
public:
	// Constructors and public methods
	Grocer();
	Grocer(string inputFileName, string outputFileName);
	void setInputFileName(string fileName);
	void setOutputFileName(string fileName);
	void readFile();
	void writeFile();
	void printGrocerMap();
	void printMenu();
	int getMenuOption();
	void executeMenuOption(int choice);
	void searchForItem();
	void run();
	void printGrocerHistogram();

private:
	// Class member variables
	map<string, int> grocerMap;
	string inputFileName;
	string outputFileName;
};