#include "main.h"
#pragma once

/* ------------------------------ Our Namespace ----------------------------- */
namespace blkjack {

	/* ------------------------------- Timer Class ------------------------------ */
	class timer {
		public:
		float maxTime = 0;
		float currTime = 0;

		/**
		 *@brief Construct a new timer object
		 *
		 * @param max_time maximum time in timer in milleseconds
		 */
		timer(float max_time) {
			maxTime = max_time;
			currTime = 0;
		}

		/**
		 *@brief update timer
		 *
		 * @param updateTime amount of time to update timer by, default 10 ms
		 */
		void update(float updateTime = 10.0) {
			currTime += updateTime;
		}

		/**
		 *@brief returns true if timer is done, else false
		 *
		 * @return true
		 * @return false
		 */
		bool done() {
			return currTime >= maxTime;
		}

		/**
		 *@brief Reset timer
		 *
		 */
		void reset() {
			currTime = 0;
		}
	};

	/**
	 *@brief Button Motor Class. links a button and a motor together for easy toggles, presses without a billion copy pastes
	 *
	 */
	class MotorButton
	{
		public:

		Motor* motor;
		ControllerButton button = ControllerButton(ControllerDigital::A);
		float speed = 100;
		bool enabled = false;

		/**
		 *@brief Construct a new Button Motor object
		 *
		 * @param m pointer to a motor m to control; ex: "&armMotor"
		 * @param b button to use; ex: "ControllerDigital::A"
		 */
		MotorButton(Motor* m, ControllerDigital b)
		{
			motor = m;
			button = ControllerButton(b);
		}

		/**
		 *@brief Checks if motor is toggled and spins motor at speed if true. returns whether is currently spinning
		 *
		 * @return true
		 * @return false
		 */
		bool toggle() {

			if (button.changedToPressed()) enabled = !enabled;

			motor->moveVelocity(enabled * speed);

			return enabled;
		}

		/**
		 *@brief Spins motor if controller is pressed. returns if currently spinning
		 *
		 * @return true
		 * @return false
		 */
		bool press() {

			enabled = button.isPressed();

			motor->moveVelocity(enabled * speed);

			return enabled;
		}

		/**
		 *@brief Sets speed
		 *
		 * @param speed float 0-100 in percent of speed
		 */
		void setSpeed(float speed) {
			speed = speed;
		}
	};


	class ControllerText
	{
		public:

		Controller* c;
		std::string text_arr[3];

		int next_line_to_write = 0;

		ControllerText(Controller* c) {
			c = c;

			for (int i = 0; i < 19; i++)
			{
				text_arr[0].append(" ");
				text_arr[1].append(" ");
				text_arr[2].append(" ");
			}
		};

		void update() {
			c->setText(next_line_to_write, 0, text_arr[next_line_to_write]);

			next_line_to_write++;
			if (next_line_to_write >= 3) next_line_to_write = 0;
		};

		void setText(int line, int col, int length, std::string label, int value) {
/*
			// Conditions

			// assign text
			text_arr[line].replace(col, label.length(), label);
			int len_for_value = length - label.length();

			string str = value;
*/
		};

	};


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
constexpr unsigned int str2int(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}




