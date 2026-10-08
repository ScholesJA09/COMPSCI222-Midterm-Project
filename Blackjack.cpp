#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

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