
#include "chassis.hpp"

/* ------------------------------- Controller ------------------------------- */
okapi::Controller controller;


/* --------------------------------- Chassis -------------------------------- */
std::shared_ptr <okapi::ChassisController> chassis =
okapi::ChassisControllerBuilder()
.withMotors(okapi::MotorGroup({ CHASSIS_L_1, CHASSIS_L_2, CHASSIS_L_3 }), okapi::MotorGroup({ CHASSIS_R_1, CHASSIS_R_2, CHASSIS_R_3 }))
.withDimensions(okapi::AbstractMotor::gearset::green, { {4_in, 11.5_in}, okapi::imev5GreenTPR })
.withOdometry()
.build();



std::shared_ptr<okapi::AsyncMotionProfileController> auton_chassis_contr =
okapi::AsyncMotionProfileControllerBuilder()
.withLimits({
  1.0, // Maximum linear velocity of the Chassis in m/s
  2.0, // Maximum linear acceleration of the Chassis in m/s/s
  10.0 // Maximum linear jerk of the Chassis in m/s/s/s
})
.withOutput(chassis)
.buildMotionProfileController();



/* ----------------------------- Lift Controller ---------------------------- */
const double liftkP = 0.001;
const double liftkI = 0.0001;
const double liftkD = 0.0001;

std::shared_ptr<okapi::AsyncPositionController<double, double>> lift_contr =
okapi::AsyncPosControllerBuilder()
.withMotor(LIFT_MOTOR_PORT) // lift motor port 3
.withGains({ liftkP, liftkI, liftkD })
.build();


