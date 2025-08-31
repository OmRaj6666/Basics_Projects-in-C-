#include <iostream>
#include <vector>
using namespace std;

// Function to print the game board
void printBoard(const vector<vector<char>> &board)
{
    cout << "\n";
    for (int i = 0; i < 3; i++)
    {
        cout << " ";
        for (int j = 0; j < 3; j++)
        {
            cout << board[i][j];
            if (j < 2)
                cout << " | ";
        }
        cout << "\n";
        if (i < 2)
            cout << "-----------\n";
    }
    cout << "\n";
}

// Function to check if a player has won
bool checkWin(const vector<vector<char>> &board, char player)
{
    // Check rows and columns
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return true;
    }

    // Check diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;

    return false;
}

// Function to check if the board is full
bool checkDraw(const vector<vector<char>> &board)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
                return false;
        }
    }
    return true;
}

int main()
{
    vector<vector<char>> board(3, vector<char>(3, ' '));
    char currentPlayer = 'X';
    int row, col;
    bool gameOver = false;

    cout << "Welcome to Tic-Tac-Toe!\n";
    cout << "Player 1: X\nPlayer 2: O\n";

    while (!gameOver)
    {
        printBoard(board);
        cout << "Player " << currentPlayer << ", enter your move (row and column 1-3): ";
        cin >> row >> col;

        // Convert to 0-based index
        row--;
        col--;

        // Validate input
        if (row < 0 || row > 2 || col < 0 || col > 2)
        {
            cout << "Invalid position! Please enter values between 1 and 3.\n";
            continue;
        }

        if (board[row][col] != ' ')
        {
            cout << "That position is already taken! Try again.\n";
            continue;
        }

        // Make the move
        board[row][col] = currentPlayer;

        // Check for win
        if (checkWin(board, currentPlayer))
        {
            printBoard(board);
            cout << "Player " << currentPlayer << " wins!\n";
            gameOver = true;
        }
        // Check for draw
        else if (checkDraw(board))
        {
            printBoard(board);
            cout << "It's a draw!\n";
            gameOver = true;
        }
        // Switch players
        else
        {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }

    char playAgain;
    cout << "Would you like to play again? (y/n): ";
    cin >> playAgain;

    if (tolower(playAgain) == 'y')
    {
        // Reset the game
        board = vector<vector<char>>(3, vector<char>(3, ' '));
        main(); // Recursive call to start a new game
    }
    else
    {
        cout << "Thanks for playing!\n";
    }

    return 0;
}