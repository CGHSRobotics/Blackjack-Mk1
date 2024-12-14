
#include "controller.hpp"


/**
 *@brief Construct a new Controller Display:: Controller Display object
 *
 */
ControllerDisplay::ControllerDisplay() {

	// Alloted for 64 chars incase over flow, vex limits to 15 on screen tho
	screen_buff[0] = (char*)malloc(sizeof(char) * 64);
	screen_buff[1] = (char*)malloc(sizeof(char) * 64);
	screen_buff[2] = (char*)malloc(sizeof(char) * 64);

}


/**
 *@brief Set text for line, uses printf format specifiers
 *
 * @param line_num line num [0-2]
 * @param fmt	"Hello %d" MAKE SURE THIS IS <= 15 CHARACTERS
 * @param ...	 5
 */
void ControllerDisplay::setLine(int line_num, char* fmt, ...)
{
	fflush(stdout);
	va_list(args);
	va_start(args, fmt);

	char buff[64];
	sprintf(buff, fmt, args);

	strcpy(screen_buff[line_num], buff);
}


/**
 *@brief start update task
 *	ONLY RUN ONCE AND IN init() !!!!!!
 *
 */
void ControllerDisplay::start_update_task() {
	pros::Task my_task([this] {
		this->update();
		pros::delay(50);
	});
}


/**
 *@brief update func to display text, do not call directly
 *
 */
void ControllerDisplay::update() {

	controller.setText(cur_line, 0, screen_buff[cur_line]);

	cur_line++;
	if (cur_line >= 3) cur_line = 0;

}