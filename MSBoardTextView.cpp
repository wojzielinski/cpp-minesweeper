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

//Display board in text mode
void MSBoardTextView::display() {
    int width = board.getBoardWidth();
    int height = board.getBoardHeight();

    std::cout << std::setw(3) << " ";                               //print each column's index
    for(int a=0; a<width;a++){
        std::cout << " " << std::setw(3) << std::right << a;
    }
    std::cout << std::endl;

    for (int row=0; row<height; row++){
        std::cout << std::setw(3) << std::right << row << " ";      //print row index
        for(int col=0; col<width; col++){
            std::cout << " [" << board.getFieldInfo(row,col) << "]";   //print field info
        }
        std::cout << std::endl;
    }
}