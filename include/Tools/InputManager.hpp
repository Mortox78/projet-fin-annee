#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include <GLFW/glfw3.h>
#include <iostream>

#include <string>

#include "vector2D.hpp"
using namespace Core::Maths;

enum Inputs
{
    alpha_A, alpha_B, alpha_C, alpha_D, alpha_E, alpha_F, alpha_G, alpha_H, alpha_I, alpha_J, alpha_K, alpha_L, alpha_M, alpha_N, alpha_O, alpha_P, alpha_Q, alpha_R, alpha_S, alpha_T, alpha_U, alpha_V, alpha_W, alpha_X, alpha_Y, alpha_Z,    
    numeral_0, numeral_1, numeral_2, numeral_3, numeral_4, numeral_5, numeral_6, numeral_7, numeral_8, numeral_9,
    function_1, function_2, function_3, function_4, function_5, function_6, function_7, function_8, function_9, function_10, function_11, function_12, function_13, function_14, function_15, function_16, function_17, function_18, function_19, function_20, function_21, function_22, function_23, function_24, function_25,
    arrow_right, arrow_left, arrow_down, arrow_up,
    mouse_left, mouse_right, mouse_middle,
    other_ESC, other_SPACE,

    NUM_OF_KEYS
};

enum Actions
{
    Pause,
    Left, Right, Forward, Backwards,
    Up, Down,
    Jump,
    Fire, WeaponSwitch,
    Save,

    NUM_OF_ACTS
};

struct InputManager
{
    /*
        * Usage
        
        - Upon the FIRST TIME you summon the Input manager, it will also be created and set as a static variable.
        - Upon CREATION, the input manager requires the GLFWwindow, otherwise it will crash.

        - All subsequent summons of the input manager can be done without giving the window in argument, as it will not be used.

        > The summon gives back a REFERENCE to the STATIC InputManager created at the first summon.


        ? To store the InputManager inside of a CLASS, or a STRUCT :

        1- Make sure that it has been summoned at least once correctly and created,
        2- "InputManager& inputs;" inside the class/struct declaration to store it,
        3- ": inputs(InputManager::Summon())" right after the constructor definition to initialize it. 
    */
    static InputManager& Summon(GLFWwindow* _window = nullptr);

    
    // -=! No default constructors shall be called, this struct is a singleton !=-
    InputManager() = delete;
    
    
    // --- Functionalities ---
    
    bool IsKeyPressed       (Inputs key);
    bool IsActionTriggered  (Actions act);
    void Remap              (Actions act, Inputs key);
    void Update             ();

    // Gives you back a string with the name of the input you gave.
    static const char* InputName(Inputs keyNum);

    // -----------------------

    Inputs keyToAct_Map[Actions::NUM_OF_ACTS];
    
    Actions actionToRemap   {Actions::NUM_OF_ACTS};
    bool    catchingInput   {false};
    bool    automaticFire   {true};

    Vec2    mousePos        {0, 0};

private:
    // -=! This struct being a singleton, the constructor is in private !=-
    InputManager(GLFWwindow* _window);
    
    GLFWwindow* window;

    bool inputs[Inputs::NUM_OF_KEYS] {false};
    bool hasFired {false};
    
    // === Input updating functions ===

    void CompleteUpdate     ();
    void MappedKeyUpdate    ();

    // Only called if "automaticFire" is false.
    void FireActionUpdate   (Inputs fireKey);

    void MouseActualizor    ();

    // --- catching function for remapping purposes ---

    void CatchInput         ();
};

#endif