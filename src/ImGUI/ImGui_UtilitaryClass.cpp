#include "ImGUI/ImGui_UtilitaryClass.hpp"
#include "Tools/InputManager.hpp"
#include "Tools/TimeManager.hpp"


ImGui_ToolClass::ImGui_ToolClass            (GLFWwindow* _window)
               : window     (_window),
                 inputs     (InputManager::Summon()),
                 time       (Tools::Time::Summon()),
                 context    (ImGui::CreateContext())
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();

    components = new ImGui_StorageClass(ImGui::GetStyle(), ImGui::GetIO());

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    ImGui::StyleColorsClassic();
}

void ImGui_ToolClass::InitPlayer            (Player* _player, PlayerShoot* _playerShoot)
{
    if (player == nullptr)
    {
        if (_player != nullptr)
            player = _player;

        else if (_player == nullptr)
            std::cout << "ImGui_ToolClass warning : Attempted initialization of the player pointer with a nullptr." << std::endl;
    }
    else if (!_playerShoot)
    {
        std::cout << "ImGui_ToolClass warning : Attempted replacement of already initialized player pointer through the InitPlayer function." << std::endl;
    }


    if (playerShoot == nullptr)
    {
        if (_playerShoot != nullptr)
            playerShoot = _playerShoot;

        else if (_playerShoot == nullptr)
            std::cout << "ImGui_ToolClass warning : Attempted initialization of the playerShoot pointer with a nullptr." << std::endl;
    }
    else if (!_player)
    {
        std::cout << "ImGui_ToolClass warning : Attempted replacement of already initialized playerShoot pointer through the InitPlayer function." << std::endl;
    }
}

void ImGui_ToolClass::Terminate             ()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext(context);
}


void ImGui_ToolClass::BeginFrame            ()
{
    int x, y;
    glfwGetWindowSize(window, &x, &y);

    components->widowDimensions     = {static_cast<float>(x), static_cast<float>(y)};
    
    if      (showMenu)                          components->IO.FontGlobalScale = fontAndSlider_MenuSize;
    else if (showLoseScreen || showWinScreen)   components->IO.FontGlobalScale = fontAndSlider_EndSSize;
    else                                        components->IO.FontGlobalScale = fontAndSlider_GameSize;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGui_ToolClass::EndFrame              ()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


void ImGui_ToolClass::MainMenuInterface     ()
{
    components->style.WindowTitleAlign = {0.5f, 0.5f};
    components->style.FrameRounding = 20.f;

    const ImVec2& win = components->widowDimensions;
    
    ImGui::Begin("< < M A I N  M E N U > >", nullptr, ImGuiWindowFlags_NoResize
                                                    | ImGuiWindowFlags_NoMove
                                                    | ImGuiWindowFlags_NoScrollWithMouse
                                                    | ImGuiWindowFlags_NoCollapse);

    ImGui::SetWindowPos({0, 0});
    ImGui::SetWindowSize({win.x, win.y});

    ImGui::SameLine(-1);
    if ( ImGui::Button("New game", {win.x /2 -5, win.y /3}) )
    { showMenu = false; }

    ImGui::SameLine();
    if ( ImGui::Button("Load game", {win.x /2 -5, win.y /3}) )
    { loadingPanel = true; }

    ImGui::NewLine();
    ImGui::SameLine(win.x /4);
    if ( ImGui::Button("Options", {win.x /2, win.y /3}))
    { openOptions = true; }

    ImGui::NewLine(), ImGui::Spacing(), ImGui::NewLine(), ImGui::Spacing();
    ImGui::SameLine(win.x /2.f - win.x /8.f);
    if ( ImGui::Button("EXIT", {win.x /4, win.y /6}) )
    { glfwSetWindowShouldClose(window, 1); }

    ImGui::End();

    if ( openOptions )
    {
        OptionPannel(win);
    }
}

void ImGui_ToolClass::OptionPannel          (ImVec2 win)
{
    ImGui::Begin("> >  O P T I O N  < <", (inputs.catchingInput ? nullptr : &openOptions), ImGuiWindowFlags_NoResize
                                                                                         | ImGuiWindowFlags_NoMove
                                                                                         | ImGuiWindowFlags_NoCollapse
                                                                                         | (inputs.catchingInput ? ImGuiWindowFlags_NoInputs : ImGuiWindowFlags_None));

    ImGui::SetWindowPos({0, 0});
    ImGui::SetWindowSize({win.x, win.y});
    ImGui::SetWindowFocus();

    if (!inputs.catchingInput)
    {
        RemapableInput("Pause button",      Actions::Pause      );

        RemapableInput("Forward input",     Actions::Forward    );
        RemapableInput("Backward input",    Actions::Backwards  );
        RemapableInput("Left input",        Actions::Left       );
        RemapableInput("Right input",       Actions::Right      );

        RemapableInput("Up input",          Actions::Up         );
        RemapableInput("Down input",        Actions::Down       );

        RemapableInput("Jump input",        Actions::Jump       );

        ImGui::Text("Fire trigger");
        ImGui::SameLine(310); ImGui::Text("Autofire");
        if ( ImGui::Button(InputManager::InputName(inputs.keyToAct_Map[Actions::Fire]), {300, 150}) )
        {
            inputs.actionToRemap = Actions::Fire;
            inputs.catchingInput = true;
        }

        ImGui::SameLine(310);
        if ( ImGui::Button(inputs.automaticFire ? "Active" : "Disabled", {150, 100}) )
        { inputs.automaticFire ^= true; }

        RemapableInput("Save trigger",      Actions::Save       );
    }
    else // ============================================================================================
    {
        RemappingInput("Pause button",      Actions::Pause      );

        RemappingInput("Forward input",     Actions::Forward    );
        RemappingInput("Backward input",    Actions::Backwards  );
        RemappingInput("Left input",        Actions::Left       );
        RemappingInput("Right input",       Actions::Right      );

        RemappingInput("Up input",          Actions::Up         );
        RemappingInput("Down input",        Actions::Down       );

        RemappingInput("Jump input",        Actions::Jump       );

        RemappingInput("Fire trigger",      Actions::Fire       );

        RemappingInput("Save trigger",      Actions::Save       );
    }

    ImGui::End();
}

void ImGui_ToolClass::RemapableInput        (const char* inputName, Actions act)
{
    ImGui::Text("%s", inputName);

    if ( ImGui::Button(InputManager::InputName(inputs.keyToAct_Map[act]), {300, 150}) )
    {
        inputs.actionToRemap = act; 
        inputs.catchingInput = true;
    }
}

void ImGui_ToolClass::RemappingInput        (const char* inputName, Actions act)
{
    ImGui::Text("%s", inputName);

    ImGui::Button(inputs.actionToRemap == act ? "Press a key" : InputManager::InputName(inputs.keyToAct_Map[act]), {300, 150});
}


void ImGui_ToolClass::LoseScreen            (const float time)
{
    if (showLoseScreen)
    {
        const ImVec2& win = components->widowDimensions;

        ImGui::Begin("GameOver", nullptr, ImGuiWindowFlags_NoResize
                                        | ImGuiWindowFlags_NoTitleBar
                                        | ImGuiWindowFlags_NoInputs
                                        | ImGuiWindowFlags_NoMove
                                        | ImGuiWindowFlags_NoScrollbar);

        ImGui::SetWindowPos ({0, 0});
        ImGui::SetWindowSize({win.x, win.y});

        components->style.Colors[ImGuiCol_WindowBg] = {1, 0, 0, 1};

        components->IO.FontGlobalScale = 7.5;
        ImGui::SetCursorScreenPos({win.x /2 - 325, win.y /2 - 50});

        ImGui::TextColored({0, 0, 0, 1}, "You lost !...");

        ImGui::End();
    }
}

void ImGui_ToolClass::WinScreen             (const float time)
{
    if (showWinScreen)
    {
        const ImVec2& win = components->widowDimensions;

        ImGui::Begin("Yay you won ^w^", nullptr, ImGuiWindowFlags_NoResize
                                               | ImGuiWindowFlags_NoTitleBar
                                               | ImGuiWindowFlags_NoInputs
                                               | ImGuiWindowFlags_NoMove
                                               | ImGuiWindowFlags_NoScrollbar);

        ImGui::SetWindowPos ({0, 0});
        ImGui::SetWindowSize({win.x, win.y});

        components->style.Colors[ImGuiCol_WindowBg] = {0, 1, 0.25, 1};

        ImGui::SetCursorScreenPos({win.x /2 - 225, win.y /2 - 50});

        ImGui::TextColored({0, 0, 0, 1}, "You won !");

        ImGui::End();
    }
}


void ImGui_ToolClass::LifeBar               ()
{
    if (!player)
    {
        std::cout << "ImGui_ToolClass warning : Attempted to display the player's life slider, but the player is not initialized and equal to nullptr." << std::endl;
    }
    else StatusBar("Life", components, {10, components->widowDimensions.y -50}, 400, player->GetHP(), player->GetHPMax());
}

void ImGui_ToolClass::AmmunitionDisplay     ()
{
    if (!playerShoot)
    {
        std::cout << "ImGui_ToolClass warning : Attempted to display the player's amunition display, but the player is not initialized and equal to nullptr." << std::endl;
    }
    else TextDisp(  "amunition", 
                    components, 
                    {components->widowDimensions.x -350, components->widowDimensions.y -45},
                    "Munitions : " + std::to_string(playerShoot->currentAmmo) + " / " + std::to_string(playerShoot->startAmmo), 
                    {255, 255, 255, 255} );
}

void ImGui_ToolClass::StatusBar             (const char* tag, ImGui_StorageClass* components, ImVec2 pos, float length, float value, float maxValue, float minValue)
{
    ImGui::Begin(tag, nullptr, ImGuiWindowFlags_NoNav
                             | ImGuiWindowFlags_NoDecoration
                             | ImGuiWindowFlags_NoInputs
                             | ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::SetWindowPos (pos);
    ImGui::PushItemWidth(length);

    // Pecentage of value remaining in function of max and min value
    float poVr = ( (value + minValue) / (maxValue + minValue) );

    if ( maxValue == 0 )
        std::cout << "ImGui_ToolClass warning : maxValue in status bar is 0" << std::endl;

    ImGui::PushStyleColor(ImGuiCol_FrameBg, { 1 - poVr , poVr, 0, 1 });

    ImGui::SliderFloat(tag, &value, minValue, maxValue);

    ImGui::PopStyleColor();

    ImGui::End();
}

void ImGui_ToolClass::TextDisp              (const char* tag, ImGui_StorageClass* components, ImVec2 pos, std::string text, ImVec4 color)
{
    ImGui::Begin(tag, nullptr, ImGuiWindowFlags_NoNav
                             | ImGuiWindowFlags_NoDecoration
                             | ImGuiWindowFlags_NoInputs
                             | ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::SetWindowPos(pos);

    ImGui::TextColored(color, "%s", text.c_str());

    ImGui::End();
}

void ImGui_ToolClass::crossDisp             (ImGui_StorageClass* components, ImVec2 crossRectSize, ImVec4 crossRectColor, float offsetFromCenter, ImVec2 crossCenter)
{
    if (crossCenter.x < 0 || crossCenter.y < 0) crossCenter = { components->widowDimensions.x/2, components->widowDimensions.y/2 };
    
    components->style.WindowMinSize = {1, 1};

    ImGui::PushStyleColor(ImGuiCol_WindowBg, crossRectColor);
    
    ImGui::Begin("Cross##pt1", nullptr, ImGuiWindowFlags_NoNav
                                      | ImGuiWindowFlags_NoDecoration
                                      | ImGuiWindowFlags_NoInputs);

    ImGui::SetWindowPos     ({ crossCenter.x + offsetFromCenter, crossCenter.y - crossRectSize.y/2});
    ImGui::SetWindowSize    ({ crossRectSize.x, crossRectSize.y });

    ImGui::End();


    ImGui::Begin("Cross##pt2", nullptr, ImGuiWindowFlags_NoNav
                                      | ImGuiWindowFlags_NoDecoration
                                      | ImGuiWindowFlags_NoInputs);

    ImGui::SetWindowPos     ({ crossCenter.x - crossRectSize.y/2, crossCenter.y + offsetFromCenter});
    ImGui::SetWindowSize    ({ crossRectSize.y, crossRectSize.x});

    ImGui::End();


    ImGui::Begin("Cross##pt3", nullptr, ImGuiWindowFlags_NoNav
                                      | ImGuiWindowFlags_NoDecoration
                                      | ImGuiWindowFlags_NoInputs);

    ImGui::SetWindowPos     ({ crossCenter.x - offsetFromCenter - crossRectSize.x, crossCenter.y - crossRectSize.y/2 });
    ImGui::SetWindowSize    ({ crossRectSize.x, crossRectSize.y });

    ImGui::End();


    ImGui::Begin("Cross##pt4", nullptr, ImGuiWindowFlags_NoNav
                                      | ImGuiWindowFlags_NoDecoration
                                      | ImGuiWindowFlags_NoInputs);

    ImGui::SetWindowPos     ({ crossCenter.x - crossRectSize.y/2, crossCenter.y - offsetFromCenter - crossRectSize.x});
    ImGui::SetWindowSize    ({ crossRectSize.y, crossRectSize.x });

    ImGui::End();

    ImGui::PopStyleColor();
}