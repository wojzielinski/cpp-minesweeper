#include "MinesweeperBoard.h"
#include "MSSFMLView.h"
#include "MSSFMLController.h"

#include <ctime>
#include <cstdlib>
#include <SFML/Graphics.hpp>

int main() {
    std::srand(std::time(NULL));

    sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper", sf::Style::Close);

    sf::Image icon;
    icon.loadFromFile("icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
/*
    sf::CircleShape circle(10,4);
    sf::FloatRect circleRect=circle.getLocalBounds();
    circle.setFillColor(sf::Color::Yellow);
    circle.setPosition(400,300);
    circle.setOrigin(
            (circleRect.left + circleRect.width)/2.0f,
            (circleRect.top + circleRect.height)/2.0f
    );
*/

    MinesweeperBoard board(22,15,DEBUG);
    MSSFMLView sfmlView(board);
    MSSFMLController sfmlController(sfmlView,board);

    sfmlController.play(window);

    return 0;
}