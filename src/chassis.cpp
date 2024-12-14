
#include "chassis.hpp"

okapi::Controller controller;


std::shared_ptr < okapi::ChassisController> chassis =

okapi::ChassisControllerBuilder()
.withMotors(okapi::MotorGroup({ CHASSIS_L_1, CHASSIS_L_2, CHASSIS_L_3 }), okapi::MotorGroup({ CHASSIS_R_1, CHASSIS_R_2, CHASSIS_R_3 }))
.withDimensions(okapi::AbstractMotor::gearset::green, { {4_in, 11.5_in}, okapi::imev5GreenTPR })
.withOdometry()
.build();
