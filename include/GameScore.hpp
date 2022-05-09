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
    void ResetScore();


protected:
    GameScore() { };
    ~GameScore() { };

private:
    int currentScore;
};
