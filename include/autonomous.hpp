#pragma once

#include "chassis.hpp"

/* ========================================================================== */
/*                                   Classes                                  */
/* ========================================================================== */

class AutoRoutine
{
private:
	void (*func)();
	std::string name;

public:
	AutoRoutine(std::string str, void (*f)());

	std::string get_name() { return name; }

	void run() { func(); }

	~AutoRoutine() {}
};

class AutonomousSelector
{
private:
	std::vector<AutoRoutine> auto_arr;

	int selected_index = 0;

public:
	AutonomousSelector();

	void add_auto(AutoRoutine ar);

	void run_selected();

	std::string get_selected();

	int set_selected(std::string str);

	int increase_selected();

	int decrease_selected();

	int get_num_autons();

	~AutonomousSelector()
	{
	}
};

extern AutonomousSelector auto_selector;

/* ========================================================================== */
/*                                  Routines                                  */
/* ========================================================================== */

extern AutoRoutine three_side;

extern AutoRoutine blue_positive;

extern AutoRoutine blue_negative;

extern AutoRoutine red_positive;

extern AutoRoutine red_negative;
