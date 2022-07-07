#include "AdditionalBehavior.hpp"

using namespace Core::DataStructure;


void AdditionalBehavior::SetData(Core::DataStructure::GameObject* _gameObject, Physics::Transform* _transform)
{
    gameObject = _gameObject;
    transform = _transform;
}
