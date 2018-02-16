//loadfactor är ~70% (vilket skulle vara bra enligt källor på stackoverflow) collisions = 727


#include "stdafx.h"
#include <fstream>
#include <string>
#include <iostream>

#include "HashTableChaining.h"
#include "EngWord.h"
//#include "Course.h"
#include <windows.h> // WinApi header


int const NRPERTIME = 20;
int const HASHTABLESIZE = 409;
const std::string EXIT = "G";
const std::string TEST = "TEST";
const std::string LOADTEST = "LT";

const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
// Add color to text
const int colorPrompt = 3;
const int colorGreen = 2;
const int colorRed = 4;

void print(const std::string & toPrint, const int color);
void printCheckEng(const int toPrint, const int toCheck);
void printCheckEng(const std::string &toPrint, const std::string &toCheck);
void printCheckEngDouble(const double &toPrint, const double &toCheck);

void loadTest(const EngWord arr[], const  int cap);


void doTests(HashTableChaining<EngWord> table, EngWord arr[], int cap);

EngWord* getFile2(int & cap);
HashTableChaining<EngWord> hashThis(const EngWord* arr, const int arrCap);
void userInteractions(const HashTableChaining<EngWord> & table, EngWord arr[], int arrCap);
std::string* getWords(const std::string &sentence, int & cap);
bool isLastDot(const std::string & str);
std::string getInputEng();


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	print("starting...\n", colorPrompt);


	int arrCap = 0;
	
	EngWord* arr = getFile2(arrCap);
	HashTableChaining<EngWord> table = hashThis(arr, arrCap);
	


	userInteractions(table, arr, arrCap);
				


			
		

		
	
	delete[] arr;
	
	return 0;
}

void print(const std::string & toPrint, const int color) {
	SetConsoleTextAttribute(hConsole, color);
	std::cout << toPrint;
	SetConsoleTextAttribute(hConsole, 7);
}

void printCheckEng(const std::string & toPrint, const std::string & toCheck)
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

void printCheckEngDouble(const double & toPrint, const double & toCheck)
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

void printCheckEng(const int toPrint, const int toCheck) {
	if (toPrint == toCheck)
	{
		print(std::to_string(toPrint) + "\n", colorGreen);
	}
	else
	{
		print(std::to_string(toPrint) + "\n", colorRed);
	}
}

void loadTest(const EngWord arr[], const int cap)
{
	for (int i = 0; i < 580; i = i +20)
	{
		HashTableChaining<EngWord> table(cap/20 + i);
		for (int k = 0; k < cap; ++k)
		{
			if (!table.insert(arr[k]))
			{
				print("fail to insert nr " + std::to_string(k) + "\n", colorRed);
			}
		}
		std::cout << "size of table: " + std::to_string(cap/20 + i) + (cap/20 + i < 100 ? " " : "") + " load factor:     " + std::to_string(table.loadFactor()) << "\n";
		std::cout << "                        Collisions: " + std::to_string(table.getNrOfCollisions()) + "\n\n";
	}
}

void doTests(HashTableChaining<EngWord> table, EngWord arr[], int cap)
{
	if (cap >= 28)
	{
		std::cout << "test made with table size 55 in mind\na[27]: ";
		printCheckEng(arr[27].getVal(), "a");

		std::cout << "contains arr[0]: ";
		printCheckEng(table.contains(arr[27]), 42);

		std::cout << "getNrOfElements: ";
		printCheckEng(table.getNrOfElements(), 999);

		std::cout << "remove: ";
		printCheckEng(table.remove(arr[27]), 1);

		std::cout << "getNrOfElements: ";
		printCheckEng(table.getNrOfElements(), 998);

		std::cout << "contains removed item: ";
		printCheckEng(table.contains(arr[27]), -1);

		std::cout << "nr of colisions: ";
		printCheckEng(table.getNrOfCollisions(), table.getNrOfElements() - HASHTABLESIZE);

		std::cout << "loadFactor: ";
		printCheckEngDouble(table.loadFactor(), 1);

		std::cout << "insert: ";
		printCheckEng(table.insert(arr[27]), 1);

		std::cout << "makeEmpty: ";
		table.makeEmpty();
		printCheckEng(table.getNrOfElements(), 0);

		std::cout << "insert: ";

		if (
			table.insert(arr[0]) == 1 &&
			table.insert(arr[1]) == 1 &&
			table.insert(arr[2]) == 1 &&
			table.insert(arr[3]) == 1 &&
			table.insert(arr[4]) == 1 &&
			table.insert(arr[5]) == 1 &&
			table.insert(arr[6]) == 1 &&
			table.insert(arr[7]) == 1 &&
			table.insert(arr[8]) == 1 &&

			table.insert(arr[9]) == 1 &&
			table.insert(arr[10]) == 1 &&
			table.insert(arr[11]) == 1 &&
			table.insert(arr[12]) == 1 &&
			table.insert(arr[13]) == 1 &&
			table.insert(arr[14]) == 1 &&
			table.insert(arr[15]) == 1 &&

			table.insert(arr[16]) == 1 &&
			table.insert(arr[17]) == 1 &&
			table.insert(arr[18]) == 1 &&
			table.insert(arr[19]) == 1 &&
			table.insert(arr[20]) == 1 &&
			table.insert(arr[21]) == 1 &&
			table.insert(arr[22]) == 1 &&
			table.insert(arr[23]) == 1 &&
			table.insert(arr[24]) == 1 &&
			table.insert(arr[25]) == 1 &&
			table.insert(arr[26]) == 1
			)
		{
			print("inserted 27 items\n", colorGreen);
		}
		else
		{
			print("failed Inserted\n", colorRed);
		}

		std::cout << "contains arr[27]: ";
		printCheckEng(table.contains(arr[27]), -1);

		std::cout << "getNrOfElements: ";
		printCheckEng(table.getNrOfElements(), 27);

		std::cout << "remove: ";
		printCheckEng(table.remove(arr[27]), 0);

		std::cout << "nr of colisions 1 : ";
		printCheckEng(table.getNrOfCollisions(), 3);

		std::cout << "loadFactor: ";
		printCheckEngDouble(table.loadFactor(), 0);

		{
			HashTableChaining<EngWord> table2 = table;

			std::cout << "	new table\ncontains arr[0]: ";
			printCheckEng(table2.contains(arr[27]), -1);

			std::cout << "getNrOfElements: ";
			printCheckEng(table2.getNrOfElements(), 27);

			std::cout << "remove: ";
			printCheckEng(table2.remove(arr[27]), 0);

			std::cout << "nr of colisions 2: ";
			printCheckEng(table2.getNrOfCollisions(), 3);

			std::cout << "nr of colisions 1: ";
			printCheckEng(table2.getNrOfCollisions(), 3);

			std::cout << "make empty 2\n";
			table2.makeEmpty();

			std::cout << "contains arr[0] 2: ";
			printCheckEng(table2.contains(arr[27]), -1);

			std::cout << "getNrOfElements 2: ";
			printCheckEng(table2.getNrOfElements(), 0);

			std::cout << "remove 2 : ";
			printCheckEng(table2.remove(arr[27]), 0);

			std::cout << "nr of colisions 2: ";
			printCheckEng(table2.getNrOfCollisions(), 0);


			std::cout << "contains arr[0] 1: ";
			printCheckEng(table.contains(arr[27]), -1);

			std::cout << "getNrOfElements 1: ";
			printCheckEng(table.getNrOfElements(), 27);

			std::cout << "remove 1 : ";
			printCheckEng(table.remove(arr[27]), 0);

			std::cout << "nr of colisions 1: ";
			printCheckEng(table.getNrOfCollisions(), 3);

			table2 = table;
			std::cout << "trying = \nnr of colisions 2: ";
			printCheckEng(table2.getNrOfCollisions(), 3);
			std::cout << "nr of colisions 1: ";
			printCheckEng(table.getNrOfCollisions(), 3);

		}


		std::cout << "nr of colisions 1: ";
		printCheckEng(table.getNrOfCollisions(), 3);

		std::cout << "restCollisions 1 \n ";
		table.resetNrOfCollisions();

		std::cout << "nr of colisions 1: ";
		printCheckEng(table.getNrOfCollisions(), 3);
	}
 
}

EngWord * getFile2(int & cap)
{
	int arrCap = 0;
	EngWord *arr;
	arr = new EngWord[0];
	EngWord temp[NRPERTIME];
	std::string tempStr;
	std::ifstream in("C:/temp/engWords.txt");

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
				temp[i] = tempStr;
				i++;


			}

			if (temp[i] == "")
			{
				i--;
			}

			if (i != 0)
			{
				//utöka arr med i
				EngWord *expand = new EngWord[arrCap + i];
				for (int k = 0; k < arrCap; k++)
				{
					expand[k] = arr[k];
				}
				delete[] arr;
				arr = expand;

				//för in temp i arr
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

	return arr;
}

HashTableChaining<EngWord> hashThis(const EngWord * arr, const int arrCap)
{
	HashTableChaining<EngWord> table(HASHTABLESIZE);

	for (int i = 0; i < arrCap; i++)
	{
		table.insert(arr[i]);
	}

	std::cout << "loadFactor: " << std::to_string(table.loadFactor()) + "\n" + "NrOfCollisions: " + std::to_string(table.getNrOfCollisions()) + "\n" + "collisions/HASHTABLESIZE: " + std::to_string((double)(table.getNrOfCollisions()) / HASHTABLESIZE) + "\n";


	return table;
}

void userInteractions(const HashTableChaining<EngWord>& table, EngWord arr[], int arrCap)
{
	std::string input = "";

	std::cout << "type \"" + EXIT + ".\" to exit, \"" + TEST + ".\" to run tests, \"" + LOADTEST + ".\" to make load test\n";
	while (input != EXIT)
	{
		input = "";
		do {
			input += getInputEng();
		} while (!isLastDot(input));
		input = input.substr(0, input.size() - 1);


		int cap = 0;
		std::string* words = getWords(input, cap);
		for (int i = 0; i < cap; ++i)
		{
			EngWord InElem = words[i];

			if (table.contains(InElem) == -1)
			{
				print(words[i] + "\n", colorRed);
			}
		}
		delete[] words;

		if (input == TEST)
		{
			EngWord a[28];
			a[0] = arr[1];
			a[1] = arr[2];
			a[2] = arr[3];
			a[3] = arr[4];
			a[4] = arr[5];
			a[5] = arr[6];
			a[6] = arr[7];
			a[7] = arr[8];
			a[8] = arr[9];

			a[9] = arr[10];
			a[10] = arr[11];
			a[11] = arr[12];
			a[12] = arr[13];
			a[13] = arr[14];
			a[14] = arr[15];
			a[15] = arr[16];

			a[16] = arr[80];
			a[17] = arr[120];
			a[18] = arr[170];
			a[19] = arr[190];
			a[20] = arr[230];
			a[21] = arr[280];
			a[22] = arr[380];
			a[23] = arr[480];
			a[24] = arr[580];
			a[25] = arr[680];
			a[26] = arr[780];
			a[27] = arr[0];
			doTests(table, a, 28);
		}
		else if (input == LOADTEST)
		{
			loadTest(arr, arrCap);
		}
	}
}

std::string* getWords(const std::string & sentence, int & cap)
{
	std::string* strWords = new std::string[1];
	std::string* temp;
	cap = 1;
	int counter = 0;
	for (short i = 0; i<sentence.length(); i++) {
		if (sentence[i] == ' ')
		{
			counter++;
			temp = new std::string[cap + 1];
			for (int k = 0; k < cap; k++)
			{
				temp[k] = strWords[k];
			}
			delete[] strWords;
			strWords = temp;
			cap++;
		}
		else
		{
			
			strWords[counter] += sentence[i];
		}
	}

	return strWords;
}

bool isLastDot(const std::string & str)
{
	bool retVal = false;
	if (str != "" && str[str.size() - 1] == '.')
	{
		retVal = true;
	}
	return retVal;
}

std::string getInputEng()
{
	std::string in;
	std::getline(std::cin, in);
	return in;
}
