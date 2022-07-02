#ifndef BOARDCODE_H
#define BOARDCODE_H
#include<SFML/Graphics.hpp>
void make_board(sf::RenderWindow& board_win);
void disp_icon_i(sf::RenderWindow& board_win, float plx_i, float ply_i, sf::CircleShape& icon_i);
void setCoods(sf::Vector2f coods[]);
#endif
