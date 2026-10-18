#include <iostream>
#include <string>
#include <random>

void play_lucky7(int& chips)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(1, 6); //6-sided Dice

	std::cout << "Welcome to Lucky 7! Bet the outcome of two dice roll." << std::endl;
	std::cout << "\nPayouts:\nLower than 7 - 1:1\nExactly 7 - 4:1\nHigher than 7 - 1:1\n" << std::endl;

	char playAgain = 'y';
	while (playAgain == 'y')
	{
		std::cout << "Current Balance: " << chips << " chips." << std::endl;

		int chips_betted = 0;
		while (chips_betted < 1 || chips_betted > chips) //Makes sure you dont bet under 1 and over total chip amount
		{
			std::cout << "How many chips are you betting? ";
			std::string chips;
			std::getline(std::cin, chips);
			try
			{
				chips_betted = std::stoi(chips);
			}
			catch (...)
			{
				chips_betted = 0;
			}
		}

		int decision = 0;
		while (decision < 1 || decision > 3) //Ensures 1-3 is inputed
		{
			std::cout << "\nWhat is your decision?\n(1) - Lower\n(2) - Exactly\n(3) - Higher" << std::endl;
			std::string inputD;
			std::getline(std::cin, inputD);
			try
			{
				decision = std::stoi(inputD);
			}
			catch (...)
			{
				decision = 0;
			}
		}

		int die1 = distr(gen); //Die 1 roll
		int die2 = distr(gen); //Die 2 roll
		int total = die1 + die2;

		std::cout << "\nDice 1 roll: " << die1 << std::endl;
		std::cout << "Dice 2 roll: " << die2 << std::endl;
		std::cout << "Total: " << total << std::endl;
		std::cout << std::endl;

		if (total < 7 && decision == 1)
		{
			std::cout << "Congratulations! You won " << chips_betted << " chips!" << std::endl;
			chips += chips_betted;
		}
		else if (total == 7 && decision == 2)
		{
			std::cout << "Congratulations! You won " << (chips_betted * 4) << " chips!" << std::endl;
			chips += (chips_betted * 4);
		}
		else if (total > 7 && decision == 3)
		{
			std::cout << "Congratulations! You won " << chips_betted << " chips!" << std::endl;
			chips += chips_betted;
		}
		else
		{
			std::cout << "Wrong! You lost all of your betted chips." << std::endl;
			chips -= chips_betted;
		}

		if (chips <= 0)
		{
			std::cout << "You ran all out of chips!" << std::endl;
			return;
		}

		std::string replayInput;
		while (true)
		{
			std::cout << "\nKeep Playing? (Y/N): ";
			std::getline(std::cin, replayInput);

			if (!replayInput.empty())
			{
				char choice = std::tolower(replayInput[0]); //case insensitive
				if (choice == 'y' || choice == 'n')
				{
					playAgain = choice;
					break;
				}
			}
			std::cout << "Invalid choice, Please enter 'Y' or 'N'." << std::endl;
		}

		if (playAgain == 'n')
		{
			std::cout << "Thanks for playing Lucky 7!" << std::endl;\
				return; //Go to main menu
		}
	}
}

int main()
{
	int player_chips = 1000;
	std::cout << "Welcome to the casino! Choose what game to play:" << std::endl;

	int decision = 0;
	while (decision < 1 || decision > 5) //Ensures 1-5 is inputed
	{
		std::cout << "(1) - Blackjack\n(2) - Roulette\n(3) - Lucky 7\n(4) - Check Stats\n(5) - Quit" << std::endl;
		std::string inputD;
		std::getline(std::cin, inputD);
		try
		{
			decision = std::stoi(inputD);
		}
		catch (...)
		{
			decision = 0;
		}

		if (decision == 1)
		{
			//Blackjack function
			decision = 0;
		}

		else if (decision == 2)
		{
			//Roulette function
			decision = 0;
		}

		else if (decision == 3)
		{
			play_lucky7(player_chips);
			decision = 0;
		}

		else if (decision == 4)
		{
			//Check stats function
			decision = 0;
		}
		else
		{
			return 0;
		}
	}
	return 0;
}