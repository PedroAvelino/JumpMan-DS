#include <nds.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <nf_lib.h>

#include "GarlicMath.hpp"
#include "Boxxy.hpp"
#include "Wall.hpp"
#include "Coin.hpp"
#include "Spike.hpp"
#include "Collectable.hpp"
#include "Singleton.hpp"
#include "GameScore.hpp"

///////
enum GameState
{
    SPLASH = 0,
    INGAME = 1,
    GAMEOVER = 2
};


GameState state = GameState::SPLASH;
Boxxy *player = new Boxxy();

char life[32];
int coinCurrentSpawnDelay = 2;
int coinDelay = 1;

int spikeCurrenSpawnDelay = 5;
int spikeDelay = 5;
std::vector<Collectable *> entities;

char score[32];
///////


void InitConsole()
{
    NF_Set2D(0, 0);
    NF_Set2D(1, 0);
    consoleDemoInit();
    consoleClear();
    NF_SetRootFolder("NITROFS");

    NF_InitSpriteBuffers();
    NF_InitSpriteSys(0);
}

void InitText()
{
    //Initialize sprite background
    NF_InitTiledBgBuffers();
    NF_InitTiledBgSys(1);
    
    //Initialize text motor
    NF_InitTextSys(1);
    NF_LoadTextFont("fonts/default","test", 256,256,0);
    NF_CreateTextLayer(1,0,0,"test");

    NF_WriteText(1, 0, 1, 1, "SCORE: 0");
    NF_WriteText(1, 0, 10, 1, "LIFE: 0");

}

/////////////////////GRAPHICS
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

void InitSpikeSprites()
{
    NF_LoadSpriteGfx("sprite/Spike", 3, 16, 16);
    NF_LoadSpritePal("palettes/Spike", 3);

    NF_VramSpriteGfx(0, 3, 3, true);
    NF_VramSpritePal(0, 3, 3);

}
void InitBackgrounds()
{
    NF_InitTiledBgSys(0);   
    NF_LoadTiledBg("bg/background", "bg", 256, 256);
    NF_LoadTiledBg("bg/splash", "logo", 256, 256);
    NF_CreateTiledBg(0, 2, "logo");
    NF_CreateTiledBg(0, 3, "bg");
}


void InitCoins()
{
    for (int i = 0; i < GameScore::GetInstance().maxCoinsToSpawn; i++)
    {
        int randPos = 64 + (std::rand() % (176 - 64 + 1));
        entities.push_back( new Coin(Vector2(randPos, 0)));
    }
}

void InitSpikes()
{
    for (int i = 0; i < GameScore::GetInstance().maxSpikesToSpawn; i++)
    {
        int randPos = 64 + (std::rand() % (176 - 64 + 1));
        entities.push_back( new Spike(Vector2(randPos, 0)));
    }
    
}

void InitScore()
{
    GameScore::GetInstance().ResetScore();
}

void SpawnCoin()
{
    if( GameScore::GetInstance().currentCoinsOnScreen >= GameScore::GetInstance().maxCoinsOnScreen &&
        state != GameState::INGAME)
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
        if( e->ClassType() != 2 ) continue;

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

void SpawnSpike()
{
    if( GameScore::GetInstance().currentSpikesOnScreen >= GameScore::GetInstance().maxSpikesOnScreen &&
        state != GameState::INGAME)
    {
        return;
    }

    if( spikeCurrenSpawnDelay > 0 )
    {
        spikeCurrenSpawnDelay--;
        return;
    }

    for (auto e : entities)
    {
        if( e->ClassType() != 1 ) continue;

        Spike* spike = static_cast<Spike*>(e);
        if( spike == nullptr ) continue;
        

        if( spike->IsActive() == false )
        {
            int randPos = 64 + (std::rand() % (176 - 64 + 1));
            spike->pos.x = randPos;
            spike->pos.y = 0;

            spike->SetActive();
            
            GameScore::GetInstance().currentSpikesOnScreen++;
            spikeCurrenSpawnDelay = spikeDelay;
            return; //Return so that we only spawn one coin
        }
    }
    

}

void UpdateScore()
{
    sprintf(score, "SCORE: %d", GameScore::GetInstance().GetScore());
    NF_WriteText(1, 0, 1, 1, score);
}

void UpdateLife()
{
    sprintf(life, "LIFE: %d", GameScore::GetInstance().GetPlayerLife());
    NF_WriteText(1, 0, 10, 1, life);
}

//////////////Game States

void UpdateSplash()
{
    scanKeys();
    int held = keysHeld();

    // Check leave state
    if( held & KEY_START )
    {
        timerStart(0,ClockDivider_1024, TIMER_FREQ_1024(2) , SpawnCoin);
        timerStart(1,ClockDivider_1024, TIMER_FREQ_1024(2) , SpawnSpike);
        player->SetActive();
        NF_HideBg(0,2);
        state = GameState::INGAME;
    }

    NF_SpriteOamSet(0);
    NF_UpdateTextLayers();
    swiWaitForVBlank();
    oamUpdate(&oamMain);
}


void UpdateInGame()
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

    UpdateScore();
    UpdateLife();
    if( GameScore::GetInstance().GetScore() == 15 && coinDelay > 1 )
    {
        coinDelay--;
        spikeDelay--;
    }
    if( GameScore::GetInstance().GetScore() == 30 && coinDelay == 1  )
    {
        coinDelay = 0;
        spikeDelay -= 2;
    }

    NF_SpriteOamSet(0);
    NF_UpdateTextLayers();
    swiWaitForVBlank();
    oamUpdate(&oamMain);
}
///////////////


int main(void)
{
    srand(time(NULL)); //Initiate random seed


    InitConsole();
    player->LoadSprite();
    InitWallSprites();
    InitCoinSprites();
    InitSpikeSprites();
    InitText();

    InitBackgrounds();

    InitScore();
    InitCoins();
    InitSpikes();

    Wall *wallL = new Wall(true);  //Create left wall
    Wall *wallR = new Wall(false); //Create right wall

    while (1)
    {
        //           """State Machine"""
        switch (state)
        {
            case GameState::SPLASH:
                UpdateSplash();
            break;

        
            case GameState::INGAME:
                UpdateInGame();
            break;

            case GameState::GAMEOVER:
                break;
        
        }


        
    }

    delete player;
    delete wallL;
    delete wallR;
    for (auto e : entities)
    {
        delete e;
    }
}