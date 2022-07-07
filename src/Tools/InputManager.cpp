#include "InputManager.hpp"

InputManager::InputManager(GLFWwindow* _window)
             : window(_window)
{
    keyToAct_Map[Actions::Pause]        = Inputs::other_ESC;
    
    keyToAct_Map[Actions::Left]         = Inputs::alpha_A;
    keyToAct_Map[Actions::Right]        = Inputs::alpha_D;
    keyToAct_Map[Actions::Forward]      = Inputs::alpha_W;
    keyToAct_Map[Actions::Backwards]    = Inputs::alpha_S;

    keyToAct_Map[Actions::Up]           = Inputs::alpha_E;
    keyToAct_Map[Actions::Down]         = Inputs::alpha_F;

    keyToAct_Map[Actions::Jump]         = Inputs::other_SPACE;

    keyToAct_Map[Actions::Fire]         = Inputs::mouse_left;
    keyToAct_Map[Actions::WeaponSwitch] = Inputs::alpha_R;

    keyToAct_Map[Actions::Save]         = Inputs::function_5;
}

InputManager& InputManager::Summon(GLFWwindow* _window)
{
    static InputManager inputManagement(_window);

    return inputManagement;
}


bool InputManager::IsKeyPressed(Inputs key)
{
    return inputs[key];
}

bool InputManager::IsActionTriggered(Actions act)
{
    return IsKeyPressed( keyToAct_Map[act] );
}

void InputManager::Remap(Actions act, Inputs key)
{ keyToAct_Map[act] = key; }

void InputManager::Update()
{
    glfwPollEvents();

    if (!catchingInput)
    { MappedKeyUpdate(); }
    else
    {
        CompleteUpdate();
        CatchInput();
    }
    
    MouseActualizor();
}


const char* InputManager::InputName(Inputs InputNum)
{
    static std::string InputName; // Static keyword needed otherwise the memory is too volatile
    
    if (InputNum <= Inputs::alpha_Z)
    {
        InputName = InputNum + 'a';
        
        return InputName.c_str();
    }

    if (InputNum >= Inputs::numeral_0 && InputNum <= Inputs::numeral_9)
    {
        InputName = (InputNum - Inputs::numeral_0) + '0';

        return InputName.c_str();
    }

    if (InputNum >= Inputs::function_1 && InputNum <= Inputs::function_25)
    {
        InputName = 'f';

        short functionNum = InputNum - Inputs::function_1 +1;
        
        if (functionNum < 10) InputName += functionNum + '0';
        else
        {
            InputName += (functionNum / 10) %10 + '0';
            InputName +=  functionNum       %10 + '0';
        }
        
        return InputName.c_str();
    }

    if (InputNum > Inputs::function_25 && InputNum <= Inputs::arrow_up)
    {
        InputName = "Arrow ";

        if      (InputNum == Inputs::arrow_right)   InputName += "right";
        else if (InputNum == Inputs::arrow_left)    InputName += "left";
        else if (InputNum == Inputs::arrow_down)    InputName += "down";
        else if (InputNum == Inputs::arrow_up)      InputName += "up";

        return InputName.c_str();
    }

    if (InputNum > Inputs::arrow_up && InputNum <= Inputs::mouse_middle)
    {
        InputName = "Mouse ";

        if      (InputNum == Inputs::mouse_left)    InputName += "left";
        else if (InputNum == Inputs::mouse_right)   InputName += "right";
        else if (InputNum == Inputs::mouse_middle)  InputName += "middle";

        return InputName.c_str();
    }

    if (InputNum == Inputs::other_ESC)   return "ESC";
    if (InputNum == Inputs::other_SPACE) return "SPACE";

    return "?";
}


void InputManager::CompleteUpdate()
{
    for ( short a   = 0 ; a   < 26 ; a++  ) inputs[                        a  ] = glfwGetKey        (window, a   + 65);
    for ( short n   = 0 ; n   < 10 ; n++  ) inputs[(Inputs::numeral_0)   + n  ] = glfwGetKey        (window, n   + 48);
    for ( short f   = 0 ; f   < 25 ; f++  ) inputs[(Inputs::function_1)  + f  ] = glfwGetKey        (window, f   + 290);
    for ( short arr = 0 ; arr < 4  ; arr++) inputs[(Inputs::arrow_right) + arr] = glfwGetKey        (window, arr + 262);
    for ( short ms  = 0 ; ms  < 3  ; ms++ ) inputs[(Inputs::mouse_left)  + ms ] = glfwGetMouseButton(window, ms);

    inputs[Inputs::other_ESC]   = glfwGetKey(window, GLFW_KEY_ESCAPE);
    inputs[Inputs::other_SPACE] = glfwGetKey(window, GLFW_KEY_SPACE);
}

void InputManager::MappedKeyUpdate()
{
    for (Inputs updateKey : keyToAct_Map)
    {
        if (updateKey <= Inputs::alpha_Z                                         )  inputs[updateKey] = glfwGetKey          (window,  updateKey                        + 65 );
        if (updateKey >  Inputs::alpha_Z     && updateKey <= Inputs::numeral_9   )  inputs[updateKey] = glfwGetKey          (window, (updateKey - Inputs::numeral_0  ) + 48 );
        if (updateKey >  Inputs::numeral_9   && updateKey <= Inputs::function_25 )  inputs[updateKey] = glfwGetKey          (window, (updateKey - Inputs::function_1 ) + 290);
        if (updateKey >  Inputs::function_25 && updateKey <= Inputs::arrow_up    )  inputs[updateKey] = glfwGetKey          (window, (updateKey - Inputs::arrow_right) + 262);
        if (updateKey >  Inputs::arrow_up    && updateKey <= Inputs::mouse_middle)  inputs[updateKey] = glfwGetMouseButton  (window,  updateKey - Inputs::mouse_left        );       

        if (updateKey == Inputs::other_ESC)   inputs[Inputs::other_ESC]   = glfwGetKey(window, GLFW_KEY_ESCAPE);
        if (updateKey == Inputs::other_SPACE) inputs[Inputs::other_SPACE] = glfwGetKey(window, GLFW_KEY_SPACE);
        
        if (updateKey == keyToAct_Map[Actions::Fire] && !automaticFire) FireActionUpdate(keyToAct_Map[Actions::Fire]);
    }
}

void InputManager::FireActionUpdate(Inputs fireKey)
{
    if (!hasFired)
    {
        if (inputs[fireKey])    hasFired        = true;
    }
    else
    {
        if (inputs[fireKey])    inputs[fireKey] = false;
        else                    hasFired        = false;
    }
}

void InputManager::MouseActualizor()
{
    double x, y;
    glfwGetCursorPos(window, &x, &y);

    mousePos = {(float)x, (float)y};
}


void InputManager::CatchInput()
{
    for (short inputNum = 0 ; inputNum < Inputs::NUM_OF_KEYS ; inputNum++)
    {
        if (inputs[inputNum])
        {
            Remap(actionToRemap, static_cast<Inputs>(inputNum));

            actionToRemap = Actions::NUM_OF_ACTS;
            catchingInput = false;
            
            return;
        }
    }
}
