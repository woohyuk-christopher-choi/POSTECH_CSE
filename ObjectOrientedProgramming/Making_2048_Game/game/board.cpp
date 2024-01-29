#include "board.h"

void Board::addRandomBlock() {
    std::vector<std::pair<int, int>> emptyPositions;

    // Find all empty positions
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (grid[i][j].getValue() == 0) {
                emptyPositions.push_back(std::make_pair(i, j));
            }
        }
    }

    // Choose a random empty position
    if (!emptyPositions.empty()) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, emptyPositions.size() - 1);

        auto [x, y] = emptyPositions[distrib(gen)];

        // Add a block with value 2
        grid[x][y].setValue(2);
    }
}

void Board::addRandomBlock1() {
    std::vector<std::pair<int, int>> emptyCells;

    // Find all empty cells
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (grid[i][j].getValue() == 0) {
                emptyCells.push_back(std::make_pair(i, j));
            }
        }
    }

    // Select a random empty cell
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, emptyCells.size() - 1);
    std::pair<int, int> cell = emptyCells[dis(gen)];

    // Assign a 2 or 4 to the block at the selected cell with 80% and 20% probability respectively
    std::uniform_real_distribution<> valueDis(0, 1);
    double value = valueDis(gen);
    grid[cell.first][cell.second].setValue(value < 0.8 ? 2 : 4);
}

void Board::mergeBlocks(Block &a, Block &b){
    int newValue = a.getValue() + b.getValue();
    a.setValue(newValue);
    b.setValue(0);
}

void Board::moveLeft() {
    bool changed = false;
    for (int i = 0; i < BOARD_SIZE; i++) {
        int moveIndex = 1; // Start from the second column

        for (int j = 0; j < BOARD_SIZE; j++) {
            if (grid[i][j].getValue() != 0) {
                // Find the target position for the block
                while (moveIndex < BOARD_SIZE && (grid[i][moveIndex - 1].getValue() == 0 || grid[i][moveIndex - 1].getValue() == grid[i][j].getValue())) {
                    --moveIndex; // Move the block to the left until an obstacle is reached
                }

                // Move the block to the target position
                if (moveIndex != j) {
                    grid[i][moveIndex - 1] = grid[i][j];
                    grid[i][j].setValue(0);
                    changed = true;
                }
            }
        }
    }

    if (changed) {
        addRandomBlock1();
    }
}

void Board::moveRight() {
    bool changed = false;
    for (int i = 0; i < BOARD_SIZE; i++) {
        int moveIndex = BOARD_SIZE - 2; // Start from the second-to-last column

        for (int j = BOARD_SIZE - 1; j >= 0; j--) {
            if (grid[i][j].getValue() != 0) {
                // Find the target position for the block
                while (moveIndex >= 0 && (grid[i][moveIndex + 1].getValue() == 0 || grid[i][moveIndex + 1].getValue() == grid[i][j].getValue())) {
                    ++moveIndex; // Move the block to the right until an obstacle is reached
                }

                // Move the block to the target position
                if (moveIndex != j) {
                    grid[i][moveIndex + 1] = grid[i][j];
                    grid[i][j].setValue(0);
                    changed = true;
                }
            }
        }
    }


    if (changed) {
        addRandomBlock1();
    }
}

void Board::moveUp() {
    bool changed = false;
    for (int j = 0; j < BOARD_SIZE; j++) {
        int moveIndex = 1; // Start from the second row

        for (int i = 0; i < BOARD_SIZE; i++) {
            if (grid[i][j].getValue() != 0) {
                // Find the target position for the block
                while (moveIndex < BOARD_SIZE && (grid[moveIndex - 1][j].getValue() == 0 || grid[moveIndex - 1][j].getValue() == grid[i][j].getValue())) {
                    --moveIndex; // Move the block upwards until an obstacle is reached
                }

                // Move the block to the target position
                if (moveIndex != i) {
                    grid[moveIndex - 1][j] = grid[i][j];
                    grid[i][j].setValue(0);
                    changed = true;
                }
            }
        }
    }

    if (changed) {
        addRandomBlock1();
    }
}

void Board::moveDown() {
    bool changed = false;
    for (int j = 0; j < BOARD_SIZE; j++) {
        int moveIndex = BOARD_SIZE - 2; // Start from the second-to-last row

        for (int i = BOARD_SIZE - 1; i >= 0; i--) {
            if (grid[i][j].getValue() != 0) {
                // Find the target position for the block
                while (moveIndex >= 0 && (grid[moveIndex + 1][j].getValue() == 0 || grid[moveIndex + 1][j].getValue() == grid[i][j].getValue())) {
                    ++moveIndex; // Move the block downwards until an obstacle is reached
                }

                // Move the block to the target position
                if (moveIndex != i) {
                    grid[moveIndex + 1][j] = grid[i][j];
                    grid[i][j].setValue(0);
                    changed = true;
                }
            }
        }
    }

    if (changed) {
        addRandomBlock1();
    }
}



