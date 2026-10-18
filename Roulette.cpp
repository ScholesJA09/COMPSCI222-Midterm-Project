#include <iostream>
#include <string>

void play_roulette(int* chips) {
	srand(time(0));
	std::cout << "Welcome to the roulette table!" << std::endl;
	while (true) {
		int bet_amount = -1;
		while (bet_amount < 1) {
			std::cout << "You have " << *chips << " chips, how many would you like to bet? (type 'cancel' to exit)" << std::endl;
			std::string temp;
			std::getline(std::cin, temp);
			if (temp == "cancel") {
				return;
			}
			try {
				bet_amount = std::stoi(temp);
			}
			catch (std::exception& e) {
				std::cout << "Invalid input! (If you were trying to exit, make sure you type 'cancel' in all lowercase)" << std::endl;
			}
			if (bet_amount < 1 || bet_amount > *chips) {
				std::cout << "Please bet an amount that you have. (Between 1 and " << *chips << ")" << std::endl;
			}
		}
		int bet_type = -1;
		std::cout << "Wager types:\nAny number 1-36 = 30x multiplier\nEven or Odd = 2x multiplier" << std::endl;
		while (bet_type < 0) {
			std::cout << "What would you like to bet on?\t";
			std::string temp;
			std::getline(std::cin, temp);
			if (temp == "Odd" || temp == "odd") {
				bet_type = 37;
			}
			else if (temp == "Even" || temp == "even") {
				bet_type = 38;
			}
			else {
				try {
					bet_type = std::stoi(temp);
					if (bet_type > 36 || bet_type < 1) {
						bet_type = -1;
						throw std::exception();
					}
				}
				catch (std::exception& e) {
					std::cout << "Invalid input! (Input odd, even, or a number from 1 to 36)" << std::endl;
				}
			}
		}
		std::cout << "Rolling..." << std::endl;
		int roll_num = (rand() % 36) + 1;
		std::cout << "The wheel rolled " << roll_num << "..." << std::endl;
		if (bet_type == 37 && (roll_num % 2) == 1) {
			bet_amount *= 2;
			std::cout << "It was odd! You win " << bet_amount << " chips!" << std::endl;
			*chips += bet_amount;
		}
		else if (bet_type == 38 && (roll_num % 2) == 0) {
			bet_amount *= 2;
			std::cout << "It was even! You win " << bet_amount << " chips!" << std::endl;
			*chips += bet_amount;
		}
		else if (bet_type == roll_num) {
			bet_amount *= 30;
			std::cout << "You guessed " << roll_num << "! You win " << bet_amount << " chips!" << std::endl;
			*chips += bet_amount;
		}
		else {
			std::cout << "You lost " << bet_amount << " chips..." << std::endl;
			*chips -= bet_amount;
		}
		if (*chips == 0) {
			std::cout << "You're out of chips, come back when you're a little bit more... richer." << std::endl;
			return;
		}
		std::string temp = "N/A";
		while (temp != "Y" && temp != "y" && temp != "Yes" && temp != "yes") {
			std::cout << "Would you like to play again?\t";
			std::getline(std::cin, temp);
			if (temp == "N" || temp == "n" || temp == "No" || temp == "no") {
				return;
			}
			else if (temp != "Y" && temp != "y" && temp != "Yes" && temp != "yes") {
				std::cout << "Invalid input! Please try again." << std::endl;
			}
		}
	}
}