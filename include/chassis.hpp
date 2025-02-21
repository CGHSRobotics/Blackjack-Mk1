#pragma once

#include "main.h"
#include "util.hpp"

extern okapi::Controller controller;

#define CHASSIS_L_1 -11
#define CHASSIS_L_2 -4



#define CHASSIS_L_3 -7



#define CHASSIS_R_1 10
#define CHASSIS_R_2 19
#define CHASSIS_R_3 8


#define LIFT_MOTOR_PORT 10

#define INTAKE_MOTOR_PORT -1

#define CHAIN_MOTOR_PORT 2

#define ROTATIONAL_SENSOR 20

#define STAKE_MOTOR_PORT 3

#define HOOK_PNEU_PORT 'A'

#define FLAP_PNEU_PORT 'B'

/* ========================================================================== */
/*                             Chassis Controller                             */
/* ========================================================================== */
extern std::shared_ptr<okapi::ChassisController> chassis;

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

extern pros::ADIDigitalOut flapPneumatics;
