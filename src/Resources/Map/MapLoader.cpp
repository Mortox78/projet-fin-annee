#include "MapLoader.hpp"

#include "OrientedBoxCollider.hpp"
#include "SwitchSceneBehavior.hpp"

#include "EnemyManager.hpp"
#include "Enemy.hpp"
#include "PhysicBody.hpp"

#include "Sprite.hpp"

using namespace Resources;

void MapLoader::ReloadMap(const char* location)
{
    oldScene = nullptr;
    newScene = nullptr;

    listScene.clear();
    SceneEnded = false;

    loadMap(location);
}

void MapLoader::loadMap(const char* location)
{
    std::ifstream in(location, std::ios::in);
    if (!in) {std::cerr << "Impossible to open " << location << std::endl; exit(EXIT_FAILURE);}

    std::vector<Resources::Shader*> listShader;

    char dump;

    std::string line;
    Core::Maths::Vec3 scale;

    std::vector<std::string> elementList;

    while(getline(in, line))
    {
        if (line.substr(0,2) == "Sh")
        {
            std::string vertex;
            std::string fragment;
            std::istringstream s(line.substr(2));

            s >> vertex;
            s >> fragment;

            listShader.push_back(Resources::ResourcesManager::LoadShader(vertex.c_str(), fragment.c_str()));
        }
        if (line.substr(0,1) == "T")
        {
            std::string Line;
            bool antiAliasing;

            std::istringstream s(line.substr(2));
            s >> Line;
            s >> antiAliasing;

            Resources::ResourcesManager::LoadTex(Line.c_str(), antiAliasing);

            elementList.push_back(Line);
        }
        if (line.substr(0, 1) == "S")
        {
            std::istringstream s(line.substr(2));
            s >> scale.x;s >> scale.y;s >> scale.z;
        }
        if (line.substr(0,3) == "R {")
        {
            LoadRoom(in, listShader, elementList);
        }
    }
}

void MapLoader::LoadRoom(std::ifstream &in, std::vector<Resources::Shader*> &listShader, std::vector<std::string> &elementList)
{
    bool firstRoom = (listScene.size() > 0);

    listScene.push_back(new Resources::Scene());

    EnemyManager* enemyManager = nullptr;
    char dump;

    std::string line;
    Core::Maths::Vec3 scale;

    while(getline(in, line))
    {
        if (line.substr(0,3) == "E }")// E end of a room
        {
            return;
        }
        else if (line.substr(0, 1) == "S")// S determinate scale of block
        {
            std::istringstream s(line.substr(2));
            s >> scale.x;s >> scale.y;s >> scale.z;
        }
        else if (line.substr(0,6) == "switch") // switch create a transition platform for the next room
        {
            Vec3 pos;
            Vec3 Scl;
            std::string texture;
            unsigned int oldScene;
            unsigned int newScene;
            int shader;
            int type;

            std::istringstream s(line.substr(6));
            s >> type;
            s >> shader;
            s >> pos.x; s >> dump >> pos.y; s >> dump >> pos.z;
            s >> Scl.x; s >> dump >> Scl.y; s >> dump >> Scl.z;
            s >> oldScene; s >> dump; s >> newScene;
        
            listScene[listScene.size() - 1]->Add(new Core::DataStructure::GameObject());

            listScene[listScene.size() - 1]->list[listScene[listScene.size() - 1]->list.size() - 1]->object->transform = Physics::Transform(pos, Scl, {0, 0, 0});
            listScene[listScene.size() - 1]->list[listScene[listScene.size() - 1]->list.size() - 1]->object->Mesh().models.push_back(Resources::Model::CreateCube());
            listScene[listScene.size() - 1]->list[listScene[listScene.size() - 1]->list.size() - 1]->object->Mesh().textures.push_back(Resources::ResourcesManager::LoadTex(elementList[type].c_str()));
            listScene[listScene.size() - 1]->list[listScene[listScene.size() - 1]->list.size() - 1]->object->Mesh().shader = listShader[shader];
            listScene[listScene.size() - 1]->list[listScene[listScene.size() - 1]->list.size() - 1]->object->AddBehavior(new SwitchSceneBehavior(oldScene, newScene, this));

            listScene[listScene.size() - 1]->list[listScene[listScene.size() - 1]->list.size() - 1]->object->isActive = false;
            


        }
        else if (line.substr(0,1) == "s") // s is the floor
        {
            Vec3 pos;
            Vec2 length;
            int shader;
            int type;

            std::istringstream s(line.substr(2));
            s >> type;
            s >> shader;
            s >> pos.x; s >> dump >> pos.y; s >> dump >> pos.z;
            s >> length.x; s >> dump >> length.y;

            Vec3 tempPos;
            tempPos.x = pos.x - length.x * (scale.x / 2) + (scale.x / 2);
            tempPos.y = pos.y;
            tempPos.z = pos.z - length.y * (scale.z / 2) + (scale.z / 2);

            listScene[listScene.size() - 1]->Add(new Core::DataStructure::GameObject());
            listScene[listScene.size() - 1]->list[listScene[listScene.size() - 1]->list.size() - 1]->object->transform = Physics::Transform(pos, {scale.x * (length.x), scale.y, scale.z * (length.y)}, {0,0,0});
            listScene[listScene.size() - 1]->list[listScene[listScene.size() - 1]->list.size() - 1]->object->AddBehavior(new Physics::OrientedBoxCollider());

            if (firstRoom)
                listScene[listScene.size() - 1]->list[listScene[listScene.size() - 1]->list.size() - 1]->object->isActive = false;

            for (unsigned int i = 0 ; i < length.x; i++)
            {
                for (unsigned int e = 0 ; e < length.y ; e++)
                {
                    listScene[listScene.size() - 1]->Add(new Core::DataStructure::GameObject());
                 
                    listScene[listScene.size() - 1]->list[listScene[listScene.size() - 1]->list.size() - 1]->object->transform = Physics::Transform(tempPos, scale, {0, 0, 0});
                    listScene[listScene.size() - 1]->list[listScene[listScene.size() - 1]->list.size() - 1]->object->Mesh().models.push_back(Resources::Model::CreateSpriteCubeY());
                    listScene[listScene.size() - 1]->list[listScene[listScene.size() - 1]->list.size() - 1]->object->Mesh().textures.push_back(Resources::ResourcesManager::LoadTex(elementList[type].c_str()));
                    listScene[listScene.size() - 1]->list[listScene[listScene.size() - 1]->list.size() - 1]->object->Mesh().shader = listShader[shader];
                    
                    tempPos.z += scale.z;
                }
                tempPos.z -= length.y * scale.z;
                tempPos.x += scale.x;
            }
        }
        else if (line.substr(0,1) == "c") // c create a cube
{
            Vec3 pos;
            Vec3 length;
            int shader;
            int type;

            std::istringstream s(line.substr(2));
            s >> type;
            s >> shader;
            s >> pos.x; s >> dump >> pos.y; s >> dump >> pos.z;
            s >> length.x; s >> dump >> length.y; s >> dump >> length.z;

            Vec3 tempPos;
            tempPos.x = pos.x - length.x * (scale.x / 2) + (scale.x / 2);
            tempPos.y = pos.y - length.y * (scale.y / 2) + (scale.y / 2);;
            tempPos.z = pos.z - length.z * (scale.z / 2) + (scale.z / 2);

            listScene[listScene.size() - 1]->Add(new Core::DataStructure::GameObject());
            listScene[listScene.size() - 1]->list[listScene[listScene.size() - 1]->list.size() - 1]->object->transform = Physics::Transform(pos, {scale.x * (length.x), scale.y * (length.y), scale.z * (length.z)}, {0,0,0});
            listScene[listScene.size() - 1]->list[listScene[listScene.size() - 1]->list.size() - 1]->object->AddBehavior(new Physics::OrientedBoxCollider());

            if (firstRoom)
                listScene[listScene.size() - 1]->list[listScene[listScene.size() - 1]->list.size() - 1]->object->isActive = false;

            for (unsigned int i = 0 ; i < length.y; i++)
            {
                for (unsigned int i = 0 ; i < length.x; i++)
                {
                    for (unsigned int e = 0 ; e < length.z ; e++)
                    {
                        if (abs((tempPos.x - pos.x) / (length.x/2)) + abs(scale.x / length.x) == abs(scale.x)
                        || abs((tempPos.y - pos.y) / (length.y/2)) + abs(scale.y / length.y) == abs(scale.y)
                        || abs((tempPos.z - pos.z) / (length.z/2)) + abs(scale.z / length.z) == abs(scale.z))
                        {
                            listScene[listScene.size() - 1]->Add(new Core::DataStructure::GameObject());

                            listScene[listScene.size() - 1]->list[listScene[listScene.size() - 1]->list.size() - 1]->object->transform = Physics::Transform(tempPos, scale, {0, 0, 0});
                            listScene[listScene.size() - 1]->list[listScene[listScene.size() - 1]->list.size() - 1]->object->Mesh().models.push_back(Resources::Model::CreateCube());
                            listScene[listScene.size() - 1]->list[listScene[listScene.size() - 1]->list.size() - 1]->object->Mesh().textures.push_back(Resources::ResourcesManager::LoadTex(elementList[type].c_str()));
                            listScene[listScene.size() - 1]->list[listScene[listScene.size() - 1]->list.size() - 1]->object->Mesh().shader = listShader[shader];
                        }

                        tempPos.z += scale.z;
                    }
                    tempPos.z -= length.z * scale.z;
                    tempPos.x += scale.x;
                }
                tempPos.y += scale.y;
                tempPos.x -= length.x * scale.x;
            }
        }
        else if (line.substr(0,3) == "w [")// w create wave of enemy
        {
            if (!enemyManager)
            {
                listScene[listScene.size() - 1]->Add(new Core::DataStructure::GameObject());
                listScene[listScene.size() - 1]->list[listScene[listScene.size() - 1]->list.size() - 1]->object->AddBehavior(new EnemyManager());
                enemyManager = dynamic_cast<EnemyManager*>(listScene[listScene.size() - 1]->list[listScene[listScene.size() - 1]->list.size() - 1]->object->listBehavior[0]);
            }

            enemyManager->waveList.push_back(Wave());            
        }       
        else if (line.substr(0,1) == "e") // e create define enemy
        {
            unsigned int shader;
            float height;
            Vec3 pos;
            Vec3 scl;
            Vec2 spawnRange;
            unsigned int nbTexture;
            std::vector<std::string> textureList;
            std::string texture;
            unsigned int size;

            std::istringstream s(line.substr(2));

            s>>shader;
            s>>nbTexture;s>>dump;
            for (unsigned int i = 0 ; i < nbTexture ; i++)
            {
                s>>texture;
                textureList.push_back(texture);
            }
            s >> pos.x; s >> dump >> pos.y; s >> dump >> pos.z;
            s >> scl.x; s >> dump >> scl.y; s >> dump >> scl.z;
            s >> spawnRange.x; s >> dump >> spawnRange.y;
            s>>size;


            for (unsigned int i = 0 ; i < size ; i++)
            {
                listScene[listScene.size() - 1]->Add(new Core::DataStructure::GameObject());

                listScene[listScene.size() - 1]->list[listScene[listScene.size() - 1]->list.size() - 1]->object->transform = Physics::Transform({pos.x + (rand() % (int)spawnRange.x * 1000) / 1000 - (spawnRange.x / 2), pos.y, pos.z + (rand() % (int)spawnRange.y * 1000) / 1000 - (spawnRange.y / 2)}, scl, {0, 0, 0});
                listScene[listScene.size() - 1]->list[listScene[listScene.size() - 1]->list.size() - 1]->object->tag = "enemy";
                listScene[listScene.size() - 1]->list[listScene[listScene.size() - 1]->list.size() - 1]->object->AddBehavior(new Enemy(1,1,1,1));
                listScene[listScene.size() - 1]->list[listScene[listScene.size() - 1]->list.size() - 1]->object->AddBehavior(new Physics::PhysicBody());
                listScene[listScene.size() - 1]->list[listScene[listScene.size() - 1]->list.size() - 1]->object->AddBehavior(new Physics::OrientedBoxCollider(true));
                listScene[listScene.size() - 1]->list[listScene[listScene.size() - 1]->list.size() - 1]->object->Mesh().models.push_back(Resources::Model::CreateSpriteCube());
                
                listScene[listScene.size() - 1]->list[listScene[listScene.size() - 1]->list.size() - 1]->object->AddBehavior(new Resources::Sprite());

                Resources::Sprite* sprite = dynamic_cast<Resources::Sprite*>(listScene[listScene.size() - 1]->list[listScene[listScene.size() - 1]->list.size() - 1]->object->GetBehavior(SPRITEBEHAVIOR));
                sprite->animate = true;
                sprite->Delay(0.5f);

                listScene[listScene.size() - 1]->list[listScene[listScene.size() - 1]->list.size() - 1]->object->Mesh().textures.push_back(Resources::ResourcesManager::LoadTex(textureList[0].c_str()));

                for (unsigned int i = 0 ; i < textureList.size() ; i++)
                {
                    std::cout << "texture Sprite [" << i << "] = " << textureList[i] << std::endl;
                    sprite->AddSprite(textureList[i].c_str());
                }
                listScene[listScene.size() - 1]->list[listScene[listScene.size() - 1]->list.size() - 1]->object->Mesh().shader = listShader[shader];

                listScene[listScene.size() - 1]->list[listScene[listScene.size() - 1]->list.size() - 1]->object->isActive = false;
            
                enemyManager->waveList[enemyManager->waveList.size() - 1].listEnemy.push_back(listScene[listScene.size() - 1]->list[listScene[listScene.size() - 1]->list.size() - 1]->object);
            }
        }
        else if (line.substr(0,1) == "O")
        {
            std::cout << "=== Object ===" << std::endl;

            std::string obj;
            std::string text;
            Vec3 pos;
            Vec3 sca;
            Vec3 rotation;
            int shader;

            std::istringstream s(line.substr(2));
            
            s >> shader;
            s >> obj;
            s >> text;
            s >> pos.x; s >> dump >> pos.y; s >> dump >> pos.z;
            s >> sca.x; s >> dump >> sca.y; s >> dump >> sca.z;
            s >> rotation.x; s >> dump >> rotation.y; s >> dump >> rotation.z;
            
            listScene[listScene.size() - 1]->Add(new Core::DataStructure::GameObject());

            listScene[listScene.size() - 1]->list[listScene[listScene.size() - 1]->list.size() - 1]->object->transform = Physics::Transform(pos, sca, rotation);
            listScene[listScene.size() - 1]->list[listScene[listScene.size() - 1]->list.size() - 1]->object->AddBehavior(new Physics::OrientedBoxCollider());
            listScene[listScene.size() - 1]->list[listScene[listScene.size() - 1]->list.size() - 1]->object->Mesh().models.push_back(Resources::ResourcesManager::LoadOBJ(obj.c_str()));
            listScene[listScene.size() - 1]->list[listScene[listScene.size() - 1]->list.size() - 1]->object->Mesh().textures.push_back(Resources::ResourcesManager::LoadTex(text.c_str()));
            listScene[listScene.size() - 1]->list[listScene[listScene.size() - 1]->list.size() - 1]->object->Mesh().shader = listShader[shader];
            
        }
    }

}


bool MapLoader::ReadActiveScene(LowRenderer::Camera &camera, std::vector<LowRenderer::Light> &ligths)
{
    if (SceneEnded)
    {
        ligths[0].specular = {0.0f, 1.0f, 0.0f};
    }
    else
    {
        ligths[0].specular = {1.0f, 0.0f, 0.0f};
    }
    

    std::vector<DisplayData> listEnemy;

    if (oldScene)
    {
        oldScene->OptimizedReadException(camera, ligths, listEnemy, "enemy");
    }
    else
    {
        if (listScene.size() > 0)
        {
            oldScene = listScene[0];
            oldScene->OptimizedReadException(camera, ligths, listEnemy, "enemy");
        }
    }
    if (newScene)
    {
        newScene->OptimizedReadException(camera, ligths, listEnemy, "enemy");
    }

    if (SceneEnded)
    {
        return false;
    }

    std::vector<Vec2> displayOrder;
    float distance;
    
    for (unsigned int i = 0 ; i < listEnemy.size() ; i++)
    {
        if (listEnemy[i].object->isActive)
        {
            if (listEnemy[i].object->transform.position.y < -10)
            {
                listEnemy[i].object->isActive = false;
            }

            displayOrder.push_back({(float)i, (camera.pos - listEnemy[i].object->transform.position).GetSqrMagnitude()});
        }
    }

    if (displayOrder.size() == 0)
    {
        if (!SceneEnded)
        {
            SceneEnded = true;
        }
        else if (SceneEnded)
        {
            if (newScene)
            {
                for (unsigned int i = 0; i < newScene->list.size() ; i++)
                {
                    if (newScene->list[i]->object->tag == "switch")
                        newScene->list[i]->object->isActive = true;
                }
            }
            if (oldScene)
            {
                for (unsigned int i = 0; i < oldScene->list.size() ; i++)
                {
                    if (oldScene->list[i]->object->tag == "switch")
                        oldScene->list[i]->object->isActive = true;
                }
            }
            if (newScene == listScene[listScene.size() - 1])
            {
                return true;
            }
        }

        return false;
    }
    else
    {
        SceneEnded = false;
        if (newScene)
        {
            for (unsigned int i = 0; i < newScene->list.size() ; i++)
            {
                if (newScene->list[i]->object->tag == "switch")
                    newScene->list[i]->object->isActive = false;
            }
        }
        if (oldScene)
        {
            for (unsigned int i = 0; i < oldScene->list.size() ; i++)
            {
                if (oldScene->list[i]->object->tag == "switch")
                    oldScene->list[i]->object->isActive = false;
            }
        }
    }

    
    for (unsigned int i = 0 ; i < displayOrder.size() ; i++) // Set the list of enemy from closer to farest to make the tranparency work
    {
        for (unsigned int e = 0 ; e < displayOrder.size() - i ; e++)
        {
            if (displayOrder[e].y < displayOrder[e + 1].y)
            {
                Vec2 temp;
                temp = displayOrder[e];
                displayOrder[e] = displayOrder[e + 1];
                displayOrder[e + 1] = temp;
            }
        }
    }

    for (unsigned int i = 0 ; i < displayOrder.size() ; i++) 
    {
        listEnemy[displayOrder[i].x].object->Mesh().display(camera.matPerspective, camera.matCam, ligths, listEnemy[displayOrder[i].x].trs);
    }

    return false;
}

void MapLoader::SwitchScene(unsigned int _newScene, unsigned int _oldScene)
{    
    if (newScene && newScene != listScene[_newScene] && newScene != listScene[_oldScene])
    {

        for (unsigned int i = 0; i < newScene->list.size() ; i++)
        {
            if (newScene->list[i]->object->tag != "switch")
                newScene->list[i]->object->isActive = false;
        }
    }
    
    newScene = listScene[_newScene];
    
    for (unsigned int i = 0; i < newScene->list.size() ; i++)
    {
        if (newScene->list[i]->object->tag != "switch" && newScene->list[i]->object->tag != "enemy")
            newScene->list[i]->object->isActive = true;
    }
    
    if (oldScene != listScene[_newScene] && oldScene != listScene[_oldScene])
    {
        for (unsigned int i = 0; i < oldScene->list.size() ; i++)
        {
            if (oldScene->list[i]->object->tag != "switch")
                oldScene->list[i]->object->isActive = false;
        }
    }
    oldScene = listScene[_oldScene];
}