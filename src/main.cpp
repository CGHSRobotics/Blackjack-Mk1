#include "main.h"

#include "util.cpp"

/* ========================================================================== */
/*                                    Ports                                   */
/* ========================================================================== */
#define CHASSIS_L_1 1
#define CHASSIS_L_2 2
#define CHASSIS_L_3 3
#define CHASSIS_R_1 4
#define CHASSIS_R_2 5
#define CHASSIS_R_3 6


/* ========================================================================== */
/*                                   Devices                                  */
/* ========================================================================== */

// Controller
Controller controller;
blkjack::ControllerText controllerText(&controller);

// Chassis Controller - lets us drive the robot around with open- or closed-loop control
std::shared_ptr<ChassisController> drive = ChassisControllerBuilder()
.withMotors(MotorGroup({ CHASSIS_L_1, CHASSIS_L_2, CHASSIS_L_3 }), MotorGroup({ CHASSIS_R_1, CHASSIS_R_2, CHASSIS_R_3 }))
// Green gearset, 4 in wheel diam, 11.5 in wheel track
.withDimensions(AbstractMotor::gearset::blue, { {4_in, 11.5_in}, imev5GreenTPR })
.withOdometry()
.build();

// Arm related objects
ADIButton armLimitSwitch('H');

// other motors, pistons, sensors etc
Motor armMotor(-8);


/* ========================================================================== */
/*                           Include Auton And LVGL                           */
/* ========================================================================== */

#include "auton.cpp"
#include "lvgl.cpp"


/* ========================================================================== */
/*                                 Initialize                                 */
/* ========================================================================== */
void initialize()
{
}


/* ========================================================================== */
/*                                  Disabled                                  */
/* ========================================================================== */
void disabled() {}


/* ========================================================================== */
/*                           Competition Initialize                           */
/* ========================================================================== */
void competition_initialize() {}


/* ========================================================================== */
/*                                 Autonomous                                 */
/* ========================================================================== */
void autonomous() {

	// Exception conditions, should never trigger
	if (auton::cur_auton < 0) auton::cur_auton = 0;
	if (auton::cur_auton >= auton::NUM_AUTONS) auton::cur_auton = auton::NUM_AUTONS - 1;

	// Switch case
	switch (str2int(auton::autons_arr[auton::cur_auton]))
	{
		case str2int("red side"):
			auton::red_side();
			break;

		case str2int("blue side"):

			break;

		case str2int("skills"):

			break;

		default:

			break;
	}
}


/* ========================================================================== */
/*                                User Control                                */
/* ========================================================================== */
void opcontrol()
{

	blkjack::MotorButton armButton(&armMotor, ControllerDigital::A);

	while (true)
	{
		/* ---------------------------------- Drive --------------------------------- */
		// arcade drive with left and right sticks
		drive->getModel()->arcade(controller.getAnalog(ControllerAnalog::leftY),
			controller.getAnalog(ControllerAnalog::rightY));

		/* ------------------------- Other Motors / Pistons ------------------------- */

		armButton.toggle();

		/* ----------------------------- Draw Controller ---------------------------- */

		/*
			How to use:

			Controller text is set with a row, a starting column, length of total string
			and a label string + a value. value is converted into string automatically to fill void
			This allows you to section off arreas of the controller screen into blocks to ensure
			there is no overcrowding

			ex:

			- - - - - - - - - - - -
			| s p e e d : _ 1 0 0 |		controllerText.setText(0, 0, 10, "speed: ", 100);
			- - - - - - - - - - - -
			^ a block of size 10

			- - - - - - - - - - - -
			| s p e e d : _ _ 8 0 |		controllerText.setText(0, 0, 10, "speed: ", 80);
			- - - - - - - - - - - -
			^ a block of size 10

			- - - - - - - - - - - -
			| s p e e d : _ _ _ 7 |		controllerText.setText(0, 0, 10, "speed: ", 7);
			- - - - - - - - - - - -
			^ a block of size 10

			line: 0-2
			col: 0-18
			length: 1-18 *MUST BE GREATER THAN LABEL LEN AND LESS THAN (18 - col)

		*/


		controllerText.update();

		/* ---------------------------------- Delay --------------------------------- */
		// Wait and give up the time we don't need to other tasks.
		// Additionally, joystick values, motor telemetry, etc. all updates every 10 ms.
		pros::delay(10);
	}
}