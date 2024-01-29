    #include "blockui.h"

/*

    BlockUI::BlockUI(QWidget *parent)
        : QLabel(parent), block(nullptr)
    {

        setFixedSize(250, 250); // The fixed size of block
        setAlignment(Qt::AlignCenter); // The alignment of the content : center

        QGridLayout* layout = new QGridLayout(this);
        layout->setSpacing(10);// block space 10

        updateStyle(0); // set the initial style
    }

    void BlockUI::setBlock(Block* block){
        this->block = block;
        int value = block->getValue();
        updateStyle(value);

        if(value == 0){
            setText("");
        }
        else{
            setText(QString::number(value));
            setAlignment(Qt::AlignCenter);
        }
    }



    void BlockUI::updateStyle(int value) {
        QString style;

        switch(value){
        case 0:
            style = "QLabel { background: rgb(255, 255, 255); color: black; border-style: solid; font: 70pt; font: bold; }";
            break;
        case 2:
            style = "QLabel { background: rgb(187, 173, 160); color: black; border-style: solid; font: 70pt; font: bold; }";
            break;
        case 4:
            style = "QLabel { background: rgb(237, 224, 200); color: black; border-style: solid; font: 70pt; font: bold; }";
            break;
        case 8:
            style = "QLabel { background: rgb(242, 177, 121); color: black; border-style: solid; font: 70pt; font: bold; }";
            break;
        case 16:
            style = "QLabel { background: rgb(245, 149, 99); color: black; border-style: solid; font: 70pt; font: bold; }";
            break;
        case 32:
            style = "QLabel { background: rgb(246, 126, 95); color: black; border-style: solid; font: 70pt; font: bold; }";
            break;
        case 64:
            style = "QLabel { background: rgb(246, 94, 59); color: black; border-style: solid; font: 70pt; font: bold; }";
            break;
        case 128:
            style = "QLabel { background: rgb(237, 207, 114); color: black; border-style: solid; font: 70pt; font: bold; }";
            break;
        case 256:
            style = "QLabel { background: rgb(237, 204, 97); color: black; border-style: solid; font: 70pt; font: bold; }";
            break;
        case 512:
            style = "QLabel { background: rgb(237, 200, 80); color: black; border-style: solid; font: 70pt; font: bold; }";
            break;
        case 1024:
            style = "QLabel { background: rgb(237, 197, 63); color: black; border-style: solid; font: 70pt; font: bold; }";
            break;
        case 2048:
            style = "QLabel { background: rgb(237,194,46); color: black; border-style: solid; font: 70pt; font: bold; }";
            break;
        default:
            style = "QLabel { background: rgb(255,255,255); color: black; border-style: solid; font: 70pt; font: bold; }";
        }

        setStyleSheet(style);
    }

*/
