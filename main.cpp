#include "MinesweeperBoard.h"
#include "MSBoardTextView.h"
#include "MSTextController.h"

#include <iostream>
#include <ctime>
#include <cstdlib>

int main() {
    //Set seed for random number generator (not a perfect solution, but good enough for minesweeper)
    std::srand(std::time(NULL));

    //Create board, text view and text controller objects
    MinesweeperBoard board(8,8,EASY);
    MSBoardTextView view(board);
    MSTextController ctrl(board, view);

    //Play minesweeper
    ctrl.play();
    return 0;
}
