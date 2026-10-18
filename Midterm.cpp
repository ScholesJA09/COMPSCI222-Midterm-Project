#include <iostream>
using namespace std;

void blackjackMenu(int& chips);


int main()
{
	int chips = 1000;

	cout << "==== BLACKJACK TEST ====\n";
	cout << "Starting Chips: " << chips << endl;

	blackjackMenu(chips);

	cout << "\n==== TEST COMPLETE ====\n";
	cout << "Final Chip Count: " << chips << endl;

	return 0;
}