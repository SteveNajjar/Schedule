#include "CourtesyClerk.h"
#include "GMC.h"
#include "Checker.h"
#include "Helper.h"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>

// hold assignments
struct assignments
	{
		std::string carts = " ";
		std::string sweeps = " ";
		std::string goBacks = " ";
		std::string bagging = " ";
	};
	
void getChecker(std::vector<Checker> & hold_Checker);
void getGMC(std::vector<GMC> & hold_GMC);
void getCC(std::vector<CourtesyClerk> & hold_CC);
void print(std::vector<Checker> & hold_Checker, std::vector<GMC> & hold_GMC, std::vector<CourtesyClerk> & hold_CC);
void fillAssignments(std::vector<assignments> & hold_assignments, std::vector<GMC> hold_GMC, std::vector<CourtesyClerk> hold_CC);

int main()
{
	// want "carts" "sweeps" "go backs" "baggging" to all be randomly assigned
	// 17 hours of operation 6:00 to 23:00 need to fill carts, sweeps go backs bagging
	// if janitor, assign sweeps whole shift
	// first hour of shift on carts
	// try to avoid two or more hours on carts and carts/sweeps right after
	// closer has sweeps for last two hours, pre closer carts

	// could use parallel arrays carts[] sweeps[] goBacks[] bagging[]
	// vector pair<carts, sweeps> pair < goBacks, bagging>

	int GMC_Workers = 0;
	int CC_Workers = 0;

	std::vector<GMC> hold_GMC;
	std::vector<CourtesyClerk> hold_CC;
	std::vector<Checker> hold_Checker;
	std::vector<assignments> hold_assignments;

	getChecker(hold_Checker);
	// getGMC(hold_GMC);
	// getCC(hold_CC);
	fillAssignments(hold_assignments, hold_GMC, hold_CC);
	print(hold_Checker, hold_GMC, hold_CC);
}



void getChecker(std::vector<Checker> & hold_Checker)
{
		int dailyNum = 0;

		std::string name = " ";
		std::string timeIn = " ";
		std::string timeOut = " ";
		int checkstand = 0;

	std::cout << "Enter number of Checkers today: " << std::endl;
	std::cin >> dailyNum;
	std::cin.ignore();

	std::cout << "Populate Checker information: " << std::endl;

	for(int i = 0; i < dailyNum; i++)
	{
		std::cout << "Enter name: " << std::endl;
		std::getline(std::cin, name);

		std::cout << "Enter time in (ex 6:30am)" << std::endl;
		std::getline(std::cin, timeIn);

		std::cout << "Enter time out (ex 6:30pm)" << std::endl;
		std::getline(std::cin, timeOut);

		std::cout << "Enter checkstand: " << std::endl;
		std::cin >> checkstand;
		std::cin.ignore();

		hold_Checker.push_back(Checker(name, checkstand, timeIn, timeOut));
		std::cout << std::endl;
	}
}



void getGMC(std::vector<GMC> & hold_GMC)
{
		int dailyNum = 0;

		std::string name = " ";
		std::string timeIn = " ";
		std::string timeOut = " ";

	std::cout << "Enter number of GMC's today: " << std::endl;
	std::cin >> dailyNum;
	std::cin.ignore();

	std::cout << "Populate GMC information: " << std::endl;

	for(int i = 0; i < dailyNum; i++)
	{
		std::cout << "Enter name: " << std::endl;
		std::getline(std::cin, name);

		std::cout << "Enter time in (ex 6:30am)" << std::endl;
		std::getline(std::cin, timeIn);

		std::cout << "Enter time out (ex 6:30pm)" << std::endl;
		std::getline(std::cin, timeOut);

		hold_GMC.push_back(GMC(name, timeIn, timeOut));
		std::cout << std::endl;
	}
}



void getCC(std::vector<CourtesyClerk> & hold_CC)
{
		int dailyNum = 0;

		std::string name = " ";
		std::string timeIn = " ";
		std::string timeOut = " ";

	std::cout << "Enter number of Courtesy clerks today: " << std::endl;
	std::cin >> dailyNum;
	std::cin.ignore();

	std::cout << "Populate Courtesy Clerk information: " << std::endl;

	for(int i = 0; i < dailyNum; i++)
	{
		std::cout << "Enter name: " << std::endl;
		std::getline(std::cin, name);

		std::cout << "Enter time in (ex 6:30am)" << std::endl;
		std::getline(std::cin, timeIn);

		std::cout << "Enter time out (ex 6:30pm)" << std::endl;
		std::getline(std::cin, timeOut);

		hold_CC.push_back(CourtesyClerk(name, timeIn, timeOut));
		std::cout << std::endl;
	}
}

void fillAssignments(std::vector<assignments> & hold_assignments, std::vector<GMC> hold_GMC, std::vector<CourtesyClerk> hold_CC)
{
	// fill carts, sweeps, go backs, bagging for full 17 hours 6:00 - 23:00
	// push back a name for carts, sweeps, go backs, bagging for each hour
	// nothing during lunch, avoid during breaks
	// if janitor, sweeps whole time, no go backs

	for(int i = 6; i < 23; i++)
	{
		assignments assign;
		for(auto gmc : hold_GMC)
		{
			if(stoi(gmc.timeIn) == 6)
			{
				assign.carts = gmc.name;
				assign.sweeps = gmc.name;
				assign.goBacks = gmc.name;
				break;
			}

			else if((stoi(gmc.timeIn) == i))
			{
				assign.carts = gmc.name;
			}
		}

		for(auto cc : hold_CC)
		{
			if(stoi(cc.timeIn) == i)
			{
				assign.sweeps = cc.name;
				break;
			}
		}
	}

	}

void print(std::vector<Checker> & hold_Checker, std::vector<GMC> & hold_GMC, std::vector<CourtesyClerk> & hold_CC)
{
	std::cout << "****************************************************" << std::endl;
	std::cout << "****************** Checkers ************************" << std:: endl;
	for(auto checker : hold_Checker)
	{
		std::cout << "Name: " << checker.name << " " << "Checkstand " << checker.checkstand <<
		" Time in: " << checker.timeIn << " " << "Break One: " << checker.breakOne;

		if(checker.lunch != " ")
		std::cout << "Lunch: " << checker.lunch;

		std::cout << " Break Two: " << checker.breakTwo << " Time out: " << checker.timeOut << std::endl;
	}


	std::cout << "****************************************************" << std::endl;
	std::cout << "****************** GMC ************************" << std:: endl;
	for(auto gmc : hold_GMC)
	{
		std::cout << "Name: " << gmc.name << std::endl;
		std::cout << "Time in: " << gmc.timeIn << std::endl;
		std::cout << "Time out: " << gmc.timeOut << std::endl;
	}


	std::cout << "****************************************************" << std::endl;
	std::cout << "****************** Courtesy Clerk ************************" << std:: endl;
	for(auto cc : hold_CC)
	{
		std::cout << "Name: " << cc.name << std::endl;
		std::cout << "Time in: " << cc.timeIn << std::endl;
		std::cout << "Time out: " << cc.timeOut << std::endl;
	}

}

