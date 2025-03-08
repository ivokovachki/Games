#include <iostream>
#include "Main.h"
using namespace std;

int main() {

	int choice = 0;

	while (choice != 4) {

		cout << "MENU" << endl;
		cout << "1. Tic Tac Toe" << endl;
		cout << "2. Connect 4" << endl;
		cout << "3. Blackjack" << endl;
		cout << "4. Exit" << endl;

		cin >> choice;

		if (choice == 1) tictacToe();
		else if (choice == 2) connect4();
		else if (choice == 3) blackjack();
		else if (choice == 4) cout << "Goodbye!" << endl;
		else cout << "Invalid choice. Please try again." << endl;

	}

	return 0;
}
