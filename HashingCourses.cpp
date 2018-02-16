//HASHTABLESIZE är 19 då det get enbart 1 miss samt ligger runt 75% loadFactorial vilket är bra då man utnyttjar merparten av minnet


#include "stdafx.h"
#include <fstream>
#include <string>
#include <iostream>

#include "HashTableLinearProbing.h"
//#include "Element.h"
#include "Course.h"
#include <windows.h> // WinApi header


int const NRPERTIME = 20;
int const HASHTABLESIZE = 19;

const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
// Add color to text
const int colorPrompt = 3;
const int colorGreen = 2;
const int colorRed = 4;

const std::string EXIT = "G";
const std::string TEST = "test";
const std::string LOADTEST = "LT";

void print(const std::string & toPrint, const int color);
void printCheck(const int toPrint, const int toCheck);
void printCheck(const std::string &toPrint, const std::string &toCheck);
void printCheckDouble(const double &toPrint, const double &toCheck);

void loadTest(const Course arr[], const  int cap);
void doTests(HashTableLinear<Course> table);
std::string getInput();

HashTableLinear<Course> hashThis(const Course* arr, const int arrCap);
Course*& getFile(int & cap);
void userInteraction(const HashTableLinear<Course> & table, Course arr[], int arrCap);
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //:P


	print("starting...\n", colorPrompt);


	int arrCap = 0;
	Course *arr = getFile(arrCap);
	

	HashTableLinear<Course> table = hashThis(arr, arrCap);
		
			
	userInteraction(table, arr, arrCap);
		

	
	delete[] arr;

	return 0;
}

void print(const std::string & toPrint, const int color) {
	SetConsoleTextAttribute(hConsole, color);
	std::cout << toPrint;
	SetConsoleTextAttribute(hConsole, 7);
}

void printCheck(const std::string & toPrint, const std::string & toCheck)
{
	if (toPrint == toCheck)
	{
		print(toPrint + "\n", colorGreen);
	}
	else
	{
		print(toPrint + "\n", colorRed);
	}
}

void printCheckDouble(const double & toPrint, const double & toCheck)
{
	if (toPrint == toCheck)
	{
		print(std::to_string(toPrint) + "\n", colorGreen);
	}
	else
	{
		print(std::to_string(toPrint) + "\n", colorRed);
	}
}

void loadTest(const Course  arr[], const int cap) 
{
 	for(int i = 0; i < 30; ++i)
	{
		HashTableLinear<Course> table(cap + i);
		for (int k = 0; k < cap; ++k)
		{
			if (!table.insert(arr[k]))
			{
				print("fail to insert nr " + std::to_string(k) + "\n", colorRed);
			}
		}
		std::cout <<"size of table: "  + std::to_string(cap + i) + (cap + i < 10 ? " " : "") + " load factor:     " + std::to_string(table.loadFactor()) << "\n";
		std::cout << "                       Collisions: " + std::to_string(table.getNrOfCollisions()) + "\n\n";
	}
}

void doTests(HashTableLinear<Course> table)
{
	Course arr[1];
	arr[0].setCode("DV1490");
	arr[0].setHp(7.5);
	arr[0].setName("Algoritmer och datastrukturer");

	//std::cout << "lenth of arr: " << std::to_string(arrCap) << "\n";

	/*std::cout << "a[0]: ";
	printCheck(arr[0].getCode(), "DV1490");
	printCheck(arr[0].getName(), "Algoritmer och datastrukturer");
	printCheck(std::to_string(arr[0].getHp()), "7.500000");*/


 	std::cout << "insert: ";
	printCheck(table.insert(arr[0]), 1);


	std::cout << "contains arr[0]: ";
	printCheck(table.contains(arr[0]), 34);



	std::cout << "getNrOfElements: ";
	printCheck(table.getNrOfElements(), 14);


	std::cout << "remove: ";
	printCheck(table.remove(arr[0]), 1);

	std::cout << "getNrOfElements: ";
	printCheck(table.getNrOfElements(), 13);

	std::cout << "contains removed item: ";
	printCheck(table.contains(arr[0]), -1);

	std::cout << "nr of colisions: ";
	printCheck(table.getNrOfCollisions(), 0);

	std::cout << "loadFactor: ";
	printCheckDouble(table.loadFactor(), 0.25454545454545454545454545454545454545454);
		
	std::cout << "insert: ";
	printCheck(table.insert(arr[0]), 1);
	

	std::cout << "makeEmpty: ";
	//table.remove();
	table.makeEmpty();
	printCheck(table.getNrOfElements(), 0);

	std::cout << "insert: ";

	if (
		table.insert(arr[0]) == 1 &&
		table.insert(arr[0]) == 1 &&
		table.insert(arr[0]) == 1 &&
		table.insert(arr[0]) == 1 &&
		table.insert(arr[0]) == 1 &&
		table.insert(arr[0]) == 1 &&
		table.insert(arr[0]) == 1 &&
		table.insert(arr[0]) == 1 &&
		table.insert(arr[0]) == 1

		)
	{
		print("inserted 9 items\n", colorGreen);
	}
	else
	{
		print("failed Inserted\n", colorRed);
	}

	std::cout << "contains arr[0]: ";
	printCheck(table.contains(arr[0]), -1);

	std::cout << "getNrOfElements: ";
	printCheck(table.getNrOfElements(), 9);

	std::cout << "remove: ";
	printCheck(table.remove(arr[0]), 0);

	std::cout << "nr of colisions 1 : ";
	printCheck(table.getNrOfCollisions(), 0);

	std::cout << "loadFactor: ";
	printCheckDouble(table.loadFactor(), 0.163636363636363636);

	{
		HashTableLinear<Course> table2 = table;

		std::cout << "	new table\ncontains arr[0]: ";
		printCheck(table2.contains(arr[0]), -1);

		std::cout << "getNrOfElements: ";
		printCheck(table2.getNrOfElements(), 9);

		std::cout << "remove: ";
		printCheck(table2.remove(arr[0]), 0);

		std::cout << "nr of colisions 2: ";
		printCheck(table2.getNrOfCollisions(), 0);

		std::cout << "nr of colisions 1: ";
		printCheck(table2.getNrOfCollisions(), 0);

		std::cout << "make empty 2\n";
		table2.makeEmpty();

		std::cout << "contains arr[0] 2: ";
		printCheck(table2.contains(arr[0]), -1);

		std::cout << "getNrOfElements 2: ";
		printCheck(table2.getNrOfElements(), 0);

		std::cout << "remove 2 : ";
		printCheck(table2.remove(arr[0]), 0);

		std::cout << "nr of colisions 2: ";
		printCheck(table2.getNrOfCollisions(), 0);


		std::cout << "contains arr[0] 1: ";
		printCheck(table.contains(arr[0]), -1);



		std::cout << "getNrOfElements 1: ";
		printCheck(table.getNrOfElements(), 9);



		std::cout << "remove 1 : ";
		printCheck(table.remove(arr[0]), 0);



		std::cout << "nr of colisions 1: kokokokkkokoko ";
		printCheck(table.getNrOfCollisions(), 0);

		table2 = table;
		std::cout << "trying = \nnr of colisions 2: ";
		printCheck(table2.getNrOfCollisions(), 0);
		std::cout << "         nr of getNrOfElements 1: ";
		printCheck(table.getNrOfElements(), 0);


		table2.insert(arr[0]);
	}

	std::cout << "         nr of getNrOfElements 1 after }: ";
	printCheck(table.getNrOfElements(), 0);

	std::cout << "nr of colisions 1: ";
	printCheck(table.getNrOfCollisions(), 0);

	std::cout << "restCollisions 1 \n ";
	table.resetNrOfCollisions();

	std::cout << "nr of colisions 1: ";
	printCheck(table.getNrOfCollisions(), 0);


		
}

std::string getInput()
{
	std::string in;
	std::getline(std::cin, in);
	return in;
}



void printCheck(const int toPrint, const int toCheck) {
	if (toPrint == toCheck)
	{
		print(std::to_string(toPrint) + "\n", colorGreen);
	}
	else
	{
		print(std::to_string(toPrint) + "\n", colorRed);
	}
}

HashTableLinear<Course> hashThis(const Course * arr, const int arrCap)
{
	HashTableLinear<Course> table(HASHTABLESIZE);
	for (int i = 0; i < arrCap; i++)
	{
		table.insert(arr[i]);
	}


	std::cout << "loadFactor: " << std::to_string(table.loadFactor()) + "\n" + "NrOfCollisions: " + std::to_string(table.getNrOfCollisions()) + "\n" + "collisions/HASHTABLESIZE: " + std::to_string((double)(table.getNrOfCollisions())/HASHTABLESIZE) + "\n";
	return table;
}

Course *& getFile(int & cap)
{
	int arrCap = 0;
	Course *arr;
	arr = new Course[0];
	Course temp[NRPERTIME];
	std::string tempStr;
	std::ifstream in("C:/temp/courses.txt");

	if (in.is_open())
	{
		while (in.is_open())
		{
			int i = 0;
			bool check = true;
			//få NRPERTIME antal många ord in i temp arrayen
			while ((check = !in.eof()) && i < NRPERTIME)
			{

				std::getline(in, tempStr);
				if (tempStr != "")
				{
					temp[i].setCode(tempStr);

					std::getline(in, tempStr);
					temp[i].setName(tempStr);

					std::getline(in, tempStr);
					temp[i].setHp(std::stod(tempStr));

					i++;
				}




			}



			if (i != 0)
			{
				//utöka arr med i
				Course *expand = new Course[arrCap + i];
				for (int k = 0; k < arrCap; k++)
				{
					expand[k] = arr[k];
				}
				delete[] arr;
				arr = expand;

				//för in temp i arr //varför? 
				for (int k = 0; k != i; k++)
				{
					arr[arrCap] = temp[k];
					arrCap++;
				}
			}
			else
			{
				in.close();
				cap = arrCap;
				
			}

		}

	}
	else
	{
		std::cout << "file not found" << std::endl << "exits..." << std::endl;
	}

	if (true)
	{
		std::cout << "arr[0]: " << arr[0].getCode()<< "\n" ;
	}

  	return arr;
}

void userInteraction(const HashTableLinear<Course>& table, Course arr[], int arrCap)
{
	std::string code = "";
	std::cout << "type \"" << EXIT << "\" to exit, \"" + TEST + "\" to run tests, \"";
	std::cout << LOADTEST;
	std::cout << "\" to run load factor tests\n";

	while (code != EXIT)
	{
		Course input;
		code = getInput();
		input.setCode(code);
		int pos = table.contains(input);
		if (pos != -1)
		{
			Course output = table.get(pos);
			print("\n" + output.toString() + "\n", colorGreen);

		}
		else if (code == TEST)
		{
			doTests(table);
		}
		else if (code == LOADTEST)
		{
			loadTest(arr, arrCap);
		}
		else
		{
			print("\ndid not find cource\n\n", colorRed);
		}
	}
}
