#ifndef COURSE_H
#define COURSE_H

#include "Hash.h"
#include <string>

class Course
{
private:
	std::string code;
	std::string name;
	double hp;

public:
	Course(const Course& elem);
	Course(const std::string& code,const std::string& name,const double& hp);
	Course();
	std::string getCode() const;
	std::string getName() const;
	double getHp() const;

	void setCode(const std::string &code);
	void setName(const std::string &name);
	void setHp(const double  &hp);

	std::string toString() const;

	//void setVal(const std::string & val);
	bool operator==(const Course & aCourse);
	//bool operator==(const std::string & aString);
	bool operator!=(const Course & aCourse);
	//bool operator!=(const std::string & aString);
	void operator=(const Course & aCource);
	//void operator=(const std::string & aString);



};

template<>
class Hash<Course>
{
private:
	int getNr(const char & x) const {
		return (int)x;
	}
public:
	int operator()(const Course& elem) const
	{
		
		int count = 0;
		std::string str = elem.getCode() + std::to_string(elem.getHp()) + elem.getName();
		for (int i = 0; i < str.size(); i++)
		{
			count += getNr(str[i]);
		}
		
		return count;
	}
};

#endif