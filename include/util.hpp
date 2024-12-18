#pragma once

#include "main.h"

enum m_or_mg { motor_type, mgroup_type };

/* ========================================================================== */
/*                             Motor Button Class                             */
/* ========================================================================== */
class ButtonMotor
{
	private:
	okapi::ControllerDigital button;

	okapi::Motor* m;
	okapi::MotorGroup* mg;
	m_or_mg type;

	bool toggle_enabled = false;

	public:

	/* ------------------------------ Contstructor ------------------------------ */
	ButtonMotor(okapi::ControllerDigital b, okapi::Motor* m) {
		button = b;
		m = m;
		mg = NULL;
		type = motor_type;
	};
	ButtonMotor(okapi::ControllerDigital b, okapi::MotorGroup* mg) {
		button = b;
		m = NULL;
		mg = mg;
		type = mgroup_type;
	}


	int gearing_multiplier() {
		if (type == motor_type)
		{
			switch (m->getGearing())
			{
				case okapi::AbstractMotor::gearset::blue:
					return 6;
					break;

				case okapi::AbstractMotor::gearset::green:
					return 2;
					break;


				case okapi::AbstractMotor::gearset::red:
					return 1;
					break;


				default:
					break;
			}
		}
	}


	/* --------------------------------- Toggle --------------------------------- */
	int toggle(int speed = 100, bool reverse = false) {

		if (controller[button].changedToPressed()) toggle_enabled = !toggle_enabled;

		if (toggle_enabled)
		{
			if (type == motor_type)
			{
				m->moveVelocity(speed * gearing_multiplier() * (reverse) ? -1 : 1);
			}
			else	// is motor group
			{
				mg->moveVelocity(speed * gearing_multiplier() * (reverse) ? -1 : 1);
			}
		}
		else
		{
			if (type == motor_type)
			{
				m->moveVelocity(0);
			}
			else	// is motor group
			{
				mg->moveVelocity(0);
			}
		}

		return toggle_enabled;
	}


	/* ---------------------------------- Press --------------------------------- */
	int press(int speed = 100, bool reverse = false) {

		if (controller[button].isPressed())
		{
			if (type == motor_type)
			{
				m->moveVelocity(speed * gearing_multiplier() * (reverse) ? -1 : 1);
			}
			else	// is motor group
			{
				mg->moveVelocity(speed * gearing_multiplier() * (reverse) ? -1 : 1);
			}
		}
		else
		{
			if (type == motor_type)
			{
				m->moveVelocity(0);
			}
			else	// is motor group
			{
				mg->moveVelocity(0);
			}
		}

		return controller[button].isPressed();
	}


	~ButtonMotor();
};
