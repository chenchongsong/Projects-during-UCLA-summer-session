#ifndef ACTOR_H
#define ACTOR_H

class Actor;
class Ice;
class IceMan;

#include "GraphObject.h"
#include "StudentWorld.h"
#include "GameConstants.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

const int TYPE_UNDEFINE = 0;
const int TYPE_BOULDER = 1;
const int TYPE_GOLD = 2;
const int TYPE_BARREL = 3;
const int TYPE_SQUIRT = 4;
const int TYPE_REGULAR_PROTESTER = 5;
const int TYPE_HARDCORE_PROTESTER = 6;


class Actor: public GraphObject { // Base Class
    
  public:
    
    Actor(int imageid, int posx, int posy, Direction dir, double size,
          unsigned int depth, StudentWorld* world)
    : GraphObject(imageid, posx, posy, dir, size, depth), m_world(world) {
        
        setVisible(true);
        m_status = true;
        m_type = 0; // actor type undefined
    }
    virtual ~Actor(){}
    virtual void doSomething() {} // pure virtual
    
    StudentWorld* getWorld() {return m_world;}
    
    bool checkNear(Actor* anotherActor, int dis);

    void moveInDirection();
    void changeDirection();
    bool changeDirectionVertical();
    bool can_go_ahead(Direction dir);
    bool can_up();
    bool can_down();
    bool can_right();
    bool can_left();
    bool can_up(int posx, int posy);
    bool can_down(int posx, int posy);
    bool can_right(int posx, int posy);
    bool can_left(int posx, int posy);
    
    int m_status, m_type, moving_time = 1, m_health = 100;

  private:
    StudentWorld* m_world;
};


class Ice: public Actor {

  public:
    Ice(int posx, int posy, StudentWorld* world): Actor(IID_ICE, posx, posy, right, 0.25, 3, world){}
    ~Ice(){};
    virtual void doSomething();
};


class IceMan: public Actor {

  public:
    IceMan(StudentWorld* world): Actor(IID_PLAYER, 30, 60, right, 1.0, 0, world) {}
    
    virtual void doSomething();
    bool notBoulder(Direction dir);
    //~IceMan();
};



class Barrel: public Actor { // Oil
    
  public:
    Barrel(int posx, int posy, StudentWorld* world);
    void doSomething();
    
    //~Barrel();
};

class Boulder: public Actor {
  public:
    Boulder(int posx, int posy, StudentWorld* world);
    void doSomething();
    
    //~Boulder();
};

class Gold: public Actor {
  public:
    Gold(int posx, int posy, StudentWorld* world);
    void doSomething();
    
    //~Gold();
};

class Sonar: public Actor {

  public:
    Sonar(int posx, int posy, StudentWorld* world);
    void doSomething();
    
    // ~Sonar();
};

class Pool: public Actor {

  public:
    Pool(int posx, int posy, StudentWorld* world);
    void doSomething();
    
    // ~Pool();
};

class Squirt: public Actor {
    
  public:
    Squirt(int posx, int posy, StudentWorld* world, Direction dir);
    void doSomething();
    
    // ~Squirt();
};


class Protester: public Actor {
  public:
    Protester(int IID, StudentWorld* world);
    void doSomething();
    void moveInShort(int posx, int posy);
    bool IceManInSight();

    const int PROTESTER_AWAY = 0;
    const int PROTESTER_LEAVE = 100001;
    const int PROTESTER_START_RESTING = 100002;
    int PROTESTER_FINISH_RESTING;
    int tick_count, max_tick_count;
    int numSquaresToMoveInCurrentDirection;
    int shout_count = 0, vertical_turn_count = 0;

};

class regularProtester: public Protester {
  public:
    regularProtester(StudentWorld* world);

};

class hardcoreProtester: public Protester {
  public:
    hardcoreProtester(StudentWorld* world);

};
#endif // ACTOR_H_
