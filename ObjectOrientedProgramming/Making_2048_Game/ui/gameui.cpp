#include "gameui.h"

/*

GameUi::~GameUi() {
    delete scoreLabel;
}


void GameUi::updateScore(int score){
    scoreLabel->setText("Score: " + QString::number(score));
}

void GameUi::addRandomBlock1() {
    // Randomly select an empty cell
    int i, j;
    do {
        i = QRandomGenerator::global()->bounded(BOARD_SIZE);
        j = QRandomGenerator::global()->bounded(BOARD_SIZE);
    } while (board[i][j]->getBlock() != nullptr);

    Block* block = new Block(2);
    blocks.push_back(block); // Add the Block object to the vector

    // Set the Block object of the BlockUI
    board[i][j]->setBlock(block);

    // Set value of the cell to 2
    //board[i][j]->setValue(2);
}
*/
