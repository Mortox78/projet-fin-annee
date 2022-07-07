#pragma once

#include <iostream>
#include <vector>

#include "AdditionalBehavior.hpp"
#include "Bullet.hpp"
#include "PlayerCamera.hpp"
#include "InputManager.hpp"
#include "TimeManager.hpp"
#include "Scene.hpp"

#define PLAYER_SHOOT_BEHAVIOR "PLAYERSHOOTBEHAVIOR"

class PlayerShoot : public Core::DataStructure::AdditionalBehavior
{
    private:
        bool canShoot = true;
        float timer = 0.f;

    public:
        PlayerShoot(PlayerCamera* _playerCamera, Resources::Scene* _world, Resources::Shader* _shader);
        ~PlayerShoot();

        unsigned int startAmmo = 150;
        unsigned int currentAmmo = 150;

        //InputManager& inputs;
        PlayerCamera* playerCamera { nullptr };
        std::vector<Core::DataStructure::GameObject> bullets;
    
        void Update() override;
        void Shoot();
};