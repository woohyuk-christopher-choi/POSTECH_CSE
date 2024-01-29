#ifndef BLOCKUI_H
#define BLOCKUI_H

#include <QLabel>
#include <QString>
#include "game/block.h"

class BlockUi : public QLabel{


public:

    BlockUi(Block& block, QWidget* parent = nullptr) : QLabel(parent), block(block) {
        setFixedSize(250, 250);
        setAlignment(Qt::AlignCenter);
        updateStyle();
    }


public slots:
    void updateStyle() {
        int value = block.getValue();
        QString color;

        switch (value) {
        case 0:
            color = "rgb(255, 255, 255)";
            break;
        case 2:
            color = "rgb(187, 173, 160)";
            break;
        case 4:
            color = "rgb(237, 224, 200)";
            break;
        case 8:
            color = "rgb(242, 177, 121)";
            break;
        case 16:
            color = "rgb(245, 149, 99)";
            break;
        case 32:
            color = "rgb(246, 126, 95)";
            break;
        case 64:
            color = "rgb(246, 94, 59)";
            break;
        case 128:
            color = "rgb(237, 207, 114)";
            break;
        case 256:
            color = "rgb(237, 204, 97)";
            break;
        case 512:
            color = "rgb(237, 200, 80)";
            break;
        case 1024:
            color = "rgb(237, 197, 63)";
            break;
        case 2048:
            color = "rgb(237, 194, 46)";
            break;
        }

        QString style = QString("QLabel { background: %1; color: black; border-style: solid; font: 70pt; font: bold; }").arg(color);
        setStyleSheet(style);
        if (value == 0) {
            setText("");
        } else {
            setText(QString::number(value));
        }
    }

private:
    Block& block;
};

/*

class BlockUI : public QLabel{

public:
    BlockUI(QWidget *parent = nullptr);

    // 연결된 블록을 설정합니다.
    void setBlock(Block* block);
    Block* getBlock() const {
        return block;
    }

private:
    void updateStyle(int value); // 블록의 값을 기반으로 스타일을 업데이트합니다.
    Block* block; // 연결된 Block 객체에 대한 참조
};
*/

#endif // BLOCKUI_H


