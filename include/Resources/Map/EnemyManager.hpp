#ifndef _ENEMYMANAGER_
#define _ENEMYMANAGER_

#include "AdditionalBehavior.hpp"
#include "Enemy.hpp"

struct Wave
{
    bool isActivated {false};
    std::vector<Core::DataStructure::GameObject*> listEnemy;
};


class EnemyManager : public Core::DataStructure::AdditionalBehavior
{
private:
    
public:

    float cumulatedDeltaTime        {0};
    unsigned int activationDivision {1};
    unsigned int currentDivision    {0};
    unsigned int aimedDivision      {2};

    unsigned int deadEnemy {0};

    float oldDeltaTime = {0};
    float currentDeltaTime = {0};

    bool firstCycle {true};

    std::vector<Wave> waveList;
    unsigned int currentWave {0};
    bool waveEnded {false};

    EnemyManager();
    ~EnemyManager();

    void Update() override;

};


#endif