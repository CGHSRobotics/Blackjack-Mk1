
#include "autonomous.hpp"
#include "chassis.hpp"
#include "lvgl.hpp"

/* ========================================================================== */
/*                             Autonomous Routines                            */
/* ========================================================================== */

AutonomousSelector auto_selector;





AutoRoutine blue_positive("Blue Positive", [] {

	
	

	
});


AutoRoutine red_positive("Red Positive", [] {
	chassis->setMaxVelocity(100);

	chassis->moveDistance(-42_in);
	// lets you do other things
	pros::delay(400);

	hookPneumatics.set_value(1);

	intake_and_chain_motors.moveVelocity(-600);

	pros::delay(400);

	chassis->turnAngle(-160_deg);

	chassis->setMaxVelocity(300);
	

	chassis->moveDistance(30_in);

	chassis->turnAngle(-200_deg);

	chassis->moveDistance(46_in);

});


AutoRoutine blue_negative("Blue Negative", [] {




});


AutoRoutine red_negative("Red Negative", [] {
	chassis->setMaxVelocity(100);

	chassis->moveDistance(-42_in);
	// lets you do other things
	pros::delay(400);

	hookPneumatics.set_value(1);

	intake_and_chain_motors.moveVelocity(-600);

	pros::delay(400);

	chassis->turnAngle(160_deg);

	chassis->setMaxVelocity(300);
	

	chassis->moveDistance(30_in);

	chassis->turnAngle(200_deg);

	chassis->moveDistance(40_in);



});
/**
 *@brief Three side auto does whattt???
 *
 */

AutoRoutine skills("skills", [] {


	chassis->setMaxVelocity(100);

	chassis->moveDistance(-12_in);
	// lets you do other things
	pros::delay(400);

	hookPneumatics.set_value(1);

	pros::delay(400);

	//first turn to line up 
	chassis->turnAngle(-235_deg);

	chassis->setMaxVelocity(300);
	
	intake_and_chain_motors.moveVelocity(-600);

	chassis->moveDistance(40_in);
	//Second turn to line up with second 
	chassis->turnAngle(180_deg);

	chassis->moveDistance(35_in);

	//third turn 
	chassis->turnAngle(150_deg);
//140
	chassis->moveDistance(25_in);
	//fourth turn 
	//chassis->turnAngle(235_deg);
	//This turn was breaking it!
	//chassis->moveDistance(-5_in);


	chassis->waitUntilSettled();

	chassis->moveDistance(-20_in);

	chassis->moveDistance(10_in);

	chassis->turnAngle(90_deg);

	chassis->moveDistance(-30_in);

	hookPneumatics.set_value(0);


	//first quat scored 

	//test after
	/*
	chassis->turnAngle(100_deg);

	chassis->moveDistance(15_in);
	*/
});
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


AutoRoutine gen_test("gen test", [] {

	lv_gen_test();
	pros::Task::delay(100);

	// Generate S curve path using math that hits these waypoints, call it A
	auton_chassis_contr->generatePath({
		{0_in, 0_in, 0_deg}, // starting pos
		{24_in, 12_in, 90_deg},
		{36_in, 24_in, 0_deg}
	}, "A");
	// Generate S curve path using math that hits these waypoints, call it A
	auton_chassis_contr->generatePath({
		{0_in, 0_in, 0_deg}, // starting pos
		{24_in, 12_in, 90_deg},
		{36_in, 24_in, 0_deg}
	}, "B");
	// Generate S curve path using math that hits these waypoints, call it A
	auton_chassis_contr->generatePath({
		{0_in, 0_in, 0_deg}, // starting pos
		{24_in, 12_in, 90_deg},
		{36_in, 24_in, 0_deg}
	}, "C");
	// Generate S curve path using math that hits these waypoints, call it A
	auton_chassis_contr->generatePath({
		{0_in, 0_in, 0_deg}, // starting pos
		{24_in, 12_in, 90_deg},
		{36_in, 24_in, 0_deg}
	}, "D");
	// Generate S curve path using math that hits these waypoints, call it A
	auton_chassis_contr->generatePath({
		{0_in, 0_in, 0_deg}, // starting pos
		{24_in, 12_in, 90_deg},
		{36_in, 24_in, 0_deg}
	}, "E");
	// Generate S curve path using math that hits these waypoints, call it A
	auton_chassis_contr->generatePath({
		{0_in, 0_in, 0_deg}, // starting pos
		{24_in, 12_in, 90_deg},
		{36_in, 24_in, 0_deg}
	}, "F");
	// Generate S curve path using math that hits these waypoints, call it A
	auton_chassis_contr->generatePath({
		{0_in, 0_in, 0_deg}, // starting pos
		{24_in, 12_in, 90_deg},
		{36_in, 24_in, 0_deg}
	}, "G");
	// Generate S curve path using math that hits these waypoints, call it A
	auton_chassis_contr->generatePath({
		{0_in, 0_in, 0_deg}, // starting pos
		{24_in, 12_in, 90_deg},
		{36_in, 24_in, 0_deg}
	}, "H");
	// Generate S curve path using math that hits these waypoints, call it A
	auton_chassis_contr->generatePath({
		{0_in, 0_in, 0_deg}, // starting pos
		{24_in, 12_in, 90_deg},
		{36_in, 24_in, 0_deg}
	}, "I");
	// Generate S curve path using math that hits these waypoints, call it A
	auton_chassis_contr->generatePath({
		{0_in, 0_in, 0_deg}, // starting pos
		{24_in, 12_in, 90_deg},
		{36_in, 24_in, 0_deg}
	}, "J");
	// Generate S curve path using math that hits these waypoints, call it A
	auton_chassis_contr->generatePath({
		{0_in, 0_in, 0_deg}, // starting pos
		{24_in, 12_in, 90_deg},
		{36_in, 24_in, 0_deg}
	}, "K");
	// Generate S curve path using math that hits these waypoints, call it A
	auton_chassis_contr->generatePath({
		{0_in, 0_in, 0_deg}, // starting pos
		{24_in, 12_in, 90_deg},
		{36_in, 24_in, 0_deg}
	}, "L");
	lv_gen_test2();


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

AutoRoutine::AutoRoutine(std::string str, void (*f)()) {
	name = str;
	func = f;

	auto_selector.add_auto(*this);
}