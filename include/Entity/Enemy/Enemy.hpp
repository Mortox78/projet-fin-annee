#pragma once
#include "Entity.hpp"
#include "vector3D.hpp"
#include "PhysicBody.hpp"

#define ENEMY_NAME "enemy"

class Enemy : public Entity
{
private:
    Entity* target {nullptr};
    Physics::PhysicBody* body {nullptr};

public:

    float deltaTimeEnemyManager {0};

    Enemy();
    Enemy(const float &_hp);
    Enemy(const float &_hp, const float &_attack);
    Enemy(const float &_hp, const float &_attack, const float &_speed);
    Enemy(const float &_hp, const float &_attack, const float &_speed, const float &_cooldown);
    ~Enemy();
    void Chase(const Core::Maths::Vec3 &position, const float &delaTime);// go in the direction of a position gift.
    void ChaseTarget(const float &deltaTime);// go in the direction of the target, if there is no target it does nothing.
    void Rotation();// make the enemy rotate in the direction of is target, if there is no target it does nothing. 
    void FindTarget(const std::string &name);// Search a target by is name in the list of entity.
    void FindTarget();// Search a target who is a player.
    void DealDamageTarget();// attack the target, if there is no target, do nothing.


    void Start() override;
    void Update() override;

    void OnTrigger(const Physics::Collider  *collider) override;
};