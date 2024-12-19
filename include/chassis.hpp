#pragma once

#include "main.h"
#include "util.hpp"

extern okapi::Controller controller;

#define CHASSIS_L_1 1
#define CHASSIS_L_2 2
#define CHASSIS_L_3 3
#define CHASSIS_R_1 4
#define CHASSIS_R_2 5
#define CHASSIS_R_3 6

#define LIFT_MOTOR_PORT 7

#define INTAKE_MOTOR_PORT 8

#define CHAIN_MOTOR_PORT 9

#define STAKE_MOTOR_PORT 10

#define HOOK_PNEU_PORT 'A'



/* ========================================================================== */
/*                             Chassis Controller                             */
/* ========================================================================== */
extern std::shared_ptr < okapi::ChassisController> chassis;

extern std::shared_ptr<okapi::AsyncMotionProfileController> auton_chassis_contr;


/* ========================================================================== */
/*                                    Motor                                   */
/* ========================================================================== */
extern std::shared_ptr<okapi::AsyncPositionController<double, double>> lift_contr;


extern okapi::Motor test_motor;

extern okapi::MotorGroup intake_and_chain_motors;

extern okapi::Motor stake_motor;



/* ========================================================================== */
/*                                    Pneumatics                              */
/* ========================================================================== */

extern pros::ADIDigitalOut hookPneumatics;

