#include "MinesweeperBoard.h"
#include "MSBoardTextView.h"
#include "MSTextController.h"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define FIELD_SIZE 30

int main() {

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

    sf::SoundBuffer duckBuffer;
    duckBuffer.loadFromFile("kaczuszka.wav");
    sf::Sound duck;
    duck.setBuffer(duckBuffer);

    sf::Font font;
    if (!font.loadFromFile("VT323-Regular.ttf"))
        return EXIT_FAILURE;

    sf::Text title("Minesweeper!", font, 40);
    title.setFillColor(sf::Color::Red);
    sf::FloatRect titleRect=title.getLocalBounds();
    title.setOrigin(
            (titleRect.left + titleRect.width)/2.0f,
            (titleRect.top + titleRect.height)/2.0f
            );

    sf::VertexArray fields(sf::Quads);

    int width=15,height=10;
    float posy=100, posx=200;
    for(int row=0; row<height; ++row){
        posx=0;
        for(int col=0; col<width; ++col){
            fields.append(sf::Vertex(sf::Vector2f(posx,posy),sf::Color::White));
            fields.append(sf::Vertex(sf::Vector2f(posx,posy+FIELD_SIZE),sf::Color::Red));
            fields.append(sf::Vertex(sf::Vector2f(posx+FIELD_SIZE,posy+FIELD_SIZE),sf::Color::Green));
            fields.append(sf::Vertex(sf::Vector2f(posx+FIELD_SIZE,posy),sf::Color::Blue));
            posx+=40;
        }
        posy+=40;
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::MouseMoved)
                circle.setPosition(event.mouseMove.x, event.mouseMove.y);
            if(event.type == sf::Event::MouseButtonPressed)
                duck.play();
        }

        window.clear(sf::Color::Black);

        window.draw(bgSprite);

        title.setPosition(400,30);
        window.draw(title);



        window.draw(fields);
        window.draw(circle);
        window.display();
    }

    std::srand(std::time(NULL));
    //MinesweeperBoard board;
    //MinesweeperBoard testBoardD(10,10,DEBUG);
    //MinesweeperBoard testBoardE(10,10,EASY);
    //MinesweeperBoard testBoardN(10,10,NORMAL);
    MinesweeperBoard testBoardH(10,10,EASY);
    MSBoardTextView MStestBoardH(testBoardH);
    MSTextController ctrl (testBoardH, MStestBoardH);
    //board.debug_display();
/*
    //TESTING FIELDS REVEALING aka AUTO-PLAY
    testBoardH.debug_display();
    do{
        int rRow = rand() % testBoardH.getBoardHeight();
        int rCol = rand() % testBoardH.getBoardWidth();
        std::cout << "(" << rRow << "," << rCol << ")" << std::endl;
        testBoardH.revealField(rRow, rCol);
        MStestBoardH.display();
    }while(testBoardH.getGameState()==RUNNING);
    testBoardH.debug_display();
    //END OF TEST
*/ // testBoardH.debug_display();
    ctrl.play();
    //testBoardE.debug_display();
    //testBoardN.debug_display();
    //testBoardH.debug_display();
    return 0;
}

/*
 SFML USAGE

 #include <SFML/Graphics.hpp>

 int main() {
    sf::RenderWindow win {...};

    while(win.isOpen()) {
        //BLOCK 1
        sf::Event event;         //tworzenie eventu
        while(win.pull(event)){
            if...
        }                       //stworzenie pętli, która dziala dopoki nie zamkniemy okna

        //BLOCK 2
    }
 }

 sf::CircleShape - kółko lub dowolny wielokąt foremny wpisany w okrąg, argument to średnica
 sf::CircleShape c{50};     //kółko
 sf::CircleShape tr{20,3};  //triangle
 */