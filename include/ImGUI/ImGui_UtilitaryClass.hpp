#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <string>

#include "Player.hpp"
#include "PlayerShoot.hpp"

struct InputManager;

namespace Tools { struct Time; };

struct ImGui_StorageClass
{
    ImGui_StorageClass(ImGuiStyle& _style, ImGuiIO& _IO)
        : style(_style), IO(_IO)
    {}
    
    ImGuiStyle& style;
    ImGuiIO&    IO;

    ImVec2      widowDimensions;
};


class ImGui_ToolClass
{
private:
    bool openOptions    {false};
    bool loadingPanel   {false};
    
    bool remapping      {false};

    ImGuiContext*       context     {nullptr};

    GLFWwindow*         window      {nullptr};
    
    ImGui_StorageClass* components  {nullptr};


    InputManager&       inputs;
    Tools::Time&        time;

    Player*             player      {nullptr};
    PlayerShoot*        playerShoot {nullptr};

    static constexpr float fontAndSlider_MenuSize = 1.f,
                           fontAndSlider_GameSize = 2.f,
                           fontAndSlider_EndSSize = 7.5f;
                         

public:
    bool    showMenu        {true}; 
    bool    showLoseScreen  {false};
    bool    showWinScreen   {false};


    // === Essential init functions ===

    ImGui_ToolClass     (GLFWwindow* _window);

    // You CAN initialize them one after the other, do not worry ! Just put "nullptr" as an argument on the part you do not initialize !
    void InitPlayer     (Player* _player = nullptr, PlayerShoot* _playerShoot = nullptr);

    void Terminate      ();


    // === Frame control functions ===

    void BeginFrame();
    void EndFrame();


    // -=- Private member access if no other possibilities -=-

    ImGui_StorageClass* giveComponents() { return components; };

    
    // -=- Interfaces display functions -=-

    void MainMenuInterface  ();
    void OptionPannel       (ImVec2 win); 
    void RemapableInput     (const char* inputName, Actions act);
    void RemappingInput     (const char* inputName, Actions act);

    void LoseScreen         (const float time);
    void WinScreen          (const float time);

    // --- HUD display functions ---

    // --- HUD display functions ---

    void LifeBar            ();
    void AmmunitionDisplay  ();

    static void StatusBar   (const char* tag, ImGui_StorageClass* components, ImVec2 pos, float length, float value, float maxValue, float minValue = 0);
    static void TextDisp    (const char* tag, ImGui_StorageClass* components, ImVec2 pos, std::string text, ImVec4 color = {1, 1, 1, 1});

    // ? "crossRectSize" is the size of the right rectangle of the cross
    static void crossDisp   (ImGui_StorageClass* components, ImVec2 crossRectSize, ImVec4 crossRectColor, float offsetFromCenter, ImVec2 crossCenter = {-1, -1});
};