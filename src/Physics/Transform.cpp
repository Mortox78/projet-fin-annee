#include "Transform.hpp"

Physics::Transform::Transform(){}
Physics::Transform::Transform(const Core::Maths::Vec3 &_position, const Core::Maths::Vec3 &_scale, const Core::Maths::Vec3 &_rotation)
{
    position    = _position;
    scale       = _scale;
    rotation    = _rotation;

    matrix = Core::Maths::Mat4::CreateTransformMatrix(rotation, position, scale);
}

Physics::Transform::~Transform(){}

const Core::Maths::Vec3 &Physics::Transform::Position()
{
    return position;
}
const Core::Maths::Vec3 &Physics::Transform::Scale()   
{
    return scale;
}
const Core::Maths::Vec3 &Physics::Transform::Rotation()
{
    return rotation;
}

void Physics::Transform::setPosition(const Core::Maths::Vec3 &_position)
{
    position    = _position;
    matrix = Core::Maths::Mat4::CreateTransformMatrix(rotation, position, scale);
}

void Physics::Transform::setScale(const Core::Maths::Vec3 &_scale)
{
    scale       = _scale;
    matrix = Core::Maths::Mat4::CreateTransformMatrix(rotation, position, scale);
}

void Physics::Transform::setRotation(const Core::Maths::Vec3 &_rotation)
{
    rotation    = _rotation;
    matrix = Core::Maths::Mat4::CreateTransformMatrix(rotation, position, scale);
}

void Physics::Transform::ResetMatrix()
{
    matrix = Core::Maths::Mat4::CreateTransformMatrix(rotation, position, scale);
}

void Physics::Transform::setMatrix(const Core::Maths::Vec3 &_position, const Core::Maths::Vec3 &_scale, const Core::Maths::Vec3 &_rotation)
{
    position    = _position;
    scale       = _scale;
    rotation    = _rotation;

    matrix = Core::Maths::Mat4::CreateTransformMatrix(rotation, position, scale);
}

const Core::Maths::Mat4 &Physics::Transform::getMatrix()
{
    //return Core::Maths::Mat4::CreateTransformMatrix(rotation, position, scale);
    return matrix;
}