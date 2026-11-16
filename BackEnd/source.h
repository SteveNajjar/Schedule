#ifndef SOURCE_H
#define SOURCE_H

#include <string>
#include <vector>

#include "Janitor.h"
#include "Checker.h"
#include "GMC.h"
#include "CourtesyClerk.h"

struct assignments{
	std::string carts = " ";
	std::string sweeps = " ";
	std::string goBacks = " ";
	std::string bagging = " ";
};

void getChecker(
    std::vector<Checker>& hold_Checker,
    const std::string& name,
    const std::string& timeIn,
    const std::string& timeOut
);

void getGMC(
    std::vector<GMC>& hold_GMC,
    const std::string& name,
    const std::string& timeIn,
    const std::string& timeOut
);

void getCC(
    std::vector<CourtesyClerk>& hold_CC,
    const std::string& name,
    const std::string& timeIn,
    const std::string& timeOut
);

void print(
    const std::vector<Checker>& hold_Checker,
    const std::vector<GMC>& hold_GMC,
    const std::vector<CourtesyClerk>& hold_CC,
    const std::vector<Janitor>& hold_Janitors,
    const std::vector<assignments>& hold_assignments
);

void fillAssignments(
    std::vector<assignments>& hold_assignments,
    const std::vector<GMC>& hold_GMC,
    const std::vector<CourtesyClerk>& hold_CC,
    const std::vector<Janitor>& hold_Janitors
);


#endif
