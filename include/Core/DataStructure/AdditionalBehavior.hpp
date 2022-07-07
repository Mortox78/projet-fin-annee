#ifndef _ADDITIONALBEHAVIOR_
#define _ADDITIONALBEHAVIOR_

#include <string>
#include <vector>
#include <memory>

#include "Transform.hpp"
//#include "GameObject.hpp"

//using class GameObject GameObject;

#define EMPTY_BEHAVIOR "Empty"

namespace Physics
{
    class  Collider;
    struct Collision;
}

namespace Core
{
    namespace DataStructure
    {
        class GameObject;

        class AdditionalBehavior
        {
        private:

        public:
        
            std::string name {EMPTY_BEHAVIOR};
            Physics::Transform* transform {nullptr};
            GameObject* gameObject {nullptr};

            bool isEnable {true};

            void SetData(Core::DataStructure::GameObject* _gameObject, Physics::Transform* _transform);

            virtual void Start() {};
        
            AdditionalBehavior() {};
            virtual ~AdditionalBehavior(){};
                
            virtual void Update() {};
            
            virtual void OnTrigger(const Physics::Collider  *collider) {};
            virtual void OnCollide(const Physics::Collision &collision) {};
        };
               
    }
}

#endif