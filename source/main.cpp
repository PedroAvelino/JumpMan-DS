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


void InitConsole()
{
    consoleDemoInit();	
	consoleClear();		
	NF_Set2D(0,0);
	NF_SetRootFolder("NITROFS");
    

    NF_InitSpriteBuffers();
	NF_InitSpriteSys(0);
}

void InitWallSprites()
{
    NF_LoadSpriteGfx("sprite/Wall", 1, 32, 64);
    NF_LoadSpritePal("palettes/Wall", 1);

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
    std::vector<Entity*> entities;
    int randPos = 64 + ( std::rand() % ( 176 - 64 + 1 ) );
    // videoSetMode(MODE_5_3D);
    // glScreen2D();
    
    InitConsole();
    InitWallSprites();
    InitCoinSprites();

    srand(time(NULL)); //Initiate random seed

    Boxxy* player = new Boxxy();
    entities.push_back(new Wall( true )); //Create left wall
    entities.push_back(new Wall( false )); //Create right wall
    
    //entities.push_back(new Coin(Vector2(randPos, 0)));

    while (1)
    {
        scanKeys();

        //Update the player
        player->Draw();
        player->Update();

        for ( auto e : entities )
        {
            if( e == nullptr ) continue;
            
            //Draw all entities
            e->Draw();

            //Update all entities
            e->Update();

            player->CheckCollision( e );
        }

        NF_SpriteOamSet(0);
        swiWaitForVBlank();
        oamUpdate(&oamMain);
    }
    
    delete player;
    for ( auto e : entities )
    {
        delete e;
    }
}