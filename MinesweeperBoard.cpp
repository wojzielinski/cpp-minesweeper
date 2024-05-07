#include "MinesweeperBoard.h"

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <cassert>

//PRIVATE
//===============

//Change location of a mine on position (row,col) - used if the first field revealed has a mine
void MinesweeperBoard::change_location(int row, int col) {
    int newRow, newCol;
    do {
        newRow = rand() % rows;
        newCol = rand() % cols;
    } while (data[newRow][newCol].hasMine); //generate new coords until field without mine is found
    data[newRow][newCol].hasMine = true;
    data[row][col].hasMine = false;
    data[row][col].isRevealed = true;
    firstMove=false;
    if(isFinishedWin()) state = FINISHED_WIN;
}

//Display field data - for debug mode
void MinesweeperBoard::display_field(int row, int col) const{
    std::cout << "[" << (data[row][col].hasMine?"M":".");
    std::cout << (data[row][col].isRevealed?"o":".");
    std::cout << (data[row][col].hasFlag?"f":".");
    std::cout << "] ";
}

//Checks if coords match board size
bool MinesweeperBoard::field_on_board(int row, int col) const{
    if(row>=getBoardHeight() || row<0 || col<0 || col>=getBoardWidth()) { return false; }
    return true;
}

//Set initial mines' positions if debug mode is chosen
void MinesweeperBoard::gen_debug() {
    int row=0,col=0;
    while(row<rows && col<cols){        //place mines on diagonal
        data[row][col].hasMine = true;
        col++;
        row++;
    }
    col=0;
    row=0;
    while(col<cols){                    //place mines on top 1st row
        data[row][col].hasMine = true;
        col++;
    }
    col=0;
    row=0;
    while(row<rows){                    //place mines in 1st column, every 2 rows
        data[row][col].hasMine = true;
        row+=2;
    }
}

//Generate mines on board, nMines = numbers of mines to generate
void MinesweeperBoard::gen_rand_mines(int nMines) {
    gen_random_fields(nMines);
    assert(getMineCount()==nMines);     //check if mines were generated successfully
}

//As described above
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

//Generates mines depending on Gamemode
void  MinesweeperBoard::generate_mines(GameMode gamemode){
    switch (gamemode) {
        case EASY:          //EASY mode = 10% of fields have mines
            gen_rand_mines(std::ceil(0.1*rows*cols));
            mode = EASY;
            break;
        case NORMAL:        //NORMAL mode = 20% of fields have mines
            gen_rand_mines(std::ceil(0.2*rows*cols));
            mode = NORMAL;
            break;
        case HARD:          //HARD mode = 30% of fields have mines
            gen_rand_mines(std::ceil(0.3*rows*cols));
            mode = HARD;
            break;
        case DEBUG:         //DEBUG mode - generate mines as described in gen_debug()
            gen_debug();
            mode = DEBUG;
            break;
    }
}

//Checks if field has mine
bool MinesweeperBoard::hasMine(int row, int col) const {
    if(field_on_board(row,col) && data[row][col].hasMine) return true;
    return false;
}

//Checks if game is finished
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

//Reveals fields recursively as long as revealed field has no mines around
void MinesweeperBoard::recursiveRevealField(int row, int col) {
    if(countMines(row,col)!=0) return;
    for(int tempRow=row-1; tempRow<=row+1; ++tempRow){
        for(int tempCol=col-1; tempCol<=col+1; ++tempCol){
            if(field_on_board(tempRow, tempCol)) {
                if (tempRow != row || tempCol != col) revealField(tempRow, tempCol);
            }
        }
    }
}

//Create empty board
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

//Set predefined fields for no-arguments constructor
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

//Constructor without arguments - for developer,debug use only
MinesweeperBoard::MinesweeperBoard(){
    cols = 7;
    rows = 6;
    set_fields();
    state = RUNNING;
    mode = DEBUG;
    firstMove = true;
}

//Board constructor - creates a board of defined size (width x height) and gamemode
MinesweeperBoard::MinesweeperBoard(int width, int height, GameMode gMode){
    cols = width;                       //set dimensions
    rows = height;
    set_empty(width,height);            //set empty board
    mode = gMode;                       //set gamemode
    generate_mines(gMode);    //generate mines
    flagsRemaining = getMineCount();    //set flags counter
    state = RUNNING;                    //set game state
    firstMove = true;                   //set firstMove flag
}

//Restart game - set empty board, generate mines, reset game state and firstMove flag
void MinesweeperBoard::restart(){
    set_empty(cols,rows);
    generate_mines(mode);
    flagsRemaining = getMineCount();
    state = RUNNING;
    firstMove = true;
}

//Print board state - for debug purposes only
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

//Get board width - simple getter
int MinesweeperBoard::getBoardWidth() const {
    return cols;
}

//Get board height - simple getter
int MinesweeperBoard::getBoardHeight() const {
    return rows;
}

//Get total amount of mines on board
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

//Count mines around field - return -1 if field is already revealed or outside board
int MinesweeperBoard::countMines(int row, int col) const {
    if(!field_on_board(row, col) || !isRevealed(row,col)){
        return -1;
    }
    int counter=0;
    for(int tempRow=row-1; tempRow<=row+1; tempRow++){
        for(int tempCol=col-1; tempCol<=col+1; tempCol++){
            if(field_on_board(tempRow, tempCol) && (tempRow!=row || tempCol!=col)){
                if(hasMine(tempRow, tempCol)) counter++;
            }
        }
    }
    return counter;
}

//Checks if field is on board and has flag
bool MinesweeperBoard::hasFlag(int row, int col) const {
    if(!field_on_board(row, col) || !data[row][col].hasFlag || isRevealed(row,col)) return false;
    return true;
}

//Toggles flag at field on coords (row,col)
void MinesweeperBoard::toggleFlag(int row, int col) {
    if(!field_on_board(row,col)) return;        //Do nothing if those
    if(getGameState() != RUNNING) return;       //conditions are
    if(isRevealed(row,col)) return;             //met

    if(hasFlag(row,col)){
        data[row][col].hasFlag = false;         //toggle hasFlag
        ++flagsRemaining;                       //update flagsRemaining
    } else {
        data[row][col].hasFlag = true;
        --flagsRemaining;
    }
}

//Reveal field at coords (row,col)
void MinesweeperBoard::revealField(int row, int col) {
    if(!field_on_board(row,col)) return;        //"Do nothing" conditions
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
    if(mode!=DEBUG && firstMove) {              //Debug mode case
        change_location(row,col);
        return;
    }
    data[row][col].isRevealed=true;
    state = FINISHED_LOSS;
    firstMove = false;
}

//Check if field at coords (row,col) is revealed
bool MinesweeperBoard::isRevealed(int row, int col) const {
    if(field_on_board(row,col) && data[row][col].isRevealed) return true;
    return false;
}

//Get current game state - simple getter
GameState MinesweeperBoard::getGameState() const {
    return state;
}

//Get field status - info returned by this function will be visible for a player
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

//Gets amount of remaining flags (amount of mines without flags) - simple getter
int MinesweeperBoard::getFlagsRemaining() const {
    return flagsRemaining;
}