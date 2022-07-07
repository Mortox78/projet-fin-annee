#ifndef _SWITCHSCENEBEHAVIOR_
#define _SWITCHSCENEBEHAVIOR_

#include "AdditionalBehavior.hpp"
#include "OrientedBoxCollider.hpp"


namespace Resources
{
    class MapLoader;

    class SwitchSceneBehavior : public Physics::OrientedBoxCollider
    {
    private:
        
    public:
        SwitchSceneBehavior();
        SwitchSceneBehavior(unsigned int _oldScene, unsigned int _newScene, MapLoader* _map);
        ~SwitchSceneBehavior();

        unsigned int oldScene {0};
        unsigned int newScene {1};

        MapLoader* map;

        void Start() override;

        void OnTrigger(const Physics::Collider  *collider) override;

    };
}



#endif