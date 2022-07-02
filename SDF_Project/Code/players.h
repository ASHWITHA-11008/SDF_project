#ifndef PLAYERS_H
#define PLAYERS_H
class player {
public:
	std::string playerName; //need code to recieve input.
	int playerProps[40]; //{6, 7, 9, 11}
	int numbProps = 0;
	int playerHouses[40];//playerhouses[i] refers to the number of houses in playerprops[i].//{1, 2, 3, 0}
	int money;
	int playerMortProps[40] = { 0 };

	//For number of cities in a colony
	int count[9] = { 0 };
	const int max_count[8] = { 2,3,3,3,3,3,3,2 };
};
#endif // !PLAYERS_H
