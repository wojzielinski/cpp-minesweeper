#include "MinesweeperBoard.h"
/*
 * [IN-PROGRESS] Missing board size check!
 */
int main() {
    srand(time(NULL));

    //MinesweeperBoard board;
    //MinesweeperBoard testBoardD(10,10,DEBUG);
    //MinesweeperBoard testBoardE(10,10,EASY);
    //MinesweeperBoard testBoardN(10,10,NORMAL);
    MinesweeperBoard testBoardH(20,20,HARD);
    //board.debug_display();

    //TESTING FIELDS REVEALING aka AUTO-PLAY
    testBoardH.debug_display();
    do{
        int rRow = rand() % 10;
        int rCol = rand() % 10;
        std::cout << "(" << rRow << "," << rCol << ")" << std::endl;
        testBoardH.revealField(rRow, rCol);
    }while(testBoardH.getGameState()==RUNNING);
    testBoardH.debug_display();
    //END OF TEST

    //testBoardE.debug_display();
    //testBoardN.debug_display();
    //testBoardH.debug_display();
    return 0;
}
