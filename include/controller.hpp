#pragma once

#include "chassis.hpp"


/* ========================================================================== */
/*                          Controller Display Class                          */
/* ========================================================================== */
class ControllerDisplay
{

	private:
	char* screen_buff[3];
	int cur_line = 0;

	public:

	ControllerDisplay();

	void setLine(int line_num, char* str, ...);

	void start_update_task();

	void update();

};

