#pragma once

#include "vector3D.hpp"
#include "OrientedBox.hpp"
#include "Sphere.hpp"
#include "referential.hpp"

namespace Core
{
    namespace Maths
    {
        class AABB
        {
            private:
                Referential ref;

            public:
                float extendX, extendY, extendZ;
                AABB();
                AABB(Vec3 _center, float _extendX, float _extendY, float _extendZ);
                ~AABB();

                Vec3& Position();
                Vec3  Position() const;

                static bool SphereAndOrientedBoxAABBCollision(const Sphere &sphere, const OrientedBox &box);
                static bool OrientedBoxAndOrientedBoxAABBCollision(const OrientedBox &box, const OrientedBox &box2);
                bool PointAndAABBCollision(Vec3 pt);
        

        };
    } // namespace Maths
} // namespace Core