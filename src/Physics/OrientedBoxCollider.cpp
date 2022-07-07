#include "OrientedBoxCollider.hpp"

using namespace Physics;

OrientedBoxCollider::OrientedBoxCollider()
{
    name = COLLIDERBEHAVIOR;
    type = ColliderType::ORIENTED_BOX;
}

OrientedBoxCollider::OrientedBoxCollider(bool _trigger)
{
    name = COLLIDERBEHAVIOR;
    type = ColliderType::ORIENTED_BOX;
    isTrigger = _trigger;
}

OrientedBoxCollider::OrientedBoxCollider(Vec3 extend, bool _trigger) : extendX{extend.x}, extendY{extend.y}, extendZ{extend.z}
{
    name = COLLIDERBEHAVIOR;
    type = ColliderType::ORIENTED_BOX;
    isTrigger = _trigger;
}

OrientedBox OrientedBoxCollider::GetOrientedBox()
{
    orientedBox.extendX = transform->scale.x / 2 * extendX;
    orientedBox.extendY = transform->scale.y / 2 * extendY;
    orientedBox.extendZ = transform->scale.z / 2 * extendZ;

    orientedBox.ref.origin = transform->position;

    Vec4 i = transform->getMatrix() * Vec4(orientedBox.ref.i, 0);
    Vec4 j = transform->getMatrix() * Vec4(orientedBox.ref.j, 0);
    Vec4 k = transform->getMatrix() * Vec4(orientedBox.ref.k, 0);

    orientedBox.ref.i = Vec3{i.x, i.y, i.z}.Normalize();
    orientedBox.ref.j = Vec3{j.x, j.y, j.z}.Normalize();
    orientedBox.ref.k = Vec3{k.x, k.y, k.z}.Normalize();

    //std::cout << "i : x = " << orientedBox.ref.i.x << ", y = " << orientedBox.ref.i.y << ", z = " << orientedBox.ref.i.z << std::endl;
    //std::cout << "j : x = " << orientedBox.ref.j.x << ", y = " << orientedBox.ref.j.y << ", z = " << orientedBox.ref.j.z << std::endl;
    //std::cout << "k : x = " << orientedBox.ref.k.x << ", y = " << orientedBox.ref.k.y << ", z = " << orientedBox.ref.k.z << std::endl;


    orientedBox.ref.origin = transform->position;
    return orientedBox;
}