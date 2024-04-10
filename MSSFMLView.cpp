#include "MSSFMLView.h"

#include <iostream>
#define X_OFF 100
#define Y_OFF 100
#define FIELD_SIZE 30

//PRIVATE
//===============
void MSSFMLView::generate_points() {
    pointsCloud.setPrimitiveType(sf::Points);
    pointsCloud.resize(board.getBoardWidth() * board.getBoardHeight());
    for(int row=0; row<boardHeight; ++row){
        for(int col=0; col<boardWidth; ++col){
            pointsCloud[row*boardWidth+col]=sf::Vertex(sf::Vector2f(X_OFF+col*FIELD_SIZE,Y_OFF+row*FIELD_SIZE),sf::Color::Cyan);
        }
    }
}

void MSSFMLView::set_textures() {
    flagTxt.loadFromFile("flag.png");
    flagSprite.setTexture(flagTxt);
    sf::FloatRect flagRect = flagSprite.getLocalBounds();
    flagSprite.setOrigin( (flagRect.width+flagRect.left)/2,
                          (flagRect.height+flagRect.top)/2);
    flagSprite.setScale(0.2,0.2);


    mineTxt.loadFromFile("mine.png");
    mineSprite.setTexture(mineTxt);
    sf::FloatRect mineRect = mineSprite.getLocalBounds();
    mineSprite.setOrigin( (mineRect.width+mineRect.left)/2,
                     (mineRect.height+mineRect.top)/2);
    mineSprite.setScale(0.2,0.2);

    fieldRevealed.setRadius(20);
    fieldRevealed.setPosition(0,0);
    fieldRevealed.setPointCount(4);
    sf::Color grey(100,100,100,240);
    sf::FloatRect fieldRevRect = fieldRevealed.getLocalBounds();
    fieldRevealed.setFillColor(grey);
    fieldRevealed.setOrigin( (fieldRevRect.width+fieldRevRect.left)/2,
                     (fieldRevRect.height+fieldRevRect.top)/2);
    fieldRevealed.setRotation(45);

    field.setRadius(20);
    field.setPosition(0,0);
    sf::FloatRect fieldRect = field.getLocalBounds();
    field.setPointCount(4);
    field.setFillColor(sf::Color::White);
    field.setOrigin( (fieldRect.width+fieldRect.left)/2,
                     (fieldRect.height+fieldRect.top)/2);
    field.setRotation(45);
}

void MSSFMLView::set_title() {
    font.loadFromFile("VT323-Regular.ttf");
    title.setFont(font);
    title.setString("O");
    title.setCharacterSize(40);
    title.setFillColor(sf::Color::Red);
    sf::FloatRect titleRect=title.getLocalBounds();
    title.setOrigin(
            (titleRect.left + titleRect.width)/2.0f,
            (titleRect.top + titleRect.height)/2.0f
    );
}

void MSSFMLView::update_board_state( sf::RenderWindow & win ) {
    for(int row=0; row<boardHeight; ++row){
        for(int col=0; col<boardWidth; ++col){
            if(board.isRevealed(row,col)){
                fieldRevealed.setPosition(pointsCloud[row*boardWidth+col].position);
                win.draw(fieldRevealed);
                if(board.getFieldInfo(row,col)=='x'){
                    mineSprite.setPosition(pointsCloud[(row+col)].position);
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
MSSFMLView::MSSFMLView(MinesweeperBoard &boardRef) : board(boardRef),boardHeight(boardRef.getBoardHeight()),boardWidth(boardRef.getBoardWidth())
{
    generate_points();
    set_title();
    set_textures();
    set_mine_count_text();
}

void MSSFMLView::draw(sf::RenderWindow &windowRef) {
    update_board_state(windowRef);
    title.setPosition(0, 0);
    windowRef.draw(title);
    windowRef.draw(pointsCloud);
}

void MSSFMLView::reveal(float x, float y) {
    float pointX, pointY;
    for(int row=0; row<boardHeight; ++row){
        for(int col=0; col<boardWidth; ++col){
            pointX = pointsCloud[row*boardWidth+col].position.x;
            pointY = pointsCloud[row*boardWidth+col].position.y;
            if(x<(pointX+FIELD_SIZE/2) && x>(pointX-FIELD_SIZE/2) && y<(pointY+FIELD_SIZE/2) && y>(pointY-FIELD_SIZE/2))
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
            if(x<(pointX+FIELD_SIZE/2) && x>(pointX-FIELD_SIZE/2) && y<(pointY+FIELD_SIZE/2) && y>(pointY-FIELD_SIZE/2))
                board.toggleFlag(row,col);
        }
    }
}