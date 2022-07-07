#include <iostream>

#include "GameObject.hpp"
#include "PlayerCamera.hpp"
#include "InputManager.hpp"
#include "vector3D.hpp"
#include "TimeManager.hpp"
#include "Collider.hpp"
#include "SphereCollider.hpp"
#include "CharacterPhysicBody.hpp"

using namespace LowRenderer;

PlayerCamera::PlayerCamera(LowRenderer::Camera* _camera, Physics::Transform* _playerTransform, Physics::CharacterPhysicBody* _playerPhysicBody)
{
    name = PLAYERCAMERABEHAVIOR;
    Debug::Assertion::Check(HIGH, _camera, "camera == nullptr");
    Debug::Assertion::Check(HIGH, _playerTransform, "playerTransform == nullptr");
    Debug::Assertion::Check(HIGH, _playerPhysicBody, "playerCollider == nullptr");
    camera = _camera;
    playerTransform = _playerTransform;
    playerPhysicBody = _playerPhysicBody;
}

void PlayerCamera::UpdatePlayerMovements()
{
    InputManager& inputs = InputManager::Summon();
    Tools::Time& timeManager = Tools::Time::Summon();

    Vec3 camRayCast = camera->GetRaycast();
    Vec3 direction = Vec3(camRayCast.x, 0.f, camRayCast.z).Normalize();

    float speed = PLAYER_SPEED * timeManager.DeltaTime();

    playerPhysicBody->velocity.x = 0;
    playerPhysicBody->velocity.z = 0;

    // We get the perpendicular vectors to "direction" (which is a vec on the plane X/Z) so we can change direction between forward/backward/left/right
    if (inputs.IsActionTriggered(Actions::Forward))
    {
        playerPhysicBody->AddForce(Vec3(direction.x, 0.f, direction.z)  * speed);
    }
    if (inputs.IsActionTriggered(Actions::Backwards))
    {
        playerPhysicBody->AddForce(Vec3(-direction.x, 0.f, -direction.z)  * speed);
    }
    if (inputs.IsActionTriggered(Actions::Left))
    {
        playerPhysicBody->AddForce(Vec3(direction.z, 0.f, -direction.x)  * speed);
    }
    if (inputs.IsActionTriggered(Actions::Right))
    {
        playerPhysicBody->AddForce(Vec3(-direction.z, 0.f, direction.x)  * speed);
    }
    if (inputs.IsActionTriggered(Actions::Up))
    {
        playerTransform->position.y += speed;
    }
    if (inputs.IsActionTriggered(Actions::Down))
    {
        playerTransform->position.y -= speed;
    }
    if (inputs.IsActionTriggered(Actions::Jump) && playerPhysicBody->isGrounded)
    {
        playerPhysicBody->AddForce(Vec3(0,1,0) * speed);
    }
}

void PlayerCamera::Update()
{
    if (!camera->window)
    {
        Debug::Assertion::Check(HIGH, true, "window == nullptr");
        return;
    }
    if (camera->initialized)
    {
        camera->UpdateRotation();
        UpdatePlayerMovements();
        camera->pos = playerTransform->position;
        playerTransform->setRotation(camera->rot);
    }
    else
    {
        glfwSetInputMode(camera->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        camera->initialized = true;
    }

    if (!camera->firstPerson)
    {
        camera->matCam = Maths::Mat4::CreateCameraMatrix(camera->aim, camera->pos, camera->Z);
    }
    else
    {
        camera->matCam =  Maths::Matrix::GetMatrixInverse(Maths::Matrix(Maths::Mat4::CreateTransformMatrix(camera->rot, camera->pos, {1.f, 1.f, 1.f})));
    } 

    glfwSetCursorPos(camera->window, 800 / 2, 600 / 2);
}

void PlayerCamera::OnTrigger(const Physics::Collider* collider)
{
    //std::cout << "Trigger tag = " << collider->gameObject->tag << std::endl;;

    if (collider->gameObject->tag == "switch")
    {
        Vec3 camRayCast = camera->GetRaycast();

        Vec3 direction = Vec3(camRayCast.x, 0.f, camRayCast.z).Normalize();

        float speed = PLAYER_SPEED;

        InputManager& inputs = InputManager::Summon();
        Tools::Time& timeManager = Tools::Time::Summon();

        if (inputs.IsActionTriggered(Actions::Forward))
        {
            transform->setPosition(transform->position + (Vec3(direction.x, 0.f, direction.z) * std::min(collider->transform->scale.x, collider->transform->scale.z)));
        }
        if (inputs.IsActionTriggered(Actions::Backwards))
        {
            transform->setPosition(transform->position + (Vec3(-direction.x, 0.f, -direction.z) * std::min(collider->transform->scale.x, collider->transform->scale.z)));
        }
        if (inputs.IsActionTriggered(Actions::Left))
        {
            transform->setPosition(transform->position + (Vec3(direction.z, 0.f, -direction.x) * std::min(collider->transform->scale.x, collider->transform->scale.z)));
        }
        if (inputs.IsActionTriggered(Actions::Right))
        {
            transform->setPosition(transform->position + (Vec3(-direction.z, 0.f, direction.x) * std::min(collider->transform->scale.x, collider->transform->scale.z)));
        }
    }
}