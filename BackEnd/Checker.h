#include <iostream>
#include <string>
#include "Helper.h"
class Checker
{
public:
	std::string name = " ";
	std::string timeIn = " ";
	std::string timeOut = " ";
	std::string breakOne = " ";
	std::string lunch = " ";
	std::string breakTwo = " ";
	int checkstand = 0;

	Checker();
	
	Checker(std::string name, int checkstand, std::string timeIn, std::string timeOut)
	{
		Helper helper;

		this->name = name;
		this->checkstand = checkstand;
		this->timeIn = timeIn;
		this->timeOut = timeOut;

		int totalMinutes = (helper.getHours(timeIn, timeOut));

		// always get one break
		breakOne = std::to_string(helper.breakOne(timeIn));

		//if (getMinutes > x amount needed for lunch break)
		lunch = std::to_string(helper.lunch(timeIn));

		//if (getMinutes > x amount needed for second break)
		breakTwo = std::to_string(helper.breakTwo(timeIn));
	}
};