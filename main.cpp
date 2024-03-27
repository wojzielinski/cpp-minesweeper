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
    MinesweeperBoard testBoardH(15,15,GameMode::EASY);
    //board.debug_display();

    // /*
    //TESTING FIELDS REVEALING aka AUTO-PLAY
    testBoardH.debug_display();
    do{
        int rRow = rand() % testBoardH.getBoardHeight();
        int rCol = rand() % testBoardH.getBoardWidth();
        std::cout << "(" << rRow << "," << rCol << ")" << std::endl;
        testBoardH.revealField(rRow, rCol);
    }while(testBoardH.getGameState()==RUNNING);
    testBoardH.debug_display();
    //END OF TEST
    // */
    /*
    MSBoardTextView view( testBoardH );
    view.display();
    testBoardH.revealField(2,1);
    testBoardH.revealField(3,0);
    testBoardH.revealField(3,1);
    testBoardH.revealField(3,2);
    testBoardH.revealField(2,3);
    testBoardH.revealField(1,0);
    testBoardH.revealField(1,2);
    testBoardH.revealField(1,3);
    view.display();
    testBoardH.debug_display();
     */
    if(testBoardH.getGameState()==FINISHED_WIN)
        std::cout << "win" << std::endl;


    //testBoardE.debug_display();
    //testBoardN.debug_display();
    //testBoardH.debug_display();
    return 0;
}
