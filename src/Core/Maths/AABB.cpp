#include "AABB.hpp"
#include "Math.hpp"
using namespace Core::Maths;
AABB::AABB() :  extendX{0}, extendY{0}, extendZ{0} {}
AABB::AABB(Vec3 _center, float _extendX, float _extendY, float _extendZ) : extendX{_extendX}, extendY{_extendY}, extendZ{_extendZ}
{
    ref.origin = _center;
}
AABB::~AABB() {}

Vec3& AABB::Position()
{
    return ref.origin;
}

Vec3 AABB::Position() const
{
    return ref.origin;
}

bool AABB::SphereAndOrientedBoxAABBCollision(const Sphere &sphere, const OrientedBox &box)
{
    Vec3 sphereLocal = box.ref.PointWorldToLocal(sphere.position);

    if (abs(sphereLocal.x) > box.extendX + sphere.ray 
    ||  abs(sphereLocal.y) > box.extendY + sphere.ray 
    ||  abs(sphereLocal.z) > box.extendZ + sphere.ray)
        return false;

    return true;
}

bool AABB::OrientedBoxAndOrientedBoxAABBCollision(const OrientedBox &box, const OrientedBox &box2)
{
    Vec3 box2LocalPos = box.ref.PointWorldToLocal(box2.ref.origin);

    if (abs(box2LocalPos.x) > box.extendX + box2.extendX ||
        abs(box2LocalPos.y) > box.extendY + box2.extendY ||
        abs(box2LocalPos.z) > box.extendZ + box2.extendZ)
    {
        return false;
    }
    return true;
}

bool AABB::PointAndAABBCollision(Vec3 pt)
{
    Vec3 localPos = ref.Point_World_To_Local(pt);
    if(Abs(localPos.x) > extendX || Abs(localPos.y) > extendY || Abs(localPos.z) > extendZ)
        return false;

    return true;
}