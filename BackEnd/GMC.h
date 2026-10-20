#pragma once

#include <string>
#include "Helper.h"

class GMC
{
public:
	std::string name;
	std::string timeIn;
	std::string timeOut;
	std::string breakOne = " ";
	std::string lunch = " ";
	std::string breakTwo = " ";
	std::string aisle = " ";

	GMC() = default;

	GMC(const std::string &name, const std::string &timeIn, const std::string &timeOut)
		: name(name), timeIn(timeIn), timeOut(timeOut)
	{
		Helper::setBreaks(timeIn, timeOut, breakOne, lunch, breakTwo);
	}
};
