//
// Created by c on 4/17/24.
//

#ifndef SAPER_MSSFMLCONTROLLER_H
#define SAPER_MSSFMLCONTROLLER_H

#include "MinesweeperBoard.h"
#include "MSSFMLView.h"

#include <SFML/Audio.hpp>

class MSSFMLController {
    MinesweeperBoard & board;
    MSSFMLView & view;
    const int boardWidth;
    const int boardHeight;

    //Assets
    sf::SoundBuffer flagBuff;
    sf::Sound flagSound;
    sf::SoundBuffer winBuff;
    sf::Sound winSound;
    sf::SoundBuffer bombBuff;
    sf::Sound bombSound;
    sf::SoundBuffer clickBuff;
    sf::Sound clickSound;

    void set_assets();
    void reveal(int x, int y);
    void flag(int x, int y);
    bool clickInBounds(sf::FloatRect bounds, int x, int y) const;
    void trigIfFinished(int x, int y);
public:
    MSSFMLController( MSSFMLView & viewRef , MinesweeperBoard & boardRef);
    void play(sf::RenderWindow & window);
};


#endif //SAPER_MSSFMLCONTROLLER_H
