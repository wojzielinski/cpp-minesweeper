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

    MinesweeperBoard board(20,15,DEBUG);
    MSSFMLView sfmlView(board);
    MSSFMLController sfmlController(sfmlView,board);

    sfmlController.play(window);

    return 0;
}