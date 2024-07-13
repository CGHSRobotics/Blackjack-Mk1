#ifndef ACE_CGHS
#define ACE_CGHS

#include "main.h"



/* ------------------------------- Timer Class ------------------------------ */
class timer {
 public:
  float maxTime = 0;
  float currTime = 0;

  timer(float max_time) {
    maxTime = max_time;
    currTime = 0;
  }

  void update(float updateTime) {
    currTime += updateTime;
  }

  bool done() {
    return currTime >= maxTime;
  }

  void reset() {
    currTime = 0;
  }
};


	/* --------------------------------- Chassis -------------------------------- */
	#define PORT_CHASSIS_L_F -6
	#define PORT_CHASSIS_L_B -7
	#define PORT_CHASSIS_L_M -9

	#define PORT_CHASSIS_R_F 16
	#define PORT_CHASSIS_R_B 15
	#define PORT_CHASSIS_R_M 12

	/* ------------------------- Other Motors / Devices ------------------------- */
	#define PORT_INTAKE -20
	#define PORT_LAUNCHER 10
	#define PORT_LIFT 2


	#define PORT_VISION 10
	#define PORT_IMU 5












#endif