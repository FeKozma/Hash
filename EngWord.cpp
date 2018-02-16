#include "stdafx.h"
#include "EngWord.h"
/*
EngWord::EngWord(EngWord *next, std::string val)
{
	this->next = next;
	this->val = val;
}



bool EngWord::equal(const EngWord & aEngWord)
{
	bool retVal = false;
	EngWord walker = aEngWord;
	EngWord follower = this;

	while (follower.val == walker.val && retVal == false)
	{
		if (walker.next == nullptr || follower.next == nullptr)
		{
			if (walker.next == nullptr && follower.next == nullptr)
			{
				retVal = true;
			}
		}
		follower = follower.next;
		walker = walker.next;
	}
	return retVal;
}

EngWord::EngWord(EngWord * next, std::string val)
{
	this->val = val;
	this->next = nullptr;
}

void EngWord::add(std::string val)
{
	if (this->next != nullptr)
	{
		EngWord newNext(nullptr, val);

	}
	else
	{
		this->next->add(val);
	}
}

bool EngWord::remove(std::string val)
{
	bool retVal = false;
	if (this->val == val)
	{
		retVal = true;
	}
	else
	{
		if (this->next != nullptr)
		{
			retVal = this->next->remove(val);
		}
	}
	return retVal;
}

EngWord::~EngWord()
{
	deallocate();
}

void EngWord::deallocate()
{
	if (this->next != nullptr)
	{
		this->next->deallocate();
	}
	delete this;
}

void EngWord::resetCollisionMaybe()
{
	if (this->next != nullptr)
	{
		this->next->deallocate();
	}
	this->next = nullptr;
}

bool EngWord::getIfExists(std::string val)
{
	bool retVal = false;
	if (this->val != val)
	{
		if (this->next != nullptr)
		{
			retVal = this->next->getIfExists(val);
		}
	}
	else
	{
		retVal = true;
	}
	return retVal;
}

bool EngWord::getIfOccupied()
{
	bool retVal = false;
	if (this->val != NULL)
	{
		retVal = true;
	}
	return retVal;
}

int EngWord::getNrOfElem()
{
	int retVal;
	if (this->next != nullptr)
	{
		retVal = this->next->getNrOfElem() + 1;
	}
	else
	{
		retVal = 1;
	}
	return retVal;
}

EngWord & EngWord::operator=(const EngWord & aEngWord)
{
	if (this != &aEngWord)
	{
		deallocate();
		next = &EngWord(nullptr, aEngWord.val);
		EngWord follower = next;
		EngWord walker = aEngWord.next;

		while (&aEngWord != nullptr)
		{
			follower = EngWord(nullptr, walker.val);
			walker = walker.next;
			follower = follower.next;

		}
	}
	return *this;
}

void EngWord::operator+=(const std::string & aString)
{
	this->add(aString);
}

bool EngWord::operator==(const EngWord & aEngWord)
{
	return this->equal(aEngWord);
}

bool EngWord::operator!=(const EngWord & aEngWord)
{
	return !(this->equal(aEngWord));
}

*/

EngWord::EngWord(const EngWord & elem)
{
	this->val = elem.val;
}

EngWord::EngWord(std::string val)
{
	this->val = val;
}

EngWord::EngWord()
{
	this->val = "";
}

std::string EngWord::getVal() const
{
	return this->val;
}

void EngWord::setVal(const std::string & val)
{
	this->val = val;
}

bool EngWord::operator==(const EngWord & aEngWord)
{
	return this->val == aEngWord.val;
}

bool EngWord::operator==(const std::string & aString)
{
	return this->val == aString;
}

bool EngWord::operator!=(const EngWord & aEngWord)
{
	return this->val != aEngWord.val;
}

bool EngWord::operator!=(const std::string & aString)
{
	return this->val != aString;
}

void EngWord::operator=(const EngWord & aEngWord)
{
	this->val = aEngWord.val;
}

void EngWord::operator=(const std::string & aString)
{
	this->val = aString;
}
