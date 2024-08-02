#include <iostream>
#include <vector>

using namespace std;

const int BOARD_SIZE = 3;
vector<vector<char>> board(BOARD_SIZE, vector<char>(BOARD_SIZE, ' '));
char currentPlayer = 'X';

void displayBoard() {
    cout << "\n";
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            cout << " " << board[i][j] << " ";
            if (j < BOARD_SIZE - 1) cout << "|";
        }
        cout << "\n";
        if (i < BOARD_SIZE - 1) cout << "---+---+---\n";
    }
    cout << "\n";
}

bool isMoveValid(int row, int col) {
    return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && board[row][col] == ' ';
}

void makeMove(int row, int col) {
    if (isMoveValid(row, col)) {
        board[row][col] = currentPlayer;
    } else {
        cout << "Invalid move. Try again.\n";
    }
}

bool checkWin() {
    
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer)
            return true;
    }

    
    for (int j = 0; j < BOARD_SIZE; ++j) {
        if (board[0][j] == currentPlayer && board[1][j] == currentPlayer && board[2][j] == currentPlayer)
            return true;
    }

    
    if (board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer)
        return true;
    if (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer)
        return true;

    return false;
}

bool checkDraw() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == ' ')
                return false;
        }
    }
    return true;
}

void switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

void resetBoard() {
    board = vector<vector<char>>(BOARD_SIZE, vector<char>(BOARD_SIZE, ' '));
    currentPlayer = 'X';
}

void playGame() {
    while (true) {
        displayBoard();
        int row, col;
        cout << "Player " << currentPlayer << ", enter your move (row and column): ";
        cin >> row >> col;

        makeMove(row - 1, col - 1);

        if (checkWin()) {
            displayBoard();
            cout << "Player " << currentPlayer << " wins!\n";
            break;
        } else if (checkDraw()) {
            displayBoard();
            cout << "The game is a draw!\n";
            break;
        }

        switchPlayer();
    }
}

int main() {
    char playAgain;
    do {
        resetBoard();
        playGame();
        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "Thanks for playing!\n";
    return 0;
}
