#include "MSSFMLView.h"

#include <iostream>

#define FIELD_SIZE 30

//PRIVATE
//===============
void MSSFMLView::generate_points() {
    //pointsCloud.setPrimitiveType(sf::Points);
    pointsCloud.resize(board.getBoardWidth() * board.getBoardHeight());
    for(int row=0; row<boardHeight; ++row){
        for(int col=0; col<boardWidth; ++col){
            pointsCloud[row*boardWidth+col]=sf::Vector2f(x_off+col*FIELD_SIZE,y_off+row*FIELD_SIZE);
        }
    }
}

void MSSFMLView::set_flag_txt() {
    flagTxt.loadFromFile("flag.png");
    flagSprite.setTexture(flagTxt);
    sf::FloatRect flagRect = flagSprite.getLocalBounds();
    flagSprite.setOrigin( (flagRect.width+flagRect.left)/2,
                          (flagRect.height+flagRect.top)/2);
    flagSprite.setScale(FIELD_SIZE/64.0,FIELD_SIZE/64.0);
}

void MSSFMLView::set_mine_txt() {
    mineTxt.loadFromFile("mine.png");
    mineSprite.setTexture(mineTxt);
    sf::FloatRect mineRect = mineSprite.getLocalBounds();
    mineSprite.setOrigin( (mineRect.width+mineRect.left)/2,
                          (mineRect.height+mineRect.top)/2);
    mineSprite.setScale(FIELD_SIZE/64.0,FIELD_SIZE/64.0);
}

void MSSFMLView::set_field_revealed_txt() {
    fieldRevealed.setRadius(FIELD_SIZE/2.0+3);
    fieldRevealed.setPosition(0,0);
    fieldRevealed.setPointCount(4);
    sf::Color grey(100,100,100,240);
    sf::FloatRect fieldRevRect = fieldRevealed.getLocalBounds();
    fieldRevealed.setFillColor(grey);
    fieldRevealed.setOrigin( (fieldRevRect.width+fieldRevRect.left)/2,
                             (fieldRevRect.height+fieldRevRect.top)/2);
    fieldRevealed.setRotation(45);
}

void MSSFMLView::set_field_txt() {
    field.setRadius(FIELD_SIZE/2.0+5);
    field.setPosition(0,0);
    sf::FloatRect fieldRect = field.getLocalBounds();
    field.setPointCount(4);
    field.setFillColor(sf::Color::White);
    field.setOrigin( (fieldRect.width+fieldRect.left)/2,
                     (fieldRect.height+fieldRect.top)/2);
    field.setRotation(45);
}

void MSSFMLView::set_field_mine_txt() {
    fieldWithMine.setRadius(FIELD_SIZE/2.0+5);
    fieldWithMine.setPosition(0,0);
    sf::FloatRect fieldWithMineRect = fieldWithMine.getLocalBounds();
    fieldWithMine.setPointCount(4);
    sf::Color redWithAlpha(255,0,0,200);
    fieldWithMine.setFillColor(redWithAlpha);
    fieldWithMine.setOrigin( (fieldWithMineRect.width+fieldWithMineRect.left)/2,
                             (fieldWithMineRect.height+fieldWithMineRect.top)/2);
    fieldWithMine.setRotation(45);
}

void MSSFMLView::set_textures() {
    set_flag_txt();
    set_mine_txt();
    set_field_revealed_txt();
    set_field_txt();
    set_field_mine_txt();
}

void MSSFMLView::set_title() {
    font.loadFromFile("VT323-Regular.ttf");
    title.setFont(font);
    title.setString("Minesweeper!");
    title.setCharacterSize(40);
    title.setFillColor(sf::Color::Red);
    sf::FloatRect titleRect=title.getLocalBounds();
    title.setOrigin(
            (titleRect.left + titleRect.width)/2.0f,
            (titleRect.top + titleRect.height)/2.0f
    );
}

void MSSFMLView::draw_field(int row, int col, sf::RenderWindow & win) {
    if(board.isRevealed(row,col)){
        fieldRevealed.setPosition(pointsCloud[row*boardWidth+col].position);
        win.draw(fieldRevealed);
        if(board.getFieldInfo(row,col)=='x'){
            fieldWithMine.setPosition(pointsCloud[(row*boardWidth+col)].position);
            win.draw(fieldWithMine);
            mineSprite.setPosition(pointsCloud[(row*boardWidth+col)].position);
            win.draw(mineSprite);
        } else{
            mineCountText[(board.countMines(row,col))].setPosition(pointsCloud[row*boardWidth+col].position);
            win.draw(mineCountText[board.countMines(row,col)]);
        }
    } else{
        field.setPosition(pointsCloud[row*boardWidth+col].position);
        win.draw(field);
        if(board.hasFlag(row,col)){
            flagSprite.setPosition(pointsCloud[row*boardWidth+col].position);
            win.draw(flagSprite);
        }
    }
}

void MSSFMLView::update_board_state( sf::RenderWindow & win ) {
    for(int row=0; row<boardHeight; ++row){
        for(int col=0; col<boardWidth; ++col){
            draw_field(row, col, win);
        }
    }
}

void MSSFMLView::set_mine_count_text() {
    mineCountText.resize(10);
    sf::FloatRect txtRect;
    for(int index=0; index<10; ++index){
        mineCountText[index]=sf::Text(std::to_string(index),font);
        mineCountText[index].setFillColor(sf::Color::Blue);
        mineCountText[index].setPosition(0,0);
        txtRect = mineCountText[index].getLocalBounds();
        mineCountText[index].setOrigin((txtRect.width+txtRect.left+5)/2,
                                       (txtRect.height+txtRect.top+10)/2);
    }
}

//PUBLIC
//===============
MSSFMLView::MSSFMLView(MinesweeperBoard &boardRef) : board(boardRef),boardWidth(boardRef.getBoardWidth()),boardHeight(boardRef.getBoardHeight())
{
    x_off=90;
    y_off=100;
    generate_points();
    set_title();
    set_textures();
    set_mine_count_text();
}

void MSSFMLView::draw(sf::RenderWindow &windowRef) {
    update_board_state(windowRef);
    title.setPosition(windowRef.getSize().x/2, 30);
    windowRef.draw(title);
    windowRef.draw(pointsCloud);
}

void MSSFMLView::reveal(float x, float y) {
    float pointX, pointY;
    for(int row=0; row<boardHeight; ++row){
        for(int col=0; col<boardWidth; ++col){
            pointX = pointsCloud[row*boardWidth+col].position.x;
            pointY = pointsCloud[row*boardWidth+col].position.y;
            if(x<(pointX+FIELD_SIZE/2.0) && x>(pointX-FIELD_SIZE/2.0) && y<(pointY+FIELD_SIZE/2.0) && y>(pointY-FIELD_SIZE/2.0))
                board.revealField(row,col);
        }
    }
}

void MSSFMLView::flag(float x, float y) {
    float pointX, pointY;
    for(int row=0; row<boardHeight; ++row){
        for(int col=0; col<boardWidth; ++col){
            pointX = pointsCloud[row*boardWidth+col].position.x;
            pointY = pointsCloud[row*boardWidth+col].position.y;
            if(x<(pointX+FIELD_SIZE/2.0) && x>(pointX-FIELD_SIZE/2.0) && y<(pointY+FIELD_SIZE/2.0) && y>(pointY-FIELD_SIZE/2.0))
                board.toggleFlag(row,col);
        }
    }
}