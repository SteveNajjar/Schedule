#pragma once

#include <string>
#include "Helper.h"

class Checker
{
public:
	std::string name;
	std::string timeIn;
	std::string timeOut;
	std::string breakOne = " ";
	std::string lunch = " ";
	std::string breakTwo = " ";
	int checkstand = 0;

	Checker() = default;

	Checker(const std::string &name, int checkstand,
	        const std::string &timeIn, const std::string &timeOut)
		: name(name), timeIn(timeIn), timeOut(timeOut), checkstand(checkstand)
	{
		Helper::setBreaks(timeIn, timeOut, breakOne, lunch, breakTwo);
	}
};
