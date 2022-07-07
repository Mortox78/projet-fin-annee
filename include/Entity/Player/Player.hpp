#pragma once

#include "Entity.hpp"
#define PLAYER_NAME "player"

class Player: public Entity
{
private:
    
public:
    Player();
    Player(const float &_hp);
    Player(const float &_hp, const float &_attack);
    Player(const float &_hp, const float &_attack, const float &_speed);
    Player(const float &_hp, const float &_attack, const float &_speed, const float &_cooldown);
    ~Player();
};


