#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "Helper.h"
class GMC
{
public:
	std::string name = " ";
	std::string timeIn = " ";
	std::string timeOut = " ";
	std::string breakOne = " ";
	std::string lunch = " ";
	std::string breakTwo = " ";
	std::string aisle = " ";

	GMC()
	{

	}

	GMC(std::string name, std::string timeIn, std::string timeOut)
	{
		Helper helper;

		// initialize variables
		this->name = name;
		this->timeIn = timeIn;
		this->timeOut = timeOut;
		breakOne = helper.breakOne(timeIn);

		//if (getMinutes > x amount needed for lunch break)
		lunch = helper.lunch(timeIn);

		//if (getMinutes > x amount needed for second break)
		breakTwo = helper.breakTwo(timeIn);
	}


	~GMC()
	{

	}


};