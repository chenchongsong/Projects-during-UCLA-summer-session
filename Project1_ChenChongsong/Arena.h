//
//  Arena.hpp
//  cs32_project1(2)
//
//  Created by CCS on 29/6/17.
//  Copyright © 2017 CCS. All rights reserved.
//

#ifndef Arena_h
#define Arena_h



#include <string>
#include "globals.h"

class Robot;
class History;
class Arena;
class Player;

class Arena
{
public:
    // Constructor/destructor
    Arena(int nRows, int nCols);
    ~Arena();
    
    // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     robotCount() const;
    int     nRobotsAt(int r, int c) const;
    void    display(std::string msg) const;
    
    // Mutators
    bool   addRobot(int r, int c);
    bool   addPlayer(int r, int c);
    void   damageRobotAt(int r, int c);
    bool   moveRobots();
    History& history();
    
private:
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Robot*  m_robots[MAXROBOTS];
    int     m_nRobots;
    History* m_history;
};

#endif /* Arena_hpp */
