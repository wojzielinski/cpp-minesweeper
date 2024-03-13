#include "MinesweeperBoard.h"
/*
 * [IN-PROGRESS] Missing board size check!
 */
int main() {
    srand(time(NULL));

    MinesweeperBoard board;
    MinesweeperBoard testBoardD(10,10,DEBUG);
    MinesweeperBoard testBoardE(10,10,EASY);
    MinesweeperBoard testBoardN(10,10,NORMAL);
    MinesweeperBoard testBoardH(15,10,HARD);
    //board.debug_display();
    testBoardD.debug_display();

    //testBoardE.debug_display();
    //testBoardN.debug_display();
    //testBoardH.debug_display();
    return 0;
}
