# C++ Game Collection

## Overview
This application is a collection of classic games including Tic Tac Toe, Connect 4, and Blackjack. It features a user authentication system with registration and login capabilities, tracks game statistics for each user, and stores this information in an SQLite database.

## Key Features

### User Management
- **Account Creation**: Users can register with a username and password
- **Secure Authentication**: Passwords are securely hashed using SHA-256 with salt
- **User Profiles**: Individual statistics tracked for each user

### Games
1. **Tic Tac Toe**
   - Classic two-player game on a 3x3 grid
   - Play against the computer
   - Tracks number of games played

2. **Connect 4**
   - Traditional vertical grid game
   - Players take turns dropping colored discs
   - Tracks number of games played

3. **Blackjack**
   - Complete card game implementation with dealer logic
   - Features traditional rules including:
     - Hit/Stand options
     - Dealer stands on 17
     - Blackjack detection
   - Virtual betting system with persistent balance
   - Ability to play multiple rounds in a session

### Statistics Tracking
- Number of Tic Tac Toe games played
- Number of Connect 4 games played
- Number of Blackjack games played
- Persistent Blackjack balance

## Technical Implementation
- Built with C++14
- Data persistence using SQLite database
- Password security using OpenSSL for hashing
- Command-line interface with intuitive navigation
- Modular design with separate files for each game

## How to Use
1. Start the application
2. Register a new account or log in with existing credentials
3. View your current game statistics
4. Choose a game to play from the main menu
5. For Blackjack, place bets with your virtual balance
6. Return to the main menu to select another game or view updated statistics

## Database Structure
The application uses a local SQLite database to store user information, including:
- User credentials (username and hashed password)
- Game play statistics
- Blackjack currency balance

## Dependencies
- SQLite3
- OpenSSL (for password hashing)
- C++ Standard Library

## Files in the Project
- `Main.cpp` - Core application with authentication and menu system
- `Main.h` - Header file with function declarations and structures
- `TicTacToe.cpp` - Implementation of the Tic Tac Toe game
- `Connect4.cpp` - Implementation of the Connect 4 game
- `Blackjack.cpp` - Implementation of the Blackjack card game with betting system
