#include "Actor.h"
#include "StudentWorld.h"
#include <cstdio>
#include <cstring>
#include <queue>

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

//========================= Actor =========================
bool Actor::checkNear(Actor* anotherActor, int dis){
    // to check whether anotherActor is within
    // a radius of "dis" from this actor
    return ABS(anotherActor->getX() - getX()) + ABS(anotherActor->getY() - getY()) <= dis;
    return true;
}

bool Actor::can_up() {
    if (getY() >= 60)
        return false;
    for (int i = getX(); i < getX()+4; i++)
        if (getWorld()->m_ice[i][getY()+4] != nullptr)
            return false;
    return true;
}
bool Actor::can_down() {
    if (getY() <= 0)
        return false;
    for (int i = getX(); i < getX()+4; i++)
        if (getWorld()->m_ice[i][getY()-1] != nullptr)
            return false;
    return true;
}
bool Actor::can_right() {
    if (getX() >= 60)
        return false;
    for (int j = getY(); j < getY()+4; j++)
        if (getWorld()->m_ice[getX()+4][j] != nullptr)
            return false;
    return true;
    
}
bool Actor::can_left() {
    if (getX() <= 0)
        return false;
    for (int j = getY(); j < getY()+4; j++)
        if (getWorld()->m_ice[getX()-1][j] != nullptr)
            return false;
    return true;
}
bool Actor::can_go_ahead(Direction dir) {
    if (dir == up) return can_up();
    if (dir == down) return can_down();
    if (dir == right) return can_right();
    if (dir == left) return can_left();
    return false;
}
//////////////////////////////////////////////////////////////////
bool Actor::can_up(int posx, int posy) {
    if (posy >= 60)
        return false;
    for (int i = posx; i < posx+4; i++)
        if (getWorld()->m_ice[i][posy+4] != nullptr)
            return false;
    return true;
}
bool Actor::can_down(int posx, int posy) {
    if (posy <= 0)
        return false;
    for (int i = posx; i < posx+4; i++)
        if (getWorld()->m_ice[i][posy-1] != nullptr)
            return false;
    return true;
}
bool Actor::can_right(int posx, int posy) {
    if (posx >= 60)
        return false;
    for (int j = posy; j < posy+4; j++)
        if (getWorld()->m_ice[posx+4][j] != nullptr)
            return false;
    return true;
    
}
bool Actor::can_left(int posx, int posy) {
    if (posx <= 0)
        return false;
    for (int j = posy; j < posy+4; j++)
        if (getWorld()->m_ice[posx-1][j] != nullptr)
            return false;
    return true;
}
//////////////////////////////////////////////////////////////////
void Actor::changeDirection() {
    std::vector<GraphObject::Direction> direction_list;
    if (getDirection() != up && can_up())
        direction_list.push_back(up);
    if (getDirection() != down && can_down())
        direction_list.push_back(down);
    if (getDirection() != right && can_right())
        direction_list.push_back(right);
    if (getDirection() != left && can_left())
        direction_list.push_back(left);
    srand(time(0));
    setDirection(direction_list[rand() % direction_list.size()]);
}

bool Actor::changeDirectionVertical() {
    std::vector<GraphObject::Direction> direction_list;
    if (getDirection() == up || getDirection() == down) {
        if (can_right())
            direction_list.push_back(right);
        if (can_left())
            direction_list.push_back(left);
    }
    else { // left or right
        if (can_up())
            direction_list.push_back(up);
        if (can_down())
            direction_list.push_back(down);
    }
    if (direction_list.size() == 0) return false; // cannot turn vertically (no change in direction)
    srand(time(0));
    setDirection(direction_list[rand() % direction_list.size()]);
    return true;
}

void Actor::moveInDirection() {
    if (getDirection() == up) moveTo(getX(), getY()+1);
    if (getDirection() == down) moveTo(getX(), getY()-1);
    if (getDirection() == right) moveTo(getX()+1, getY());
    if (getDirection() == left) moveTo(getX()-1, getY());
}

//========================= Ice =========================

void Ice::doSomething() {
    
    if (getWorld()->getHealth() == 0)
        return;
    
    int tmpx = getWorld()->getPlayer()->getX();
    int tmpy = getWorld()->getPlayer()->getY();
    
    // set ice as invisible when it is covered by the iceman
    if (tmpx <= getX() && getX() <= tmpx + 3)
        if (tmpy <= getY() && getY() <= tmpy+3) {
            
            setVisible(false);
            getWorld()->soundTriggered[SOUND_DIG] = true;
            getWorld()->m_ice[getX()][getY()] = nullptr;
            m_status = false;
        }
}

//========================= Ice Man =========================

bool IceMan::notBoulder(Direction dir) { // iceman cannot move whenever there is a boulder

    for (int i=0; i<getWorld()->ActorList.size(); i++) {
        Actor* tmp = getWorld()->ActorList[i];
        int tmpx = tmp->getX();
        int tmpy = tmp->getY();
        
        if (tmp->m_type == TYPE_BOULDER) { // is boulder
            if (dir == up && ABS(tmpx-getX())<4 && tmpy>getY() && tmpy-getY() <= 4)
                return false; // a boulder is in the way (upwards)

            if (dir == down && ABS(tmpx-getX()) < 4 && getY()>tmpy && getY()-tmpy <= 4)
                return false; // a boulder is in the way (downwards)
            
            if (dir == right && ABS(tmpy-getY()) < 4 && tmpx>getX() && tmpx-getX() <= 4)
                return false; // a boulder is in the way (rightwards)
            
            if (dir == left && ABS(tmpy-getY()) < 4 && getX()>tmpx && getX()-tmpx <= 4)
                return false; // a boulder is in the way (leftwards)
        }
    }
    return true;
}

void IceMan::doSomething() {
    
    if (getWorld()->getHealth() == 0)
        return;
    int ch;
    if (getWorld()->getKey(ch) == true) {
        
        //user hit a key this tick!
        switch(ch) {
            case KEY_PRESS_UP:
                if (getDirection() == up)
                    moveTo(getX(), getY() + (getY() < 60 && notBoulder(up)));
                else
                    setDirection(up);
                break;
            
            case KEY_PRESS_DOWN:
                if (getDirection() == down)
                    moveTo(getX(), getY() - (getY() > 0 && notBoulder(down)) );
                else
                    setDirection(down);
                break;
            
            case KEY_PRESS_RIGHT:
                if (getDirection() == right)
                    moveTo(getX() + (getX() < 60 && notBoulder(right)), getY());
                else
                    setDirection(right);
                break;
            
            case KEY_PRESS_LEFT:
                if (getDirection() == left)
                    moveTo(getX() - (getX() > 0 && notBoulder(left)), getY());
                else
                    setDirection(left);
                break;
            case KEY_PRESS_TAB:
                if (getWorld()->getGold() > 0) {
                    getWorld()->incGold(-1);
                    Gold* tmp_gold = new Gold(getX(), getY(), getWorld());
                    tmp_gold->m_status = 2; // thrown
                    getWorld()->ActorList.push_back(tmp_gold);
                }
                break;
            case 'z': // use sonar kits
                if (getWorld()->getSonar() == 0)
                    break;
                
                getWorld()->soundTriggered[SOUND_SONAR] = true;
                getWorld()->incSonar(-1);
                for (int i=0; i<getWorld()->ActorList.size(); i++) {
                    
                    Actor* tmp = getWorld()->ActorList[i];
                    if (tmp->m_type != TYPE_GOLD && tmp->m_type != TYPE_BARREL)
                        continue;
                    
                    if (checkNear(tmp, 30)) // if gold or barrel within a radius of 13
                        tmp->setVisible(true);
                }
                break;
            case 'Z': // use sonar kits
                if (getWorld()->getSonar() == 0)
                    break;
                
                getWorld()->soundTriggered[SOUND_SONAR] = true;
                getWorld()->incSonar(-1);
                for (int i=0; i<getWorld()->ActorList.size(); i++) {
                    
                    Actor* tmp = getWorld()->ActorList[i];
                    if (tmp->m_type != TYPE_GOLD && tmp->m_type != TYPE_BARREL)
                        continue;
                    
                    if (checkNear(tmp, 30)) // if gold or barrel within a radius of 13
                        tmp->setVisible(true);
                }
                break;
            case KEY_PRESS_SPACE:
                if (getWorld()->getWater() == 0)
                    break;
                getWorld()->incWater(-1);
                getWorld()->soundTriggered[SOUND_PLAYER_SQUIRT] = true;
                if (getDirection() == up && !can_up()) break;
                if (getDirection() == down && !can_down()) break;
                if (getDirection() == right && !can_right()) break;
                if (getDirection() == left && !can_left()) break;
                int tmpx = getX(), tmpy = getY();
                if (getDirection() == up) tmpy += 4;
                if (getDirection() == down) tmpy -= 4;
                if (getDirection() == right) tmpx += 4;
                if (getDirection() == left) tmpx -= 4;

                getWorld()->ActorList.push_back(new Squirt(tmpx, tmpy, getWorld(), getDirection()));
                
        }
    }
}

//========================= Barrel =========================

Barrel::Barrel(int posx, int posy, StudentWorld* world)
: Actor(IID_BARREL, posx, posy, right, 1.0, 2, world) {
    setVisible(false);
    m_type = TYPE_BARREL;
}

void Barrel::doSomething() {
    
    if (getWorld()->getHealth() == 0)
        return;

    if (checkNear(getWorld()->getPlayer(), 4)) // when the iceman is within a radius of 4 from barrel
        setVisible(true);

    if (checkNear(getWorld()->getPlayer(), 3)) {
        m_status = false;
        getWorld()->soundTriggered[SOUND_FOUND_OIL] = true;
        getWorld()->increaseScore(1000);
        getWorld()->incLeftOil(-1);
    }
}

//========================= Gold =========================

Gold::Gold(int posx, int posy, StudentWorld* world)
:Actor(IID_GOLD, posx, posy, right, 1.0, 2, world)  {
    
    setVisible(false);
    m_type = TYPE_GOLD;
}

void Gold::doSomething() {
    
    if (getWorld()->getHealth() == 0)
        return;
    
    if (m_status == 1) { // can only be picked up by iceman
        
        if (checkNear(getWorld()->getPlayer(), 4))
            setVisible(true);
        if (checkNear(getWorld()->getPlayer(), 3)) {
            m_status = false;
            getWorld()->soundTriggered[SOUND_GOT_GOODIE] = true;
            getWorld()->increaseScore(10);
            getWorld()->incGold(1);
        }
        return;
    }
    
    // status >= 2
    if (m_status < 100) { // in volatile state, can only be picked up by protesters
        m_status++;
        setVisible(true);
        for (int i=0; i<getWorld()->ActorList.size(); i++) {
            
            Actor* tmp = getWorld()->ActorList[i];
            if (tmp->m_type == TYPE_REGULAR_PROTESTER && checkNear(tmp, 3)) {
                getWorld()->soundTriggered[SOUND_PROTESTER_FOUND_GOLD] = true;
                getWorld()->increaseScore(25);
                tmp->m_status = 100001; // PROTESTER_LEAVE
                
                m_status = false; // the Gold being picked up
                setVisible(false);
                break;
            }
            if (tmp->m_type == TYPE_HARDCORE_PROTESTER && checkNear(tmp, 3)) {
                getWorld()->soundTriggered[SOUND_PROTESTER_FOUND_GOLD] = true;
                getWorld()->increaseScore(50);
                tmp->m_status = 100002; // PROTESTER_START_RESTING
                
                m_status = false; // the Gold being picked up
                setVisible(false);
                break;
            }
        }
        return;
    }
    
    // when m_status == 100
    m_status = false;
    getWorld()->increaseScore(10);
}

//========================= Boulder =========================

Boulder::Boulder(int posx, int posy, StudentWorld* world)
:Actor(IID_BOULDER, posx, posy, down, 1.0, 1, world)  {

    setVisible(true);
    m_type = TYPE_BOULDER; // mark actor type as boulder
    
    for (int i = posx; i < posx+4; i++) {
        for (int j = posy; j < posy+4; j++) {
            Actor* tmp = getWorld()->m_ice[i][j];
            tmp->setVisible(false);
            tmp->m_status = false;
            getWorld()->m_ice[i][j] = nullptr;
        }
    }
}

void Boulder::doSomething() {
    
    if (getWorld()->getHealth() == 0)
        return;
    
    if (m_status == 1) { // in stable status
        for (int i = 0; i < 4; i++) {
            if (getWorld()->m_ice[getX()+i][getY()-1] != nullptr) // still ice underneath
                return;
        }
        // no ice under
        m_status = 2; // in waiting status
        return;
    }
    
    if (m_status < 32) {
        m_status++;
        return;
    }
    
    if (m_status == 32) { // play falling sound
        getWorld()->soundTriggered[SOUND_FALLING_ROCK] = true;
        m_status++;
        return;
    }
    
    if (m_status == 33) { // start falling
        
        for (int i=0; i<getWorld()->ActorList.size(); i++) {
            Actor* tmp = getWorld()->ActorList[i];
            
            if ( (tmp->m_type==TYPE_REGULAR_PROTESTER||tmp->m_type==TYPE_HARDCORE_PROTESTER)
                 && checkNear(tmp, 3) && tmp->m_status < 100002)
            {
                getWorld()->soundTriggered[SOUND_PROTESTER_GIVE_UP] = true;
                getWorld()->increaseScore(500);
                tmp->m_health -= 100;
                tmp->m_status = 100002; // make the protester stunning (to rest)
            }
        }
        for (int i=0; i<4; i++)
            if (getWorld()->m_ice[getX()+i][getY()-1] != nullptr)
                m_status = 0; // boulder dead
        
        if (getY() == 0)
            m_status = 0;
        
        if (m_status == 33)
            moveTo(getX(), getY()-1);
    }
    
    if (m_status == 0)
        setVisible(false);
}

//========================= Sonar =========================


Sonar::Sonar(int posx, int posy, StudentWorld* world)
:Actor(IID_SONAR, posx, posy, right, 1.0, 2, world)  {
    
    setVisible(false);
}

void Sonar::doSomething() {
    if (getWorld()->getHealth() == 0)
        return;
    
    int time_interval = 300;
    
    if (m_status < time_interval) {
        m_status++;
        return;
    }
    
    // sonar kit appear for sonar_time ticks
    setVisible(true);
    int sonar_time = MAX(100, 300 - 10 * getWorld()->getLevel());
    
    if (m_status < time_interval + sonar_time) {
        
        m_status++;
        
        if (checkNear(getWorld()->getPlayer(), 3)) {
            m_status = 1;
            setVisible(false);
            getWorld()->soundTriggered[SOUND_GOT_GOODIE] = true;
            getWorld()->increaseScore(75);
            getWorld()->incSonar(1);
        }
        return;
    }
    
    // status == time_interval + sonar_time
    // sonar kit should disappear
    
    m_status = 1;
    setVisible(false);
}


//========================= Water Pool =========================

Pool::Pool(int posx, int posy, StudentWorld* world)
:Actor(IID_WATER_POOL, posx, posy, right, 1.0, 2, world)  {
    
    setVisible(false);
}

void Pool::doSomething() {
    // -- moment1 -> position determined
    // -- moment2 -> pool showing up and available
    // -- moment3 -> pool disappear
    
    if (getWorld()->getHealth() == 0)
        return;
    
    int moment1 = 150;
    int moment2 = 270;
    int moment3 = moment2 + MAX(100, 300 - 10 * getWorld()->getLevel());
    
    if (m_status < moment1) {
        m_status++;
        return;
    }
    
    if (m_status == moment1) {
        moveTo(getWorld()->getPlayer()->getX(), getWorld()->getPlayer()->getY());
        m_status++;
        return;
    }
    
    if (m_status < moment2) {
        m_status++;
        return;
    }
    if (m_status >= moment2) { // water pool appears for several ticks
        setVisible(true);
        m_status++;
        
        if (checkNear(getWorld()->getPlayer(), 3)) { // iceman got the water
            m_status = 1;
            setVisible(false);
            getWorld()->soundTriggered[SOUND_GOT_GOODIE] = true;
            getWorld()->increaseScore(100);
            getWorld()->incWater(5);
        }
        return;
    }
    
    if (m_status >= moment3) { // water pool should disappear
        m_status = 1;
        setVisible(false);
    }
}

//========================= Water Squirt =========================

Squirt::Squirt(int posx, int posy, StudentWorld* world, Direction dir)
:Actor(IID_WATER_SPURT, posx, posy, dir, 1.0, 1, world)  {
    
    setVisible(true);
    m_status = 1;
    m_type = TYPE_SQUIRT;
}

void Squirt::doSomething() {
    if (m_status == 8) {
        m_status = 0;
        return;
    }
    m_status++;
    if (getDirection() == up && can_up()) // cannot go up anymore
        moveInDirection();
    if (getDirection() == down && can_down()) // cannot go down anymore
        moveInDirection();
    if (getDirection() == right && can_right()) // cannot go right anymore
        moveInDirection();
    if (getDirection() == left && can_left()) // cannot go left anymore
        moveInDirection();
    
    for (int i=0; i<getWorld()->ActorList.size(); i++) {
        
        Actor* tmp = getWorld()->ActorList[i];
        if (tmp->m_type == TYPE_REGULAR_PROTESTER && checkNear(tmp, 1)) {
            getWorld()->soundTriggered[SOUND_PROTESTER_ANNOYED] = true;
            getWorld()->increaseScore(100);
            tmp->m_health -= 40;
            tmp->m_status = 100002;
            
            m_status = false; // squirt dead
            break;
        }
        if (tmp->m_type == TYPE_HARDCORE_PROTESTER && checkNear(tmp, 1)) {
            getWorld()->soundTriggered[SOUND_PROTESTER_ANNOYED] = true;
            getWorld()->increaseScore(100);
            tmp->m_health -= 10;
            tmp->m_status = 100002;
            
            m_status = false; // squirt dead
            break;
        }
    }
}

//========================= Protester =========================

Protester::Protester(int IID, StudentWorld* world)
: Actor(IID, 60, 60, left, 1.0, 0, world) {
    
    setVisible(true);
    m_status = 1;
    tick_count = 0;
    max_tick_count = MAX(0, 3 - getWorld()->getLevel()/4);
    numSquaresToMoveInCurrentDirection = rand() % 53 + 8;
    
    shout_count = vertical_turn_count = 0;
    PROTESTER_FINISH_RESTING = PROTESTER_START_RESTING + MAX(50, 100-getWorld()->getLevel()*10);
}

void Protester::moveInShort(int posx, int posy) { // BFS()
    // Breadth First Search using Queue
    // to find the shortest path to (posx, posy)
    // and move one step accordingly
    
    if (getX() == posx && getY() == posy) {
        return;
    }
    int prev[64*64];
    bool vis[64*64];
    memset(vis, false, sizeof(vis));
    int tmp, tmpx, tmpy;
    std::queue<int> Q;
    
    Q.push(getY() * 64 + getX());
    vis[getY() * 64 + getX()] = true;

    while (!Q.empty()) {
        tmp = Q.front(); Q.pop();
        tmpx = tmp % 64;
        tmpy = tmp / 64;
        if (tmpx == posx && tmpy == posy) break;
        if (can_up(tmpx, tmpy) && !vis[tmp+64]) {
            Q.push(tmp + 64);
            prev[tmp+64] = tmp;
            vis[tmp+64] = true;
        }
        if (can_down(tmpx, tmpy) && !vis[tmp-64]) {
            Q.push(tmp-64);
            prev[tmp-64] = tmp;
            vis[tmp-64] = true;
        }
        if (can_right(tmpx, tmpy) && !vis[tmp+1]) {
            Q.push(tmp + 1);
            prev[tmp+1] = tmp;
            vis[tmp+1] = true;
        }
        if (can_left(tmpx, tmpy) && !vis[tmp-1]) {
            Q.push(tmp - 1);
            prev[tmp-1] = tmp;
            vis[tmp-1] = true;
        }
    }
    
    int cur_node = posy*64 + posx, pre_node = prev[cur_node];
    while (true) {
        tmpx = pre_node % 64;
        tmpy = pre_node / 64;
        if (tmpx == getX() && tmpy == getY()) {
            int curx = cur_node % 64, cury = cur_node / 64;
            if (cury > tmpy) setDirection(up);
            if (cury < tmpy) setDirection(down);
            if (curx > tmpx) setDirection(right);
            if (curx < tmpx) setDirection(left);
            moveTo(curx, cury);
            break;
        }
        pre_node = prev[pre_node];
        cur_node = prev[cur_node];
    }
}

bool Protester::IceManInSight() {
    IceMan* tmp_player = getWorld()->getPlayer();
    int tmpx = tmp_player->getX();
    int tmpy = tmp_player->getY();
    if (tmpx != getX() && tmpy != getY())
        return false;
    
    for (int x = MIN(tmpx, getX()); x <= MAX(tmpx, getX()); x++)
        for (int y = tmpy; y< tmpy+4; y++)
            if (getWorld()->m_ice[x][y] != nullptr)
                return false;
    
    for (int x = tmpx; x < tmpx+4; x++)
        for (int y = MIN(tmpy, getY()); y <= MAX(tmpy, getY()); y++)
            if (getWorld()->m_ice[x][y] != nullptr)
                return false;
    return true;
}

void Protester::doSomething() {
    if (m_status == 0) return; // Protester DEAD
    
    if (m_status >= PROTESTER_START_RESTING) { // in resting state
        if (m_health <= 0) {
            getWorld()->soundTriggered[SOUND_PROTESTER_GIVE_UP] = true;
            m_status = PROTESTER_LEAVE;
            return;
        }
        
        m_status++;
        if (m_status >= PROTESTER_FINISH_RESTING)
            m_status = 1;
        return;
    }
    
    tick_count++;
    if (tick_count < max_tick_count) return; // move one step for every "max_tick_count" ticks
    tick_count = 0;
    
    IceMan* tmp_player = getWorld()->getPlayer();
    
    if (m_status == PROTESTER_LEAVE) {
        moveInShort(60, 60);
        if (getX() == 60 && getY() == 60) {
            m_status = 0;
            setVisible(false);
        }
        return;
    }
    
    shout_count++;
    vertical_turn_count++;
    if (checkNear(tmp_player, 4) && shout_count >= 15) { // shout
        shout_count = 0;
        getWorld()->soundTriggered[SOUND_PROTESTER_YELL] = true;
        getWorld()->incHealth(-20);
        m_status = PROTESTER_START_RESTING;
        return;
    }
    
    if (IceManInSight()) {
        moveInShort(tmp_player->getX(), tmp_player->getY());
        //puts("1 -------------------- insight ");
    }
    else {
        if ( --numSquaresToMoveInCurrentDirection <=0 ) {
            numSquaresToMoveInCurrentDirection = rand() % 53 + 8;
            changeDirection();
            //puts("2 -------------------- dis");
        }
        else if (vertical_turn_count >= 100) { // this number should be 200 according to requirement
            if (changeDirectionVertical()) {
                //puts("3 -------------------- vertical");
                vertical_turn_count = 0;
                numSquaresToMoveInCurrentDirection = rand() % 53 + 8;
            }
        }
        
        if (can_go_ahead(getDirection())) {
            moveInDirection();
            //puts("4 -------------------- forward");
        }
        else {
            //puts("5 -------------------- blocked");
            changeDirection();
            numSquaresToMoveInCurrentDirection = rand() % 53 + 8;
            
        }
    }
}

//========================= Regualr Protester =========================

regularProtester::regularProtester(StudentWorld* world)
: Protester(IID_PROTESTER, world) {
    
    m_type = TYPE_REGULAR_PROTESTER;
}

//========================= Hardcore Protester =========================

hardcoreProtester::hardcoreProtester(StudentWorld* world)
: Protester(IID_HARD_CORE_PROTESTER, world) {
    
    m_type = TYPE_HARDCORE_PROTESTER;
}


