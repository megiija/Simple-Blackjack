#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <time.h>
#include "Deck.h"
#include <windows.h>
#include <stdlib.h> 
#include <vector>

using namespace std;
using std::vector;

int remaining = 51;
vector<Card>playerHand = {};
int playerSum;
vector<Card>computerHand = {};
int compSum;
bool notbust;
int playerAces;
int compAces;


void checkAce(vector<Card>& hand, int& aces) {
	Card c = hand.back();
	if (c.Rank == 11) {
		aces += 1;
	}
}

void deal(vector<Card>&arrCards, vector<Card>& hand, int& sum, int& aces){
	int random = 1 + (rand() % remaining);
	Card c = arrCards[random];
	hand.push_back(arrCards[random]);
	checkAce(hand, aces);
	arrCards.erase(arrCards.begin() + random);
	sum = sum + c.Rank;

	remaining = remaining - 1;
}

void displayCardLast(vector<Card>& hand) {
	Card c = hand.back();
	cout << "\n[" << c.faceName << " of " << c.suitName << "]";
}


void playerTurn(vector<Card>&arrCards, vector<Card>& hand, int& sum, int& aces) {
	bool in_play = true;
	while (in_play) {
		if (sum <= 21) {
			cout << "\n\nYour cards total is " << sum << "\n";
			int choice = 0;
			cout << "Choose your play. \n\nHit = 1	 Stand = 2 \n";
			cin >> choice;
			cin.ignore(256, '\n');
			if (choice == 1) {
				deal(arrCards, playerHand, playerSum, playerAces); Sleep(1000);
				displayCardLast(playerHand);
			}
			else if (choice == 2) {
				break;
			}
			else {
				std::cin.clear();
				std::cin.ignore(256, '\n');
			}
		}
		else {
			if(aces != 0) {
				aces -= 1;
				sum = sum - 10;
			}
			else if(sum > 21) {
				notbust = false;
				in_play = false;
			}
			
		}

	}
}

void compTurn(vector<Card>& arrCards, vector<Card>& hand, int& sum, int& aces) {
	bool in_play = true;
	while (in_play) {
		if (sum < 17) {
			deal(arrCards, computerHand, compSum, compAces);
			displayCardLast(hand); Sleep(1000);
		}
		else if (sum <= 21 and sum >= 17) {
			in_play = false;
		}
		else {
			if (aces != 0) {
				aces -= 1;
				sum = sum - 10;
			}
			else if (sum >= 17) {
				in_play = false;
			}

		}
	}
}

void reveal(vector<Card>& hand) {
	Card hiddenCard = hand.front();
	cout << "\nThe dealer's hand contains:\n"; Sleep(750);
	cout << "[" << hiddenCard.faceName << " of " << hiddenCard.suitName << "]"; Sleep(1000);
	displayCardLast(hand); Sleep(1000);
}

void checkScores(int playerSum, int compSum) {
	if (compSum > 21) {
		cout << "\n\nThe dealer bust. You win!\n";
	}
	else if (compSum > playerSum) {
		cout << "\n\nDealer wins with a hand of " << compSum << "!\n";
	}
	else if (compSum == playerSum) {
		cout << "\n\nDealer wins by bias!\n";
	}
	else {
		cout << "\n\nYou win!\n";
	}
}

int main() {

	//create random seed
//	LARGE_INTEGER cicles;
	//
//	QueryPerformanceCounter(&cicles);
//	srand(cicles.QuadPart);

	srand(time(NULL));


bool running = true;
while (running) {

	//clear variables
	int remaining = 51;
	playerHand.clear();
	::playerSum = 0;
	computerHand.clear();
	::compSum = 0;
	::notbust = true;
	::playerAces = 0;
	::compAces = 0;
	bool split = false;

	//setup deck
	Deck deck;
	DeckSetup(deck);

	vector<Card>arrCards(deck.arrCards, deck.arrCards + 52);

	//game begin
	cout << "\n  	BLACKJACK	\n\n";
	system("pause"); cout<<"\n";

	//inital deal
	// can be for looped
	cout << "You have been dealt:"; Sleep(750);
	deal(arrCards, playerHand, playerSum, playerAces); Sleep(1000);
	displayCardLast(playerHand);
	deal(arrCards, playerHand, playerSum, playerAces); Sleep(1000);
	displayCardLast(playerHand); Sleep(750);

	cout << "\n\nThe computer was dealt:"; Sleep(1000);
	deal(arrCards, computerHand, compSum, compAces); Sleep(1000);
	cout << "\n[Hidden Card]";
	deal(arrCards, computerHand, compSum, compAces); Sleep(1000);
	displayCardLast(computerHand); Sleep(750);

	//player turn begins
	playerTurn(arrCards, playerHand, playerSum, playerAces);
	if (notbust) {
		//computer plays
		reveal(computerHand);
		compTurn(arrCards, computerHand, compSum, compAces);

		//check who wins
		checkScores(playerSum, compSum);
	}
	else {
		cout << "\nYou have bust. Game over!\n";
	}

	//play again?
	cout << "\n Play again? (y/n): ";
	char answer;
	cin >> answer;
	cin.ignore(256, '\n');
	if (tolower(answer) != 'y') {
		running = false;
	}
	}
}