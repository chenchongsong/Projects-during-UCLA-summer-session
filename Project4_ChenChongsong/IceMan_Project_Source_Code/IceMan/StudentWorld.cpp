#include "StudentWorld.h"
#include <cstring>
//#include "GameWorld.h"

using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp

int MIN(int A, int B) {return A<B?A:B;}
int MAX(int A, int B) {return A>B?A:B;}
int ABS(int x) {return x > 0 ? x : -x;}
//int ToNode(int x, int y) {return x * 64 + }

StudentWorld::StudentWorld(std::string assetDir)
: GameWorld(assetDir) {
    
    // initialize variables
    m_health = 100;
    m_water = 0;
    m_gold = 0;
    m_sonar = 1;
    left_gold = MAX(5 - getLevel() / 2, 2);
    left_oil = MIN(2 + getLevel(), 21);
    m_boulder = MIN(getLevel() / 2 + 2, 9);
}

StudentWorld::~StudentWorld() {
    cleanUp();
}

//========================= init() =========================

void StudentWorld::init_Ice_IceMan_Protester() {
    // Iceman
    m_player = new IceMan(this);
    ActorList.push_back(m_player);
    
    // Ice
    for (int i = 0; i < 64; i++)
        for (int j = 60; j < 64; j++)
            m_ice[i][j] = nullptr;
    for (int i = 0; i < 64; i++)
        for (int j = 0; j < 60; j++) {
            m_ice[i][j] = new Ice(i, j, this);
            ActorList.push_back(m_ice[i][j]);
        }
    for (int i = 30; i < 34; i++)
        for (int j = 4; j < 60; j++) {
            m_ice[i][j]->setVisible(false);
            m_ice[i][j]->m_status = false;
            m_ice[i][j] = nullptr;
        }
    
    // Protester
    ActorList.push_back(new regularProtester(this));
    num_protester = 1;
}

void StudentWorld::init_Barrel_Gold_Boulder() {

    srand(10086);
    for (int i=0; i<left_oil; i++)
        ActorList.push_back(new Barrel(rand()%60, rand()%50, this));
    
    for (int i=0; i<left_gold; i++)
        ActorList.push_back(new Gold(rand()%60, rand()%50, this));
    
    for (int i=0; i<m_boulder; i++)
        ActorList.push_back(new Boulder(rand()%60, rand()%50+1, this));
}

void StudentWorld::init_Sonar_Pool() {
    ActorList.push_back(new Sonar(0, 60, this));
    ActorList.push_back(new Pool(30, 30, this));
}

int StudentWorld::init() {

    // initialize variables
    m_health = 100;
    m_water += 5;
    m_sonar = 1;
    left_gold = MAX(5 - getLevel() / 2, 2);
    left_oil = MIN(2 + getLevel(), 21);
    m_boulder = MIN(getLevel() / 2 + 2, 9);
    
    init_Ice_IceMan_Protester();
    init_Barrel_Gold_Boulder();
    init_Sonar_Pool();
    
    // sound
    for (int i=0; i<100; i++)
        soundTriggered[i] = false;
    if (getLevel())
        soundTriggered[SOUND_THEME] = true;
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move() {
    
    updateDisplayText();
    
    for (int i = 0; i < ActorList.size(); i++)
        ActorList[i]->doSomething();
    
    // remove dead actors from ActorList
    for (int i=0; i < ActorList.size(); i++) {
        Actor* tmp = ActorList[i];
        
        if (tmp->m_status == false) {
            
            if (tmp->m_type == TYPE_HARDCORE_PROTESTER || tmp->m_type == TYPE_REGULAR_PROTESTER)
                num_protester--;
            
            delete ActorList[i];
            ActorList.erase(ActorList.begin() + i);
            i--;
        }
    }
    
    for (int i=0; i<100; i++)
        if (soundTriggered[i]) {
            playSound(i);
            soundTriggered[i] = false;
        }
    
    // add new protesters
    if (num_protester < getLevel()+2) {
        int tmp = rand()%150;
        if (tmp == 1) {
            ActorList.push_back(new regularProtester(this));
            num_protester++;
        }
        if (tmp == 2) {
            ActorList.push_back(new hardcoreProtester(this));
            num_protester++;
        }
    }

    if (left_oil == 0) {
        playSound(SOUND_FINISHED_LEVEL);
        return GWSTATUS_FINISHED_LEVEL;
    }
    if (getHealth() == 0) {
        playSound(SOUND_PLAYER_GIVE_UP);
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp() {
    
    for (int i = 0; i < ActorList.size(); i++)
        delete ActorList[i];
    ActorList.clear();
}

IceMan* StudentWorld::getPlayer() {
    return m_player;
}

void StudentWorld::updateDisplayText() {
    int level = getLevel();
    std::string txt = "Lvl: " + std::to_string(level);
    
    int lives = getLives();
    txt = txt + " Lives: " + std::to_string(lives);
    
    int health = getHealth();
    txt = txt + " Health: " + std::to_string(health);

    int water = getWater();
    txt = txt + " Water: " + std::to_string(water);
    
    int gold = getGold();
    txt = txt + " Gold: " + std::to_string(gold);
    
    int oil = getLeftOil();
    txt = txt + " Oil_Left: " + std::to_string(oil);
    
    int sonar = getSonar();
    txt = txt + " Sonar: " + std::to_string(sonar);
    
    int score = getScore();
    txt = txt + " Scr: " + std::to_string(score);
    
    setGameStatText(txt);
}
