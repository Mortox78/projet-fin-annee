#include "SphereCollider.hpp"

using namespace Physics;

SphereCollider::SphereCollider()
{
    name = COLLIDERBEHAVIOR;
    type = ColliderType::SPHERE;
    sphere.ray = 1;
}

SphereCollider::SphereCollider(bool trigger)
{
    name = COLLIDERBEHAVIOR;
    type = ColliderType::SPHERE;
    sphere.ray = 1;
    isTrigger = trigger;
}

SphereCollider::SphereCollider(float _ray, Vec3 _position, bool trigger) : ray{_ray}, position{_position}
{
    name = COLLIDERBEHAVIOR;
    type = ColliderType::SPHERE;
    sphere.ray = 1;
    isTrigger = trigger;
}

Sphere SphereCollider::GetSphere()
{
    sphere.position = transform->position + position;
    sphere.ray = std::max(transform->scale.x, std::max(transform->scale.y, transform->scale.z)) * ray;
    return sphere;
}