#include <iostream>
#include <string>
#include "grid.h"
using namespace std;

int main() {
    cin.exceptions(ios::eofbit | ios::failbit);
    string cmd;
    Grid g;
    bool gameStarted = false;
    int moves = 0;
    try {
        while (cin >> cmd) {
            if (cmd == "new") {// Start the new game with grid
                int n;
                cin >> n;
                g.init(n); // Initialize the grid with n * n
                gameStarted = false;
                moves = 0; // Resests the move counter
            } else if (cmd == "init") { // Initialise the sate of grid before starting the game
                int r, c;
                while (true) {
                    cin >> r >> c;
                    if (r == -1 && c == -1) break; // Initialisation end
                    g.turnOn(r, c);// turn on the specified cell on the grid
                }
                cout << g;
            } else if (cmd == "game") { // command to start the game and set the number of moves
                cin >> moves;
                gameStarted = true; // Start a new game with grid
                if (moves == 1) {
                    cout << "1 move left" << endl;
                } else {
                    cout << moves << " moves left" << endl;
                }
                if (moves == 0) {
                    if (g.isWon()) {
                        cout << "Won" << endl;
                        break;
                    } else {
                        cout << "Lost" << endl;
                        break;
                    }
                }
            } else if (cmd == "switch") { // toglles the state of cell and it's adjacent neighbours
                int r, c;
                cin >> r >> c;
                g.toggle(r, c); // Toggles the cell and its neighbours
                cout << g; // Prints the grid
                if (gameStarted) {
                    --moves;
                    if (moves == 1) {
                        cout << "1 move left" << endl;
                    } else {
                        cout << moves << " moves left" << endl;
                    }
                    if (g.isWon()) {
                        cout << "Won" << endl;
                        break;
                    } else if (moves == 0) {
                        cout << "Lost" << endl;
                        break;
                    }
                }
                if (!gameStarted) {
                    --moves;
                    cout << moves << " moves left" << endl;
                    if (g.isWon()) {
                        cout << "Won" << endl;
                        break;
                    }
                }
            }
        }
    } catch (const ios_base::failure&) {
        // Handles the input stream errors
    }
    return 0;
}
