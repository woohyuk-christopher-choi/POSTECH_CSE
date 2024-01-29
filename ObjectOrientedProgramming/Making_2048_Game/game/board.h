#ifndef BOARD_H
#define BOARD_H

#include "block.h"
#include <QKeyEvent>
#include <QEvent>
#include <vector>
#include <random>

class Board{
public:
    const int BOARD_SIZE = 4;
    Board() : grid(4, std::vector<Block>(4)), score(0) {resetBoard();}

    void resetBoard(){
        for (int i = 0; i < 4; ++i){
            for (int j = 0; j < 4; ++j) {
                grid[i][j].setValue(0);
            }
        }
        score = 0;
        addRandomBlock();
        addRandomBlock();
    }

    int getScore() const {
        return score;
    }

    std::vector<Block> &operator[](int index) {
        return grid[index];
    }

    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void addRandomBlock();

    //void moveAndMergeLine(std::vector<Block>& line);

    /*
    void compressRow(std::vector<Block> &row);
    void mergeRow(std::vector<Block > &row);
    void reverseRow(std::vector<Block> &row);
    void compressColumn(std::vector<Block> &column);
    void mergeColumn(std::vector<Block> &column);
    void reverseColumn(std::vector<Block> &column);
*/



private:
    std::vector<std::vector<Block>> grid;
    int score;

    void addRandomBlock1();
    void mergeBlocks(Block &a , Block &b);
};









/*

class Board{
public:
    static const int BOARD_SIZE = 4;

    enum class Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    void move(Direction direction);
    void merge(Block* first, Block* second);
    void addNewBlock();
    void removeBlock(Block* block);


private:
    Block* board[BOARD_SIZE][BOARD_SIZE];

};
*/

#endif // BOARD_H

