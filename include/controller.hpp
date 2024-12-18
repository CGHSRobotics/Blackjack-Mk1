#pragma once

#include "chassis.hpp"


using enum okapi::ControllerDigital;


/* ========================================================================== */
/*                          Controller Display Class                          */
/* ========================================================================== */
class ControllerDisplay
{

	private:
	char* screen_buff[3];
	int cur_line = 0;

	void update();

	public:

	ControllerDisplay();

	void setLine(int line_num, char* str, ...);

	void start_update_task();


	~ControllerDisplay() {
		free(screen_buff[0]);
		free(screen_buff[1]);
		free(screen_buff[2]);
	}
};

