#pragma once

#include <nds.h>
#include <stdio.h>
#include <vector>

#include "Singleton.hpp"
#include "Entity.hpp"
#include "GarlicMath.hpp"

class GameScore : public Singleton<GameScore>
{
    friend class Singleton<GameScore>;
public:
    void IncrementScore();
    void DecreaseLife() { playerLife--; }
    void ResetScore();

    void CoinDeactivated();
    void SpikeDeactivated();

    int GetScore() { return currentScore; }
    int GetPlayerLife() { return playerLife; }


protected:
    GameScore();
    ~GameScore() { };

private:
    int currentScore;
    int playerLife;


public:
    int maxCoinsToSpawn;
    int maxSpikesToSpawn;


public:
    int currentCoinsOnScreen;
    int currentSpikesOnScreen;
    int maxCoinsOnScreen;
    int maxSpikesOnScreen;
};
