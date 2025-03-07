#include <iostream>
#include "Main.h"
#include <string>
using namespace std;

void printTable(char table[3][3]) {
    for (int i = 0; i < 3; i++) {
        cout << "-------------" << endl;
        for (int j = 0; j < 3; j++) {
            cout << "| " << table[i][j] << " ";
        }
        cout << "|" << endl;
    }
    cout << "-------------" << endl;
}

int checkWinner(char table[3][3]) {
    for (int i = 0; i < 3; i++) {

        if (table[i][0] == table[i][1] && table[i][1] == table[i][2] && table[i][0] != ' ') {
            cout << "Player " << table[i][0] << " wins!" << endl;
            return 1;//row check
        }

        if (table[0][i] == table[1][i] && table[1][i] == table[2][i] && table[0][i] != ' ') {
            cout << "Player " << table[0][i] << " wins!" << endl;
            return 1;//column check
        }
    }

    if (table[0][0] == table[1][1] && table[1][1] == table[2][2] && table[0][0] != ' ') {
        cout << "Player " << table[0][0] << " wins!" << endl;
        return 1;//diagonal check
    }
    if (table[0][2] == table[1][1] && table[1][1] == table[2][0] && table[0][2] != ' ') {
        cout << "Player " << table[0][2] << " wins!" << endl;
        return 1;//diagonal check
    }
    return 0;
}

int turns(char table[3][3], bool& player) {
    int x = 0;
    int y = 0;

    string input;

    cout << "Player 1 is X and Player 2 is O" << endl;

    if (player) {
        cout << "Player 1, enter the cell you want to fill: ";
    }
    else {
        cout << "Player 2, enter the cell you want to fill: ";
    }
    //cin >> y >> x;

    cin >> input;
    if (input == "top") {


        cin >> input;
        if (input == "left") {
            cout << "You chose the top left cell" << endl;
            x = 0;
            y = 0;
        }
        else if (input == "middle") {
            cout << "You chose the top middle cell" << endl;
            x = 0;
            y = 1;
            input = "";
        }
        else if (input == "right") {
            cout << "You chose the top right cell" << endl;
            x = 0;
            y = 2;
        }
        else {
            cout << "Invalid input. Please try again." << endl;
            return turns(table, player);
        }

    }
    else if (input == "middle") {

        cin >> input;
        if (input == "left") {
            cout << "You chose the top left cell" << endl;
            x = 1;
            y = 0;
        }
        else if (input == "middle") {
            cout << "You chose the top middle cell" << endl;
            x = 1;
            y = 1;
        }
        else if (input == "right") {
            cout << "You chose the top right cell" << endl;
            x = 1;
            y = 2;
        }
        else {
            cout << "Invalid input. Please try again." << endl;
            return turns(table, player);
        }

    }
    else if (input == "bottom") {
        cin >> input;
        if (input == "left") {
            cout << "You chose the top left cell" << endl;
            x = 2;
            y = 0;
        }
        else if (input == "middle") {
            cout << "You chose the top middle cell" << endl;
            x = 2;
            y = 1;
        }
        else if (input == "right") {
            cout << "You chose the top right cell" << endl;
            x = 2;
            y = 2;
        }
        else {
            cout << "Invalid input. Please try again." << endl;
            return turns(table, player);
        }
    }
    else if (input == "exit") {
        cout << "Goodbye!" << endl;
        return 0;
    }
    else {

        cout << "Invalid input. Please try again." << endl;
        return turns(table, player);

    }



    if (table[x][y] == 'X' || table[x][y] == 'O') {
        cout << "This cell is already filled. Please choose another one." << endl;
        return turns(table, player);  // retry
    }
    else {
        table[x][y] = (player ? 'X' : 'O');
        player = !player;
        return 1;
    }
}

int tictacToe() {
    char table[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    short count = 0;
    bool player = true;
    char playAgain;

    cout << "Welcome to Tic Tac Toe!" << endl;
    cout << "Type 'top' for the top row, 'middle' for the middle row, and 'bottom' for the bottom row." << endl;
    cout << "Type 'left' for the left column, 'middle' for the middle column, and 'right' for the right column." << endl;
    cout << "For example, type 'top left' to place your piece in the top left cell." << endl;
    cout << "To exit type 'exit'." << endl;

    printTable(table);

    do {
        while (count < 9) {

            if (!turns(table, player)) break;
            count++;
            printTable(table);
            if (checkWinner(table)) {

                break;
            }
            else if (count == 9) {
                cout << "It's a draw!" << endl;
            }
        }

        cout << "Play again? (y/n): ";
        cin >> playAgain;

        if (playAgain == 'y') {
            count = 0;
            player = true;

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    table[i][j] = ' ';
                }
            }
            printTable(table);
        }
        else {
            cout << "Goodbye!" << endl;
        }
    } while (playAgain == 'y');

    return 0;
}
