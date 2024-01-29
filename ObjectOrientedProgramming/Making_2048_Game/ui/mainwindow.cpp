#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // GameUi 인스턴스를 생성하고 MainWindow의 central widget에 추가합니다.
    Board board;
    gameui = new GameUi(board, this);
    this->setCentralWidget(gameui);
    this->resize(1300,1000);

}
