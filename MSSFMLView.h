#ifndef SAPER_MSSFMLVIEW_H
#define SAPER_MSSFMLVIEW_H

#include "MinesweeperBoard.h"

#include <SFML/Graphics.hpp>

class MSSFMLView {
    MinesweeperBoard & board;

    const int boardWidth;
    const int boardHeight;

    sf::VertexArray pointsCloud;

    sf::Font font;
    sf::Text title;

    std::vector<sf::Text> mineCountText;
    sf::Texture flagTxt;
    sf::Sprite flagSprite;
    sf::Texture mineTxt;
    sf::Sprite mineSprite;
    sf::CircleShape fieldRevealed;
    sf::CircleShape field;

    void generate_points();
    void set_textures();
    void set_title();
    void set_mine_count_text();

    void update_board_state( sf::RenderWindow & win );


public:
    MSSFMLView( MinesweeperBoard & boardRef );
    void draw( sf::RenderWindow & windowRef );
    void reveal( float x, float y );
    void flag( float x, float y );

};


#endif //SAPER_MSSFMLVIEW_H
