#include "CourtesyClerk.h"
#include "GMC.h"
#include "Checker.h"
#include "Janitor.h"
#include "Helper.h"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

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
void getJanitors(std::vector<Janitor> & hold_Janitors);
void print(const std::vector<Checker> &hold_Checker,
		   const std::vector<GMC> &hold_GMC,
		   const std::vector<CourtesyClerk> &hold_CC,
		   const std::vector<Janitor> &hold_Janitors,
		   const std::vector<assignments> &hold_assignments);
void fillAssignments(std::vector<assignments> & hold_assignments,
					 const std::vector<GMC> &hold_GMC,
					 const std::vector<CourtesyClerk> &hold_CC,
					 const std::vector<Janitor> &hold_Janitors);

int main()
{
	std::vector<GMC> hold_GMC;
	std::vector<CourtesyClerk> hold_CC;
	std::vector<Janitor> hold_Janitors;
	std::vector<Checker> hold_Checker;
	std::vector<assignments> hold_assignments;

	getChecker(hold_Checker);
	getGMC(hold_GMC);
	getCC(hold_CC);
	getJanitors(hold_Janitors);

	// Coordinate breaks among employees in the same position. Breaks for
	// different positions are allowed to overlap.
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
	for (auto &janitor : hold_Janitors)
		breakSchedules.push_back({Helper::toMinutes(janitor.timeIn), Helper::toMinutes(janitor.timeOut), 3,
		                          &janitor.breakOne, &janitor.lunch, &janitor.breakTwo});
	Helper::avoidBreakOverlaps(breakSchedules);

	fillAssignments(hold_assignments, hold_GMC, hold_CC, hold_Janitors);
	print(hold_Checker, hold_GMC, hold_CC, hold_Janitors, hold_assignments);
	return 0;
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

void getJanitors(std::vector<Janitor> &hold_Janitors)
{
	int dailyNum = 0;
	std::string name;
	std::string timeIn;
	std::string timeOut;

	std::cout << "Enter number of Janitors today: " << std::endl;
	std::cin >> dailyNum;
	std::cin.ignore();

	for (int i = 0; i < dailyNum; ++i)
	{
		std::cout << "Enter janitor name: " << std::endl;
		std::getline(std::cin, name);
		std::cout << "Enter time in (24-hour time, e.g. 06:00): " << std::endl;
		std::getline(std::cin, timeIn);
		std::cout << "Enter time out (24-hour time, e.g. 14:30): " << std::endl;
		std::getline(std::cin, timeOut);

		hold_Janitors.emplace_back(name, timeIn, timeOut);
	}
}

void fillAssignments(std::vector<assignments> &hold_assignments,
					 const std::vector<GMC> &hold_GMC,
					 const std::vector<CourtesyClerk> &hold_CC,
					 const std::vector<Janitor> &hold_Janitors)
{
	// Build one common list so each hour can choose from all eligible staff.
	struct Worker
	{
		std::string name;
		int start;
		int end;
		bool isJanitor;
	};
	std::vector<Worker> workers;
	for (const auto &gmc : hold_GMC)
		workers.push_back({gmc.name, Helper::toMinutes(gmc.timeIn), Helper::toMinutes(gmc.timeOut), false});
	for (const auto &cc : hold_CC)
		workers.push_back({cc.name, Helper::toMinutes(cc.timeIn), Helper::toMinutes(cc.timeOut), false});
	for (const auto &janitor : hold_Janitors)
		workers.push_back({janitor.name, Helper::toMinutes(janitor.timeIn),
		                   Helper::toMinutes(janitor.timeOut), true});

	hold_assignments.clear();
	std::vector<int> cartsCounts(workers.size(), 0);
	std::vector<int> sweepsCounts(workers.size(), 0);
	std::vector<int> goBacksCounts(workers.size(), 0);
	int lastCarts = -1;
	int lastSweeps = -1;
	int lastGoBacks = -1;
	const auto appendName = [](std::string &field, const std::string &name)
	{
		if (field != " ")
			field += ", ";
		else field.clear();
			field += name;
	};

	for (int hour = 6; hour < 23; ++hour)
	{
		const int hourStart = hour * 60;
		const int hourEnd = hourStart + 60;
		std::vector<int> availableStaff;
		for (std::size_t i = 0; i < workers.size(); ++i)
		{
			const int overlapStart = std::max(workers[i].start, hourStart);
			const int overlapEnd = std::min(workers[i].end, hourEnd);
			// Schedule only staff who cover at least half of this hour. This
			// avoids assigning a whole hourly slot to someone on shift for only
			// a few minutes at the edge of the hour.
			if (overlapEnd - overlapStart >= 30)
				availableStaff.push_back(static_cast<int>(i));
		}

		assignments assign;
		std::vector<bool> assignedToTask(workers.size(), false);
		std::vector<int> janitorsOnShift;
		std::vector<int> otherStaff;
		for (int index : availableStaff)
		{
			if (workers[index].isJanitor)
			{
				janitorsOnShift.push_back(index);
				appendName(assign.sweeps, workers[index].name);
				assignedToTask[index] = true;
			}
			else
			{
				otherStaff.push_back(index);
			}
		}

		// Pick the least-used eligible employee. First avoid both someone
		// already assigned this hour and the person who did this task last hour.
		// If that leaves nobody, allow the previous worker; only share tasks
		// when there is no other eligible employee.
		const auto chooseStaff = [&](const std::vector<int> &candidates,
								 const std::vector<int> &alreadyUsed,
								 const std::vector<int> &taskCounts,
								 int previousWorker)
		{
			const auto pick = [&](bool allowPrevious, bool allowUsed)
			{
				int selected = -1;
				for (int candidate : candidates)
				{
					const bool alreadyAssigned = std::find(alreadyUsed.begin(), alreadyUsed.end(), candidate) != alreadyUsed.end();
					if (!allowUsed && alreadyAssigned) continue;
					if (!allowPrevious && candidate == previousWorker) continue;
					if (selected == -1 || taskCounts[candidate] < taskCounts[selected])
						selected = candidate;
				}
				return selected;
			};

			int selected = pick(false, false);
			if (selected == -1) selected = pick(true, false);
			if (selected == -1) selected = pick(true, true);
			return selected;
		};

		std::vector<int> used;
		const int carts = chooseStaff(otherStaff, used, cartsCounts, lastCarts);
		if (carts >= 0)
		{
			assign.carts = workers[carts].name;
			assignedToTask[carts] = true;
			used.push_back(carts);
			++cartsCounts[carts];
			lastCarts = carts;
		}

		if (janitorsOnShift.empty())
		{
			// Without a janitor, the sweeper also handles go-backs.
			const int sweeper = chooseStaff(otherStaff, used, sweepsCounts, lastSweeps);
			if (sweeper >= 0)
			{
				assign.sweeps = workers[sweeper].name;
				assign.goBacks = workers[sweeper].name;
				assignedToTask[sweeper] = true;
				++sweepsCounts[sweeper];
				++goBacksCounts[sweeper];
				lastSweeps = sweeper;
				lastGoBacks = sweeper;
			}
		}
		else
		{
			// A janitor remains on sweeps. Assign go-backs to a different,
			// non-janitor employee; avoid the carts person when possible.
			const int goBacks = chooseStaff(otherStaff, used, goBacksCounts, lastGoBacks);
			if (goBacks >= 0)
			{
				assign.goBacks = workers[goBacks].name;
				assignedToTask[goBacks] = true;
				used.push_back(goBacks);
				++goBacksCounts[goBacks];
				lastGoBacks = goBacks;
			}
		}

		// Any available non-janitor who did not get carts, sweeps, or go-backs
		// is assigned to bagging. Janitors stay dedicated to sweeps.
		for (int index : otherStaff)
		{
			if (!assignedToTask[index])
			{
				appendName(assign.bagging, workers[index].name);
			}
		}
		hold_assignments.push_back(assign);
	}
}

void print(const std::vector<Checker> &hold_Checker,
		   const std::vector<GMC> &hold_GMC,
		   const std::vector<CourtesyClerk> &hold_CC,
		   const std::vector<Janitor> &hold_Janitors,
		   const std::vector<assignments> &hold_assignments)
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

	std::cout << "****************************************************" << std::endl;
	std::cout << "****************** Janitors ************************" << std::endl;
	for (const auto &janitor : hold_Janitors)
	{
		std::cout << "Name: " << janitor.name << " Time in: " << janitor.timeIn
		          << " Time out: " << janitor.timeOut << std::endl;
	}

	std::cout << "****************************************************" << std::endl;
	std::cout << "****************** Assignments *********************" << std::endl;
	for (std::size_t i = 0; i < hold_assignments.size(); ++i)
	{
		const int hour = 6 + static_cast<int>(i);
		std::cout << hour << ":00-" << hour + 1 << ":00"
		          << " | Carts: " << hold_assignments[i].carts
		          << " | Sweeps: " << hold_assignments[i].sweeps
		          << " | Go-backs: " << hold_assignments[i].goBacks
		          << " | Bagging: " << hold_assignments[i].bagging << std::endl;
	}
}

