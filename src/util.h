#pragma once

#include "main.h"

/* ------------------------------ Our Namespace ----------------------------- */
namespace blkjack
{

	/* ------------------------------- Timer Class ------------------------------ */
	class timer
	{
	public:
		float maxTime = 0;
		float currTime = 0;

		/**
		 *@brief Construct a new timer object
		 *
		 * @param max_time maximum time in timer in milleseconds
		 */
		timer(float max_time)
		{
			maxTime = max_time;
			currTime = 0;
		}

		/**
		 *@brief update timer
		 *
		 * @param updateTime amount of time to update timer by, default 10 ms
		 */
		void update(float updateTime = 10.0)
		{
			currTime += updateTime;
		}

		/**
		 *@brief returns true if timer is done, else false
		 *
		 * @return true
		 * @return false
		 */
		bool done()
		{
			return currTime >= maxTime;
		}

		/**
		 *@brief Reset timer
		 *
		 */
		void reset()
		{
			currTime = 0;
		}
	};

	/**
	 *@brief Button Motor Class. links a button and a motor together for easy toggles, presses without a billion copy pastes
	 *
	 */
	class MotorButton
	{
		private:
		float speed = 100;
		bool enabled = false;
		bool is_mg = false;
		int gearint = 1;
		// Defaults to green
		AbstractMotor::gearset gear = AbstractMotor::gearset::green;
		AbstractMotor::encoderUnits encodingUnits = AbstractMotor::encoderUnits::degrees;

		void find_gearint() {
			if (gear == AbstractMotor::gearset::red) gearint = 1;
			if (gear == AbstractMotor::gearset::green) gearint = 2;
			if (gear == AbstractMotor::gearset::blue) gearint = 6;
		}
		
		public:
		Motor *motor;
		MotorGroup *motor_group;
		ControllerButton button = ControllerButton(ControllerDigital::A);
		
		/**
		 *@brief Construct a new Button Motor object
		 *
		 * @param m pointer to a motor m to control; ex: "&armMotor"
		 * @param b button to use; ex: "ControllerDigital::A"
		 */
		MotorButton(Motor *m, ControllerDigital b)
		{
			motor = m;
			button = ControllerButton(b);
			gear = motor->getGearing();
		}
		// Same as above but for motor groups
		MotorButton(MotorGroup *mg, ControllerDigital b, AbstractMotor::gearset gearing = AbstractMotor::gearset::green)
		{
			motor_group = mg;
			button = ControllerButton(b);
			is_mg = true;
			gear = gearing;
		}

		/**
		 *@brief Checks if motor is toggled and spins motor at speed if true. returns whether is currently spinning
		 *
		 * @return true
		 * @return false
		 */
		bool toggle()
		{

			if (button.changedToPressed())
				enabled = !enabled;

			if (!is_mg)
				motor->moveVelocity(enabled * speed * gearint);
			else
				motor_group->moveVelocity(enabled * speed * gearint);

			return enabled;
		}

		/**
		 *@brief Spins motor if controller is pressed. returns if currently spinning
		 *
		 * @return true
		 * @return false
		 */
		bool press()
		{
			enabled = button.isPressed();

			if (!is_mg)
				motor->moveVelocity(enabled * speed);
			else
				motor_group->moveVelocity(enabled * speed);

			return enabled;
		}

		/**
		 *@brief Sets speed
		 *
		 * @param speed float 0-100 in percent of speed
		 */
		void setSpeed(float speed)
		{
			speed = speed;
		}
	};

	/**
	 *@brief Class to control text on controller screen
	 *
	 */
	class ControllerText
	{
	public:
		Controller *c;
		std::string text_arr[3];

		int next_line_to_write = 0;

		ControllerText(Controller *c)
		{
			c = c;
			clearAll();
		};

		/**
		 *@brief updates screen by drawing next line
		 *
		 */
		void update(void *param)
		{
			c->setText(next_line_to_write, 0, text_arr[next_line_to_write]);

			next_line_to_write++;
			if (next_line_to_write >= 3)
				next_line_to_write = 0;
		};

		/**
		 *@brief Clears the whole screen
		 *
		 */
		void clearAll()
		{
			text_arr[0] = "                   ";
			text_arr[1] = "                   ";
			text_arr[2] = "                   ";
		}

		/**
		 *@brief Clears particular line
		 *
		 * @param line line to clear
		 */
		void clearLine(int line)
		{
			text_arr[line] = "                   ";
		}

		/**
		 *@brief Set text for a certain block
		 *
		 * @param line line for block
		 * @param col starting column
		 * @param length length of total block
		 * @param label string label
		 * @param value value in int
		 */
		void setText(int line, int col, int length, std::string label, int value)
		{

			// Conditions

			// assign text
			text_arr[line].replace(col, label.length(), label);
			int len_for_value = length - label.length();

			string str = std::to_string(value);

			text_arr[line].replace(col + label.length(), len_for_value, str);
		};
	};

	void update_controller_text(void *cl)
	{
		ControllerText *ct = (ControllerText *)cl;
		ct->c->setText(ct->next_line_to_write, 0, ct->text_arr[ct->next_line_to_write]);

		ct->next_line_to_write++;
		if (ct->next_line_to_write >= 3)
			ct->next_line_to_write = 0;
	};

	const pros::ADIDigitalOut hookPneumatics(PORT_PNEU_HOOK, false);

	void hook_toggle(bool enabled)
	{
		if (enabled) {
    hookPneumatics.set_value(1);
    return;

  } else {
    hookPneumatics.set_value(0);

		}
	}

/* ========================================================================== */
/*                            Random Util Function                            */
/* ========================================================================== */

/**
 *@brief copy pastes from stack overflow. converts std::string to int. contextptr is so it can pre math-inate
 *
 * @param str string to convert
 * @param h
 * @return constexpr unsigned int
 */
constexpr unsigned int str2int(const char *str, int h = 0)
{
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}
