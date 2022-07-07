#include "CharacterPhysicBody.hpp"

#include "OrientedBoxCollider.hpp"
#include "GameObject.hpp"

using namespace Physics;

CharacterPhysicBody::CharacterPhysicBody() : Physics::SphereCollider(1, {0, -1.0f, 0})
{
    name = CHARACTER_PHYSIC_BODY;
    //collider.gameObject = gameObject;
}

CharacterPhysicBody::~CharacterPhysicBody()
{
}

void CharacterPhysicBody::Start()
{

}

void CharacterPhysicBody::Update()
{
    ApplyLimit();
    CheckCollisionWithAllCollider(this);
    Move(velocity);

    Sphere sph = GetSphere();

    Hit hit;

    if (isGrounded)
    {
        velocity.y = 0;
        //velocity.y += 0;
    }
    else
    {
        velocity.y -= gravity/10;
    }
    
}

void CharacterPhysicBody::AddForce(const Vec3& force)
{
    velocity = velocity + force;   
}

void CharacterPhysicBody::Move(Vec3& movement)
{
    isGrounded = false;

    Sphere sph = GetSphere();
    sph.position = sph.position + movement;
    Vec3 savePos = sph.position;

    unsigned int listSize = allCollider.size();
    for (unsigned int i = 0; i < listSize; i++)
    {
        if ((Collider*)(this) != allCollider[i])
        {
            if (allCollider[i]->gameObject->isActive)
            {
                if (!allCollider[i]->isTrigger && allCollider[i]->isEnable)
                {
                    if(allCollider[i]->Type() == ColliderType::ORIENTED_BOX)
                    {
                        sph.position = savePos + movement;
                        if (AABB::SphereAndOrientedBoxAABBCollision(sph, ((OrientedBoxCollider*)(allCollider[i]))->GetOrientedBox()))
                        {
                            if (IsSphereAndOrientedBoxCollide(sph, ((OrientedBoxCollider*)(allCollider[i]))->GetOrientedBox()))
                            {
                                Hit hit;
                                // Use of simplified version of the collision to gain performance
                                if (GetFirstCollisionPointBetweenMovingSphereAndStaticBox(((OrientedBoxCollider*)(allCollider[i]))->GetOrientedBox(), GetSphere(), movement, 1, hit))
                                {   
                                    gameObject->OnCollideAll(Collision(&hit, this));
                                    allCollider[i]->gameObject->OnCollideAll(Collision(&hit, this));

                                    if (hit.normal.y > 0)
                                    {
                                        isGrounded = true;
                                    }
                                
                                    movement.x *= (1.0f - abs(hit.normal.x));
                                    movement.y *= (1.0f - abs(hit.normal.y));
                                    movement.z *= (1.0f - abs(hit.normal.z));
            
                                }                                
                            }
                        }
                    }     
                }
            }
        }
    }

    transform->position = transform->position + movement;
    transform->ResetMatrix();

}

void CharacterPhysicBody::ApplyLimit()
{
    if (abs(velocity.x) > SpeedLimit.x && velocity.x != 0)
    {
        velocity.x = SpeedLimit.x * (abs(velocity.x) / velocity.x);
    }
    
    if (abs(velocity.y) > SpeedLimit.y && velocity.y != 0)
    {
        velocity.y = SpeedLimit.y * (abs(velocity.y) / velocity.y);
    }
    
    if (abs(velocity.z) > SpeedLimit.z && velocity.z != 0)
    {
        velocity.z = SpeedLimit.z * (abs(velocity.z) / velocity.z);
    }
}

void CharacterPhysicBody::OnTrigger(const Physics::Collider  *collider)
{

}
