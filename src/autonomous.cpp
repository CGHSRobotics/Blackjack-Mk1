
#include "autonomous.hpp"
#include "chassis.hpp"

/* ========================================================================== */
/*                             Autonomous Routines                            */
/* ========================================================================== */

/**
 *@brief Three side auto does whattt???
 *
 */
AutoRoutine three_side("Three Side", [] {

	// waits until chassis is done
	chassis->moveDistance(10_in);

	// lets you do other things
	chassis->moveDistanceAsync(10_in);
	// do other things
	chassis->waitUntilSettled();

	// same thing as first but turning
	chassis->turnAngle(90_deg);

	// lets you do other things
	chassis->turnAngleAsync(90_deg);
	// do other things
	chassis->waitUntilSettled();

	/* ---------- RATHER THAN DOING ALL THAT BULLSHIT, DO THIS INSTEAD ---------- */
	// vexforums says the generate may take some time so if you notice any delay at all lemme know
	// i have some solutions i can cook up

	// Generate S curve path using math that hits these waypoints, call it A
	auton_chassis_contr->generatePath({
		{0_in, 0_in, 0_deg}, // starting pos
		{24_in, 12_in, 90_deg},
		{36_in, 24_in, 0_deg}
	}, "A");

	// Execute "A" Path
	auton_chassis_contr->setTarget("A");
	auton_chassis_contr->waitUntilSettled();
});


/* ========================================================================== */
/*                              Class Definitions                             */
/* ========================================================================== */
/* --------------- DO NOT TOUCH UNLESS YOU KNOW WHAT UR DOING --------------- */

AutonomousSelector::AutonomousSelector() {
	std::vector<AutoRoutine> auto_arr();
}


/**
 *@brief add auto routine to back of auto arr
 *
 * @param ar auto routine to add
 */
void AutonomousSelector::add_auto(AutoRoutine ar) {
	auto_arr.push_back(ar);
}


/**
 *@brief run currently selected auto
 *
 */
void AutonomousSelector::run_selected() {
	auto_arr[selected_index].run();
}


/**
 *@brief get name of current selected auto
 *
 * @return std::string
 */
std::string AutonomousSelector::get_selected() {
	return auto_arr[selected_index].get_name();
}


/**
 *@brief Search through arr and select auto with name str
 *
 * @param str name to match
 * @return int index of selected; -1 if not found
 */
int AutonomousSelector::set_selected(std::string str) {
	for (size_t i = 0; i < auto_arr.size(); i++)
	{
		if (str == auto_arr[i].get_name()) {
			selected_index = i;
			return selected_index;
		}
	}

	return -1;
}


/**
 *@brief increase selected index by 1 or wrap around if currently at max
 *
 * @return int current index
 */
int AutonomousSelector::increase_selected() {
	selected_index++;
	if (selected_index >= auto_arr.size()) selected_index = 0;
	return selected_index;
}


/**
 *@brief decrease selected index by 1 or wrap around if currently at 0
 *
 * @return int current index
 */
int AutonomousSelector::decrease_selected() {
	selected_index--;
	if (selected_index < 0) selected_index = auto_arr.size() - 1;
	return selected_index;
}


/**
 *@brief return size of auto routine vector
 *
 * @return int
 */
int AutonomousSelector::get_num_autons() {
	return auto_arr.size();
}