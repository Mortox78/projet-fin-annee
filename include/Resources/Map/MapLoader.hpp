#ifndef _MAPLOADER_
#define _MAPLOADER_

#include <limits.h>
#include <string>
#include <cstdlib>

#include <iostream>

#include <ctime>
#include <cstdio>
#include <fstream>
#include <sstream>

#include "Mesh.hpp"
#include "Camera.hpp"
#include "Scene.hpp"
#include "Assertion.hpp"
#include "ResourcesManager.hpp"

#include "AdditionalBehavior.hpp"

#include "GameObject.hpp"
#include "SwitchSceneBehavior.hpp"

namespace Resources
{
    class MapLoader
    {
    private:
    public:
        MapLoader() {};

        Scene* oldScene {nullptr};
        Scene* newScene {nullptr};
        
        bool SceneEnded {false};
        std::vector<Scene *> listScene;

        void ReloadMap(const char* location);

        void loadMap(const char* location);
        void LoadRoom(std::ifstream &in, std::vector<Resources::Shader*> &listShader, std::vector<std::string> &elementList);
        bool ReadActiveScene(LowRenderer::Camera &camera, std::vector<LowRenderer::Light> &ligths);
        void SwitchScene(unsigned int _newScene, unsigned int _oldScene);

    };
    
}

#endif