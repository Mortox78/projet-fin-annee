#ifndef _CHARACTERPHYSICSBODY_
#define _CHARACTERPHYSICSBODY_

#include "SphereCollider.hpp"
#include "AdditionalBehavior.hpp"

#define CHARACTER_PHYSIC_BODY "CharacterPhysicBody"

namespace Physics
{
    class CharacterPhysicBody : public Physics::SphereCollider
    {

    public:
        Vec3 velocity;

        float gravity = 0.5f;
        float jump = 10;

        Vec3 SpeedLimit{1,1,1};

        bool isGrounded = false;

        CharacterPhysicBody();
        ~CharacterPhysicBody();

        void Start() override;
        void Update() override;
        
        void AddForce(const Vec3& force);

        void Move(Vec3 &movement);
        void ApplyLimit();

        void OnTrigger(const Physics::Collider  *collider) override;
    };
}

#endif