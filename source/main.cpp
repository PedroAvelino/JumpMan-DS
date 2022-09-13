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
#include "Reverse.hpp"
#include "Bomb.hpp"
#include "Fire.hpp"
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
int spikeDelay = 8;
bool shouldUpdateFire = false;

std::vector<Collectable *> entities;
std::vector<Collectable *> nonCollectables;



Vector2 ee = Vector2(1, 2);

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

#pragma region Graphics Initialization
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

#pragma endregion

#pragma region Entities Initialization
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

void InitBombs()
{
    for (int i = 0; i < GameScore::GetInstance().maxSpikesToSpawn; i++)
    {
        int randPos = 64 + (std::rand() % (176 - 64 + 1));
        entities.push_back( new Bomb(Vector2(randPos, 0)));
    }
    
}

void InitFire()
{
    //Fire 1: 32
    //Fire 2: 208

    nonCollectables.push_back( new Fire( Vector2(32, 0) ) );
    nonCollectables.push_back( new Fire( Vector2(208, 0) ) );
}

void InitScore()
{
    GameScore::GetInstance().ResetScore();
}
#pragma endregion

#pragma region Spawn
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

void SpawnBomb()
{
    if( GameScore::GetInstance().currentSpikesOnScreen >= GameScore::GetInstance().maxSpikesOnScreen &&
        state != GameState::INGAME || GameScore::GetInstance().isFireOn)
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
        if( e->ClassType() != 4 ) continue;

        Bomb* bomb = static_cast<Bomb*>(e);
        if( bomb == nullptr ) continue;
        

        if( bomb->IsActive() == false )
        {
            int randPos = 64 + (std::rand() % (176 - 64 + 1));
            bomb->pos.x = randPos;
            bomb->pos.y = 0;
            bomb->SetHeightToExplode( player->pos.y );

            bomb->SetActive();
            
            GameScore::GetInstance().currentSpikesOnScreen++;
            spikeCurrenSpawnDelay = spikeDelay;
            return; //Return so that we only spawn one coin
        }
    }
}
#pragma endregion

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

    //POS 1
    //X1:32
    //X2:32
    //Y1: tanto faz (20)
    //Y2: 64

    //POS 2
    //X1:192
    //X2: 224
    //Y1: tanto faz (20)
    //Y2: 64
    if( held & KEY_START )
    {
        timerStart(0,ClockDivider_1024, TIMER_FREQ_1024(2) , []() {SpawnSpike;SpawnCoin;});
        // timerStart(1,ClockDivider_1024, TIMER_FREQ_1024(2) , SpawnSpike);
        timerStart(1,ClockDivider_1024, TIMER_FREQ_1024(2) , SpawnBomb);

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
            //Update all entities
            e->Update();

            //Draw all entities
            e->Draw();

            player->CheckCollision(e);
        }
    }

    //Prepare fire
    if( GameScore::GetInstance().createFire )
    {
        shouldUpdateFire = true;
        for (auto i : nonCollectables)
        {
            if ( i->IsActive() ) continue;

            i->SetActive();
            i->pos = GameScore::GetInstance().explosionLocation;
        }

        GameScore::GetInstance().createFire = false;
    }

    if( shouldUpdateFire )
    {
        int firesDone = 0;
        for ( auto n : nonCollectables )
        {
            if( n->IsActive() == false )
            {
                firesDone++;
                continue;
            }

            //Update all entities
            n->Update();

            //Draw all entities
            n->Draw();
        }

        if ( firesDone == 2 )
        {
            shouldUpdateFire = false;
            GameScore::GetInstance().isFireOn = false;
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
    InitBombs();
    InitFire();

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
    for (auto e : nonCollectables)
    {
        delete e;
    }
}