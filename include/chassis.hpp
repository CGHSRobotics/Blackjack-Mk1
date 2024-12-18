#pragma once

#include "main.h"

extern okapi::Controller controller;

#define CHASSIS_L_1 1
#define CHASSIS_L_2 2
#define CHASSIS_L_3 3
#define CHASSIS_R_1 4
#define CHASSIS_R_2 5
#define CHASSIS_R_3 6

#define LIFT_MOTOR_PORT 7


/* ========================================================================== */
/*                             Chassis Controller                             */
/* ========================================================================== */
extern std::shared_ptr < okapi::ChassisController> chassis;

extern std::shared_ptr<okapi::AsyncMotionProfileController> auton_chassis_contr;


/* ========================================================================== */
/*                                    Motor                                   */
/* ========================================================================== */
extern std::shared_ptr<okapi::AsyncPositionController<double, double>> lift_contr;