#include "main.h"

#include "util.h"

/* ========================================================================== */
/*                                    Ports                                   */
/* ========================================================================== */
#define CHASSIS_L_1 -11
#define CHASSIS_L_2 -2
#define CHASSIS_L_3 -1
#define CHASSIS_R_1 20
#define CHASSIS_R_2 19
#define CHASSIS_R_3 12
#define OPTICAL_PORT 5

/* ========================================================================== */
/*                                   Devices                                  */
/* ========================================================================== */

// Controller
Controller controller;
// This may need to go into init!
pros::Optical optical_sensor(OPTICAL_PORT);
// Controller Task
/*
blkjack::ControllerText controllerText(&controller);
pros::Task update_controller_task = pros::Task(blkjack::update_controller_text, (void*)&controllerText);
*/

// Chassis Controller - lets us drive the robot around with open- or closed-loop control
std::shared_ptr<ChassisController> drive = ChassisControllerBuilder()
.withMotors(MotorGroup({ CHASSIS_L_1, CHASSIS_L_2, CHASSIS_L_3 }), MotorGroup({ CHASSIS_R_1, CHASSIS_R_2, CHASSIS_R_3 }))
// Green gearset, 4 in wheel diam, 11.5 in wheel track
.withDimensions(AbstractMotor::gearset::blue, { {2.75_in, 9_in}, imev5BlueTPR })
.withOdometry()
.build();

// Arm related objects
ADIButton armLimitSwitch('H');

// other motors, pistons, sensors etc
Motor armMotor(-8, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
MotorGroup intakeMotors({ -15, 6 });

/* ========================================================================== */
/*                           Include Auton And LVGL                           */
/* ========================================================================== */

#include "auton.h"
#include "lvgl.h"
#include "notagame.h"

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
void autonomous()
{

	// Exception conditions, should never trigger
	if (auton::cur_auton < 0)
		auton::cur_auton = 0;
	if (auton::cur_auton >= auton::NUM_AUTONS)
		auton::cur_auton = auton::NUM_AUTONS - 1;

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

//hi

/* ========================================================================== */
/*                                User Control                                */
/* ========================================================================== */
void opcontrol()
{
	pros::Optical optical_sensor(OPTICAL_PORT);


	blkjack::MotorButton armButton(&armMotor, ControllerDigital::A);

	blkjack::MotorButton intakeButton(&intakeMotors, ControllerDigital::L1);
	// blkjack::MotorButton intakeButton(&intakeMotors, ControllerDigital::B);

	ControllerButton notagamebutton(ControllerDigital::X);

	while (true)
	{
		// if (notagamebutton.changedToPressed()) not_blackjack(&controllerText);

		/* ---------------------------------- Drive --------------------------------- */
		// arcade drive with left and right sticks
		drive->getModel()->tank(controller.getAnalog(ControllerAnalog::leftY),
								controller.getAnalog(ControllerAnalog::rightY));

		/* ------------------------- Other Motors / Pistons ------------------------- */

		armButton.toggle();

		intakeButton.press();

		// intakeButton.toggle();

		/* ---------------------------------- Delay --------------------------------- */
		// Wait and give up the time we don't need to other tasks.
		// Additionally, joystick values, motor telemetry, etc. all updates every 10 ms.
		pros::delay(10);
	}
}