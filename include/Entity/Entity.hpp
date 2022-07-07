#pragma once

#include <iostream>
#include <vector>

#include "AdditionalBehavior.hpp"
#include "Collider.hpp"
#include "SphereCollider.hpp"

#define ENTITY_NAME "entity"

enum ENTITY_TYPE
{
    PLAYER,
    ENEMY,
    ENTITY
};

class Entity : public Core::DataStructure::AdditionalBehavior
{
protected:
    float hp        {10.f};
    float attack    {1.f};
    float speed     {1.f};
    float hpMax     {1.f};
    float cooldown  {1.f};
    float cooldownStart;// It's the start value of the cooldown
    bool canAttack {true};
    bool alive{true};
    ENTITY_TYPE type{ENTITY};

    
    static std::vector<Entity*> entities;

public:
    Entity();
    Entity(const float &_hp);
    Entity(const float &_hp, const float &_attack);
    Entity(const float &_hp, const float &_attack, const float &_speed);
    Entity(const float &_hp, const float &_attack, const float &_speed, const float &_cooldown);

    ~Entity(){};
    std::string GetName();
    float GetHP();
    float GetHPMax();
    float GetAttack();
    float GetSpeed();
    float GetCooldown();
    bool GetAlive();// return alive.
    ENTITY_TYPE GetType();

    void TakeDamage(const float &damage);
    void DealDamage(Entity &entity);
    void DisplayStats();
    void Cooldown(const float &deltatime);
    void ChangeCooldown(const float &_cooldown);// set new value to cooldownStart

    ENTITY_TYPE Type() const;
    bool GetCanAttack();
};