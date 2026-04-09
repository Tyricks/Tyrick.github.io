#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// We initialize the board
const int ROWS = 6;
const int COLS = 7;

// ANSI color codes
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"
#define RESET   "\033[0m"

// To color wrap the game pieces
string color(char s) {
    if (s == 'X') return string(RED) + "X" + RESET;
    if (s == 'O') return string(YELLOW) + "O" + RESET;
    return " ";
}

// This part clears the board 
void clearBoard(char b[ROWS][COLS]) {
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++)
            b[r][c] = ' ';
}

// Prints the board
void showBoard(char b[ROWS][COLS]) {
    cout << CYAN << "\n  1 2 3 4 5 6 7" << RESET << "\n";
    for (int r = 0; r < ROWS; r++) {
        cout << " ";
        for (int c = 0; c < COLS; c++) {
            cout << "|" << color(b[r][c]);
        }
        cout << "|\n";
    }
    cout << CYAN << " -----------------" << RESET << "\n";
}

// Drops a piece in a column
bool placePiece(char b[ROWS][COLS], int col, char mark) {
    if (col < 0 || col >= COLS) return false;

    for (int r = ROWS - 1; r >= 0; r--) {
        if (b[r][col] == ' ') {
            b[r][col] = mark;
            return true;
        }
    }
    return false;
}

// Check for win (horizontal, vertical, diagonals)
bool fourConnected(char b[ROWS][COLS], char m) {

    // Horizontal
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS - 3; c++)
            if (b[r][c] == m && b[r][c+1] == m && b[r][c+2] == m && b[r][c+3] == m)
                return true;

    // Vertical
    for (int c = 0; c < COLS; c++)
        for (int r = 0; r < ROWS - 3; r++)
            if (b[r][c] == m && b[r+1][c] == m && b[r+2][c] == m && b[r+3][c] == m)
                return true;

    // Diagonal down
    for (int r = 0; r < ROWS - 3; r++)
        for (int c = 0; c < COLS - 3; c++)
            if (b[r][c] == m && b[r+1][c+1] == m && b[r+2][c+2] == m && b[r+3][c+3] == m)
                return true;

    // Diagonal up
    for (int r = 3; r < ROWS; r++)
        for (int c = 0; c < COLS - 3; c++)
            if (b[r][c] == m && b[r-1][c+1] == m && b[r-2][c+2] == m && b[r-3][c+3] == m)
                return true;

    return false;
}

// Checks to see if the board is full
bool filled(char b[ROWS][COLS]) {
    for (int c = 0; c < COLS; c++)
        if (b[0][c] == ' ') return false;
    return true;
}

// Menu display
void menu() {
    cout << "\n Hi, Welcome to Connect Four \n" << RESET;
    cout << GREEN << "1. Start Game\n"; 
    cout << YELLOW << "2. Quit\n";
    cout << "Choose: ";
}


int main() {
    char board[ROWS][COLS];
    char piece[2] = {'X', 'O'};
    string names[2];
    int choice;

    while (true) {
        menu();
        cin >> choice;

        if (choice == 2) {
            cout <<RED<< "Goodbye!\n";
            break;
        }

        // Get player names
        cout << "Enter name for Player 1 (X): ";
        cin >> names[0];
        cout << "Enter name for Player 2 (O): ";
        cin >> names[1];

        clearBoard(board);

        srand(time(0));
        int turn = rand() % 2;  // Random start

        cout << CYAN << "\n" << names[turn] << " will start!\n" << RESET;

        showBoard(board);

        bool gameEnd = false;

        while (!gameEnd) {
            int col;
            cout << names[turn] << " [" 
                 << (piece[turn] == 'X' ? RED : YELLOW)
                 << piece[turn] << RESET 
                 << "] choose column (1-7): ";
            cin >> col;
            col--;

            if (!placePiece(board, col, piece[turn])) {
                cout << RED << "Invalid move. Try again.\n" << RESET;
                continue;
            }

            showBoard(board);

            if (fourConnected(board, piece[turn])) {
                cout << GREEN << "\n " << names[turn] << " wins! Congratulations! \n" << RESET;
                gameEnd = true;
            }
            else if (filled(board)) {
                cout << CYAN << "\n Oh No! It's a draw!\n" << RESET;
                gameEnd = true;
            }
            else {
                turn = 1 - turn;  // Switch player
            }
        }
    }

    return 0;
}
