#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "Helper.h"
class CourtesyClerk
{
public:
	std::string name = " ";
	std::string timeIn = " ";
	std::string timeOut = " ";
	std::string breakOne = " ";
	std::string lunch = " ";
	std::string breakTwo = " ";

	CourtesyClerk()
	{

	}

	CourtesyClerk(std::string name, std::string timeIn, std::string timeOut)
	{
		Helper helper;
		
		this->name = name;
		this->timeIn = timeIn;
		this->timeOut = timeOut;

		breakOne = helper.breakOne(timeIn);

		//if (getMinutes > x amount needed for lunch break)
		lunch = helper.lunch(timeIn);

		//if (getMinutes > x amount needed for second break)
		breakTwo = helper.breakTwo(timeIn);
		// no shift less than 4 hours will always have one break
		// breakOne = timeIn + 2;

		// if(timeOut - timeIn >= 5.5)
		// {
		// 	// 5 or more hour shift get a lunch and second break
		// 	lunch = timeIn + 4;
		// 	breakTwo = timeIn + 6;
		// }
		
	}

	~CourtesyClerk()
	{

	}


	// double getTotalHours(std::string timeIn, std::string timeOut)
	// {
	// 	std::stringstream ss;
	// 	ss >> timeIn;
	// 	while
	// }
};