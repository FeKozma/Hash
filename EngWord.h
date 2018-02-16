#ifndef ELEMENT_H
#define ELEMENT_H

#include "Hash.h"
#include <string>

class EngWord
{
private:
	std::string val;
	//EngWord *next; //no
	//bool equal(const EngWord & aEngWord); //no

public:
	/*EngWord(EngWord *next = nullptr, std::string val = ""); //nja
	void add(std::string val); //no
	bool remove(std::string val);
	~EngWord();
	void deallocate();
	void resetCollisionMaybe();

	bool getIfExists(std::string val);
	bool getIfOccupied();
	int getNrOfElem();
	EngWord& operator=(const EngWord & aEngWord);
	void operator+=(const std::string & aString);
	bool operator==(const EngWord &aEngWord);
	bool operator!=(const EngWord &aEngWord);
	*/
	EngWord(const EngWord & elem);
	EngWord(std::string);
	EngWord();
	std::string getVal() const;
	void setVal(const std::string & val);
	bool operator==(const EngWord & aEngWord);
	bool operator==(const std::string & aString);
	bool operator!=(const EngWord & aEngWord);
	bool operator!=(const std::string & aString);
	void operator=(const EngWord & aEngWord);
	void operator=(const std::string & aString);
	


};

template<>
class Hash<EngWord>
{
private:
	int getNr(const char & x) const {
		return (int)x;
	}
public:
	int operator()(const EngWord& elem) const
	{
		int count = 0;
		std::string str = elem.getVal();
		for (int i = 0; i < str.size(); i++)
		{
			count += getNr(str[i]);
		}

		return count;
	}
};

#endif