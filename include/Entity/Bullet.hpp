#ifndef _BULLET_
#define _BULLET_

#include "SphereCollider.hpp"

#define BULLETBEHAVIOR "bulletBehavior"

class Bullet : public Physics::SphereCollider
{
private:
    float speed{50.0f};
    float timer {0.f};
    float lifeDuration {5.f};
    float lifeDurationAfterHit {2.f};
    bool  hit = false;

public:
    Bullet() : Physics::SphereCollider(true) {name = BULLETBEHAVIOR;};
    ~Bullet() {};

    Vec3 direction {0,0,0};

    void Restart(const Vec3 &_direction);
    void Update() override;
    void OnTrigger(const Physics::Collider  *collider) override;
};


#endif