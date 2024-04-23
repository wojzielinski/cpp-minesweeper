#include "MSSFMLView.h"

#include <iostream>

//PRIVATE
//===============
void MSSFMLView::generate_points() {
    //pointsCloud.setPrimitiveType(sf::Points);
    pointsCloud.resize(board.getBoardWidth() * board.getBoardHeight());
    for(int row=0; row<boardHeight; ++row){
        for(int col=0; col<boardWidth; ++col){
            pointsCloud[row*boardWidth+col] = sf::Vector2f(x_off+col*field_size,y_off+row*field_size);
        }
    }
}

void MSSFMLView::set_restart_button() {
    restartButton.setSize(sf::Vector2f(120,40));
    restartButton.setFillColor(sf::Color(255,191,0));
    restartButton.setOutlineColor(sf::Color::Black);
    restartButton.setOutlineThickness(2);
    restartButton.setOrigin((restartButton.getLocalBounds().left+restartButton.getLocalBounds().width)/2,
                            (restartButton.getLocalBounds().top+restartButton.getLocalBounds().height)/2);
    restartText.setString("RESTART");
    restartText.setFont(font);
    restartText.setCharacterSize(40);
    restartText.setFillColor(sf::Color::Black);
    restartText.setOrigin((restartText.getLocalBounds().left+restartText.getLocalBounds().width)/2,
                            (restartText.getLocalBounds().top+restartText.getLocalBounds().height)/2);
    restartButton.setPosition(400,570);
    restartText.setPosition(restartButton.getPosition().x, restartButton.getPosition().y-10);
}

void MSSFMLView::set_flag_txt() {
    flagTxt.loadFromFile("flag.png");
    flagSprite.setTexture(flagTxt);
    sf::FloatRect flagRect = flagSprite.getLocalBounds();
    flagSprite.setOrigin( (flagRect.width+flagRect.left)/2,
                          (flagRect.height+flagRect.top)/2);
    flagSprite.setScale(field_size/64.0,field_size/64.0);
}

void MSSFMLView::set_mine_txt() {
    mineTxt.loadFromFile("mine.png");
    mineSprite.setTexture(mineTxt);
    sf::FloatRect mineRect = mineSprite.getLocalBounds();
    mineSprite.setOrigin( (mineRect.width+mineRect.left)/2,
                          (mineRect.height+mineRect.top)/2);
    mineSprite.setScale(field_size/64.0,field_size/64.0);
}

void MSSFMLView::set_field_revealed_txt() {
    fieldRevealed.setRadius(field_size/2.0+3);
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
    field.setRadius(field_size/2.0+5);
    field.setPosition(0,0);
    sf::FloatRect fieldRect = field.getLocalBounds();
    field.setPointCount(4);
    field.setFillColor(sf::Color::White);
    field.setOrigin( (fieldRect.width+fieldRect.left)/2,
                     (fieldRect.height+fieldRect.top)/2);
    field.setRotation(45);
}

void MSSFMLView::set_field_mine_txt() {
    fieldWithMine.setRadius(field_size/2.0+5);
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
    bgImage.loadFromFile("saper_bg.jpg");
    bgSprite.setTexture(bgImage);

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
    sf::FloatRect titleRect = title.getLocalBounds();
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

void MSSFMLView::set_flags_count_text() {
    std::string str = "Flags remaining: ";
    str.append(std::to_string(board.getFlagsRemaining()));
    font.loadFromFile("VT323-Regular.ttf");
    flagsCounter.setFont(font);
    flagsCounter.setString(str);
    flagsCounter.setCharacterSize(25);
    flagsCounter.setFillColor(sf::Color(255, 191,0));
    flagsCounter.setPosition(x_off-field_size/2,y_off-50);
}

//PUBLIC
//===============
MSSFMLView::MSSFMLView(MinesweeperBoard &boardRef) : board(boardRef),boardWidth(boardRef.getBoardWidth()),boardHeight(boardRef.getBoardHeight())
{
    field_size=30;
    x_off=90;
    y_off=100;
    generate_points();
    set_title();
    set_textures();
    set_mine_count_text();
    set_flags_count_text();
    set_restart_button();
}

void MSSFMLView::draw(sf::RenderWindow &windowRef) {
    windowRef.clear(sf::Color::Black);
    windowRef.draw(bgSprite);
    update_board_state(windowRef);
    title.setPosition(windowRef.getSize().x/2, 30);
    if(board.getGameState()==FINISHED_LOSS) {
        title.setString("Game Over!");
        title.setOrigin(
                (title.getLocalBounds().left + title.getLocalBounds().width) / 2.0f,
                (title.getLocalBounds().top + title.getLocalBounds().height) / 2.0f
        );
        windowRef.draw(restartButton);
        windowRef.draw(restartText);
    }
    if(board.getGameState()==FINISHED_WIN) {
        title.setString("You won!");
        title.setOrigin(
                (title.getLocalBounds().left + title.getLocalBounds().width) / 2.0f,
                (title.getLocalBounds().top + title.getLocalBounds().height) / 2.0f
        );
        windowRef.draw(restartButton);
        windowRef.draw(restartText);
    }
    windowRef.draw(title);
    windowRef.draw(flagsCounter);
    //windowRef.draw(pointsCloud);
}

sf::Vector2i MSSFMLView::get_point_pos(int row, int col) const {
    sf::Vector2i position(  pointsCloud[row*boardWidth+col].position.x,
                            pointsCloud[row*boardWidth+col].position.y);
    return position;
}

int MSSFMLView::get_field_size() const {
    return field_size;
}

sf::FloatRect MSSFMLView::getRButtonBound() const {
    return restartButton.getGlobalBounds();
}

void MSSFMLView::update_flags_rem_text() {
    std::string str = "Flags remaining: ";
    str.append(std::to_string(board.getFlagsRemaining()));
    flagsCounter.setString(str);
}