#include <iostream>
#include <string>
#include <cctype>
#pragma once

class Helper
{
public:
	int getHours(std::string timeIn, std::string timeOut)
	{
		int start = std::stoi(timeIn);
		std::cout << "get hours start: " << start;
		int end = std::stoi(timeOut);
		std::cout << "get hours end: " << end;

		return (end -  start) * 24;
	}


	int breakOne(std::string timeIn)
	{
		int b = std::stoi(timeIn);
		if(b + 2 > 12)
		return b - 12;
		else
		return b + 2;
	}


	int lunch(std::string timeIn)
	{
		int b = std::stoi(timeIn);
		if(b + 4 > 12)
		return b - 12;
		else
		return b + 4;
	}


	int breakTwo(std::string timeIn)
	{
		int b = std::stoi(timeIn);
		if(b + 6 > 12)
		return b - 12;
		else
		return b + 6;
	}

};
