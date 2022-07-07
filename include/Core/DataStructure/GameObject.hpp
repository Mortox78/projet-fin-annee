#ifndef _GAMEOBJECT_
#define _GAMEOBJECT_

#include "Mesh.hpp"
#include "Transform.hpp"

namespace Physics
{
    class Collider;
    struct Collision;
}

namespace Core
{
    namespace DataStructure
    {
        class AdditionalBehavior;
        class Mesh;

        //typedef class  Collider  Collider;

        class GameObject
        {
        private:
            LowRenderer::Mesh mesh;

        public:
        
            bool isActive {true};
            bool isCrucial  {false};// Check if the gameObject must be display everytime.
            std::string tag;
            Physics::Transform transform;
            
            std::vector<AdditionalBehavior*> listBehavior;

            GameObject() {};
            ~GameObject(){};

            LowRenderer::Mesh& Mesh();

            AdditionalBehavior *GetBehavior(const std::string &behavName);


            std::vector<AdditionalBehavior*> GetAllBehavior(const std::string &behavName);

            void AddBehavior(AdditionalBehavior *newBehavior);
            
            void Update();

            void OnTriggerAll(const Physics::Collider *collider);
            void OnCollideAll(const Physics::Collision &collision);
            
            friend std::ostream& operator<<(std::ostream& os, const GameObject& player)
            {
                os << player.mesh;
                os << player.transform;
                return os;
            }

            friend std::istream& operator>>(std::istream& is, GameObject& player)
            {
                is >> player.mesh >> player.transform;
                return is;
            }
        };
    }   
}

#endif