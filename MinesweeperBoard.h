#ifndef MINESWEEPERBOARD_H
#define MINESWEEPERBOARD_H

#include<iostream>
#define MAX_SIZE 100
struct Field {
    bool hasMine;
    bool hasFlag;
    bool isRevealed;
};

enum GameMode { DEBUG, EASY, NORMAL, HARD };

class MinesweeperBoard {
    private:
        int cols;
        int rows;
        Field data[MAX_SIZE][MAX_SIZE];
        void set_fields();
        void display_field(int, int) const;
    public:
        MinesweeperBoard();
        MinesweeperBoard(int width, int height, GameMode mode);
        void debug_display() const;
};

#endif //MINESWEEPERBOARD_H
