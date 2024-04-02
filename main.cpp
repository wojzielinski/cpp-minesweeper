#include "MinesweeperBoard.h"
#include "MSBoardTextView.h"
#include "MSTextController.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

int main() {
    std::srand(std::time(NULL));
    //MinesweeperBoard board;
    //MinesweeperBoard testBoardD(10,10,DEBUG);
    //MinesweeperBoard testBoardE(10,10,EASY);
    //MinesweeperBoard testBoardN(10,10,NORMAL);
    MinesweeperBoard testBoardH(15,15,DEBUG);
    MSBoardTextView MStestBoardH(testBoardH);
    MSTextController ctrl (testBoardH, MStestBoardH);
    //board.debug_display();
/*
    //TESTING FIELDS REVEALING aka AUTO-PLAY
    testBoardH.debug_display();
    do{
        int rRow = rand() % 10;
        int rCol = rand() % 10;
        std::cout << "(" << rRow << "," << rCol << ")" << std::endl;
        testBoardH.revealField(rRow, rCol);
        MStestBoardH.display();
    }while(testBoardH.getGameState()==RUNNING);
    testBoardH.debug_display();
    //END OF TEST
*/  testBoardH.debug_display();
    ctrl.play();
    //testBoardE.debug_display();
    //testBoardN.debug_display();
    //testBoardH.debug_display();
    return 0;
}
