#ifndef SAPER_MSSFMLVIEW_H
#define SAPER_MSSFMLVIEW_H

#include "MinesweeperBoard.h"

#include <SFML/Graphics.hpp>

class MSSFMLView {
    MinesweeperBoard & board;
    const int boardWidth;
    const int boardHeight;
    int x_off;
    int y_off;

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
    sf::CircleShape fieldWithMine;

    void generate_points();
    void set_textures();
    void set_title();
    void set_mine_count_text();
    void set_flag_txt();
    void set_mine_txt();
    void set_field_revealed_txt();
    void set_field_txt();
    void set_field_mine_txt();

    void update_board_state( sf::RenderWindow & win );
    void draw_field( int row, int col, sf::RenderWindow & win );

public:
    explicit MSSFMLView( MinesweeperBoard & boardRef);
    void draw( sf::RenderWindow & windowRef );
    void reveal( float x, float y );
    void flag( float x, float y );
};


#endif //SAPER_MSSFMLVIEW_H
