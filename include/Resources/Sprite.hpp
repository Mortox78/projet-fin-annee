#pragma once 

#include <vector>

#include "Texture.hpp"
#include "AdditionalBehavior.hpp"

#define SPRITEBEHAVIOR "spriteBehavior"

namespace Resources
{
    class Sprite: public Core::DataStructure::AdditionalBehavior
    {
    private:
        std::vector <Texture> sprites;
        float delay{0};// actual time before the next sprites
        float delayStart{1};// delay between 2 sprites
        float index {0};

    public:
        bool animate{false};// enable/disable animation

        Sprite();
        ~Sprite();
        void AddSprite(const char *filename);
        void Animation();
        void Delay(const float &_delay);// change delayStart
        void DelayCountdown(const float &deltaTime);
        void DelayReset();// set delay to delayStart if delay is <= 0

        void Update() override;
    };  
}