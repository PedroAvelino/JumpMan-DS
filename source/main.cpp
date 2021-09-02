#include <nds.h>
#include <gl2d.h>
#include <stdio.h>
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

int main(void)
{
    std::vector<Entity*> entities;
    // entities.push_back(new Wall( true )); //Create left wall
    // entities.push_back(new Wall( false )); //Create right wall
    // entities.push_back(new Coin(Vector2(100, 0)));
    // videoSetMode(MODE_5_3D);
    // glScreen2D();
    
    InitConsole();

    entities.push_back(new Boxxy()); //Create a new box

    while (1)
    {
        scanKeys();
        for ( auto e : entities )
        {
            e->Draw();
        }

        // for ( auto e : entities )
        // {
        //     e->Update();
        // }

        NF_SpriteOamSet(0);
        swiWaitForVBlank();
        oamUpdate(&oamMain);
    }
    

    for ( auto e : entities )
    {
        delete e;
    }
}