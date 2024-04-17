#include "MSSFMLController.h"
#include "MSSFMLView.h"
#include "MinesweeperBoard.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

void MSSFMLController::set_assets() {
    flagBuff.loadFromFile("flagSound.wav");
    flagSound.setBuffer(flagBuff);
    flagSound.setVolume(10);

    winBuff.loadFromFile("winSound.wav");
    winSound.setVolume(50);
    winSound.setBuffer(winBuff);

    bombBuff.loadFromFile("bombSound.wav");
    bombSound.setBuffer(bombBuff);
    bombSound.setVolume(50);

    clickBuff.loadFromFile("clickSound.wav");
    clickSound.setBuffer(clickBuff);
}

void MSSFMLController::reveal(int x, int y) {
    sf::Vector2i pos;
    int field_size = view.get_field_size();
    for(int row=0; row<boardHeight; ++row){
        for(int col=0; col<boardWidth; ++col){
            pos = view.get_point_pos(row, col);
            if(x<(pos.x+field_size/2) && x>(pos.x-field_size/2) && y<(pos.y+field_size/2) && y>(pos.y-field_size/2))
                board.revealField(row,col);
        }
    }
}

void MSSFMLController::flag(int x, int y) {
    sf::Vector2i pos;
    int field_size = view.get_field_size();
    for(int row=0; row<boardHeight; ++row){
        for(int col=0; col<boardWidth; ++col){
            pos = view.get_point_pos(row, col);
            if(x<(pos.x+field_size/2) && x>(pos.x-field_size/2) && y<(pos.y+field_size/2) && y>(pos.y-field_size/2))
                board.toggleFlag(row,col);
        }
    }
}



MSSFMLController::MSSFMLController(MSSFMLView &viewRef, MinesweeperBoard &boardRef) : board(boardRef), view(viewRef),boardWidth(boardRef.getBoardWidth()),boardHeight(boardRef.getBoardHeight())
{
    set_assets();
}

void MSSFMLController::play(sf::RenderWindow & window) {
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button==sf::Mouse::Left) {
                    reveal(event.mouseButton.x, event.mouseButton.y);
                    if(board.getGameState()==FINISHED_WIN) {
                        winSound.play();
                    }
                    if(board.getGameState()==FINISHED_LOSS){
                        bombSound.play();
                    }
                    clickSound.play();
                }
                if(event.mouseButton.button==sf::Mouse::Right) {
                    flag(event.mouseButton.x, event.mouseButton.y);
                    flagSound.play();
                }
            }
        }
        view.draw(window);
        window.display();
    }
}