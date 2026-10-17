#include <iostream>
#include <string>

int main()
{
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
	}


	return 0;
}