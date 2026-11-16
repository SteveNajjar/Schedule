#pragma once

#include <algorithm>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// Shared time parsing and break scheduling for backend employee models.
class Helper
{
public:
	// A small view of an employee's break fields. The coordinator uses this
	// so it can work with Checkers, GMCs, and Courtesy Clerks together.
	struct BreakSchedule
	{
		int shiftStart;
		int shiftEnd;
		int position;
		std::string *firstBreak;
		std::string *lunch;
		std::string *lastBreak;
	};

	static int toMinutes(const std::string &time)
	{
		const std::size_t colon = time.find(':');
		try
		{
			const int hours = std::stoi(time.substr(0, colon));
			const int minutes = colon == std::string::npos
				? 0
				: std::stoi(time.substr(colon + 1));
			if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59)
				throw std::invalid_argument("time is outside the 24-hour clock");
			return hours * 60 + minutes;
		}
		catch (const std::exception &)
		{
			throw std::invalid_argument("time must use 24-hour HH:MM format: " + time);
		}
	}

	static std::string toTime(int minutes)
	{
		if (minutes < 0 || minutes >= 24 * 60)
			throw std::invalid_argument("time is outside the 24-hour clock");
		std::ostringstream result;
		result << std::setfill('0') << std::setw(2) << minutes / 60
		       << ':' << std::setw(2) << minutes % 60;
		return result.str();
	}

	static int getMinutes(const std::string &timeIn, const std::string &timeOut)
	{
		const int start = toMinutes(timeIn);
		const int end = toMinutes(timeOut);
		if (end <= start)
			throw std::invalid_argument("shift end must be after shift start");
		return end - start;
	}

	// Kept for older callers; returns the whole-hour portion of a shift.
	static int getHours(const std::string &timeIn, const std::string &timeOut)
	{
		return getMinutes(timeIn, timeOut) / 60;
	}

	static std::string breakOne(const std::string &timeIn)
	{
		return toTime(toMinutes(timeIn) + 120);
	}

	static void setBreaks(const std::string &timeIn, const std::string &timeOut,
	                      std::string &firstBreak, std::string &lunchStart,
	                      std::string &secondBreak)
	{
		const int duration = getMinutes(timeIn, timeOut);
		const int start = toMinutes(timeIn);
		const int end = toMinutes(timeOut);

		// A single space means this break does not apply to the shift.
		firstBreak = " ";
		lunchStart = " ";
		secondBreak = " ";

		// Everyone gets their first break two hours after starting, as long as
		// it begins before the shift ends.
		const int firstBreakAt = start + 120;
		if (firstBreakAt < end)
		{
			firstBreak = toTime(firstBreakAt);
		}

		// Shifts shorter than five hours only get that first break.
		if (duration < 5 * 60)
		{
			return;
		}

		// Five-hour-or-longer shifts get lunch four hours after clock-in.
		const int lunchAt = start + 240;
		int lunchLength = 30;
		if (duration >= 9 * 60)
		{
			lunchLength = 60;
		}

		const int lunchEnd = lunchAt + lunchLength;
		if (lunchEnd > end)
		{
			// The planned lunch would run past clock-out, so leave lunch and
			// the second break unset. The first break remains scheduled.
			return;
		}

		lunchStart = toTime(lunchAt);

		// Only shifts of at least seven hours get a last break.
		if (duration < 7 * 60)
		{
			return;
		}

		// Aim for two hours after lunch ends. A 10-minute break must finish
		// before clock-out, so move it earlier only when the target will not fit.
		const int targetBreakAt = lunchEnd + 120;
		const int latestBreakAt = end - 10;
		int lastBreakAt = targetBreakAt;

		if (targetBreakAt + 10 > end)
		{
			lastBreakAt = latestBreakAt;
		}

		// Schedule the last break only if it fits after both lunch and the
		// first break. Otherwise there is no valid time for it in this shift.
		if (lastBreakAt >= lunchEnd && lastBreakAt >= firstBreakAt + 10)
		{
			secondBreak = toTime(lastBreakAt);
		}
	}

	static void avoidBreakOverlaps(std::vector<BreakSchedule> &employees)
	{
		// The employee who started earlier keeps their break time. Later
		// arrivals yield when their break overlaps an already scheduled one.
		std::stable_sort(employees.begin(), employees.end(),
			[](const BreakSchedule &left, const BreakSchedule &right)
			{
				return left.shiftStart < right.shiftStart;
			});

		for (std::size_t later = 0; later < employees.size(); ++later)
		{
			std::string *laterBreaks[] = {
				employees[later].firstBreak,
				employees[later].lunch,
				employees[later].lastBreak
			};

			for (std::string *laterBreak : laterBreaks)
			{
				if (laterBreak == nullptr || *laterBreak == " ")
				{
					continue;
				}

				const int breakLength = laterBreak == employees[later].lunch
					? (employees[later].shiftEnd - employees[later].shiftStart >= 9 * 60 ? 60 : 30)
					: 10;
				int breakStart = toMinutes(*laterBreak);

				// Keep moving this break 15 minutes earlier until it no longer
				// overlaps any break belonging to an earlier arrival. Stop if
				// moving it would put it before clock-in.
				bool hasConflict = true;
				while (hasConflict)
				{
					hasConflict = false;
					for (std::size_t earlier = 0; earlier < later; ++earlier)
					{
						// Break staggering is limited to people in the same position.
						if (employees[earlier].position != employees[later].position)
						{
							continue;
						}

						std::string *earlierBreaks[] = {
							employees[earlier].firstBreak,
							employees[earlier].lunch,
							employees[earlier].lastBreak
						};

						for (std::string *earlierBreak : earlierBreaks)
						{
							if (earlierBreak == nullptr || *earlierBreak == " ")
							{
								continue;
							}

							const int earlierLength = earlierBreak == employees[earlier].lunch
								? (employees[earlier].shiftEnd - employees[earlier].shiftStart >= 9 * 60 ? 60 : 30)
								: 10;
							const int earlierStart = toMinutes(*earlierBreak);
							const bool overlaps = breakStart < earlierStart + earlierLength &&
							                      earlierStart < breakStart + breakLength;

							if (overlaps)
							{
								const int earlierStartCandidate = breakStart - 15;
								if (earlierStartCandidate >= employees[later].shiftStart)
								{
									breakStart = earlierStartCandidate;
									hasConflict = true;
								}
								break;
							}
						}
						if (hasConflict)
						{
							break;
						}
					}
				}

				if (breakStart + breakLength <= employees[later].shiftEnd)
				{
					*laterBreak = toTime(breakStart);
				}
			}
		}
	}
};
