#ifndef _PHYSICBODY_
#define _PHYSICBODY_

#include "AdditionalBehavior.hpp"
#include "SphereCollider.hpp"

#define PHYSICBODYBEHAVIOR "PhysicBodyBehavior"

namespace Physics
{
    class PhysicBody : public Physics::SphereCollider
    {
    private:

    
    public:

        Vec3 velocity;
        float gravity {10.f};

        PhysicBody();
        PhysicBody(float ray, Vec3 position = {0,0,0});
        ~PhysicBody();

        void Update() override;

        void AddForce(const Vec3& force);
        void Move();
    };   
}

#endif