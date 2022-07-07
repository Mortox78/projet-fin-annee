#include "Entity.hpp"

Entity::Entity() : cooldownStart{cooldown}
{
    name = ENTITY_NAME;
    entities.push_back(this);
}
Entity::Entity(const float &_hp) : hp{_hp}, hpMax{_hp}, cooldownStart{cooldown}
{
    name = ENTITY_NAME;
    entities.push_back(this);
}
Entity::Entity(const float &_hp, const float &_attack) : hp{_hp}, attack{_attack}, hpMax{_hp}, cooldownStart{cooldown}
{
    name = ENTITY_NAME;
    entities.push_back(this);
}
Entity::Entity(const float &_hp, const float &_attack, const float &_speed) : hp{_hp}, attack{_attack}, speed{_speed}, hpMax{_hp}, cooldownStart{cooldown}
{
    name = ENTITY_NAME;
    entities.push_back(this);
}
Entity::Entity(const float &_hp, const float &_attack, const float &_speed, const float &_cooldown) : hp{_hp}, attack{_attack}, speed{_speed}, hpMax{_hp}, cooldown{_cooldown}, cooldownStart{_cooldown}
{
    name = ENTITY_NAME;
    entities.push_back(this);
}

std::string Entity::GetName()
{
    return name;
}

float Entity::GetHP()
{
    return hp;
}

float Entity::GetHPMax()
{
    return hpMax;
}

float Entity::GetAttack()
{
    return attack;
}
float Entity::GetSpeed()
{
    return speed;
}
float Entity::GetCooldown()
{
    return cooldown;
}

bool Entity::GetAlive()
{
    return alive;
}

ENTITY_TYPE Entity::GetType()
{
    return type;
}

void Entity::TakeDamage(const float &damage)
{
    if (!alive)
        return;

    hp - damage <= 0 ? hp = 0 : hp -= damage;
    if (hp <= 0)
        alive = false;
}

void Entity::DealDamage(Entity &entity)
{
    if (!canAttack)
        return;

    entity.TakeDamage(attack);
    canAttack = false;
}

void Entity::DisplayStats()
{
    std::cout << "====================================Stats of " << name << "====================================" << std::endl;
    std::cout << "hp: " << hp << "/" << hpMax << std::endl;
    std::cout << "attack: " << attack << std::endl;
    std::cout << "speed: " << speed << std::endl;
    std::cout << "cooldown: " << cooldown << "/" << cooldownStart << std::endl;
    std::cout << "\n";
}

ENTITY_TYPE Entity::Type() const
{
    return type;
}


void Entity::Cooldown(const float &deltatime)
{
    if (canAttack)
        return;

    cooldown - deltatime <= 0 ? cooldown = 0 : cooldown -= deltatime;
    if (cooldown <= 0 && !canAttack)
    {
        canAttack = true;
        cooldown = cooldownStart;
    }
}

void Entity::ChangeCooldown(const float &_cooldown)
{
    cooldownStart = _cooldown;
}

bool Entity::GetCanAttack()
{
    return canAttack;
}
