#include "MinesweeperBoard.h"
#include "MSBoardTextView.h"

#include <iostream>
#include <ctime>
#include <cstdlib>

int main() {
    std::srand(std::time(NULL));
    //MinesweeperBoard board;
    //MinesweeperBoard testBoardD(10,10,DEBUG);
    //MinesweeperBoard testBoardE(10,10,EASY);
    //MinesweeperBoard testBoardN(10,10,NORMAL);
    MinesweeperBoard testBoardH(10,10,GameMode::DEBUG);
    //board.debug_display();

    /*
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
    */
    MSBoardTextView view( testBoardH );
    view.display();
    testBoardH.revealField(2,1);
    testBoardH.revealField(3,5);
    testBoardH.revealField(7,3);
    testBoardH.revealField(4,12);
    testBoardH.toggleFlag(0,0);
    testBoardH.toggleFlag(0,1);
    testBoardH.toggleFlag(0,2);
    testBoardH.toggleFlag(0,3);
    testBoardH.toggleFlag(1,1);
    testBoardH.toggleFlag(2,2);
    testBoardH.toggleFlag(2,0);
    testBoardH.toggleFlag(3,3);
    testBoardH.revealField(3,0);
    view.display();
    testBoardH.debug_display();
    if(testBoardH.getGameState()==FINISHED_WIN)
    std::cout << "win" << std::endl;

    //testBoardE.debug_display();
    //testBoardN.debug_display();
    //testBoardH.debug_display();
    return 0;
}
