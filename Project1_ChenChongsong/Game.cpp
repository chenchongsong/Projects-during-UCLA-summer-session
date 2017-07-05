//
//  Game.cpp
//  cs32_project1(2)
//
//  Created by CCS on 29/6/17.
//  Copyright © 2017 CCS. All rights reserved.
//

#include <iostream>
//#include <string>
//#include <cstdlib>
//#include <ctime>
//#include "globals.h"
#include "Player.h"
//#include "Robot.h"
#include "Arena.h"
#include "Game.h"
#include "History.h"

///////////////////////////////////////////////////////////////////////////
//  Game implementations
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nRobots)
{
    if (nRobots > MAXROBOTS)
    {
        std::cout << "***** Trying to create Game with " << nRobots
        << " robots; only " << MAXROBOTS << " are allowed!" << std::endl;
        exit(1);
    }
    
    // Create arena
    m_arena = new Arena(rows, cols);
    
    // Add player
    int rPlayer = 1 + rand() % rows;
    int cPlayer = 1 + rand() % cols;
    m_arena->addPlayer(rPlayer, cPlayer);
    
    // Populate with robots
    while (nRobots > 0)
    {
        int r = 1 + rand() % rows;
        int c = 1 + rand() % cols;
        // Don't put a robot where the player is
        if (r == rPlayer  &&  c == cPlayer)
            continue;
        m_arena->addRobot(r, c);
        nRobots--;
    }
}

Game::~Game()
{
    delete m_arena;
}

void Game::play()
{
    Player* p = m_arena->player();
    if (p == nullptr)
    {
        m_arena->display("");
        return;
    }
    std::string msg = "";
    do
    {
        m_arena->display(msg);
        msg = "";
        std::cout << std::endl;
        std::cout << "Move (u/d/l/r/su/sd/sl/sr/c/q/h): ";
        std::string action;
        getline(std::cin,action);
        if (action.size() == 0)
            p->stand();
        else
        {
            switch (action[0])
            {
                default:   // if bad move, nobody moves
                    std::cout << '\a' << std::endl;  // beep
                    continue;
                case 'q':
                    return;
                case 'c':  // computer moves player
                    msg = p->takeComputerChosenTurn();
                    break;
                case 'u':
                case 'd':
                case 'l':
                case 'r':
                    p->move(decodeDirection(action[0]));
                    break;
                case 'h': //modified
                    m_arena->history().display();
                    std::cout << std::endl << "Press enter to continue.";
                    std::cin.ignore(10000,'\n');
                    continue;
                case 's':
                    if (action.size() < 2)  // if no direction, nobody moves
                    {
                        std::cout << '\a' << std::endl;  // beep
                        continue;
                    }
                    switch (action[1])
                {
                    default:   // if bad direction, nobody moves
                        std::cout << '\a' << std::endl;  // beep
                        continue;
                    case 'u':
                    case 'd':
                    case 'l':
                    case 'r':
                        if (p->shoot(decodeDirection(action[1])))
                            msg = "Hit!";
                        else
                            msg = "Missed!";
                        break;
                }
                    break;
            }
        }
        m_arena->moveRobots();
    } while ( ! m_arena->player()->isDead()  &&  m_arena->robotCount() > 0);
    m_arena->display(msg);
}

