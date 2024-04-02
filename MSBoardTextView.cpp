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
    int width = board.getBoardWidth();
    int height = board.getBoardHeight();

    std::cout << std::setw(3) << " ";
    for(int a=0; a<width;a++){
        std::cout << " " << std::setw(3) << std::right << a;
    }
    std::cout << std::endl;

    for (int row=0; row<height; row++){
        std::cout << std::setw(3) << std::right << row << " ";
        for(int col=0; col<width; col++){
            std::cout << " [" << board.getFieldInfo(row,col) << "]";
        }
        std::cout << std::endl;
    }
}