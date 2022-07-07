#include "PhysicBody.hpp"

#include "OrientedBoxCollider.hpp"
#include "GameObject.hpp"
#include "TimeManager.hpp"

using namespace Physics;


PhysicBody::PhysicBody()
{
    name = PHYSICBODYBEHAVIOR;
}

PhysicBody::PhysicBody(float ray, Vec3 position) : SphereCollider(ray, position)
{
    name = PHYSICBODYBEHAVIOR;
}

PhysicBody::~PhysicBody()
{
}

void PhysicBody::Update()
{
    Tools::Time& timeManager = Tools::Time::Summon();

    velocity.y -= gravity * timeManager.DeltaTime();
    Move();    
}

void PhysicBody::AddForce(const Vec3& force)
{
    velocity = velocity + force;   
}

void PhysicBody::Move()
{
    Tools::Time& timeManager = Tools::Time::Summon();    

    Sphere sph = GetSphere();
    sph.position = sph.position + velocity * 1.5;

    unsigned int listSize = allCollider.size();
    for (unsigned int i = 0; i < listSize; i++)
    {
        if ((Collider*)(this) != allCollider[i])
        {
            if (!allCollider[i]->isTrigger && allCollider[i]->isEnable)
            {
                if(allCollider[i]->Type() == ColliderType::ORIENTED_BOX)
                {
                    //sph.position = sph.position + velocity;
                    if (AABB::SphereAndOrientedBoxAABBCollision(sph, ((OrientedBoxCollider*)(allCollider[i]))->GetOrientedBox()))
                    {
                        if (IsSphereAndOrientedBoxCollide(sph, ((OrientedBoxCollider*)(allCollider[i]))->GetOrientedBox()))
                        {
                            Hit hit;
                            // Use of simplified version of the collision to gain performance
                            if (GetFirstCollisionPointBetweenMovingSphereAndStaticBox(((OrientedBoxCollider*)(allCollider[i]))->GetOrientedBox(), GetSphere(), velocity, 1, hit))
                            {   
                                gameObject->OnCollideAll(Collision(&hit, this));

                                //transform->setPosition(hit.point);

                                //hit.normal.Normalize();
                                velocity.x *= (1 - abs(hit.normal.x));
                                velocity.y *= (1 - abs(hit.normal.y));
                                velocity.z *= (1 - abs(hit.normal.z));

                            }
                            
                        }
                    }
                }     
            }
        }
    }

    transform->position = transform->position + velocity;
    transform->ResetMatrix();

}