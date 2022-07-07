#pragma once
#include "Collider.hpp"

namespace Physics
{
    class OrientedBoxCollider : public Physics::Collider
    {
        private:
            OrientedBox orientedBox;
                    
        public:
            float extendX {1};
            float extendY {1};
            float extendZ {1};

            OrientedBoxCollider();
            OrientedBoxCollider(bool _trigger);
            OrientedBoxCollider(Vec3 extend, bool _trigger);

            ~OrientedBoxCollider(){};

            OrientedBox GetOrientedBox();
    };
}