#ifndef MINESWEEPERBOARD_H
#define MINESWEEPERBOARD_H

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#define MAX_SIZE 10
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
        void set_empty(int, int);
        void display_field(int, int) const;
        void gen_easy();
        void gen_normal();
        void gen_hard();
        void gen_debug();
        void gen_random_fields(int);
        void generate_mines(GameMode);
    public:
        MinesweeperBoard();
        MinesweeperBoard(int, int, GameMode);
        void debug_display() const;
};

#endif //MINESWEEPERBOARD_H
