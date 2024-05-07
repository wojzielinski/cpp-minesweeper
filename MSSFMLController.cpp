#include "MSSFMLController.h"
#include "MSSFMLView.h"
#include "MinesweeperBoard.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

//PRIVATE
//===============

//Prepares audio assets for SFML app
void MSSFMLController::set_assets() {
    flagBuff.loadFromFile("flagSound.wav");     //sound on flag toggling
    flagSound.setBuffer(flagBuff);
    flagSound.setVolume(10);

    winBuff.loadFromFile("winSound.wav");       //sound played after winning
    winSound.setVolume(50);
    winSound.setBuffer(winBuff);

    bombBuff.loadFromFile("bombSound.wav");     //sound played after revealing mine
    bombSound.setBuffer(bombBuff);
    bombSound.setVolume(50);

    clickBuff.loadFromFile("clickSound.wav");   //sound played on click
    clickSound.setBuffer(clickBuff);
}

//Translate cursor position to field on board and reveal field
void MSSFMLController::reveal(int x, int y) {
    sf::Vector2i pos;
    int field_size = view.get_field_size();
    for(int row=0; row<boardHeight; ++row){             //compare click position with every field on board
        for(int col=0; col<boardWidth; ++col){
            pos = view.get_point_pos(row, col);
            if(x<(pos.x+field_size/2) && x>(pos.x-field_size/2) && y<(pos.y+field_size/2) && y>(pos.y-field_size/2))
                board.revealField(row,col);
        }
    }
}

//Translate cursor position to field on board and toggle flag
void MSSFMLController::flag(int x, int y) {
    sf::Vector2i pos;
    int field_size = view.get_field_size();
    for(int row=0; row<boardHeight; ++row){             //compare click position with every field on board
        for(int col=0; col<boardWidth; ++col){
            pos = view.get_point_pos(row, col);
            if(x<(pos.x+field_size/2) && x>(pos.x-field_size/2) && y<(pos.y+field_size/2) && y>(pos.y-field_size/2))
                board.toggleFlag(row,col);
        }
    }
    view.update_flags_rem_text();                       //update "flags remaining" label
}

//Checks if position of click (x,y) is inside given bounds
bool MSSFMLController::clickInBounds(sf::FloatRect bounds, int x, int y) const {
    if(x >= bounds.left && x <= (bounds.left+bounds.width) &&
        y >= bounds.top && y <= (bounds.top+bounds.height))
        return true;
    return false;
}

//Checks if the game is finished and restarts game if "restart" button has been clicked
void MSSFMLController::trigIfFinished (int x, int y) {
    if(board.getGameState()==FINISHED_WIN) {
        winSound.play();
        if(clickInBounds(view.getRButtonBound(), x, y)){
            board.restart();
        }
    }
    if(board.getGameState()==FINISHED_LOSS){
        bombSound.play();
        if(clickInBounds(view.getRButtonBound(), x, y)){
            board.restart();
        }
    }
}

//PUBLIC
//===============

//SFML Controller constructor - initializes board and view references, sets assets
MSSFMLController::MSSFMLController(MSSFMLView &viewRef, MinesweeperBoard &boardRef) : board(boardRef), view(viewRef),boardWidth(boardRef.getBoardWidth()),boardHeight(boardRef.getBoardHeight())
{
    set_assets();
}

//Run game in loop as long as window is open
void MSSFMLController::play(sf::RenderWindow & window) {
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))                                     //record event type
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button==sf::Mouse::Left) {                 //reveal field on LMB
                    reveal(event.mouseButton.x, event.mouseButton.y);
                    clickSound.play();
                    trigIfFinished(event.mouseButton.x, event.mouseButton.y);
                }
                if(event.mouseButton.button==sf::Mouse::Right) {                //toggle flag on RMB
                    flag(event.mouseButton.x, event.mouseButton.y);
                    flagSound.play();
                }
            }
        }
        view.draw(window);
        window.display();
    }
}