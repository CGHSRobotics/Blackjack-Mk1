#pragma once

#include "main.h"

namespace auton {

	/* ========================================================================== */
	/*                            Autonomous Constants                            */
	/* ========================================================================== */

	const int NUM_AUTONS = 3;
	const char* autons_arr[3] = { "red side", "blue side", "skills" };
	int cur_auton = 0;

	/* ========================================================================== */
	/*                          Autonomous Util Functions                         */
	/* ========================================================================== */


	/* ========================================================================== */
	/*                             Autonomous Routines                            */
	/* ========================================================================== */

	/**
	 *@brief red side auton routine
	 *
	 */
	void red_side() {
		// do thing
	}



}