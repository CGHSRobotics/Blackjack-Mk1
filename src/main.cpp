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
#include "notagame.cpp"


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

	ControllerButton notagamebutton(ControllerDigital::X);


	while (true)
	{
		if (notagamebutton.changedToPressed()) not_blackjack(&controllerText);

		/* ---------------------------------- Drive --------------------------------- */
		// arcade drive with left and right sticks
		drive->getModel()->arcade(controller.getAnalog(ControllerAnalog::leftY),
			controller.getAnalog(ControllerAnalog::rightY));

		/* ------------------------- Other Motors / Pistons ------------------------- */

		armButton.toggle();

		/* ----------------------------- Draw Controller ---------------------------- */

		controllerText.update();

		/* ---------------------------------- Delay --------------------------------- */
		// Wait and give up the time we don't need to other tasks.
		// Additionally, joystick values, motor telemetry, etc. all updates every 10 ms.
		pros::delay(10);
	}
}