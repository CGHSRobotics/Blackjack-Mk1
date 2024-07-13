#include "main.h"

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

// Chassis Controller - lets us drive the robot around with open- or closed-loop control
std::shared_ptr<ChassisController> drive =
	ChassisControllerBuilder()
		.withMotors(MotorGroup({CHASSIS_L_1, CHASSIS_L_2, CHASSIS_L_3}), MotorGroup({CHASSIS_R_1, CHASSIS_R_2, CHASSIS_R_3}))
		// Green gearset, 4 in wheel diam, 11.5 in wheel track
		.withDimensions(AbstractMotor::gearset::blue, {{4_in, 11.5_in}, imev5GreenTPR})
		.withOdometry()
		.build();

// Arm related objects
ADIButton armLimitSwitch('H');

// other motors, pistons, sensors etc


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
void autonomous() {}


/* ========================================================================== */
/*                                User Control                                */
/* ========================================================================== */
void opcontrol()
{

	// Joystick to read analog values for tank or arcade control
	// Master controller by default
	Controller controller;


	ControllerButton armUpButton(ControllerDigital::A);
	ControllerButton armDownButton(ControllerDigital::B);
	Motor armMotor(-8);

	// Button to run our sample autonomous routine
	ControllerButton runAutoButton(ControllerDigital::X);

	while (true)
	{
		// Tank drive with left and right sticks
		drive->getModel()->arcade(controller.getAnalog(ControllerAnalog::leftY),
								controller.getAnalog(ControllerAnalog::rightY));

		// Don't power the arm if it is all the way down
		if (armLimitSwitch.isPressed())
		{
			armMotor.moveVelocity(0);
		}
		else
		{
			// else, the arm isn't all the way down
			if (armUpButton.isPressed())
			{
				armMotor.moveVoltage(12000);
			}
			else if (armDownButton.isPressed())
			{
				armMotor.moveVoltage(-12000);
			}
			else
			{
				armMotor.moveVoltage(0);
			}
		}

		// Run the test autonomous routine if we press the button
		if (runAutoButton.changedToPressed())
		{
			// Drive the robot in a square pattern using closed-loop control
			for (int i = 0; i < 4; i++)
			{
				drive->moveDistance(12_in); // Drive forward 12 inches
				drive->turnAngle(90_deg);	// Turn in place 90 degrees
			}
		}

		// Wait and give up the time we don't need to other tasks.
		// Additionally, joystick values, motor telemetry, etc. all updates every 10 ms.
		pros::delay(10);
	}
}