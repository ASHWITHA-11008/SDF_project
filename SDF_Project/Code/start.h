#ifndef START_H
#define START_H
#include<iostream>
#include<SFML/Graphics.hpp>

void input(sf::Window &window, sf::Event &event, sf::RectangleShape box, std::string &str, sf::Text &text, sf::Font *font, int x, int y, bool sel);

void setBox(sf::RectangleShape &box, sf::Texture *texture, float scaleX, float scaleY, int x, int y, sf::Color outColor);

void setBox(sf::RectangleShape &box, int x, int y, sf::Color fillColor, sf::Color outColor, int t);

void setText(sf::Text &text, sf::Font *font, std::string str, int x, int y, int size, sf::Color color);

void setSprite(sf::Sprite &sprite, float scaleX, float scaleY, int x, int y, sf::Texture *texture);

void msgDisplay(std::string str);


typedef struct 
{
    int num_players;
    std::string Name[4];
} Inputs;

Inputs Run(bool& run);







#endif