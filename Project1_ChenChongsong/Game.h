//
//  Game.hpp
//  cs32_project1(2)
//
//  Created by CCS on 29/6/17.
//  Copyright © 2017 CCS. All rights reserved.
//

#ifndef Game_h
#define Game_h

class Game;

//#include <iostream>
//#include <string>
//#include <cstdlib>
//#include <ctime>
//#include "globals.h"
//#include "Player.h"
//#include "Robot.h"
//#include "Arena.h"
class Arena;
//#include "Game.h"
//#include "History.h"

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nRobots);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Arena* m_arena;
};

#endif /* Game_h */
