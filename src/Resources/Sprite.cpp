#include "Sprite.hpp"
#include "ResourcesManager.hpp"
#include "GameObject.hpp"
#include "TimeManager.hpp"

using namespace Resources;


Sprite::Sprite()
{
    name = SPRITEBEHAVIOR;
} 
    
Sprite::~Sprite(){}

void Sprite::AddSprite(const char *filename)
{
    sprites.push_back(Resources::ResourcesManager::LoadTex(filename));
}

void Sprite::Animation()
{
    if (sprites.empty())// if there is no sprite
        return;

    if(!animate)// if the users decide to not animate, that display only the first sprite
        index = 0;

    if (gameObject->Mesh().textures[0].name != sprites[index].name)// change the texture of the mesh in order to display the sprite
        gameObject->Mesh().textures[0] = sprites[index];

    if (delay <= 0 && animate)// change the sprite in function of deltatime, if we already are at the last sprite it return to the first
        index + 1 < sprites.size()? index++ : index = 0;
    
}

void Sprite::Delay(const float &_delay)
{
    delayStart = _delay;
}

void Sprite::DelayCountdown(const float &deltaTime)
{
    delay - deltaTime <= 0? delay = 0 : delay -= deltaTime;
}

void Sprite::DelayReset()
{
    delay <= 0? delay = delayStart : delay;
}

void Sprite::Update()
{
    Tools::Time& timeManager = Tools::Time::Summon();// summon the timeManager for deltatime
    DelayCountdown(timeManager.DeltaTime());

    Animation();

    DelayReset();
}