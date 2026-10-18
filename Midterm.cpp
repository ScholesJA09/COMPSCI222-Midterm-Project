#include <iostream>
#include <string>

void play_roulette(int* chips);

int main() {
	int player_chips = 500;

	play_roulette(&player_chips);

	return 0;
}