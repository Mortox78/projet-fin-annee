#include "PlayerShoot.hpp"
#include "Assertion.hpp"

PlayerShoot::PlayerShoot(PlayerCamera* _playerCamera, Resources::Scene* _world, Resources::Shader* _shader)
{
    name = PLAYER_SHOOT_BEHAVIOR;

    Debug::Assertion::Check(HIGH, _playerCamera, "_playerCamera == nullptr");
    Debug::Assertion::Check(HIGH, _world, "_world == nullptr");
    playerCamera = _playerCamera;

    bullets.resize(startAmmo);

    for (unsigned int i = 0; i < startAmmo; ++i)
    {
        bullets[i].tag = "bullet";
        LowRenderer::Mesh& mesh = bullets[i].Mesh();
        mesh.models.push_back(Resources::Model::CreateSphere(5,5, {1.f, 1.f, 1.f, 0.1f}));
        mesh.shader = _shader;
        bullets[i].transform.scale = Vec3(0.1f, 0.1f, 0.1f);
        bullets[i].isActive = false;
        bullets[i].AddBehavior(new Bullet());
        _world->Add(&bullets[i]);
    }
}

PlayerShoot::~PlayerShoot()
{
    for (unsigned int i = 0; i < startAmmo; ++i)
    {
        delete bullets[i].GetBehavior(BULLETBEHAVIOR);
    }
}

void PlayerShoot::Update()
{
    Tools::Time& timeManager = Tools::Time::Summon();
    InputManager& inputs = InputManager::Summon();
    bool mouseClick = inputs.IsActionTriggered(Actions::Fire);

    timer += timeManager.DeltaTime();
    if (currentAmmo < startAmmo && timer > 1.f)
    {
        timer = 0.f;
        currentAmmo++;
    }

    if (canShoot && mouseClick)
    {
        Shoot();
    }
    if (!canShoot && !mouseClick)
    {
        canShoot = true;
    }
}

void PlayerShoot::Shoot()
{
    if (currentAmmo == 0)
    {
        std::cout << "No more ammo" << std::endl;
        return;
    }

    for (unsigned int i = 0; i < startAmmo; i++)
    {
        if (!bullets[i].isActive)
        {
            Bullet* bullet = dynamic_cast<Bullet*>(bullets[i].GetBehavior(BULLETBEHAVIOR));
            bullet->direction = playerCamera->camera->GetRaycast();
            bullets[i].transform.position = playerCamera->camera->pos;
            bullets[i].isActive = true;
            --currentAmmo;
            canShoot = false;
            return;
        }
    }
}
