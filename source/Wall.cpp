#include "Wall.hpp"
#include "SpriteIDServer.hpp"

Wall::Wall( bool p_Left )
:isLeft(p_Left),wallSpriteAmount(6)
{
    size.x = 32.0f;
    size.y = 192.0f;

    if(p_Left)
    {
        pos.x = 0;
        pos.y = 0;
    }
    else
    {
        pos.x = 224;
        pos.y = 0;
    }

    for (int i = 0; i < wallSpriteAmount; i++)
    {
        spriteIDS.push_back(SpriteIDServer::GetInstance().GetID());
    }
    
    Draw();
}


void Wall::Draw()
{   
    //This is terrible lmao
    if( isLeft )
    {
        //First left wall        
        NF_CreateSprite(0,spriteIDS[0],1,1, pos.x, pos.y);
        //Second left wall
        NF_CreateSprite(0,spriteIDS[1],1,1, pos.x, pos.y + 64);
        //Third left wall
        NF_CreateSprite(0,spriteIDS[2],1,1, pos.x, pos.y + 64 + 64);
    }
    else
    {   
        //First right wall
        NF_CreateSprite(0,spriteIDS[3],1,1, pos.x, pos.y);
        NF_HflipSprite( 0,spriteIDS[3], true);
        //Second right wall
        NF_CreateSprite(0,spriteIDS[4],1,1, pos.x, pos.y + 64);
        NF_HflipSprite( 0,spriteIDS[4], true);
        //Third right wall
        NF_CreateSprite(0,spriteIDS[5],1,1, pos.x, pos.y + 64 + 64);
        NF_HflipSprite( 0,spriteIDS[5], true);
    }
}

Wall::~Wall()
{
}