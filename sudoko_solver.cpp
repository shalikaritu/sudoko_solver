#include <iostream>
#include <vector>

using namespace std;

const int SIZE = 9; // Size of the Sudoku grid

// Function to print the Sudoku grid
void printGrid(const vector<vector<int>>& grid) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cout << grid[i][j] << ' ';
        }
        cout << endl;
    }
}

// Function to check if placing num in grid[row][col] is valid
bool isValid(const vector<vector<int>>& grid, int row, int col, int num) {
    // Check if num is not repeated in the current row
    for (int x = 0; x < SIZE; ++x) {
        if (grid[row][x] == num) {
            return false;
        }
    }

    // Check if num is not repeated in the current column
    for (int x = 0; x < SIZE; ++x) {
        if (grid[x][col] == num) {
            return false;
        }
    }

    // Check if num is not repeated in the current 3x3 box
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to solve the Sudoku grid using backtracking
bool solveSudoku(vector<vector<int>>& grid) {
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            // Find an empty cell
            if (grid[row][col] == 0) {
                // Try placing digits 1 to 9 in the empty cell
                for (int num = 1; num <= SIZE; ++num) {
                    if (isValid(grid, row, col, num)) {
                        grid[row][col] = num;

                        // Recursively try to solve the rest of the grid
                        if (solveSudoku(grid)) {
                            return true;
                        }

                        // If placing num didn't lead to a solution, backtrack
                        grid[row][col] = 0;
                    }
                }

                // No valid number can be placed, so return false
                return false;
            }
        }
    }

    // All cells are filled
    return true;
}

// Main function
int main() {
    vector<vector<int>> grid = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    cout << "Original Sudoku Grid:" << endl;
    printGrid(grid);

    if (solveSudoku(grid)) {
        cout << "\nSolved Sudoku Grid:" << endl;
        printGrid(grid);
    } else {
        cout << "No solution exists." << endl;
    }

    return 0;
}
