#include <iostream>
#include <stdlib.h>


enum class Suits {
	SPADES,
	CLUBS,
	HEARTS,
	DIAMONDS,
};

enum class FaceValue {
	ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN,
	EIGHT, NINE, TEN, JACK, QUEEN, KING,
};

struct Card {
	Suits suit;
	FaceValue face;
	std::string suitName;
	std::string faceName;
	int Rank;
};

struct Deck {
	Card arrCards[52];
};

void DeckSetup(Deck& deck) {
	for (int i = (int)Suits::SPADES; i <= (int)Suits::DIAMONDS; i++) {
		for (int k = (int)FaceValue::ACE; k <= (int)FaceValue::KING; k++) {
			Card c;
			c.suit = (Suits)i;
			c.face = (FaceValue)k;

			if (c.face == FaceValue::JACK) {
				c.Rank = 10;
				c.faceName = "Jack";
			}
			else if (c.face == FaceValue::QUEEN) {
				c.Rank = 10;
				c.faceName = "Queen";
			}
			else if (c.face == FaceValue::KING) {
				c.Rank = 10;
				c.faceName = "King";
			}
			else if (c.face == FaceValue::ACE) {
				c.faceName = "Ace";
				c.Rank = 11;
			}
			else {
				c.Rank = (int)c.face;
				c.faceName = std::to_string((int)c.face);
			}

			if (c.suit == Suits::CLUBS) {
				c.suitName = "Clubs";
			}
			else if (c.suit == Suits::SPADES) {
				c.suitName = "Spades";
			}
			else if (c.suit == Suits::DIAMONDS) {
				c.suitName = "Diamonds";
			}
			else if (c.suit == Suits::HEARTS) {
				c.suitName = "Hearts";
			}
			int index = (13 * i) + k - 1;
			deck.arrCards[index] = c;
		}
	}
}

void PrintDeck(const Deck& deck) {
	for (Card c : deck.arrCards) {
		std::cout << (int)c.face << " of " << (int)c.suit << std::endl;
	}
}
