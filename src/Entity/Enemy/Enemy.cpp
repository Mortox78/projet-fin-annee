#include "Enemy.hpp"
#include "Player.hpp"
#include "Collider.hpp"
#include "Assertion.hpp"

#include "Collider.hpp"
#include "GameObject.hpp"
#include "TimeManager.hpp"

using namespace Core::Maths;

std::vector<Entity *> Entity::entities = std::vector<Entity *>();

Enemy::Enemy()
{
    name = ENEMY_NAME;
    type = ENEMY;
}

Enemy::Enemy(const float &_hp) : Entity{_hp}
{
    name = ENEMY_NAME;
    type = ENEMY;
}
Enemy::Enemy(const float &_hp, const float &_attack) : Entity{_hp, _attack}
{
    name = ENEMY_NAME;
    type = ENEMY;
}
Enemy::Enemy(const float &_hp, const float &_attack, const float &_speed) : Entity{_hp, _attack, _speed}
{
    name = ENEMY_NAME;
    type = ENEMY;
}
Enemy::Enemy(const float &_hp, const float &_attack, const float &_speed,const float &_cooldown) : Entity{_hp, _attack, _speed, _cooldown}
{
    name = ENEMY_NAME;
    type = ENEMY;
}
Enemy::~Enemy() {}

void Enemy::Chase(const Vec3 &position, const float &delaTime)
{
    if (!transform)
        return;
    
        
    Vec3 direction = position - transform->position;
    float angleY = atan2(direction.x, direction.z);
    transform->rotation = Vec3(transform->rotation.x, angleY, transform->rotation.z);

    if (direction.GetMagnitude() <= 0.1f)
        return;

    direction = direction.Normalize();
    direction.y = 0;
    direction.Normalize();

    if (body)
    {

        body->velocity = (direction * (speed * delaTime));
    }
}

void Enemy::FindTarget()
{
    for (unsigned int i = 0; i < entities.size(); i++)
    {
        if (entities[i]->GetType() == PLAYER)
        {
            target = entities[i];
            return;
        }
    }
}
void Enemy::FindTarget(const std::string &name)
{
    for (unsigned int i = 0; i < entities.size(); i++)
    {
        if (entities[i]->GetName() == name)
        {
            target = entities[i];
            return;
        }
    }
}

void Enemy::ChaseTarget(const float &deltaTime)
{
    if (!transform || !target || !target->transform)
        return;
    Chase(target->transform->position, deltaTime);
}
void Enemy::Rotation()
{
    if(!target)
        return;
        
    Vec3 direction = target->transform->position - transform->position;
    float angleY = atan2(direction.x, direction.z);
    transform->rotation = Vec3(transform->rotation.x, angleY, transform->rotation.z);
}

void Enemy::DealDamageTarget()
{
    if (!target)
    {
        std::cout << "There is no target" << std::endl;
        return;
    } 
    DealDamage(*target);
    target->DisplayStats();   
}

void Enemy::Start()
{
    FindTarget();
}

void Enemy::Update()
{
    Tools::Time& timeManager = Tools::Time::Summon();

    if (!target)
    {
        FindTarget();
    }

    if(!body)
        body = dynamic_cast<Physics::PhysicBody*>(gameObject->GetBehavior(PHYSICBODYBEHAVIOR));

    Rotation();
    ChaseTarget(timeManager.DeltaTime());
} 

void Enemy::OnTrigger(const Physics::Collider  *collider)
{
    if(collider->gameObject->tag == "player")
        DealDamageTarget();
}