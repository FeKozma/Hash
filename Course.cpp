#include "stdafx.h"
#include "Course.h"

Course::Course(const Course & elem)
{
	this->code = elem.code;
	this->hp = elem.hp;
	this->name = elem.name;
}

Course::Course(const std::string& code, const std::string& name, const double& hp)
{
	this->code = code;
	this->name = name;
	this->hp = hp;
}

Course::Course()
{
	this->code = "";
	this->name = "";
	this->hp = 0;
}



std::string Course::getCode() const
{
	return this->code;
}

std::string Course::getName() const
{
	return this->name;
}

double Course::getHp() const
{
	return this->hp;
}
void Course::setCode(const std::string & code)
{
	this->code = code;
}
void Course::setName(const std::string & name)
{
	this->name = name;
}
void Course::setHp(const double & hp)
{
	this->hp = hp;
}

std::string Course::toString() const
{
	return this->code + '\n' + this->name + '\n' + std::to_string(this->hp) + '\n';
}
/*
void Course::setVal(const std::string & val)
{
	this->code = val;
}*/

bool Course::operator==(const Course & aCourse)
{
	return (this->code == aCourse.code);// && this->name == aCourse.name && this->hp == aCourse.hp && this->def == aCourse.def);
}
/*
bool Course::operator==(const std::string & aString)
{
	return this->code == aString;
}*/

bool Course::operator!=(const Course & aCourse)
{
	return (this->code != aCourse.code); // || this->name != aCourse.name || this->hp != aCourse.hp || this->def != aCourse.def);
}
/*
bool Course::operator!=(const std::string & aString)
{
	return this->code != aString;
}*/

void Course::operator=(const Course & aCource)
{
	this->code = aCource.code;
	this->name = aCource.name;
	this->hp = aCource.hp;
}
/*
void Course::operator=(const std::string & aString)
{
	this->code = aString;
	if (this->code != "")
	{
		this->def = true;
	}
	else
	{
		this->def = false;
	}
}*/
