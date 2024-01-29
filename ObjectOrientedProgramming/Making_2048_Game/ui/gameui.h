#ifndef GAMEUI_H
#define GAMEUI_H
#include <QWidget>
#include <QApplication>
#include <QGridLayout>
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QKeyEvent>
#include <QEvent>
#include <vector>
#include "blockui.h"
#include "game/board.h"

class GameUi : public QWidget{


public:
    explicit GameUi(Board &board, QWidget *parent = nullptr)
        : QWidget(parent), board(board){
        auto* layout = new QHBoxLayout(this);
        layout->setContentsMargins(0,0,0,0);

        gameBoardLayout = new QGridLayout(this);
        gameBoardLayout->setSpacing(10);
        gameBoardLayout->setContentsMargins(0,0,0,0);
        createBlockUis();

        auto* gameBoardWidget = new QWidget();
        gameBoardWidget->setLayout(gameBoardLayout);
        layout->addWidget(gameBoardWidget, 0, Qt::AlignLeft);
        setFocusPolicy(Qt::StrongFocus);

        scoreLabel = new QLabel();
        int score = board.getScore(); // 보드에서의 score값 가져오기
        QString labelText = "Score : " + QString::number(score);
        scoreLabel->setText(labelText);
        QFont font("", 44);  // 폰트 크기를 24로 설정
        scoreLabel->setFont(font);
        layout->addWidget(scoreLabel, 0, Qt::AlignTop|Qt::AlignRight);


        auto* btnLayout = new QVBoxLayout();


        auto* restoreBtn = new QPushButton("Restore");
        restoreBtn->setFixedSize(300, 200);
        restoreBtn->setFont(QFont("", 20));
        btnLayout->addWidget(restoreBtn);


        auto* exitBtn = new QPushButton("Exit");
        exitBtn->setFixedSize(300,200);//Exit 버튼은 300,200으로 크기 정해짐.
        exitBtn->setFont(QFont("",20));
        exitBtn->setFocusPolicy(Qt::NoFocus);

        btnLayout->addWidget(exitBtn);
        btnLayout->setAlignment(Qt::AlignBottom|Qt::AlignRight);

        layout->addLayout(btnLayout);

        connect(exitBtn, &QPushButton::clicked, this, &GameUi::confirmExit);


    }

    ~GameUi() {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                delete blockUis[i][j];
            }
        }
    }

    void confirmExit() {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Exit", "Are you sure to quit?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            QApplication::quit();
        } else {
            // Do nothing
        }
    }


    void createBlockUis() {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                BlockUi *blockUi = new BlockUi(board[i][j], this);
                gameBoardLayout->addWidget(blockUi, i, j);
                blockUis[i][j] = blockUi;
            }
        }
    }

    void refresh() {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                blockUis[i][j]->updateStyle();
            }
        }
    }

protected:
    void keyPressEvent(QKeyEvent *event) override {
        switch (event->key()) {
        case Qt::Key_Left:
            board.moveLeft();
            break;
        case Qt::Key_Right:
            board.moveRight();
            break;
        case Qt::Key_Up:
            board.moveUp();
            break;
        case Qt::Key_Down:
            board.moveDown();
            break;
        default:
            QWidget::keyPressEvent(event);
        }
        refresh(); // 키를 누른 후 UI를 갱신합니다.
    }


private:
    Board &board;
    QGridLayout *gameBoardLayout;
    QLabel* scoreLabel;
    std::vector<std::vector<BlockUi*>> blockUis = std::vector<std::vector<BlockUi*>>(4, std::vector<BlockUi*>(4));
};

#endif


