#include "main.h"
#include "util.cpp"

/* -------------------------------------------------------------------------- */
/*                                  Blackjack   NOT                              */
/* -------------------------------------------------------------------------- */
void not_blackjack(blkjack::ControllerText* controllerText) {

	// Game Variables
	std::vector<int> player_hand;
	std::vector<int> dealer_hand;


	bool input_confirmed = false;
	bool input_canceled = false;
	ControllerButton confirmButton(ControllerDigital::A);
	ControllerButton cancelButton(ControllerDigital::B);

	// Game Loop
	while (true) {

		/* ----------------------------- Set Game State ----------------------------- */

		if (player_hand.size() >= 2) {

			if (input_confirmed)
			{
				player_hand.push_back(6);
			}

			if (input_canceled) {

				break;
			}

		}


		if (player_hand.size() == 0) {
			player_hand.push_back(9);
			player_hand.push_back(10);
		}
		if (dealer_hand.size() == 0) {
			dealer_hand.push_back(10);
			dealer_hand.push_back(8);
		}


		/* ------------------------------ Update Screen ----------------------------- */
		controllerText->update();
		pros::delay(25);
		controllerText->update();
		pros::delay(25);
		controllerText->update();
		pros::delay(25);


		/* -------------------------- Wait For Player Input ------------------------- */

		// clear previous inputs
		input_confirmed = false;
		input_canceled = false;


		// wait for new input
		while (true)
		{

			if (confirmButton.changedToReleased())
			{
				input_confirmed = true;
				break;
			}

			if (cancelButton.changedToReleased())
			{
				input_canceled = true;
				break;
			}

			pros::delay(25);
		}
	}

	/* ---------------------------- Determine Winner ---------------------------- */

	// sum player hand
	int psum = 0;
	for (int i = 0; i < player_hand.size(); i++)
	{
		psum += player_hand[i];
	}

	// sum dealer hand
	int dsum = 0;
	for (int i = 0; i < dealer_hand.size(); i++)
	{
		dsum += dealer_hand[i];
	}

	// if player || dealer bust
	if (psum > 21 || dsum > 21)
	{
		// if player && dealer bust
		if (psum > 21 && dsum > 21)
		{
			controllerText->setText(1, 0, 19, "You Tie. ", 0);
		}
		// if player
		else if (psum > 21)
		{
			// loss
			controllerText->setText(1, 0, 19, "You LOSE!! STUPID -_-", 0);
		}
		// if dealer
		else {
			controllerText->setText(1, 0, 19, "You Win!!", 0);
		}
	}


	// if player > dealer
	else if (psum > dsum) {
		controllerText->setText(1, 0, 19, "You Win!!", 0);
	}
	// if dealer > player
	else if (psum < dsum) {
		controllerText->setText(1, 0, 19, "You LOSE!! STUPID -_-", 0);
	}
	// else tie
	else {
		controllerText->setText(1, 0, 19, "You Tie. ", 0);
	}

	controllerText->update();
	pros::delay(25);
	controllerText->update();
	pros::delay(25);
	controllerText->update();
	pros::delay(25);

	while (true)
	{
		pros::delay(100);
	}

}