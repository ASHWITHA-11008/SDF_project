#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <array>
#include <SFML/Graphics.hpp>
#include "start.h"
#include "diceRoller.h"
#include "BoardCode.h"
#include "community_chest.h"
#include "playing_cards.h"
#include "chance.h"

enum class places
{
  GO = 0,
  GUWAHATI,
  COMCH1,
  BHUBANESHWAR,
  TAXREF,
  CHENCENTR,
  PANAJI,
  AGRA,
  CHANCE1,
  VADODARA,
  JAIL,
  LUDHIANA,
  ELEC,
  PATNA,
  BHOPAL,
  HOWRSTAT,
  INDORE,
  COMCH2,
  NAGPUR,
  KOCHI,
  FREEPARK,
  LUCKNOW,
  CHANCE2,
  CHANDIGARH,
  JAIPUR,
  DELHISTAT,
  PUNE,
  WATER,
  HYDERABAD,
  AHMEDABAD,
  GOTOJAIL,
  KOLKATA,
  CHENNAI,
  COMCH3,
  BANGALORE,
  MUMBAISTAT,
  CHANCE3,
  DELHI,
  TAX,
  MUMBAI
};

enum colony
{
  SHAMROCK = 0,
  MINERAL_GREEN,
  RED,
  PINK,
  CREAM,
  YELLOW,
  GRASS_GREEN,
  BLUE
};

enum class cardType
{
  MOVE,
  MONEY
};

std::vector<std::vector<int>> group{{{1, 3}, {6, 7, 9}, {11, 13, 14}, {16, 18, 19}, {21, 23, 24}, {26, 28, 29}, {31, 32, 34}, {37, 39}, {5, 15, 25, 35}}};

class player
{
public:
  std::string playerName; //need code to recieve input.
  int playerProps[40];    //{6, 7, 9, 11}
  int numbProps = 0;
  int playerHouses[40]; //playerhouses[i] refers to the number of houses in playerprops[i].//{1, 2, 3, 0}
  int money;
  sf::CircleShape icon;
  //For number of cities in a colony
  int count[9] = {0};
  const int max_count[8] = {2, 3, 3, 3, 3, 3, 3, 2};
};

class Board // SINGLETON
{
  Board()
  {
    window.create(sf::VideoMode(1440, 960), "Monopoly");
  }
  Board(const Board &) = delete;
  void operator=(Board &) = delete;

public:
  sf::RenderWindow window;
  static Board *getInstance()
  {
    static Board *instance;
    if (instance == nullptr)
      instance = new Board();
    return instance;
  }
};

class card
{
  cardType type;
  int pos;
  int money;

public:
  void setType(cardType _type)
  {
    type = _type;
  }
  void setPosition(int _pos)
  {
    pos = _pos;
  }
  int getPosition()
  {
    return pos;
  }
  void setMoney(int _money)
  {
    money = _money;
  }
  int getMoney()
  {
    return money;
  }
  cardType getType()
  {
    return type;
  }
};



int Find_property(int i)
{
  int j;
  for (j = 0; j < 8; j++)
  {
    auto find = std::find(begin(group[j]), end(group[j]), i);

    if (find != std::end(group[j]))
    {
      break;
    }
  }
  return j;
}

template <std::size_t s>
bool Find_card(int i, std::array<int, s> arr)
{
  auto find = std::find(arr.begin(), arr.end(), i);
  if (find != arr.end())
    return true;
  else
    return false;
}

int main()
{
  bool run = 0;
  Inputs ip;
  ip = Run(run); // implements code in start.cpp
  int size = ip.num_players;
  player pl[size];
  if (size == 2)
  {
    pl[0].icon.setFillColor(sf::Color(30, 130, 76));
    pl[0].icon.setRadius(16.0);
    pl[1].icon.setFillColor(sf::Color(37, 116, 169));
    pl[1].icon.setRadius(16.0);
  }
  if (size == 3)
  {
    pl[0].icon.setFillColor(sf::Color(30, 130, 76));
    pl[0].icon.setRadius(16.0);
    pl[1].icon.setFillColor(sf::Color(37, 116, 169));
    pl[1].icon.setRadius(16.0);
    pl[2].icon.setFillColor(sf::Color(140, 20, 252));
    pl[2].icon.setRadius(16.0);
  }
  if (size == 4)
  {
    pl[0].icon.setFillColor(sf::Color(30, 130, 76));
    pl[0].icon.setRadius(16.0);
    pl[1].icon.setFillColor(sf::Color(37, 116, 169));
    pl[1].icon.setRadius(16.0);
    pl[2].icon.setFillColor(sf::Color(140, 20, 252));
    pl[2].icon.setRadius(16.0);
    pl[3].icon.setFillColor(sf::Color(211, 84, 0));
    pl[3].icon.setRadius(16.0);
  }

  sf::Vector2f coods[40];

  setCoods(coods);

  float plx[size], ply[size];
  int owners[40] = {0}; //{0, 1, 0, 0, 0, ...0}<--40 elem,

  bool plbuy = false;
  //	intitialisation
  for (int q = 0; q < 4; q++)
  {
    plx[q] = coods[0].x;
    ply[q] = coods[0].y;
  }
  int rent[6][40] = {{//0 houses
                      0, 6, 0, 8, 0, 0, 10, 10, 0, 10, 0, 14, 0, 14, 16, 0, 15, 0, 16, 20, 0, 22, 0, 22, 24, 0, 22, 0, 32, 28, 0, 32, 32, 0, 33, 0, 0, 32, 0, 35},

                     //1 house
                     {0, 20, 0, 20, 0, 0, 30, 30, 0, 30, 0, 50, 0, 0, 60, 50, 70, 0, 70, 80, 0, 90, 0, 90, 100, 0, 110, 0, 120, 110, 0, 130, 130, 0, 150, 0, 0, 175, 0, 200},

                     //2 houses
                     {0, 40, 0, 60, 0, 0, 90, 90, 0, 90, 0, 150, 0, 150, 250, 0, 200, 0, 200, 220, 0, 250, 0, 250, 300, 0, 330, 0, 360, 330, 0, 390, 390, 0, 450, 0, 0, 500, 0, 600},

                     //3 houses
                     {0, 90, 0, 180, 0, 0, 270, 270, 0, 270, 0, 450, 0, 450, 500, 0, 550, 0, 550, 600, 0, 700, 0, 700, 750, 0, 800, 0, 850, 800, 0, 900, 900, 0, 1000, 0, 0, 1100, 0, 1400},

                     // 4 houses
                     {0, 160, 0, 320, 0, 0, 400, 400, 0, 400, 0, 625, 0, 625, 700, 0, 750, 0, 750, 800, 0, 875, 0, 875, 925, 0, 975, 0, 1025, 975, 0, 1100, 1100, 0, 1200, 0, 0, 1300, 0, 1700},

                     // 5 houses / hotel
                     {0, 250, 0, 450, 0, 0, 550, 550, 0, 550, 0, 750, 0, 750, 900, 0, 950, 0, 950, 1000, 0, 1050, 0, 1050, 1100, 0, 1150, 0, 1200, 1150, 0, 1275, 1275, 0, 1400, 0, 0, 1500, 0, 2000}};

  int houses[40] = {0};

  int house_cost[40] = {0};

  int numrot[size];

  int money[size];

  card chanceCard[13];
  card comChCard[14];

  chanceCard[2].setType(cardType::MOVE);
  chanceCard[2].setPosition(39);

  chanceCard[3].setType(cardType::MOVE);
  chanceCard[3].setPosition(0);

  chanceCard[4].setType(cardType::MOVE);
  chanceCard[4].setPosition(24);

  chanceCard[5].setType(cardType::MONEY);
  chanceCard[5].setMoney(-35);

  chanceCard[6].setType(cardType::MONEY);
  chanceCard[6].setMoney(50);

  chanceCard[7].setType(cardType::MONEY);
  chanceCard[7].setMoney(20);

  chanceCard[8].setType(cardType::MONEY);
  chanceCard[8].setMoney(50);

  chanceCard[9].setType(cardType::MOVE);
  chanceCard[9].setPosition(10);

  chanceCard[10].setType(cardType::MONEY);
  chanceCard[10].setMoney(-15);

  chanceCard[11].setType(cardType::MOVE);
  chanceCard[11].setPosition(37);

  chanceCard[12].setType(cardType::MONEY);
  chanceCard[12].setMoney(150);
  //start writing comch cards
  comChCard[0].setType(cardType::MOVE);
  comChCard[0].setPosition(0);

  comChCard[1].setType(cardType::MONEY);
  comChCard[1].setMoney(200);

  comChCard[2].setType(cardType::MONEY);
  comChCard[2].setMoney(-50);

  comChCard[3].setType(cardType::MONEY);
  comChCard[3].setMoney(50);

  comChCard[4].setType(cardType::MOVE);
  comChCard[4].setPosition(10);

  comChCard[5].setType(cardType::MONEY);
  comChCard[5].setMoney(100);

  comChCard[6].setType(cardType::MONEY);
  comChCard[6].setMoney(20);

  comChCard[7].setType(cardType::MONEY);
  comChCard[7].setMoney(100);

  comChCard[8].setType(cardType::MONEY);
  comChCard[8].setMoney(-100);

  comChCard[9].setType(cardType::MONEY);
  comChCard[9].setMoney(-50);

  comChCard[10].setType(cardType::MONEY);
  comChCard[10].setMoney(25);

  comChCard[11].setType(cardType::MONEY);
  comChCard[11].setMoney(10);

  comChCard[12].setType(cardType::MONEY);
  comChCard[12].setMoney(100);

  comChCard[13].setType(cardType::MOVE);
  comChCard[13].setPosition(39); //has to be updated, as of now, write GO TO MUMBAI.

  int oldBlock[size];
  int dicecall = 0;
  int flag[size];

  std::array<int, 3> communityChest = {2, 17, 33};
  std::array<int, 3> chance = {8, 22, 36};
  std::array<int, 4> corners = {0, 10, 20, 30};

  for (int i = 0; i < size; i++)
  {
    numrot[i] = 0;
    money[i] = 2000;
    oldBlock[i] = 0;
    flag[i] = 0;
  }
  if (run)
  {

    //############ Events in Board  ################

    Board *board = Board::getInstance();
    while ((board->window).isOpen())
    {

      sf::Event event;
      make_board(board->window); // implements code from BoardCode.cpp
      for (int disp_iter = 0; disp_iter < size; disp_iter++)
      {
        disp_icon_i(board->window, plx[disp_iter], ply[disp_iter], pl[disp_iter].icon);
      }

      while ((board->window).pollEvent(event))
      {

        if (event.type == sf::Event::Closed)
        {
          (board->window).close();
        }
      }
      ((board)->window).display();

      int i=0;
      while (0)
      { // replace 0 with number of alive > 1

        dicecall = rollDice(); // implements code from diceRoller.cpp

      //##############  Moving icons #################

        for (int move_incr = 1; move_incr <= dicecall; move_incr++) 
        {
          if ((oldBlock[i] + move_incr) == 40)
          {
            oldBlock[i] = 0;
            numrot[i]++;
            flag[i] = 1;
          }
          plx[i] = coods[oldBlock[i] + move_incr].x;
          ply[i] = coods[oldBlock[i] + move_incr].x;
          oldBlock[i] += move_incr;
          disp_icon_i(board->window, plx[i], ply[i], pl[i].icon);
        }
        if (flag[i] == 1)
        {
          money[i] += 200;
          flag[i] = 0;
        }

        //############ Build Houses and Hotels  ################

        bool buildWin_Open = 0;

        //if he clicks on build,
        buildWin_Open = 1;

        // a new window opens with all the properties which has count==max_count
        while (buildWin_Open) //write for sfml window
        {
          // if he clicks on property p and num of houses n
          int p, n;

          int find = Find_property(p);
          if (pl[i].count[find] == pl[p].max_count[find])
          {
            // pl[i] can build houses
            pl[i].playerHouses[p] += n;
            houses[p] += 1;
            pl[i].money -= n * house_cost[p];
          }
        }

        //############ Sell Houses and Hotels  ################

        bool SellWin_Open = 0;

        //if he clicks on sell,
        SellWin_Open = 1;

        // a new window opens with all the properties he owns and num of houses>0
        while (SellWin_Open) //write for sfml window
        {
          // if he clicks on property p and num of houses n
          int p, n;

          pl[i].playerHouses[p] -= n;
          houses[p] -= 1;
          pl[i].money += n * house_cost[p];
        }

        //############ Buy property  ################  // From playing_cards.cpp
        for (int iter = 0; iter < 40; iter++)
        {
          if (coods[iter].x == plx[i] && coods[iter].y == ply[i])
          {
            if (owners[iter] == 0)
            {
              if (Find_card(iter, communityChest) || Find_card(iter, chance) || Find_card(iter, corners))
              {
                plbuy = false;
              }
              //  community_chest(1);
              if (plbuy == true)
              {
                owners[iter] = (i + 1);
                //draw as this person's property
                pl[i].playerProps[pl[i].numbProps] = iter;
                pl[i].playerHouses[pl[i].numbProps] = 0;
                pl[i].numbProps++;
                pl[i].count[Find_property(iter)]++;
                //deduct money
                plbuy = false;
              }
            }
            //let player 1 has properties 9, 13, 17, 21, 22, 24. He wants to build a house on 22, first check the element number of 22 (player[0].playerProps[5])in player1.playerProps, let it be q, then when he builds a house there, we need to do houses[22]++ and pl1.playerHouses[q(5)]++. Please note this.
            //pl[0].playerProps = {9, 13, 17, 21, 22, 24}. while running a loop, run the loop till pl[i].numbProps

            //############ Pay rent  ################

            if (owners[iter] >= 1)
            {
              if (owners[iter] != (i + 1))
              {
                if (iter == 12 || iter == 27) //Utilities
                {
                  if (owners[12] == owners[27])
                  {
                    int utilrent1 = 10 * (dicecall);
                    money[owners[iter] - 1] += utilrent1;
                    money[i] -= utilrent1;
                  }
                  else
                  {
                    int utilrent2 = 4 * (dicecall);
                    money[owners[iter] - 1] += utilrent2;
                    money[i] -= utilrent2;
                  }
                }
                if (iter == 5 || iter == 15 || iter == 25 || iter == 35) //Railways
                {
                  if (pl[owners[iter] - 1].count[8] == 1)
                  {
                    money[owners[iter] - 1] += 25;
                    money[i] -= 25;
                  }
                  if (pl[owners[iter] - 1].count[8] == 2)
                  {
                    money[owners[iter] - 1] += 50;
                    money[i] -= 50;
                  }
                  if (pl[owners[iter] - 1].count[8] == 3)
                  {
                    money[owners[iter] - 1] += 100;
                    money[i] -= 100;
                  }
                  if (pl[owners[iter] - 1].count[8] == 4)
                  {
                    money[owners[iter] - 1] += 200;
                    money[i] -= 200;
                  }
                }
                for (int j = 0; j < 5; j++)//Properties
                {
                  if (houses[iter] == j)
                  {
                    money[owners[iter] - 1] += rent[j][iter];
                    money[i] -= rent[j][iter];
                  }
                }
              }
            }

            //############ Community Chest  ################

            if (owners[iter] == 0)
            {
              if (Find_card(iter, communityChest))
              {

                //community chest cards random choose
                int randgen = (rand() % 14);
                community_chest(randgen); //  From community_chest.cpp
                if (comChCard[randgen].getType() == cardType::MOVE)
                {
                  plx[i] = coods[comChCard[randgen].getPosition()].x;
                  ply[i] = coods[comChCard[randgen].getPosition()].y;
                }
                if (randgen == 0) // Both move and money
                {
                  money[i] += 200;
                  pl[i].money += 200;
                }
                if (comChCard[randgen].getType() == cardType::MONEY)
                {
                  money[i] += comChCard[randgen].getMoney();
                  pl[i].money += comChCard[randgen].getMoney();
                }
              }
              if (iter == 4)
              {
                money[i] += 150;
              }

              //############ Chance card  ################

              if (Find_card(iter, chance))
              {

                chance_card(dicecall); //From chance.cpp
                if (chanceCard[dicecall].getType() == cardType::MOVE)
                {
                  plx[i] = coods[chanceCard[dicecall].getPosition()].x;
                  ply[i] = coods[chanceCard[dicecall].getPosition()].y;
                }
                if (dicecall == 3)
                {
                  money[i] += 200;
                  pl[i].money += 200;
                }
                if (chanceCard[dicecall].getType() == cardType::MONEY)
                {
                  money[i] += chanceCard[dicecall].getMoney();
                  pl[i].money += chanceCard[dicecall].getMoney();
                }
              }
              if (iter == 30)
              {
                plx[i] = coods[10].x;
                ply[i] = coods[10].y;
              }
              if (iter == 38) //Tax
              {
                money[i] -= 75;
              }
            }

            if (i == (size - 1))
              i = 0;
            else
              i++;
          }
        }
      }
    }
  }
  return 0;
}
