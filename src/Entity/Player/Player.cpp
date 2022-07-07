#include "Player.hpp"

Player::Player()
{
    name = PLAYER_NAME;
    type = PLAYER;
    entities.push_back(this);
}

Player::Player(const float &_hp):Entity{_hp}
{
    name = PLAYER_NAME;
    type = PLAYER;
    entities.push_back(this);
}
Player::Player(const float &_hp, const float &_attack):Entity{_hp, _attack}
{
    name = PLAYER_NAME;
    type = PLAYER;
    entities.push_back(this);
}
Player::Player(const float &_hp, const float & _attack, const float &_speed):Entity{_hp, _attack, _speed}
{
    name = PLAYER_NAME;
    type = PLAYER;
    entities.push_back(this);
}

Player::Player(const float &_hp, const float &_attack, const float &_speed,const float &_cooldown) : Entity{_hp, _attack, _speed, _cooldown}
{
    name = PLAYER_NAME;
    type = PLAYER;
    entities.push_back(this);
}
Player::~Player(){}