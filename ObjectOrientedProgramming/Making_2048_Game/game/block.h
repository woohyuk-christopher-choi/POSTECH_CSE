#ifndef BLOCK_H
#define BLOCK_H



class Block {
public:
    Block(int value = 0) : value(value) {}

    void setValue(int value) {
        this->value = value;
    }

    int getValue() const {
        return value;
    }

    bool operator==(const Block& other) const {
        return value == other.value;
    }

    bool operator!=(const Block& other) const {
        return !(*this == other);
    }


private:
    int value;
};

#endif // BLOCK_H
