#include <iostream>  // Input/output
#include <cstdlib>   // For random numbers
using namespace std;

/// -------------------------------------------------------------------------
/// Function prototypes
/// -------------------------------------------------------------------------
int randomInt(int rangeLow, int rangeHigh);
int getDollar();
void printGameStats(int TotalGames, int playerWinCount, int playerWinnings,
                    int houseWinCount, int houseWinnings);

/// -------------------------------------------------------------------------
/// Main program
/// -------------------------------------------------------------------------
int main() {
    srand(42);  // Seed random numbers

    const int dieSides = 6;   // Number of sides on each die
    int totalGames = 0;        // Count of total games played
    int playerWinCount = 0;    // Count of player wins
    int houseWinCount = 0;     // Count of house wins
    int playerWinnings = 0;    // Total money player won
    int houseWinnings = 0;     // Total money house won
    char playAgain = 'y';      // Control loop to keep playing

    // Main game loop
    while (playAgain == 'Y' || playAgain == 'y') {
        const int bet = getDollar();   // Ask user for a bet

        if (bet > 0) {  // Only play if valid bet
            totalGames++;  // Increment game counter

            // Roll two dice
            const int die1 = randomInt(1, dieSides);
            const int die2 = randomInt(1, dieSides);
            const int rollTotal = die1 + die2;

            cout << "Roll = " << die1 << " and " << die2
                 << " totaling " << rollTotal << endl;

            // Decide winner
            if (rollTotal == 3 || rollTotal == 5 || rollTotal == 9) {
                cout << "House Wins!" << endl;
                houseWinCount++;
                houseWinnings += bet;
            }
            else if (rollTotal == 7 || rollTotal == 11) {
                cout << "Player Wins $" << (bet * 1.5) << "!" << endl;
                playerWinCount++;
                playerWinnings += static_cast<int>(bet * 1.5);
            }
            else if (die1 == die2 && (die1 == 2 || die1 == 4 || die1 == 5)) {
                cout << "Player Wins $" << (bet * 1.5) << "!" << endl;
                playerWinCount++;
                playerWinnings += static_cast<int>(bet * 1.5);
            }
            else if (die1 == die2 && (die1 == 1 || die1 == 3 || die1 == 6)) {
                cout << "House Wins!" << endl;
                houseWinCount++;
                houseWinnings += bet;
            }
            else {
                cout << "No Winner!" << endl;
            }
        }
        else {
            cout << "\nInvalid input, session over.\n" << endl;
        }

        // Ask if the player wants to continue
        cout << "Do you want to play again Y/N? ";
        cin >> playAgain;
    }

    cout << "\nGame over. Thanks for playing!\n" << endl;

    // Print final statistics
    printGameStats(totalGames, playerWinCount, playerWinnings, houseWinCount,
     houseWinnings);

    return 0;
}

/// -------------------------------------------------------------------------
/// Returns a random integer between rangeLow and rangeHigh
/// -------------------------------------------------------------------------
int randomInt(int rangeLow, int rangeHigh) {
    // Ensure rangeLow is smaller than rangeHigh
    if (rangeLow > rangeHigh) {
        const int temp = rangeLow;
        rangeLow = rangeHigh;
        rangeHigh = temp;
    }

    // Random number between rangeLow and rangeHigh
    const int num = rand() % (rangeHigh - rangeLow + 1) + rangeLow;
    return num;
}


/// -------------------------------------------------------------------------
/// Ask user for a positive integer bet
/// Give user 3 tries, return -1 if failed
/// -------------------------------------------------------------------------
int getDollar() {
    const int maxTries = 3;
    int attempt = 0;
    string input;
    int dollar = -1;  // final result

    while (attempt < maxTries && dollar == -1) {
        cout << "Enter a bet in integer dollars: ";
        cin >> input;

        bool validInput = true;

        // Check digits only
        for (size_t i = 0; i < input.length(); i++) {
            if (!isdigit(input[i])) {
                validInput = false;
            }
        }

        if (input.length() > 0 && validInput) {
            int temp = 0;

            // Convert string to int
            for (size_t i = 0; i < input.length(); i++) {
                temp = temp * 10 + (input[i] - '0');
            }

            if (temp > 0) {
                dollar = temp;  //  this will end the loop naturally
            }
        }

        if (dollar == -1) {
             const int remaining = maxTries - attempt - 1;
            cout << "Error... " << remaining << " attempt(s) left!" << endl;
            attempt++;
        }
    }

    return dollar;  // only return
}


/// -------------------------------------------------------------------------
/// Print statistics for the game session
/// -------------------------------------------------------------------------
void printGameStats(int TotalGames, int playerWinCount, int playerWinnings,
                    int houseWinCount, int houseWinnings) {
    cout << "Game Stats" << endl;
    cout << "----------------------------------------" << endl;
    cout << "                   Total Games:   "  << TotalGames << endl;
    cout << "Number of times the player won:   "  << playerWinCount << endl;
    cout << "               Player Winnings: "  << playerWinnings << endl;
    cout << " Number of times the house won:   "  << houseWinCount << endl;
    cout << "                House Winnings: " <<  houseWinnings << endl;
}
