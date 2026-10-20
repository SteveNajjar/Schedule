#include "CourtesyClerk.h"
#include "GMC.h"
#include "Checker.h"
#include "Helper.h"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <limits>

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
	getGMC(hold_GMC);
	getCC(hold_CC);

	// Coordinate all break schedules together so different employee types
	// are included in the same overlap checks.
	std::vector<Helper::BreakSchedule> breakSchedules;
	for (auto &checker : hold_Checker)
		breakSchedules.push_back({Helper::toMinutes(checker.timeIn), Helper::toMinutes(checker.timeOut), 0,
		                          &checker.breakOne, &checker.lunch, &checker.breakTwo});
	for (auto &gmc : hold_GMC)
		breakSchedules.push_back({Helper::toMinutes(gmc.timeIn), Helper::toMinutes(gmc.timeOut), 1,
		                          &gmc.breakOne, &gmc.lunch, &gmc.breakTwo});
	for (auto &cc : hold_CC)
		breakSchedules.push_back({Helper::toMinutes(cc.timeIn), Helper::toMinutes(cc.timeOut), 2,
		                          &cc.breakOne, &cc.lunch, &cc.breakTwo});
	Helper::avoidBreakOverlaps(breakSchedules);

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

		std::cout << "Enter time in (in military time, ex 6:30 or 18:30)" << std::endl;
		std::getline(std::cin, timeIn);

		std::cout << "Enter time out (in military time, ex 6:30 or 18:30)" << std::endl;
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

		std::cout << "Enter time in (in military time, ex 6:30 or 18:30)" << std::endl;
		std::getline(std::cin, timeIn);

		std::cout << "Enter time out (in military time, ex 6:30 or 18:30)" << std::endl;
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

		std::cout << "Enter time in (in military time, ex 6:30 or 18:30)" << std::endl;
		std::getline(std::cin, timeIn);

		std::cout << "Enter time out (in military time, ex 6:30 or 18:30)" << std::endl;
		std::getline(std::cin, timeOut);

		hold_CC.push_back(CourtesyClerk(name, timeIn, timeOut));
		std::cout << std::endl;
	}
}

void fillAssignments(std::vector<assignments> & hold_assignments, std::vector<GMC> hold_GMC, std::vector<CourtesyClerk> hold_CC)
{
	// Each row represents one store hour: 6:00-7:00 through 22:00-23:00.
	// The employee doing sweeps also handles go-backs, per the store rules.
	using Worker = std::pair<std::string, std::pair<int, int>>; // name, [start, end)
	const auto toMinutes = [](const std::string &time) {
		const std::size_t colon = time.find(':');
		const int hours = std::stoi(time.substr(0, colon));
		const int minutes = colon == std::string::npos ? 0 : std::stoi(time.substr(colon + 1));
		return hours * 60 + minutes;
	};
	std::vector<Worker> workers;
	for (const auto &gmc : hold_GMC)
		workers.push_back({gmc.name, {toMinutes(gmc.timeIn), toMinutes(gmc.timeOut)}});
	for (const auto &cc : hold_CC)
		workers.push_back({cc.name, {toMinutes(cc.timeIn), toMinutes(cc.timeOut)}});

	hold_assignments.clear();
	std::vector<int> taskCounts(workers.size(), 0);
	int lastCarts = -1;
	int lastSweeps = -1;
	for (int hour = 6; hour < 23; ++hour)
	{
		const int hourStart = hour * 60;
		const int hourEnd = hourStart + 60;
		std::vector<int> available;
		for (std::size_t i = 0; i < workers.size(); ++i)
			if (workers[i].second.first < hourEnd && workers[i].second.second > hourStart)
				available.push_back(static_cast<int>(i));

		const auto choose = [&](int previous, int avoid) {
			int selected = -1;
			int fewestTasks = std::numeric_limits<int>::max();
			for (int index : available)
			{
				if (index == previous || index == avoid) continue;
				if (taskCounts[index] < fewestTasks) {
					selected = index;
					fewestTasks = taskCounts[index];
				}
			}
			// Keep the hour covered when staffing is limited, even if this
			// means reusing the previous worker or assigning both tasks to one person.
			if (selected < 0)
				for (int index : available)
					if (taskCounts[index] < fewestTasks) {
						selected = index;
						fewestTasks = taskCounts[index];
					}
			return selected;
		};

		assignments assign;
		const int carts = choose(lastCarts, -1);
		const int sweeps = choose(lastSweeps, carts);
		if (carts >= 0) {
			assign.carts = workers[carts].first;
			++taskCounts[carts];
			lastCarts = carts;
		}
		if (sweeps >= 0) {
			assign.sweeps = workers[sweeps].first;
			assign.goBacks = workers[sweeps].first;
			++taskCounts[sweeps];
			lastSweeps = sweeps;
		}
		hold_assignments.push_back(assign);
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

