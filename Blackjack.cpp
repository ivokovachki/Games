#include <unordered_map>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

struct Card {

	int value;
	string suit;
	string name;
	Card() : value(0), suit(""), name("") {}
};

int initDeckOfCards(vector<Card>& deckOfCards) {
	// Initialize the deck of cards
	deckOfCards.clear();

	unordered_map<int, string> NameCards = {

	{  2, "Two" },
	{ 3, "Three" },
	{ 4, "Four" },
	{ 5, "Five" },
	{ 6, "Six" },
	{ 7, "Seven" },
	{ 8, "Eight" },
	{ 9, "Nine" },
	{ 10, "Ten" },
	{ 11, "Jack" },
	{ 12, "Queen" },
	{ 13, "King" },
	{ 14, "Ace" },

	};

	string suits[] = { "Hearts", "Diamonds", "Clubs", "Spades" };

	for (int i = 0; i < 4; i++) {
		for (int j = 2; j <= 14; j++) {
			Card card;
			card.value = (j > 10) ? ((j == 14) ? 11 : 10) : j;
			card.suit = suits[i];
			card.name = NameCards[j];
			deckOfCards.push_back(card);

		}
	}

	return 0;
}

void drawACard(vector<Card>& deckOfCards, vector<Card>& hand) {

	// Draw a card from the deck and add it to the hand
	unordered_map<int, string> valueMap;
	int index = rand() % deckOfCards.size();
	hand.push_back(deckOfCards[index]);
	deckOfCards.erase(deckOfCards.begin() + index);

}

void printCard(Card card) {

	cout << "- " + card.name << " of " << card.suit << endl;

}

int play() {
	unordered_map<int, string> valueMap;

	vector<Card> playerhand;
	vector<Card> dealerhand;
	vector<Card> deckOfCards;
	playerhand.clear();
	dealerhand.clear();
	initDeckOfCards(deckOfCards);
	srand(time(0));

	struct Score {
		int score;
		Score() : score(0) {}
	};

	Score playerScore;
	Score dealerScore;

	cout << endl;
	cout << "Welcome to BlackJack!" << endl;
	cout << endl;
	cout << "Dealing Cards..." << endl;
	cout << endl;

	drawACard(deckOfCards, playerhand);
	playerScore.score += playerhand[0].value;

	drawACard(deckOfCards, dealerhand);
	dealerScore.score += dealerhand[0].value;

	drawACard(deckOfCards, playerhand);
	playerScore.score += playerhand[1].value;

	if (playerScore.score == 21)
	{
		cout << "Your Hand: " << endl;
		printCard(playerhand[0]);
		printCard(playerhand[1]);

		cout << "BlackJack!" << endl;
		
		drawACard(deckOfCards, dealerhand);
		dealerScore.score += dealerhand[1].value;

		while (dealerScore.score < 17) {
			drawACard(deckOfCards, dealerhand);
			dealerScore.score += dealerhand[dealerhand.size() - 1].value;
			for (int i = 0; i < dealerhand.size(); i++)
			{
				if (dealerScore.score > 21 && dealerhand[i].value == 11)
				{
					dealerScore.score -= 10;
				}
			}
		}
		cout << "Dealer's Hand: " << endl;
		for (int i = 0; i < dealerhand.size(); i++) {
			printCard(dealerhand[i]);
		}
		cout << "Dealer's score: " << dealerScore.score << endl;
		cout << endl;
		if (dealerScore.score == 21)
		{
			cout << "Dealer has BlackJack too! It's a tie!" << endl;

			return 2;
		}
		else if (dealerScore.score < 21)
		{
			cout << "You win!" << endl;
			return 1;
		}
		else if (dealerScore.score > 21)
		{
			cout << "Dealer busts! You win!" << endl;
			return 1;
		}
	}
	else if (playerScore.score > 21) {
		playerScore.score -= 10;
	}

	drawACard(deckOfCards, dealerhand);

	cout << "Your Hand: " << endl;
	printCard(playerhand[0]);
	printCard(playerhand[1]);

	cout << "Your score: " << playerScore.score << endl;
	cout << endl;
	cout << "Dealer's Hand: " << endl;
	printCard(dealerhand[0]);
	cout << "Unknown Card" << endl;
	cout << endl;

	while (true) {

		cout << "Enter 'hit' to take another card or 'stand' to keep your current hand or 'exit' to exit the game: ";

		string choice = "";
		cin >> choice;
		cout << endl;
		if (choice == "hit" || choice == "Hit")
		{
			drawACard(deckOfCards, playerhand);
			playerScore.score += playerhand[playerhand.size() - 1].value;

			for (int i = 0; i < playerhand.size(); i++)
			{
				if (playerScore.score > 21 && playerhand[i].value == 11)
				{
					playerhand[i].value = 1;
					playerScore.score -= 10;
				}
			}

			cout << "Your Hand: " << endl;
			for (int i = 0; i < playerhand.size(); i++) {
				printCard(playerhand[i]);
			}
			cout << "Your score: " << playerScore.score << endl;
			cout << endl;
			if (playerScore.score == 21)
			{
				cout << "BlackJack!" << endl;

				dealerScore.score += dealerhand[1].value;

				while (dealerScore.score < 17) {
					drawACard(deckOfCards, dealerhand);
					dealerScore.score += dealerhand[dealerhand.size() - 1].value;
					for (int i = 0; i < dealerhand.size(); i++)
					{
						if (dealerScore.score > 21 && dealerhand[i].value == 11)
						{
							dealerhand[i].value = 1;
							dealerScore.score -= 10;
						}
					}
				}
				cout << endl;
				cout << "Dealer's Hand: " << endl;
				for (int i = 0; i < dealerhand.size(); i++) {
					printCard(dealerhand[i]);
				}
				cout << "Dealer's score: " << dealerScore.score << endl;
				cout << endl;
				if (dealerScore.score == 21)
				{
					cout << "Dealer has BlackJack too! It's a tie!" << endl;

					return 2;
				}
				else if (dealerScore.score < 21)
				{
					cout << "You win!" << endl;
					return 1;
				}
				else if (dealerScore.score > 21)
				{
					cout << "Dealer busts! You win!" << endl;
					return 1;
				}
			}
			else if (playerScore.score > 21)
			{
				cout << "Bust! You lose." << endl;
				return 0;
			}

			cout << "Dealer's Hand: " << endl;
			printCard(dealerhand[0]);
			cout << "- Unknown Card" << endl;
		}
		else if (choice == "stand" || choice == "Stand")
		{
			dealerScore.score += dealerhand[1].value;

			cout << "Your Hand: " << endl;
			for (int i = 0; i < playerhand.size(); i++) {
				printCard(playerhand[i]);
			}
			cout << "Your score: " << playerScore.score << endl;

			while (dealerScore.score < 17) {
				drawACard(deckOfCards, dealerhand);
				dealerScore.score += dealerhand[dealerhand.size() - 1].value;
				for (int i = 0; i < dealerhand.size(); i++)
				{
					if (dealerScore.score > 21 && dealerhand[i].value == 11)
					{
						dealerhand[i].value = 1;
						dealerScore.score -= 10;
					}
				}
			}
			cout << "Dealer's Hand: " << endl;
			for (int i = 0; i < dealerhand.size(); i++) {
				printCard(dealerhand[i]);
			}
			cout << "Dealer's score: " << dealerScore.score << endl;


			if (dealerScore.score == 21)
			{
				cout << "Dealer has BlackJack! You lose!" << endl;
				return 0;
			}
			else if (dealerScore.score > 21)
			{
				cout << "Dealer busts! You win!" << endl;
				return 1;
			}
			else if (dealerScore.score > playerScore.score)
			{
				cout << "Dealer wins!" << endl;
				return 0;
			}
			else if (dealerScore.score < playerScore.score)
			{
				cout << "You win!" << endl;
				return 1;
			}
			else if (dealerScore.score == playerScore.score)
			{
				cout << "It's a tie!" << endl;
				return 2;


			}
		}
		else if (choice == "exit") {
			return 0;
		}
		else {
			cout << "Invalid choice. Please try again." << endl;
		}
	}
}

int blackjack() {
	char playAgain = ' ';
	do {
		play();
		cout << "Do you want to play again? (y/n) ";
		cin >> playAgain;
	} while (playAgain == 'Y' || playAgain == 'y');
	return 0;
}
