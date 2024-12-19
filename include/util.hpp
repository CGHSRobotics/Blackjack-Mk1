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
	ButtonMotor(okapi::ControllerDigital b, okapi::Motor* mi) {
		button = b;
		m = mi;
		mg = NULL;
		type = motor_type;
	};
	ButtonMotor(okapi::ControllerDigital b, okapi::MotorGroup* mgi) {
		button = b;
		m = NULL;
		mg = mgi;
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


	~ButtonMotor() {};
};


/* ---------------------------- Pnuematics Button --------------------------- */
// cheeky copy paste
class ButtonPneumatics
{
	private:
	okapi::ControllerDigital button;

	pros::ADIDigitalOut* p;

	bool toggle_enabled = false;

	public:

	/* ------------------------------ Contstructor ------------------------------ */
	ButtonPneumatics(okapi::ControllerDigital b, pros::ADIDigitalOut* p) {
		button = b;
		p = p;
	};


	/* --------------------------------- Toggle --------------------------------- */
	int toggle() {

		if (controller[button].changedToPressed()) toggle_enabled = !toggle_enabled;

		if (toggle_enabled)
		{
			p->set_value(true);
		}
		else
		{
			p->set_value(false);
		}

		return toggle_enabled;
	}


	/* ---------------------------------- Press --------------------------------- */
	int press(int speed = 100, bool reverse = false) {

		if (controller[button].isPressed())
		{
			p->set_value(true);
		}
		else
		{
			p->set_value(false);
		}

		return controller[button].isPressed();
	}


	~ButtonPneumatics() {};
};
