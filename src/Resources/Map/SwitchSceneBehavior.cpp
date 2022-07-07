#include "SwitchSceneBehavior.hpp"

#include "Player.hpp"
#include "GameObject.hpp"
#include "MapLoader.hpp"

using namespace Resources;

SwitchSceneBehavior::SwitchSceneBehavior() { isTrigger = true;}

SwitchSceneBehavior::SwitchSceneBehavior(unsigned int _oldScene, unsigned int _newScene, MapLoader* _map) : oldScene{_oldScene}, newScene{_newScene}, map{_map} { isTrigger = true;}

SwitchSceneBehavior::~SwitchSceneBehavior() {}


void SwitchSceneBehavior::Start()
{
    gameObject->tag = "switch";
}

void SwitchSceneBehavior::OnTrigger(const Physics::Collider  *collider)
{

    if (collider->gameObject->tag == "player")
    {
        if (newScene < map->listScene.size() && oldScene < map->listScene.size())
        {
            map->SwitchScene(newScene, oldScene);  
        }
    }
}