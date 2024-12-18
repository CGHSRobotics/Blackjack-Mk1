#include "main.h"

#include "chassis.hpp"
#include "controller.hpp"
#include "autonomous.hpp"
#include "lvgl.hpp"


ControllerDisplay controller_display;

AutonomousSelector auto_selector;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {

	// Start Controller Display Task
	controller_display.start_update_task();

	auto_selector.add_auto(three_side);
	//auto_selector.add_auto(two_side);
	//auto_selector.add_auto(awp);
	//auto_selector.add_auto(skills);

	// Lvgl test, lemme know if no worky
	lv_example_get_started_3();

}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	// nothing here
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	// Nothing here
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	auto_selector.set_selected("Three Side");
	auto_selector.run_selected();
}


void test() {

}
/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {

	// test button motor with button A and test_motor
	// should also work with motor groups (think intake)
	ButtonMotor test(A, &test_motor);

	while (true) {


		/* ========================================================================== */
		/*                                  Controls                                  */
		/* ========================================================================== */

		// use test motor like a toggle on button a
		// 60% speed, reversed
		test.toggle(60, true);




		/* ========================================================================== */
		/*                                    Drive                                   */
		/* ========================================================================== */
		chassis->getModel()->tank(controller.getAnalog(okapi::ControllerAnalog::leftY),
							controller.getAnalog(okapi::ControllerAnalog::rightY));


		/* ========================================================================== */
		/*                                   Screen                                   */
		/* ========================================================================== */

		//start controller display
		controller_display.setLine(0, "Hello %s!", "Nick");

		// display variables like so
		int num = 5;
		controller_display.setLine(1, "num: %d", num);

		// or make variables always 3 min wide like this
		controller_display.setLine(2, "num: %03d", num);

		// Cheat Sheet available here:
		// https://alvinalexander.com/programming/printf-format-cheat-sheet/


		/* ---------------------------------- Delay --------------------------------- */
		pros::delay(10);                               // Run for 10 ms then update
	}
}