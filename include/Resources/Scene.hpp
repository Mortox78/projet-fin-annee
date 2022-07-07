#ifndef _SCENE_
#define _SCENE_

#include "Graph.hpp"
#include "Light.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"

#include "Enemy.hpp"
#include "GameObject.hpp"

namespace Resources
{
    struct DisplayData
    {
        DisplayData(){};
        DisplayData(const Core::Maths::Mat4 &_trs, Core::DataStructure::GameObject* _object) : trs{_trs}, object{_object} {};

        Core::Maths::Mat4 trs;
        Core::DataStructure::GameObject* object;
    };
    


    class Scene : public Core::DataStructure::Graph<Core::DataStructure::GameObject, Scene>
    {
    public:
        Scene()  = default;
        ~Scene() = default;
    
        void Display(const Core::Maths::Mat4 &projection, Core::Maths::Mat4 view,
                     const std::vector<LowRenderer::Light> &lights, Core::Maths::Mat4 TRS = Maths::Mat4::GetIdentityMatrix());

        void Read(const Core::Maths::Mat4 &projection, const Core::Maths::Mat4 &view,
                     const std::vector<LowRenderer::Light> &lights, Core::Maths::Mat4 TRS = Maths::Mat4::GetIdentityMatrix());

        void OptimizedRead(const LowRenderer::Camera &camera,
                     const std::vector<LowRenderer::Light> &lights, Core::Maths::Mat4 TRS = Maths::Mat4::GetIdentityMatrix());
        
        void OptimizedReadException(const LowRenderer::Camera &camera,
                     const std::vector<LowRenderer::Light> &lights,
                     std::vector<DisplayData> &listException,
                     const char* exception, 
                     Core::Maths::Mat4 TRS = Maths::Mat4::GetIdentityMatrix());
    };
}


#endif