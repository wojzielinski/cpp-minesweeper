#include "MinesweeperBoard.h"
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

void MinesweeperBoard::gen_easy() {
    int nMines = std::ceil(0.1*rows*cols);
    gen_random_fields(nMines);
}

void MinesweeperBoard::gen_normal() {
    int nMines = std::ceil(0.2*rows*cols);
    gen_random_fields(nMines);
}

void MinesweeperBoard::gen_hard() {
    int nMines = std::ceil(0.3*rows*cols);
    gen_random_fields(nMines);
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
            gen_easy(); break;
        case NORMAL:
            gen_normal(); break;
        case HARD:
            gen_hard(); break;
        case DEBUG:
            gen_debug(); break;
    }
}

MinesweeperBoard::MinesweeperBoard(){
    cols = 7;
    rows = 6;
    set_fields();
}

MinesweeperBoard::MinesweeperBoard(int width, int height, GameMode mode){
    cols = width;
    rows = height;
    set_empty(width,height);
    generate_mines(mode);
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
            if(data[row][col].hasMine){
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
            if(field_on_board(tempRow, tempCol) && tempRow!=row && tempCol!=col){
                if(data[tempRow][tempCol].hasMine) { counter++; }
            }
        }
    }
    return counter;
}

bool MinesweeperBoard::field_on_board(int row, int col) const{
    if(row>=getBoardHeight() || row<0 || col<0 || col>=getBoardWidth()) { return false; }
    return true;
}

bool MinesweeperBoard::hasFlag(int row, int col) const {
    if(field_on_board(row, col) && data[row][col].hasFlag) { return true; }
    else if(!field_on_board(row, col) || !data[row][col].hasFlag || isRevealed(row,col)) { return false; }
}

void MinesweeperBoard::toggleFlag(int row, int col) {
    if(!field_on_board(row,col) || getGameState() != RUNNING || isRevealed(row,col)) return;
    if(!isRevealed(row,col)) {
        if(hasFlag(row,col)){
            data[row][col].hasFlag = false;
        } else {
            data[row][col].hasFlag = true;
        }
    }
}

void MinesweeperBoard::revealField(int row, int col) {
//TO DO
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
    else if(!isRevealed(row,col)){
        if(hasFlag(row,col)) return 'F';
        return '_';
    } else {
        if(data[row][col].hasMine) return 'x';
        if(countMines(row,col)==0) return ' ';
        //return countMines(row,col; should be char, is int!!!
    }
}