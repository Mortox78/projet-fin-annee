#include "ResourcesManager.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"

using namespace Resources;

std::vector<Model> ResourcesManager::models = std::vector<Resources::Model>();
std::vector<Texture> ResourcesManager::textures = std::vector<Resources::Texture>();
std::vector<Shader*> ResourcesManager::shaders = std::vector<Resources::Shader*>();


ResourcesManager::ResourcesManager()
{

}

ResourcesManager::~ResourcesManager()
{
    /*for (unsigned int i = 0; i < models.size(); ++i)
        // Delete                                     */
    //for (unsigned int i = 0; i < textures.size(); ++i)
    //    glDeleteTextures(1, &textures[i].nbTexture);
}


// This function return a mesh with only one OBJ and one texture
LowRenderer::Mesh ResourcesManager::LoadSingleMesh(const char* objFileName, const char* texFileName)
{
    LowRenderer::Mesh askedMesh;

    askedMesh.models[0] = LoadOBJ(objFileName);
    askedMesh.textures[0] = LoadTex(texFileName);

    //askedMesh.load_buffers();
    return askedMesh;
}

Resources::Model ResourcesManager::LoadOBJ(const char* objFileName)
{
    Resources::Model askedModel;

    // looking for asked model
    for (std::vector<Model>::iterator it = models.begin(); it != models.end(); ++it)
    {
        if (it->data.name == objFileName)
            askedModel = *it;
    }

    // if model not found, add it to the resourcesManager and return askedModel
    if (!askedModel.data.loaded)
    {
        askedModel = Model(objFileName);
        models.push_back(askedModel);
        std::cout << "Didn't find \"" + std::string(objFileName) + "\" in resourcesManager -> Adding it in resourcesManager's list" << std::endl;
    }
    else
    {
        std::cout << "Found OBJ in resourcesManager" << std::endl;
    }

    return askedModel;
}


Resources::Texture ResourcesManager::LoadTex(const char* texFileName, bool antiAliasing)
{
    Resources::Texture askedTex;

    // looking for asked texture
    for (std::vector<Texture>::iterator it = textures.begin(); it != textures.end(); ++it)
    {
        if (it->name == texFileName)
            askedTex = *it;
    }

    // if texture not found, add it to the resourcesManager and return askedTex
    if (!askedTex.loaded)
    {
        askedTex = Texture(texFileName, antiAliasing
        );
        textures.push_back(askedTex);
        std::cout << "Didn't find \"" + std::string(texFileName) + "\" texture in resourcesManager -> Adding it in resourcesManager's list" << std::endl;
    }
    else
    {
        //std::cout << "Found texture in resourcesManager" << std::endl;
    }

    return askedTex;
}

Resources::Shader* ResourcesManager::LoadShader(const char *vertex_file_path, const char *fragment_file_path)
{
    Shader* sh = nullptr;

    // looking for asked shaders
    for (std::vector<Resources::Shader*>::iterator it = shaders.begin(); it != shaders.end(); ++it)
    {
        if ((*it)->vertexShaderPath == vertex_file_path && (*it)->fragmentShaderPath == fragment_file_path)
        {
            sh = (*it);
        }        
    }
    
    // if texture not found, add it to the resourcesManager and return askedTex
    if (!sh)
    {
        shaders.push_back(new Shader(vertex_file_path, fragment_file_path));
        sh = shaders[shaders.size() - 1];
        //std::cout << "Didn't find \"" + std::string(texFileName) + "\" texture in resourcesManager -> Adding it in resourcesManager's list" << std::endl;
    }
    else
    {
        //std::cout << "Found texture in resourcesManager" << std::endl;
    }

    return sh;
}