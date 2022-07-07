#include "Bullet.hpp"

#include "Camera.hpp"
#include "InputManager.hpp"
#include "GameObject.hpp"
#include "TimeManager.hpp"
#include "Entity.hpp"
#include "AdditionalBehavior.hpp"

void Bullet::Update()
{
    Tools::Time& timeManager = Tools::Time::Summon();

    // If time spent in the scene is higher than its life duration
    timer += timeManager.DeltaTime();
    if (!hit)
    {
        if (timer > lifeDuration)
        {
            timer = 0.f;
            gameObject->isActive = false;
            return;
        }

        transform->setPosition(transform->position + (direction * speed * timeManager.DeltaTime()));
        CheckCollisionWithAllCollider(this);
    }
    else
    {
        if (timer > lifeDurationAfterHit)
        {
            timer = 0.f;
            LowRenderer::Mesh& mesh = gameObject->Mesh();
            mesh.models.clear();
            mesh.models.push_back(Resources::Model::CreateSphere(5, 5, {1.f, 1.f, 1.f, 0.1f}));
            gameObject->isActive = false;
            hit = false;
            return;
        }
    }
}

void Bullet::OnTrigger(const Physics::Collider  *collider)
{
    if (collider->gameObject->tag == "bullet" || collider->gameObject->tag == "player")
    {
        return;
    }

    if (!hit)
    {
        hit = true;
        timer = 0.f;
        LowRenderer::Mesh& mesh = gameObject->Mesh();
        mesh.models.clear();
        mesh.models.push_back(Resources::Model::CreateSphere(5, 5, {1.f, 0.f, 0.f, 1.f}));

        if (collider->gameObject->tag == "enemy")
        {
            std::cout << "Bullet : Collision enemy" << std::endl;
            Core::DataStructure::AdditionalBehavior *temp = collider->gameObject->GetBehavior("enemy");
            Entity *e = (Entity*)temp;

            e->TakeDamage(1.f);
            std::cout << "enemy life: "<< e->GetHP() << "/" << e->GetHPMax() << std::endl;

            if(!e->GetAlive())
                collider->gameObject->isActive = false;
        }
    }
}