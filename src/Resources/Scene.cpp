#include "Scene.hpp"

#include "Plane.hpp"

void Resources::Scene::Display(const Core::Maths::Mat4 &projection, Core::Maths::Mat4 view,
    const std::vector<LowRenderer::Light> &lights, Core::Maths::Mat4 TRS)
{
    if (object)
    {
        object->Mesh().display(projection, view, lights, TRS);
        TRS = TRS * object->Mesh().transform->getMatrix();
    }
    
    for (unsigned int i = 0 ; i < list.size() ; i++)
    {
        list[i]->Display(projection, view, lights, TRS);
    }
}

void Resources::Scene::Read(const Core::Maths::Mat4 &projection, const Core::Maths::Mat4 &view,
    const std::vector<LowRenderer::Light> &lights, Core::Maths::Mat4 TRS)
{
    if (object)
    {
        if (object->isActive)
        {
            object->Update();
            object->Mesh().display(projection, view, lights, TRS);
        }
        TRS = TRS * object->Mesh().transform->getMatrix();
    }
    
    for (unsigned int i = 0 ; i < list.size() ; i++)
    {
        list[i]->Read(projection, view, lights, TRS);
    }
}

void Resources::Scene::OptimizedRead(const LowRenderer::Camera &camera,
                     const std::vector<LowRenderer::Light> &lights, Core::Maths::Mat4 TRS)
{
    if (object)
    {
        if (object->isActive)
        {
            Vec3 ray = camera.GetRaycast();

            Core::Maths::Plane camPlane(camera.pos, ray);          
            object->Update();

            Vec3 posPlus;
            posPlus.x = ray.x * object->transform.scale.x;
            posPlus.y = ray.y * object->transform.scale.y;
            posPlus.z = ray.z * object->transform.scale.z;

            if (!object->isCrucial) 
            {
                if (camPlane.GetSide(object->transform.position + posPlus))
                    object->Mesh().display(camera.matPerspective, camera.matCam, lights, TRS);
            }
            else
            {
                object->Mesh().display(camera.matPerspective, camera.matCam, lights, TRS);
            }
            
        }
        TRS = TRS * object->Mesh().transform->getMatrix();
    }
    
    for (unsigned int i = 0 ; i < list.size() ; i++)
    {
        list[i]->OptimizedRead(camera, lights, TRS);
    }
}

void Resources::Scene::OptimizedReadException(const LowRenderer::Camera &camera,
                     const std::vector<LowRenderer::Light> &lights,
                     std::vector<DisplayData> &listException,
                     const char* exception,
                     Core::Maths::Mat4 TRS)
{
    if (object)
    {
        if (object->isActive)
        {
            Vec3 ray = camera.GetRaycast();

            Core::Maths::Plane camPlane(camera.pos, ray);          
            object->Update();

            Vec3 posPlus;
            posPlus.x = ray.x * object->transform.scale.x;
            posPlus.y = ray.y * object->transform.scale.y;
            posPlus.z = ray.z * object->transform.scale.z;

            if (!object->isCrucial && camPlane.GetSide(object->transform.position + posPlus))
                object->Mesh().display(camera.matPerspective, camera.matCam, lights, TRS);
        }
        TRS = TRS * object->Mesh().transform->getMatrix();
    }
    
    for (unsigned int i = 0 ; i < list.size() ; i++)
    {
        if (list[i]->object->tag != exception)
        {
            list[i]->OptimizedReadException(camera, lights, listException, exception, TRS);
        }
        else
        {
            listException.push_back(DisplayData(TRS, list[i]->object));
        }
        
    }
}