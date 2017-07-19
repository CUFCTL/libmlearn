/**
 * @file timer.cpp
 *
 * Implementation of the timer.
 */
#include <cassert>
#include "logger.h"
#include "timer.h"

/**
 * Global timer object.
 */
timekeeper_t timer;

/**
 * Start a new timer item.
 *
 * @param name
 */
void timer_push(const std::string& name)
{
	timer_item_t item;
	item.name = name;
	item.level = timer.level;
	item.start = std::chrono::system_clock::now();
	item.duration = -1;

	timer.items.push_back(item);
	timer.level++;

	log(LL_VERBOSE, "%*s%s", 2 * item.level, "", item.name.c_str());
}

/**
 * Stop the most recent timer item which is still running.
 *
 * @return duration of the timer item
 */
float timer_pop(void)
{
	std::vector<timer_item_t>::reverse_iterator iter;

	for ( iter = timer.items.rbegin(); iter != timer.items.rend(); iter++ ) {
		if ( iter->duration == -1 ) {
			break;
		}
	}

	assert(iter != timer.items.rend());

	iter->end = std::chrono::system_clock::now();
	iter->duration = std::chrono::duration_cast<std::chrono::milliseconds>(iter->end - iter->start).count() / 1000.0f;

	timer.level--;

	return iter->duration;
}

/**
 * Print all timer items.
 */
void timer_print(void)
{
	std::vector<timer_item_t>::iterator iter;

	// determine the maximum string length
	int max_len = 0;

	for ( iter = timer.items.begin(); iter != timer.items.end(); iter++ ) {
		int len = 2 * iter->level + iter->name.size();

		if ( max_len < len ) {
			max_len = len;
		}
	}

	// print timer items
	log(LL_VERBOSE, "Timing");
	log(LL_VERBOSE, "%-*s  %s", max_len, "Name", "Duration (s)");
	log(LL_VERBOSE, "%-*s  %s", max_len, "----", "------------");

	for ( iter = timer.items.begin(); iter != timer.items.end(); iter++ ) {
		log(LL_VERBOSE, "%*s%-*s  % 12.3f",
			2 * iter->level, "",
			max_len - 2 * iter->level, iter->name.c_str(),
			iter->duration);
	}
	log(LL_VERBOSE, "");
}
