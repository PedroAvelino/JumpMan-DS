#include <nds.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <nf_lib.h>

#include "GarlicMath.hpp"
#include "Boxxy.hpp"
#include "Wall.hpp"
#include "Coin.hpp"
#include "Collectable.hpp"
#include "Singleton.hpp"
#include "GameScore.hpp"

class GameScore;
class SpriteIDServer;

///////
int coinCurrentSpawnDelay = 1;
int coinDelay = 2;
std::vector<Collectable *> entities;
///////

void InitConsole()
{
    consoleDemoInit();
    consoleClear();
    NF_Set2D(0, 0);
    NF_SetRootFolder("NITROFS");

    NF_InitSpriteBuffers();
    NF_InitSpriteSys(0);
}

void InitCoins()
{
    for (int i = 0; i < GameScore::GetInstance().maxCoinsToSpawn; i++)
    {
        int randPos = 64 + (std::rand() % (176 - 64 + 1));
        entities.push_back( new Coin(Vector2(randPos, 0)));
    }
    
}

void InitScore()
{
    GameScore::GetInstance().ResetScore();
}

void SpawnCoin()
{
    if( GameScore::GetInstance().currentCoinsOnScreen >= GameScore::GetInstance().maxCoinsOnScreen )
    {
        return;
    }

    if( coinCurrentSpawnDelay > 0 )
    {
        coinCurrentSpawnDelay--;
        return;
    }

    for (auto e : entities)
    {
        Coin* coin = static_cast<Coin*>(e);
        if( coin == nullptr ) continue;
        

        if( coin->IsActive() == false )
        {
            int randPos = 64 + (std::rand() % (176 - 64 + 1));
            coin->pos.x = randPos;
            coin->pos.y = 0;

            coin->SetActive();
            
            GameScore::GetInstance().currentCoinsOnScreen++;
            coinCurrentSpawnDelay = coinDelay;
            return; //Return so that we only spawn one coin
        }
    }
    

}

void InitWallSprites()
{
    NF_LoadSpriteGfx("sprite/Blockwall", 1, 32, 64);
    NF_LoadSpritePal("palettes/Blockwall", 1);

    NF_VramSpriteGfx(0, 1, 1, true);
    NF_VramSpritePal(0, 1, 1);
}

void InitCoinSprites()
{
    NF_LoadSpriteGfx("sprite/Coin", 2, 16, 16);
    NF_LoadSpritePal("palettes/Coin", 2);

    NF_VramSpriteGfx(0, 2, 2, true);
    NF_VramSpritePal(0, 2, 2);

}



int main(void)
{
    srand(time(NULL)); //Initiate random seed

    InitConsole();
    InitScore();
    InitWallSprites();
    InitCoinSprites();
    InitCoins();

    timerStart(0,ClockDivider_1024, TIMER_FREQ_1024(2) , SpawnCoin);

    Boxxy *player = new Boxxy();
    Wall *wallL = new Wall(true);  //Create left wall
    Wall *wallR = new Wall(false); //Create right wall


    while (1)
    {
        scanKeys();

        //Update the player
        player->Draw();
        player->Update();

        for (auto e : entities)
        {
            if (e->IsActive())
            {
                //Draw all entities
                e->Draw();

                //Update all entities
                e->Update();

                player->CheckCollision(e);
            }
        }
        
        if( GameScore::GetInstance().GetScore() == 15 && coinDelay > 1 )
        {
            coinDelay--;
        }
        if( GameScore::GetInstance().GetScore() == 30 && coinDelay == 1  )
        {
            coinDelay = 0;
        }

        NF_SpriteOamSet(0);
        swiWaitForVBlank();
        oamUpdate(&oamMain);
    }

    delete player;
    delete wallL;
    delete wallR;
    for (auto e : entities)
    {
        delete e;
    }
}