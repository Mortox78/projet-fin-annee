#pragma once
#include "Collider.hpp"

namespace Physics
{
    class SphereCollider : public Physics::Collider
    {
        private:
            float ray {1};
            Vec3 position {0,0,0};
            Sphere sphere;

        public:

            SphereCollider();
            SphereCollider(bool trigger);
            SphereCollider(float _ray, Vec3 _position = {0,0,0}, bool trigger = false);
            ~SphereCollider(){};

            Sphere GetSphere();
    };
}