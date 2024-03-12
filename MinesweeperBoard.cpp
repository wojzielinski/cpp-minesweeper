#include "MinesweeperBoard.h"
void MinesweeperBoard::set_fields() {
    MinesweeperBoard::set_empty(cols,rows);
    //BE CAREFUL! There is no dimensions sanitization for fields below!!!
    data[0][0].hasMine = true;
    data[0][0].hasFlag = false;
    data[1][1].isRevealed = true;
    data[0][2].hasMine = true;
    data[0][2].hasFlag = true;
    data[3][4].hasFlag = true;
    data[3][4].hasMine = true;
    data[3][4].isRevealed = true;
}

void MinesweeperBoard::set_empty(int width, int height) {
    if(height <= MAX_SIZE && width <= MAX_SIZE){
        for(int row=0; row<height; row++){
            for(int col=0; col<width; col++){
                data[row][col].hasMine=false;
                data[row][col].hasFlag=false;
                data[row][col].isRevealed=false;
            }
        }
    } else {
        std::cout << "Could not initialize board. Dimensions limits exceeded (max 100x100)" << std::endl;

    }
}

void MinesweeperBoard::display_field(int row, int col) const{
    std::cout << "[" << (data[row][col].hasMine?"M":".");
    std::cout << (data[row][col].isRevealed?"o":".");
    std::cout << (data[row][col].hasFlag?"f":".");
    std::cout << "] ";
}
void MinesweeperBoard::gen_random_fields(int nMines) {
    int i=0, row,col;
    do {
        row=rand() % rows;
        col=rand() % cols;
        if(!data[row][col].hasMine){
            data[row][col].hasMine = true;
            i++;
        }
    } while (i<nMines);
}

void MinesweeperBoard::gen_easy() {
    int nMines = std::ceil(0.1*rows*cols);
    MinesweeperBoard::gen_random_fields(nMines);
    std::cout << "There are: " << nMines << " mines" << std::endl;
}
void MinesweeperBoard::gen_normal() {
    int nMines = std::ceil(0.2*rows*cols);
    MinesweeperBoard::gen_random_fields(nMines);
    std::cout << "There are: " << nMines << " mines" << std::endl;
}
void MinesweeperBoard::gen_hard() {
    int nMines = std::ceil(0.3*rows*cols);
    MinesweeperBoard::gen_random_fields(nMines);
    std::cout << "There are: " << nMines << " mines" << std::endl;
}
void MinesweeperBoard::gen_debug() {
    int row=0,col=0;
    while(row<rows && col<cols){
        data[row][col].hasMine = true;
        col++;
        row++;
    }
    col=0;
    row=0;
    while(col<cols){
        data[row][col].hasMine = true;
        col++;
    }
    col=0;
    row=0;
    while(row<rows){
        data[row][col].hasMine = true;
        row+=2;
    }
}

void  MinesweeperBoard::generate_mines(GameMode mode){
    switch (mode) {
        case EASY:
            MinesweeperBoard::gen_easy(); break;
        case NORMAL:
            MinesweeperBoard::gen_normal(); break;
        case HARD:
            MinesweeperBoard::gen_hard(); break;
        case DEBUG:
            MinesweeperBoard::gen_debug(); break;
    }
}

MinesweeperBoard::MinesweeperBoard(){
    cols = 7;
    rows = 6;
    MinesweeperBoard::set_fields();
}

MinesweeperBoard::MinesweeperBoard(int width, int height, GameMode mode){
    cols = width;
    rows = height;
    MinesweeperBoard::set_empty(width,height);
    MinesweeperBoard::generate_mines(mode);
}
void MinesweeperBoard::debug_display() const {
    std::cout << "      ";
    for(int a=0; a<cols;a++){
        std::cout << a << "     ";
    }
    std::cout << std::endl;

    for (int row = 0; row < rows; row++) {
        std::cout << row <<"\t";
        for (int col=0; col < cols; col++) {
            this->display_field(row,col);
        }
        std::cout << std::endl;
    }
}