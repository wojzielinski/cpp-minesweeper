#include "MinesweeperBoard.h"
#include "MSBoardTextView.h"
#include "MSTextController.h"

#include <iostream>
#include <ctime>
#include <cstdlib>

int main() {
    std::srand(std::time(NULL));
    MinesweeperBoard board(8,8,EASY);
    MSBoardTextView view(board);
    MSTextController ctrl(board, view);
    ctrl.play();
    return 0;
}
