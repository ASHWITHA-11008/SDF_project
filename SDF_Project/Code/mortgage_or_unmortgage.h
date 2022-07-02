#ifndef MORTGAGE_OR_UNMORTGAGE_H
#define	MORTGAGE_OR_UNMORTGAGE_H
#include"players.h"
#include<SFML/Graphics.hpp>
void print_places(int *num, sf::Text &text);
int set_id(sf::Text &playerInput);
bool check_id(int id, player pl);
void mortgage(player pl, int player_chance);
void unmortgage(player pl, int player_chance);

#endif // !MORTGAGE_OR_UNMORTGAGE_H

