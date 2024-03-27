#include <iostream>
#include <iomanip>

#include "MSBoardTextView.h"
#include "MinesweeperBoard.h"

//PUBLIC
//===============
MSBoardTextView::MSBoardTextView(MinesweeperBoard & boardRef) : board(boardRef)
{
    //assigned MinesweeperBoard reference to "board"
}

void MSBoardTextView::display() {
    int rows = board.getBoardHeight();
    int cols = board.getBoardWidth();
    std::cout << std::setw(4) << " ";
    for(int ncol=0; ncol<cols;ncol++){
        std::cout << " " << std::setw(3) << std::right << ncol;
    }
    std::cout << std::endl;
    for (int row = 0; row < rows; row++) {
        std::cout << std::setw(4) << std::right << row << " ";
        for (int col=0; col < cols; col++) {
            std::cout << " [" << board.getFieldInfo(row,col) << "]" ;
        }
        std::cout << std::endl;
    }
}