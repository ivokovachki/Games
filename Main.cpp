#include <iostream>
#include "Main.h"
using namespace std;

int main() {

	int choice = 0;

	while (choice != 3) {

		cout << "MENU" << endl;
		cout << "1. Tic Tac Toe" << endl;
		cout << "2. Connect 4" << endl;
		cout << "3. Exit" << endl;

		cin >> choice;

		if (choice == 1) tictacToe();
		else if (choice == 2) connect4();
		else if (choice == 3) cout << "Goodbye!" << endl;
		else cout << "Invalid choice. Please try again." << endl;

	}

	return 0;
}
