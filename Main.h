#pragma once
#include <string>
using namespace std;
int tictacToe();
int connect4();
int blackjack();

// New functions for user statistics
struct UserStats {
    int tictactoeGames;
    int connect4Games;
    int blackjackGames;
    double blackjackBalance;
};

bool updateGameStats(const string& username, const string& gameType, bool increment = true);
bool updateBlackjackBalance(const string& username, double amount);
bool getUserStats(const string& username, UserStats& stats);