#include "GameObject.hpp"
#include "AdditionalBehavior.hpp"
#include "Collider.hpp"

using namespace Core::DataStructure;
using namespace Physics;

LowRenderer::Mesh &GameObject::Mesh()
{
    if (mesh.transform != &transform)
       mesh.transform = &transform;
    return mesh;
};

AdditionalBehavior *GameObject::GetBehavior(const std::string &behavName)
{
    for (unsigned i = 0; i < listBehavior.size(); i++)
    {
        if (listBehavior[i]->name == behavName)
        {
            return listBehavior[i];
        }
    }
    return nullptr;
}

std::vector<AdditionalBehavior*> GameObject::GetAllBehavior(const std::string &behavName)
{
    std::vector<AdditionalBehavior> listResult;

    for (unsigned i = 0; i < listBehavior.size(); i++)
    {
        if (listBehavior[i]->name == behavName)
        {
            listBehavior.push_back(listBehavior[i]);
        }
    }
    return listBehavior;
}

void GameObject::AddBehavior(AdditionalBehavior *newBehavior)
{
    listBehavior.push_back(newBehavior);
    listBehavior[listBehavior.size() - 1]->SetData(this, &transform);
    listBehavior[listBehavior.size() - 1]->Start();
}

void GameObject::Update()
{
    if (!isActive)
        return;

    for (unsigned i = 0; i < listBehavior.size(); i++)
    {
        if (listBehavior[i]->isEnable)
        {
            listBehavior[i]->Update();
        }
    }
}

void GameObject::OnTriggerAll(const Physics::Collider *collider)
{
    for (unsigned int i = 0 ; i < listBehavior.size() ; i++)
    {
        listBehavior[i]->OnTrigger(collider);
    }
}

void GameObject::OnCollideAll(const Collision &collision)
{
    for (unsigned int i = 0 ; i < listBehavior.size() ; i++)
    {
        listBehavior[i]->OnCollide(collision);
    }
}