#include "MinesweeperBoard.h"

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <cassert>

//PRIVATE
//===============
void MinesweeperBoard::change_location(int row, int col) {
    int newRow, newCol;
    do {
        newRow = rand() % rows;
        newCol = rand() % cols;
    } while (data[newRow][newCol].hasMine);
    data[newRow][newCol].hasMine = true;
    data[row][col].hasMine = false;
    data[row][col].isRevealed = true;
    firstMove=false;
    if(isFinishedWin()) state = FINISHED_WIN;
}

void MinesweeperBoard::display_field(int row, int col) const{
    std::cout << "[" << (data[row][col].hasMine?"M":".");
    std::cout << (data[row][col].isRevealed?"o":".");
    std::cout << (data[row][col].hasFlag?"f":".");
    std::cout << "] ";
}

bool MinesweeperBoard::field_on_board(int row, int col) const{
    if(row>=getBoardHeight() || row<0 || col<0 || col>=getBoardWidth()) { return false; }
    return true;
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

void MinesweeperBoard::gen_rand_mines(int nMines) {
    gen_random_fields(nMines);
    assert(getMineCount()==nMines);
}

void MinesweeperBoard::gen_random_fields(int nMines) {
    int count=0, row,col;
    do {
        row=rand() % rows;
        col=rand() % cols;
        if(!data[row][col].hasMine){
            data[row][col].hasMine = true;
            count++;
        }
    } while (count<nMines);
}

void  MinesweeperBoard::generate_mines(GameMode gamemode){
    switch (gamemode) {
        case EASY:
            gen_rand_mines(std::ceil(0.1*rows*cols));
            mode = EASY;
            break;
        case NORMAL:
            gen_rand_mines(std::ceil(0.2*rows*cols));
            mode = NORMAL;
            break;
        case HARD:
            gen_rand_mines(std::ceil(0.3*rows*cols));
            mode = HARD;
            break;
        case DEBUG:
            gen_debug();
            mode = DEBUG;
            break;
    }
}

bool MinesweeperBoard::hasMine(int row, int col) const {
    if(field_on_board(row,col) && data[row][col].hasMine) return true;
    return false;
}

bool MinesweeperBoard::isFinishedWin() const {
    if(getGameState()==FINISHED_LOSS) return false;
    int counter = 0;
    int width = getBoardWidth();
    int height = getBoardHeight();
    for(int row =0; row<height; row++){
        for(int col=0; col<width; col++){
            if(isRevealed(row,col)){
                counter++;
            }
        }
    }
    if(counter==(width*height)-getMineCount()) return true;
    return false;
}

void MinesweeperBoard::recursiveRevealField(int row, int col) {
    if(countMines(row,col)==0){
        for(int tempRow=row-1; tempRow<=row+1; tempRow++){
            for(int tempCol=col-1; tempCol<=col+1; tempCol++){
                if(!field_on_board(tempRow, tempCol)) return;
                if(tempRow!=row || tempCol!=col){
                    revealField(tempRow,tempCol);
                }
            }
        }
    }
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

void MinesweeperBoard::set_fields() {
    set_empty(cols,rows);
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

//PUBLIC
//===============
MinesweeperBoard::MinesweeperBoard(){
    cols = 7;
    rows = 6;
    set_fields();
    state = RUNNING;
    mode = DEBUG;
    firstMove = true;
}

MinesweeperBoard::MinesweeperBoard(int width, int height, GameMode gMode){
    cols = width;
    rows = height;
    set_empty(width,height);
    mode = gMode;
    generate_mines(gMode);
    state = RUNNING;
    firstMove = true;
}

void MinesweeperBoard::debug_display() const {
    std::cout << std::setw(5) << " ";
    for(int a=0; a<cols;a++){
        std::cout << " " << std::setw(5) << std::right << a;
    }
    std::cout << std::endl;

    for (int row = 0; row < rows; row++) {
        std::cout << std::setw(5) << std::right << row << " ";
        for (int col=0; col < cols; col++) {
            this->display_field(row,col);
        }
        std::cout << std::endl;
    }
}

int MinesweeperBoard::getBoardWidth() const {
    return cols;
}

int MinesweeperBoard::getBoardHeight() const {
    return rows;
}

int MinesweeperBoard::getMineCount() const {
    int counter = 0;
    int width = getBoardWidth();
    int height = getBoardHeight();
    for(int row =0; row<height; row++){
        for(int col=0; col<width; col++){
            if(hasMine(row,col)){
                counter++;
            }
        }
    }
    return counter;
}

int MinesweeperBoard::countMines(int row, int col) const {
    if(!field_on_board(row, col) || !isRevealed(row,col)){
        return -1;
    }
    int counter =0;
    for(int tempRow=row-1; tempRow<=row+1; tempRow++){
        for(int tempCol=col-1; tempCol<=col+1; tempCol++){
            if(field_on_board(tempRow, tempCol) && (tempRow!=row || tempCol!=col)){
                if(hasMine(tempRow, tempCol)) { counter++; }
            }
        }
    }
    return counter;
}

bool MinesweeperBoard::hasFlag(int row, int col) const {
    if(!field_on_board(row, col) || !data[row][col].hasFlag || isRevealed(row,col)) return false;
    return true;
}

void MinesweeperBoard::toggleFlag(int row, int col) {
    if(!field_on_board(row,col)) return;
    if(getGameState() != RUNNING) return;
    if(isRevealed(row,col)) return;

    if(hasFlag(row,col)){
        data[row][col].hasFlag = false;
    } else {
        data[row][col].hasFlag = true;
    }
}

void MinesweeperBoard::revealField(int row, int col) {
    if(!field_on_board(row,col)) return;
    if(isRevealed(row,col)) return;
    if(getGameState()!=RUNNING) return;
    if(hasFlag(row,col)) return;

    if(!hasMine(row,col)) {
        data[row][col].isRevealed = true;
        firstMove=false;
        recursiveRevealField(row,col);
        if(isFinishedWin()) state = FINISHED_WIN;
        return;
    }
    if(mode!=DEBUG && firstMove) {
        change_location(row,col);
        return;
    }
    data[row][col].isRevealed=true;
    state = FINISHED_LOSS;
    firstMove = false;
}

bool MinesweeperBoard::isRevealed(int row, int col) const {
    if(field_on_board(row,col) && data[row][col].isRevealed) return true;
    return false;
}

GameState MinesweeperBoard::getGameState() const {
    return state;
}

char MinesweeperBoard::getFieldInfo(int row, int col) const {
    if(!field_on_board(row,col)){ return '#'; }
    if(!isRevealed(row,col)){
        if(hasFlag(row,col)) return 'F';
        return '_';
    }
    if(data[row][col].hasMine) return 'x';
    if(countMines(row,col)==0) return ' ';
    return static_cast<char>(countMines(row,col)+'0');
}