#include "GameScore.hpp"

GameScore::GameScore()
: maxCoinsToSpawn(5), currentScore(0), maxSpikesToSpawn(1), currentCoinsOnScreen(0), currentSpikesOnScreen(0), maxSpikesOnScreen(3), maxCoinsOnScreen(5)
{
    
}
void GameScore::ResetScore()
{
    currentScore = 0;
}

void GameScore::IncrementScore()
{
    currentScore++;
}