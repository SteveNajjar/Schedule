#pragma once

#include <string>
#include "Helper.h"

// Janitors are scheduled for sweeps for their entire shift. They are not
// eligible for carts, go-backs, or bagging.
class Janitor
{
public:
	std::string name;
	std::string timeIn;
	std::string timeOut;
	std::string breakOne = " ";
	std::string lunch = " ";
	std::string breakTwo = " ";

	Janitor() = default;

	Janitor(const std::string &name, const std::string &timeIn,
	        const std::string &timeOut)
		: name(name), timeIn(timeIn), timeOut(timeOut)
	{
		Helper::setBreaks(timeIn, timeOut, breakOne, lunch, breakTwo);
	}
};
