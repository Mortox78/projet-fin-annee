#ifndef _PLAYERCAMERA_
#define _PLAYERCAMERA_

#include "AdditionalBehavior.hpp"
#include "Camera.hpp"
#include "Assertion.hpp"
#include "Collider.hpp"
#include "SphereCollider.hpp"
#include "CharacterPhysicBody.hpp"

#include "Bullet.hpp"

#define PLAYER_SPEED 5.0f

#define PLAYERCAMERABEHAVIOR "PlayerCameraBehavior"

class PlayerCamera : public Core::DataStructure::AdditionalBehavior
{
    public:
        LowRenderer::Camera* camera                     {nullptr};
        Physics::Transform* playerTransform             {nullptr};
        Physics::CharacterPhysicBody* playerPhysicBody  {nullptr};
        
        PlayerCamera(LowRenderer::Camera* _camera, Physics::Transform* _playerTransform, Physics::CharacterPhysicBody* _playerPhysicBody);
        ~PlayerCamera(){}

        void Update() override;
        void UpdatePlayerMovements();

        void OnTrigger(const Physics::Collider* collider) override;
};

#endif