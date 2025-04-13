#include <iostream>
#include "Main.h"
#include <sqlite3.h>
#include <string>
#include <iomanip>
#include <sstream>
#include <openssl/sha.h>
#include <openssl/evp.h>

using namespace std;

string hashPassword(const string& password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    EVP_MD_CTX* ctx = EVP_MD_CTX_new(); // Create a new EVP context

    if (!ctx) {
        cerr << "Failed to create EVP_MD_CTX" << endl;
        return "";
    }

    // Initialize the context with SHA-256
    if (EVP_DigestInit_ex(ctx, EVP_sha256(), NULL) != 1) {
        cerr << "EVP_DigestInit_ex failed" << endl;
        EVP_MD_CTX_free(ctx);
        return "";
    }

    // Add a salt to prevent rainbow table attacks
    string saltedPassword = password + "4m0n6U5";

    // Update the context with the salted password
    if (EVP_DigestUpdate(ctx, saltedPassword.c_str(), saltedPassword.length()) != 1) {
        cerr << "EVP_DigestUpdate failed" << endl;
        EVP_MD_CTX_free(ctx);
        return "";
    }

    // Finalize the hash
    unsigned int length = 0;
    if (EVP_DigestFinal_ex(ctx, hash, &length) != 1) {
        cerr << "EVP_DigestFinal_ex failed" << endl;
        EVP_MD_CTX_free(ctx);
        return "";
    }

    EVP_MD_CTX_free(ctx); // Free the context

    // Convert hash to hexadecimal string
    stringstream ss;
    for (unsigned int i = 0; i < length; i++) {
        ss << hex << setw(2) << setfill('0') << static_cast<int>(hash[i]);
    }

    return ss.str();
}
// Function to initialize the database and users table
bool initializeDatabase() {
    sqlite3* db;
    char* errorMsg = 0;
    int rc;

    // Open database connection
    rc = sqlite3_open("games.db", &db);
    if (rc) {
        cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return false;
    }

    // Create users table if it doesn't exist
    const char* sql = "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT UNIQUE NOT NULL,"
        "password TEXT NOT NULL,"
        "tictactoe_games INTEGER DEFAULT 0,"
        "connect4_games INTEGER DEFAULT 0,"
        "blackjack_games INTEGER DEFAULT 0,"
        "blackjack_balance REAL DEFAULT 100.0);";

    rc = sqlite3_exec(db, sql, 0, 0, &errorMsg);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << errorMsg << endl;
        sqlite3_free(errorMsg);
        sqlite3_close(db);
        return false;
    }

    sqlite3_close(db);
    return true;
}

// Function to register a new user
bool registerUser(const string& username, const string& password) {
    sqlite3* db;
    char* errorMsg = 0;
    int rc;
    string hashedPassword = hashPassword(password);
    rc = sqlite3_open("games.db", &db);
    if (rc) {
        cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return false;
    }

    // Prepare SQL statement to insert user
    string sql = "INSERT INTO users (username, password, tictactoe_games, connect4_games, blackjack_games, blackjack_balance) "
        "VALUES ('" + username + "', '" + hashedPassword + "', 0, 0, 0, 100.0);";

    rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errorMsg);
    if (rc != SQLITE_OK) {
        cerr << "Registration error: " << errorMsg << endl;
        sqlite3_free(errorMsg);
        sqlite3_close(db);
        return false;
    }

    sqlite3_close(db);
    return true;
}

// Callback function for login query
static int loginCallback(void* data, int argc, char** argv, char** colNames) {
    bool* result = static_cast<bool*>(data);
    *result = true;
    return 0;
}

// Function to authenticate user
bool loginUser(const string& username, const string& password) {
    sqlite3* db;
    char* errorMsg = 0;
    int rc;
    bool authenticated = false;

    // Hash the input password
    string hashedPassword = hashPassword(password);

    rc = sqlite3_open("games.db", &db);
    if (rc) {
        cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return false;
    }

    // Prepare SQL statement to check credentials
    string sql = "SELECT * FROM users WHERE username = '" + username +
        "' AND password = '" + hashedPassword + "';";

    rc = sqlite3_exec(db, sql.c_str(), loginCallback, &authenticated, &errorMsg);
    if (rc != SQLITE_OK) {
        cerr << "Login error: " << errorMsg << endl;
        sqlite3_free(errorMsg);
        sqlite3_close(db);
        return false;
    }

    sqlite3_close(db);
    return authenticated;
}

string currentUser = ""; // Global variable to store current user

// Function to handle login/registration


// Function to update game statistics for a user
bool updateGameStats(const string& username, const string& gameType, bool increment) {
    sqlite3* db;
    char* errorMsg = 0;
    int rc;

    rc = sqlite3_open("games.db", &db);
    if (rc) {
        cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return false;
    }

    // Determine which column to update based on game type
    string column;
    if (gameType == "tictactoe") {
        column = "tictactoe_games";
    }
    else if (gameType == "connect4") {
        column = "connect4_games";
    }
    else if (gameType == "blackjack") {
        column = "blackjack_games";
    }
    else {
        cerr << "Invalid game type" << endl;
        sqlite3_close(db);
        return false;
    }

    // Prepare SQL statement to update game count
    string sql = "UPDATE users SET " + column + " = " + column + " + 1 WHERE username = '" + username + "';";

    rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errorMsg);
    if (rc != SQLITE_OK) {
        cerr << "Update error: " << errorMsg << endl;
        sqlite3_free(errorMsg);
        sqlite3_close(db);
        return false;
    }

    sqlite3_close(db);
    return true;
}

// Function to update blackjack balance
bool updateBlackjackBalance(const string& username, double amount) {
    sqlite3* db;
    char* errorMsg = 0;
    int rc;

    rc = sqlite3_open("games.db", &db);
    if (rc) {
        cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return false;
    }

    // Prepare SQL statement to update blackjack balance
    string sql = "UPDATE users SET blackjack_balance = blackjack_balance + " + to_string(amount) +
        " WHERE username = '" + username + "';";

    rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errorMsg);
    if (rc != SQLITE_OK) {
        cerr << "Update error: " << errorMsg << endl;
        sqlite3_free(errorMsg);
        sqlite3_close(db);
        return false;
    }

    sqlite3_close(db);
    return true;
}

// Callback function for getting user stats
static int getUserStatsCallback(void* data, int argc, char** argv, char** colNames) {
    UserStats* stats = static_cast<UserStats*>(data);

    for (int i = 0; i < argc; i++) {
        string colName = colNames[i];
        if (colName == "tictactoe_games") {
            stats->tictactoeGames = argv[i] ? stoi(argv[i]) : 0;
        }
        else if (colName == "connect4_games") {
            stats->connect4Games = argv[i] ? stoi(argv[i]) : 0;
        }
        else if (colName == "blackjack_games") {
            stats->blackjackGames = argv[i] ? stoi(argv[i]) : 0;
        }
        else if (colName == "blackjack_balance") {
            stats->blackjackBalance = argv[i] ? stod(argv[i]) : 100.0;
        }
    }

    return 0;
}

// Function to retrieve user stats
bool getUserStats(const string& username, UserStats& stats) {
    sqlite3* db;
    char* errorMsg = 0;
    int rc;

    stats = { 0, 0, 0, 100.0 }; // Default values

    rc = sqlite3_open("games.db", &db);
    if (rc) {
        cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return false;
    }

    // Prepare SQL statement to get user stats
    string sql = "SELECT tictactoe_games, connect4_games, blackjack_games, blackjack_balance "
        "FROM users WHERE username = '" + username + "';";

    rc = sqlite3_exec(db, sql.c_str(), getUserStatsCallback, &stats, &errorMsg);
    if (rc != SQLITE_OK) {
        cerr << "Error retrieving stats: " << errorMsg << endl;
        sqlite3_free(errorMsg);
        sqlite3_close(db);
        return false;
    }

    sqlite3_close(db);
    return true;
}

bool authenticateUser() {
    int authChoice = 0;
    string username, password;
    UserStats stats;
    // Initialize database
    if (!initializeDatabase()) {
        cerr << "Failed to initialize database." << endl;
        return false;
    }

    while (true) {
        cout << "AUTHENTICATION" << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Exit" << endl;
        cin >> authChoice;

        if (authChoice == 1) {
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;

            if (loginUser(username, password)) {
                cout << "Login successful! Welcome, " << username << "!" << endl;
                currentUser = username; // Store the current username

                /*// Display user stats
                if (getUserStats(username, stats)){
                cout << "\n--- YOUR STATS ---" << endl;
                cout << "Tic Tac Toe games played: " << stats.tictactoeGames << endl;
                cout << "Connect 4 games played: " << stats.connect4Games << endl;
                cout << "Blackjack games played: " << stats.blackjackGames << endl;
                cout << "Blackjack balance: $" << stats.blackjackBalance << endl;
                cout << "-----------------\n" << endl;*/
                
                return true;
            }
            else {
                cout << "Invalid username or password." << endl;
            }
        }
        else if (authChoice == 2) {
            cout << "Create a new account" << endl;
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;

            if (registerUser(username, password)) {
                cout << "Registration successful! Please login." << endl;
            }
            else {
                cout << "Registration failed. Username may already exist." << endl;
            }
        }
        else if (authChoice == 3) {
            cout << "Goodbye!" << endl;
            return false;
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

int main() {
    // Start with authentication
    if (!authenticateUser()) {
        return 0;
    }

    int choice = 0;

    while (choice != 4) {
        // Display user stats before showing the menu
        UserStats stats;
        if (getUserStats(currentUser, stats)) {
            cout << "\n--- YOUR STATS ---" << endl;
            cout << "Tic Tac Toe games played: " << stats.tictactoeGames << endl;
            cout << "Connect 4 games played: " << stats.connect4Games << endl;
            cout << "Blackjack games played: " << stats.blackjackGames << endl;
            cout << "Blackjack balance: $" << stats.blackjackBalance << endl;
            cout << "-----------------\n" << endl;
        }
        else {  
            cout << "Error retrieving user stats. Using default balance." << endl;
            stats.blackjackBalance = 100.0; // Default balance
        }

        cout << "MENU" << endl;
        cout << "1. Tic Tac Toe" << endl;
        cout << "2. Connect 4" << endl;
        cout << "3. Blackjack" << endl;
        cout << "4. Exit" << endl;

        cin >> choice;

        if (choice == 1) {
            updateGameStats(currentUser, "tictactoe");
            tictacToe();
        }
        else if (choice == 2) {
            updateGameStats(currentUser, "connect4");
            connect4();
        }
        else if (choice == 3) {
            // We're moving the updateGameStats to inside the blackjack() function
            // to handle multiple plays in one session
            blackjack();
            // Removed the balance updates because they're now handled inside blackjack()
        }
        else if (choice == 4) cout << "Goodbye!" << endl;
        else cout << "Invalid choice. Please try again." << endl;
    }

    return 0;
}


