#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <algorithm>
#include <limits>
#include <cstdlib>
using namespace std;

int player_chips = 1000;
int highest_player_chips = 0;
int current_rounds_won = 0;
int most_rounds_won = 0;
int biggest_win = 0;

struct Card
{
	string rank;
	string suit;
	int value;
};

vector<Card> createDeck()
{
	vector<Card> deck;

	string suits[] = { "Hearts", "Diamonds", "Clubs", "Spades" };
	string ranks[] = {
		"2", "3", "4", "5", "6", "7", "8", "9", "10",
		"Jack", "Queen", "King", "Ace"
	};

	for (string suit : suits)
	{
		for (string rank : ranks)
		{
			Card card;

			card.suit = suit;
			card.rank = rank;

			if (rank == "Jack" || rank == "Queen" || rank == "King")
			{
				card.value = 10;
			}
			else if (rank == "Ace")
			{
				card.value = 11;
			}
			else
			{
				card.value = stoi(rank);
			}

			deck.push_back(card);
		}
	}

	return deck;
}

void round_won(int& current, int& most)
{
	current++;
	if (current > most)
	{
		most = current;
	}
}

void round_lost(int& current)
{
	current = 0;
}

int highest_chip_peak(int& chips, int highest_chips)
{
	if (chips > highest_chips)
	{
		return chips;
	}
	return highest_chips;
}

int biggest_amount_won(int& chips_won, int& biggest)
{
	if (chips_won > biggest)
	{
		biggest = chips_won;
		return chips_won;
	}
	return biggest;
}

void shuffleDeck(vector<Card>& deck)
{
	random_device rd;
	mt19937 generator(rd());

	shuffle(deck.begin(), deck.end(), generator);
}

int calculateHandValue(vector<Card> hand)
{
	int total = 0;
	int aceCount = 0;

	for (Card card : hand)
	{
		total += card.value;

		if (card.rank == "Ace")
		{
			aceCount++;
		}
	}

	while (total > 21 && aceCount > 0)
	{
		total -= 10;
		aceCount--;
	}

	return total;
}

bool isBlackjack(vector<Card> hand)
{
	return hand.size() == 2 && calculateHandValue(hand) == 21;
}

void displayHand(vector<Card> hand)
{
	for (Card card : hand)
	{
		cout << card.rank << " of " << card.suit << endl;
	}

	cout << "Total Value: " << calculateHandValue(hand) << endl;
}

Card dealCard(vector<Card>& deck)
{
	Card card = deck.back();

	deck.pop_back();

	return card;
}

void displayDealerHand(vector<Card> hand, bool hideCard)
{
	cout << "\nDealer's Hand:\n";

	for (int i = 0; i < hand.size(); i++)
	{
		if (i == 1 && hideCard)
		{
			cout << "[Hidden Card]" << endl;
		}
		else
		{
			cout << hand[i].rank << " of "
				<< hand[i].suit << endl;
		}
	}

	if (!hideCard)
	{
		cout << "Total Value: "
			<< calculateHandValue(hand) << endl;
	}
}

void playBlackjack(int& chips)
{
	int bet;

	cout << "\n==== PLACE BET ====\n";
	cout << "Available chips: " << chips << endl;

	while (true)
	{
		cout << "Enter your bet: ";

		if (!(cin >> bet))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "invalid input.  Enter a number.\n";
			continue;
		}

		if (bet <= 0)
		{
			cout << "You cannot bet 0\n";
		}

		else if (bet > chips)
		{
			cout << "You dont have enough chips to bet\n";
		}

		else
		{
			break;
		}
	}

	chips -= bet;

	cout << "\nYou bet " << bet << " chips.\n";
	cout << "Remaining Chips: " << chips << endl;

	vector<Card> deck = createDeck();
	shuffleDeck(deck);

	vector<Card> playerHand;
	vector<Card> dealerHand;

	// Deal two cards to each player
	playerHand.push_back(dealCard(deck));
	dealerHand.push_back(dealCard(deck));

	playerHand.push_back(dealCard(deck));
	dealerHand.push_back(dealCard(deck));

	cout << "\n===== BLACKJACK =====\n";

	cout << "\nYour Hand:\n";
	displayHand(playerHand);

	displayDealerHand(dealerHand, true);

	// Check for a natural Blackjack
	bool playerBlackjack = isBlackjack(playerHand);
	bool dealerBlackjack = isBlackjack(dealerHand);

	if (playerBlackjack || dealerBlackjack)
	{
		cout << "\n==== BLACKJACK ====\n";

		displayDealerHand(dealerHand, false);

		if (playerBlackjack && dealerBlackjack)
		{
			cout << "Both have Blackjack! its a push.\n";
			chips += bet;
		}

		else if (playerBlackjack)
		{
			cout << "Natural Blackjack! you win!\n";
			chips += bet + (bet * 3 / 2);
			round_won(current_rounds_won, most_rounds_won);
			biggest_win = biggest_amount_won(bet, biggest_win);
		}

		else
		{
			cout << "Dealer has Blackjack! you lose.\n";
			round_lost(current_rounds_won);
		}

		cout << "\nCurrent Chips: " << chips << endl;

		highest_player_chips = highest_chip_peak(player_chips, highest_player_chips);

		return;
	}

	//player turn
	bool playerTurn = true;

	while (playerTurn)
	{
		int choice;

		cout << "\n1. Hit";
		cout << "\n2. Stand";

		if (playerHand.size() == 2 && chips >= bet)
		{
			cout << "\n3. Double Down";
		}

		cout << "\nEnter your choice: ";

		if (!(cin >> choice))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input.  Try again.\n";
			continue;
		}

		if (choice == 1)
		{
			playerHand.push_back(dealCard(deck));

			cout << "\nYour Hand:\n";
			displayHand(playerHand);

			if (calculateHandValue(playerHand) > 21)
			{
				cout << "\nYou busted! You lose.\n";

				round_lost(current_rounds_won);
				highest_player_chips = highest_chip_peak(player_chips, highest_player_chips);

				playerTurn = false;
			}
		}


		else if (choice == 2)
		{
			cout << "\nYou chose to stand.\n";
			playerTurn = false;
		}

		else if (choice == 3 && playerHand.size() == 2 && chips >= bet)
		{
			chips -= bet;
			bet *= 2;

			cout << "\nYou doubled down!\n";
			cout << "Total Bet: " << bet << endl;

			playerHand.push_back(dealCard(deck));

			cout << "\nYour Hand:\n";
			displayHand(playerHand);

			if (calculateHandValue(playerHand) > 21)
			{
				cout << "You Busted!\n";
				round_lost(current_rounds_won);
				highest_player_chips = highest_chip_peak(player_chips, highest_player_chips);
			}

			playerTurn = false;
		}

		else
		{
			cout << "\nInvalid choice.  Try again.\n";
		}

	}

	// Dealers turn
	if (calculateHandValue(playerHand) <= 21)
	{
		cout << "\n==== DEALER'S TURN ====\n";

		displayDealerHand(dealerHand, false);

		while (calculateHandValue(dealerHand) < 17)
		{
			cout << "\nDealer hits!\n";

			dealerHand.push_back(dealCard(deck));

			displayDealerHand(dealerHand, false);
		}

		if (calculateHandValue(dealerHand) > 21)
		{
			cout << "\nDealer busted! you win!\n";
			round_won(current_rounds_won, most_rounds_won);
			biggest_win = biggest_amount_won(bet, biggest_win);
		}

		else
		{
			cout << "\nDealer stands with "
				<< calculateHandValue(dealerHand)
				<< ".\n";
		}
	}

	// Determine the winner
	int playerTotal = calculateHandValue(playerHand);
	int dealerTotal = calculateHandValue(dealerHand);

	cout << "\n==== ROUND RESULT ====\n";

	cout << "Your total: " << playerTotal << endl;
	cout << "Dealer total: " << dealerTotal << endl;

	if (playerTotal > 21)
	{
		cout << "You busted! Dealer wins!\n";
		round_lost(current_rounds_won);
	}

	else if (dealerTotal > 21)
	{
		cout << "Dealer busted! You win!\n";
		chips += bet * 2;
		round_won(current_rounds_won, most_rounds_won);
		biggest_win = biggest_amount_won(bet, biggest_win);
	}

	else if (dealerTotal > playerTotal)
	{
		cout << "Dealer wins!\n";
		round_lost(current_rounds_won);

	}

	else if (playerTotal > dealerTotal)
	{
		cout << "You win!\n";
		chips += bet * 2;
		round_won(current_rounds_won, most_rounds_won);
		biggest_win = biggest_amount_won(bet, biggest_win);
	}

	else
	{
		cout << "You both push.\n";
		chips += bet;
	}
	highest_player_chips = highest_chip_peak(player_chips, highest_player_chips);
	cout << "\nCurrent Chips: " << chips << endl;
}

void blackjackMenu(int& chips)
{
	int choice;

	while (chips > 0)
	{
		cout << "\n==== BLACKJACK MENU ====\n";
		cout << "Current Chips: " << chips << endl;

		cout << "\n1. Play Blackjack";
		cout << "\n2. Return to Casino";
		cout << "\nEnter your choice: ";

		if (!(cin >> choice))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "Invalid input.  Try again.\n";
			continue;
		}

		if (choice == 1)
		{
			playBlackjack(chips);
		}

		else if (choice == 2)
		{
			cout << "\nReturning to Casino...\n";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return;
		}

		else
		{
			cout << "Invalid choice.  Try again\n";
		}
	}

	cout << "\nYou ran out of chips!\n";
}

void play_roulette(int& chips) {
	srand(time(0));
	std::cout << "Welcome to the roulette table!" << std::endl;
	while (true) {
		int bet_amount = -1;
		while (bet_amount < 1) {
			std::cout << "You have " << chips << " chips, how many would you like to bet? (type 'cancel' to exit)" << std::endl;
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
			if (bet_amount < 1 || bet_amount > chips) {
				std::cout << "Please bet an amount that you have. (Between 1 and " << chips << ")" << std::endl;
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
			chips += bet_amount;
			round_won(current_rounds_won, most_rounds_won);
			biggest_win = biggest_amount_won(bet_amount, biggest_win);
		}
		else if (bet_type == 38 && (roll_num % 2) == 0) {
			bet_amount *= 2;
			std::cout << "It was even! You win " << bet_amount << " chips!" << std::endl;
			chips += bet_amount;
			round_won(current_rounds_won, most_rounds_won);
			biggest_win = biggest_amount_won(bet_amount, biggest_win);
		}
		else if (bet_type == roll_num) {
			bet_amount *= 30;
			std::cout << "You guessed " << roll_num << "! You win " << bet_amount << " chips!" << std::endl;
			chips += bet_amount;
			round_won(current_rounds_won, most_rounds_won);
			biggest_win = biggest_amount_won(bet_amount, biggest_win);
		}
		else {
			std::cout << "You lost " << bet_amount << " chips..." << std::endl;
			chips -= bet_amount;
			round_lost(current_rounds_won);
		}

		highest_player_chips = highest_chip_peak(player_chips, highest_player_chips);

		if (chips == 0) {
			std::cout << "You're out of chips, come back when you have more chips!" << std::endl;
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
			round_won(current_rounds_won, most_rounds_won);
			biggest_win = biggest_amount_won(chips_betted, biggest_win);
		}
		else if (total == 7 && decision == 2)
		{
			std::cout << "Congratulations! You won " << (chips_betted * 4) << " chips!" << std::endl;
			chips += (chips_betted * 4);
			round_won(current_rounds_won, most_rounds_won);
			chips_betted = chips_betted * 4;
			biggest_win = biggest_amount_won(chips_betted, biggest_win);
		}
		else if (total > 7 && decision == 3)
		{
			std::cout << "Congratulations! You won " << chips_betted << " chips!" << std::endl;
			chips += chips_betted;
			round_won(current_rounds_won, most_rounds_won);
			biggest_win = biggest_amount_won(chips_betted, biggest_win);
		}
		else
		{
			std::cout << "Wrong! You lost all of your betted chips." << std::endl;
			chips -= chips_betted;
			round_lost(current_rounds_won);
		}

		highest_player_chips = highest_chip_peak(player_chips, highest_player_chips);

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

void check_stats(int highest_chips, int most_rounds, int most_won)
{
	std::cout << "\nStats:" << std::endl;
	std::cout << "Highest chip peak: " << highest_chips << std::endl;
	std::cout << "Most rounds won in a row: " << most_rounds << std::endl;
	std::cout << "Biggest single win: $" << most_won << "\n" <<  std::endl;
}

int main()
{
	std::cout << "Welcome to the casino! Choose what game to play:" << std::endl;

	while (true)
	{
		std::cout << "(1) - Blackjack\n(2) - Roulette\n(3) - Lucky 7\n(4) - Check Stats\n(5) - Quit" << std::endl;
		std::string inputD;
		std::getline(std::cin, inputD);

		int decision;
		highest_player_chips = highest_chip_peak(player_chips, highest_player_chips);

		try
		{
			decision = std::stoi(inputD);
		}
		catch (...)
		{
			std::cout << "Invalid input." << std::endl;
			decision = 0;
		}

		if (decision == 1)
		{
			blackjackMenu(player_chips);
		}

		else if (decision == 2)
		{
			play_roulette(player_chips);
		}

		else if (decision == 3)
		{
			play_lucky7(player_chips);
		}

		else if (decision == 4)
		{
			check_stats(highest_player_chips, most_rounds_won, biggest_win);
		}
		else if (decision == 5)
		{
			std::cout << "Thanks for visiting the casino!" << std::endl;
			return 0;
		}
		else
		{
			std::cout << "Invalid choice, try again." << std::endl;
		}
	}
}