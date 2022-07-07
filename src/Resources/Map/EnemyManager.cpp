#include "EnemyManager.hpp"

#include "GameObject.hpp"

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Update()
{
    if (!waveList[currentWave].isActivated)
    {
        for (unsigned int i = 0 ; i < waveList[currentWave].listEnemy.size() ; i++)
        {
            waveList[currentWave].listEnemy[i]->isActive = true;
        }
        waveList[currentWave].isActivated = true;
        std::cout << "Wave Size = " << waveList[currentWave].listEnemy.size() << std::endl;
        return;
    }

    unsigned int deadEnemy = 0;

    for (unsigned int i = 0 ; i < waveList[currentWave].listEnemy.size() ; i++)
    {
        if (!waveList[currentWave].listEnemy[i]->isActive)
        {
            deadEnemy++;
        }
        else
        {
            waveList[currentWave].listEnemy[i]->Update();
        }
        
    }

    if (waveList[currentWave].listEnemy.size() <= deadEnemy && currentWave < waveList.size() - 1)
    {
        currentWave++;
    }

}