#include "GameScore.hpp"

GameScore::GameScore()
: maxCoinsToSpawn(5), currentScore(0), maxSpikesToSpawn(5), 
currentCoinsOnScreen(0), currentSpikesOnScreen(0), 
maxSpikesOnScreen(3), maxCoinsOnScreen(5),playerLife(3), isFireOn(false),
explosionLocation(Vector2(0,0)), createFire(false)
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