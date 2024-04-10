#include "MSSFMLView.h"

//PRIVATE
//===============
void MSSFMLView::generate_points() {
    pointsCloud.resize(board.getBoardWidth() * board.getBoardHeight());
    for(int row=0; row<)
}

void MSSFMLView::set_textures() {
    flagTxt.loadFromFile("flag.jpg");
    flagSprite.setTexture(flagTxt);

    mineTxt.loadFromFile("mine.jpg");
    mineSprite.setTexture(mineTxt);

    fieldRevealed.setRadius(20);
    fieldRevealed.setPointCount(4);
    sf::Color grey(192,192,192,1);
    fieldRevealed.setFillColor(grey);

    field.setRadius(20);
    field.setPointCount(4);
    field.setFillColor(sf::Color::White);
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

//PUBLIC
//===============
MSSFMLView::MSSFMLView(MinesweeperBoard &boardRef) : board(boardRef),boardHeight(boardRef.getBoardHeight()),boardWidth(boardRef.getBoardWidth())
{
    set_title();
    set_textures();
}

void MSSFMLView::draw(sf::RenderWindow &windowRef) {

}