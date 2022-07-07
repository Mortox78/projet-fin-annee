#include "Mesh.hpp"
#include "Camera.hpp"
#include "Scene.hpp"
#include "Assertion.hpp"
#include "ResourcesManager.hpp"

#include "TimeManager.hpp"

#include "AdditionalBehavior.hpp"

#include "GameObject.hpp"

#include "SaveManager.hpp"
#include "InputManager.hpp"

#include <iostream>

#include "Collider.hpp"
#include "SphereCollider.hpp"
#include "OrientedBoxCollider.hpp"

#include "CharacterPhysicBody.hpp"
#include "PhysicBody.hpp"

#include "ImGui_UtilitaryClass.hpp"
#include "PlayerCamera.hpp"

#include "MapLoader.hpp"

#include "Player.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "Sprite.hpp"
#include "PlayerShoot.hpp"
#include "PlayerShoot.hpp"
#include "Sprite.hpp"

int main(int argc, char *argv[])
{
    int screenWidth = 1200;
    int screenHeight = 800;

    // Init GLFW
    if (!glfwInit())
    {
        fprintf(stderr, "glfwInit failed.\n");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    // Create window
    GLFWwindow *window = glfwCreateWindow(screenWidth, screenHeight, "Fenaitre", NULL, NULL);
    if (!window)
    {
        fprintf(stderr, "glfwCreateWindow failed.\n");
        glfwTerminate();
        return -1;
    }

    glfwSwapInterval(1); // Enable v-sync

    glfwMakeContextCurrent(window);

    // Load OpenGL functions
    if (!gladLoadGL())
    {
        fprintf(stderr, "gladLoadGL failed.\n");
        glfwTerminate();
        return -1;
    }

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create and compile our GLSL program from the shaders
    Resources::Shader textureID("include/Resources/Shader/BasicVertexShader.vs", "include/Resources/Shader/TextureFragmentShader.fs");
    Resources::Shader simpleID("include/Resources/Shader/BasicVertexShader.vs", "include/Resources/Shader/ColorFragmentShaderNoLight.fs");

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    Tools::Time &timeManager = Tools::Time::Summon();
    timeManager.Update();

    Resources::MapLoader map;

    map.loadMap("./resources/Map.mp");

    //PLAYER
    Core::DataStructure::GameObject player;
    player.transform = Physics::Transform({0.5f, 8.f, 0.5f}, {0.2f, 0.2f, 0.2f}, {0.f, 0.f, 0.f});
    player.Mesh().shader = &simpleID;
    Physics::CharacterPhysicBody playerPhysicBody;
    player.AddBehavior(&playerPhysicBody);
    Player ply;
    player.AddBehavior(&ply);
    player.tag = "player";

    //WEAPON
    Core::DataStructure::GameObject weapon;
    weapon.transform = Physics::Transform({0.3f, -0.55f, 0.f}, {0.08f, 0.08f, 0.08f}, {0, 0, 3.14f});
    weapon.tag = "weapon";
    weapon.Mesh().models.push_back(Resources::ResourcesManager::LoadOBJ("resources/deagle.obj"));
    weapon.Mesh().shader = &simpleID;

    weapon.transform = Physics::Transform({0.80f, -0.65f, -1.f}, {5.f, 5.f, 5.f}, {-(3.14f/2.f), 0, 0});
    weapon.tag = "weapon";
    weapon.Mesh().models.push_back(Resources::ResourcesManager::LoadOBJ("resources/Ak_47/ak47.obj"));
    weapon.Mesh().textures.push_back(Resources::ResourcesManager::LoadTex("./resources/DirtCube.jpg"));
    weapon.Mesh().textures.push_back(Resources::ResourcesManager::LoadTex("./resources/DirtCube.jpg"));
    weapon.Mesh().shader = &textureID;
    weapon.isCrucial = true;

    Resources::Scene world;
    Resources::Scene playerScene;
    playerScene.object = &player;
    playerScene.Add(&weapon);

    //LIGHT
    LowRenderer::Light light;
    light.ambient = {0.3f, 0.3f, 0.3f};
    light.direction = {0.0f, 0.0f, 0.0f};
    light.diffuse = {0.9f, 0.7f, 0.7f};
    light.specular = {0.0f, 1.0f, 0.0f};
    light.constant = 1.0f;
    light.linear = 0.014f;
    light.quadratic = 0.007f;

    std::vector<LowRenderer::Light> lights;
    lights.push_back(light);

    world.Add(&playerScene);

    // Main loop

    //CAMERA
    LowRenderer::Camera camera(66, screenWidth, screenHeight, 0.01, 1000);
    camera.firstPerson = true;
    camera.window = window;
    
    //PLAYER_CAMERA
    PlayerCamera playerCamera(&camera, &player.transform, &playerPhysicBody);
    player.AddBehavior(&playerCamera);
    player.AddBehavior(new PlayerShoot(&playerCamera, &world, &simpleID));

    Core::DataStructure::AdditionalBehavior *chara = player.GetBehavior(CHARACTER_PHYSIC_BODY);
    Physics::CharacterPhysicBody *phB = (Physics::CharacterPhysicBody *)chara;

    phB->SpeedLimit.y = 10;

    InputManager &inputs = InputManager::Summon(window);
    ImGui_ToolClass imGui(window);

    imGui.InitPlayer( dynamic_cast<Player*>(player.GetBehavior("player")), dynamic_cast<PlayerShoot*>(player.GetBehavior("PLAYERSHOOTBEHAVIOR")) );

    Capsule cap({0,0,0}, {1,0,0}, 1, 1);
    Segment seg({-1,0,0}, {3,0,0});
    Hit hit;

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    bool gameLose = false;

    while (!glfwWindowShouldClose(window))
    {
        timeManager.Update();
        inputs.Update();

        imGui.BeginFrame();

        if (imGui.showMenu)
        {
            imGui.MainMenuInterface();
            imGui.crossDisp(imGui.giveComponents(), {10, 5}, {1, 1, 1, 1}, 5, {inputs.mousePos.x, inputs.mousePos.y});
        }
        else if (imGui.showLoseScreen)
        {
            imGui.LoseScreen(350);
        }
        else if (imGui.showWinScreen)
        {
            imGui.WinScreen(985);
        }
        else
        {
                        
            if (glfwGetKey(window, GLFW_KEY_ESCAPE))
                glfwSetWindowShouldClose(window, 1);

            // Set all the pixel of the screen to the same color (here black)
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.2f, 0.1f, 0.1f, 1.f);

            world.OptimizedRead(camera, lights);
            lights[0].position = player.transform.position + Vec3(0,1,0);

            map.ReadActiveScene(camera, lights);

            imGui.crossDisp(imGui.giveComponents(), {10, 5}, {1, 1, 1, 1}, 5, {(float)screenWidth/2, (float)screenHeight/2});
            imGui.LifeBar();
            imGui.AmmunitionDisplay();
        }

        imGui.EndFrame();

        // Present buffer
        glfwSwapBuffers(window);
    }

    imGui.Terminate();
    glfwTerminate();

    return 0;
}
