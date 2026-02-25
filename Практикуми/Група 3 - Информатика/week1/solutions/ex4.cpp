#include <iostream>


// Помислете дали може функциите да бъдат написани по хитро (може ли да се преизползва еднаквата логика)
bool rowIsCorrct(int sudoku[9][9], int row) {
    bool seen[9] = {false};
    for (int j = 0; j < 9; ++j) {
        int num = sudoku[row][j];
        if (num < 0 || num > 9) {
            return true;
        }
        if (num != 0) {
            if (seen[num-1]) {
                return true;
            }
            seen[num-1] = true;
        }
    }
    return false;
}

bool sudokuIsCorrectByRows(int sudoku[9][9]) {
    for (int i = 0; i < 9; ++i) {
        if (rowIsCorrct(sudoku, i)) {
            return false;
        }
    }
    return true;
}

bool columnIsCorrct(int sudoku[9][9], int col) {
    bool seen[9] = {false};
    for (int i = 0; i < 9; ++i) {
        int num = sudoku[i][col];
        if (num < 0 || num > 9) {
            return true;
        }
        if (num != 0) {
            if (seen[num-1]) {
                return true;
            }
            seen[num-1] = true;
        }
    }
    return false;
}

bool columnsAreCorrect(int sudoku[9][9]) {
    for (int j = 0; j < 9; ++j) {
        if (columnIsCorrct(sudoku, j)) {
            return false;
        }
    }
    return true;
}

bool boxIsCorrect(int sudoku[9][9], int boxRow, int boxCol) {
    bool seen[9] = {false};
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int num = sudoku[boxRow + i][boxCol + j];
            if (num < 0 || num > 9) {
                return true;
            }
            if (num != 0) {
                if (seen[num-1]) {
                    return true;
                }
                seen[num-1] = true;
            }
        }
    }
    return false;
}

bool boxesAreCorrect(int sudoku[9][9]) {
    for (int boxRow = 0; boxRow < 9; boxRow += 3) {
        for (int boxCol = 0; boxCol < 9; boxCol += 3) {
            if (boxIsCorrect(sudoku, boxRow, boxCol)) {
                return false;
            }
        }
    }
    return true;
}

bool validateSudoku(int sudoku[9][9]){
    return sudokuIsCorrectByRows(sudoku) &&
           columnsAreCorrect(sudoku) &&
           boxesAreCorrect(sudoku);
}

bool generateSolution(int sudoku[9][9], int row, int col) {
    if (row == 9) {
        std::cout << "Solution:" << std::endl;
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                std::cout << sudoku[i][j] << " ";
            }
            std::cout << std::endl;
        }
        return true;
    }
    if (col == 9) {
        return generateSolution(sudoku, row + 1, 0);
    }
    if (sudoku[row][col] != 0) {
        return generateSolution(sudoku, row, col + 1);
    }
    for (int num = 1; num <= 9; ++num) {
        sudoku[row][col] = num;
        std::cout << "Trying " << num << " at (" << row << ", " << col << ")" << std::endl;
        if (validateSudoku(sudoku)) {
            if (generateSolution(sudoku, row, col + 1) ){
                return true;
            } else {
                std::cout << "Backtracking from (" << row << ", " << col << ")" << std::endl;
            }
        }
        sudoku[row][col] = 0;
    }
    return false;
}

int main() {
    int sudoku[9][9];
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            std::cin >> sudoku[i][j];
        }
    }
    std::cout << validateSudoku(sudoku) << std::endl;
    
    return 0;
}
