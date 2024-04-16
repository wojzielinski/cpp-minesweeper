#include "MinesweeperBoard.h"
#include "MSSFMLView.h"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define FIELD_SIZE 30

int main() {
    std::srand(std::time(NULL));

    sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper");

    sf::CircleShape circle(10,4);
    sf::FloatRect circleRect=circle.getLocalBounds();
    circle.setFillColor(sf::Color::Yellow);
    circle.setPosition(400,300);
    circle.setOrigin(
            (circleRect.left + circleRect.width)/2.0f,
            (circleRect.top + circleRect.height)/2.0f
    );

    sf::Texture bgImage;
    if (!bgImage.loadFromFile("saper_bg.jpg"))
        return EXIT_FAILURE;
    sf::Sprite bgSprite(bgImage);

    sf::SoundBuffer flagBuff;
    flagBuff.loadFromFile("flagSound.wav");
    sf::Sound flagSound;
    flagSound.setBuffer(flagBuff);

    sf::SoundBuffer winBuff;
    winBuff.loadFromFile("winSound.wav");
    sf::Sound winSound;
    winSound.setBuffer(winBuff);

    sf::SoundBuffer bombBuff;
    bombBuff.loadFromFile("bombSound.wav");
    sf::Sound bombSound;
    bombSound.setBuffer(bombBuff);

    sf::SoundBuffer clickBuff;
    clickBuff.loadFromFile("clickSound.wav");
    sf::Sound clickSound;
    clickSound.setBuffer(clickBuff);

    MinesweeperBoard board(22,15,EASY);
    MSSFMLView sfmlView(board);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::MouseMoved)
                circle.setPosition(event.mouseMove.x, event.mouseMove.y);
            if(event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button==sf::Mouse::Left) {
                    sfmlView.reveal(event.mouseButton.x, event.mouseButton.y);
                    if(board.getGameState()==FINISHED_WIN) {
                        std::cout << "WYGRANA" << std::endl;
                        winSound.play();
                    }
                    if(board.getGameState()==FINISHED_LOSS){
                        std::cout << "PRZEGRANA" << std::endl;
                        bombSound.play();
                    }
                    clickSound.play();
                }
                if(event.mouseButton.button==sf::Mouse::Right) {
                    sfmlView.flag(event.mouseButton.x, event.mouseButton.y);
                    flagSound.play();
                }
            }
        }

        window.clear(sf::Color::Black);

        window.draw(bgSprite);
        sfmlView.draw(window);
        window.display();
    }

    return 0;
}