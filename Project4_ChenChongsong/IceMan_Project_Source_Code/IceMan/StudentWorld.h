#ifndef STUDENTWORLD_H
#define STUDENTWORLD_H

class StudentWorld;

int MAX(int A, int B);
int MIN(int A, int B);
int ABS(int x);
int ToNode(int x, int y);

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <vector>
#include <cstdio>
#include <ctime>
#include <cstdlib>


// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld {

public:
    StudentWorld(std::string assetDir);
    ~StudentWorld();
    
    virtual int init();
    void init_Ice_IceMan_Protester();
    void init_Barrel_Gold_Boulder();
    void init_Sonar_Pool();
    
    virtual int move();
    virtual void cleanUp();
    IceMan* getPlayer();
    void updateDisplayText();
    
    void incHealth(int delta) { m_health += delta;}
    void incWater(int delta) { m_water += delta;}
    void incGold(int delta) { m_gold += delta;}
    void incLeftOil(int delta) {left_oil += delta;}
    void incSonar(int delta) {m_sonar += delta;}
    
    int getHealth() {return m_health;}
    int getWater() {return m_water;}
    int getGold() {return m_gold;}
    int getLeftOil() {return left_oil;}
    int getSonar() {return m_sonar;}

    bool soundTriggered[100];
    Ice* m_ice[128][128];
    std::vector<Actor*> ActorList;

private:
    
    IceMan* m_player;
    int m_health, m_water, m_gold, m_sonar;
    int left_oil, left_gold, m_boulder;
    int num_protester;
    
};

#endif // STUDENTWORLD_H_



// unsigned int getLives() const;
// void decLives();
// void incLives();
// unsigned int getScore() const;
// unsigned int getLevel() const;
// void increaseScore(unsigned int howMuch);
// void setGameStatText(string text);
// bool getKey(int& value);
// void playSound(int soundID);
