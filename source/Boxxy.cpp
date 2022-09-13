#include "Boxxy.hpp"
#include "GameScore.hpp"
#include "SpriteIDServer.hpp"

Boxxy::Boxxy()
:speed(3.0), isLeftWall(true),state(BoxxyState::Left), isJumping(false)
{
    pos.x = 28;
    pos.y = 150;

    size.x = 28.0f;
    size.y = 28.0f;

    active = false;
}

void Boxxy::LoadSprite()
{
    spriteID = SpriteIDServer::GetInstance().GetID();
    NF_LoadSpriteGfx("sprite/Boxxy", 0, 32, 32);
    NF_LoadSpritePal("palettes/Boxxy", 0);

    NF_VramSpriteGfx(0, 0, 0, true);
	NF_VramSpritePal(0, 0, 0);

    NF_CreateSprite(0,spriteID,0,0, pos.x, pos.y);
    NF_ShowSprite(0,spriteID,false);
}

//=================================================================
//=================================================================

void Boxxy::Draw()
{
    if( active )
    {
        NF_MoveSprite(0, spriteID, pos.x, pos.y );
        NF_ShowSprite(0,spriteID,true);
    }
}
//=================================================================
//=================================================================

void Boxxy::Move( const Vector2& p_direction )
{
    Vector2 direction;
    direction = p_direction;

    VectorScale(direction, direction, isJumping ? speed *2 : speed);

    VectorAdd( pos, pos, direction );
}

//=================================================================
//=================================================================

void Boxxy::Update()
{
    if( active == false ) return;

    state = CheckState();
    int held = keysHeld();


    //Jump
    if( held & KEY_B )
    {
        if( isJumping == false )
        {
            isJumping = CanJump();
        }
    }
    
    //Up
    if( held & KEY_UP )
    {
        if( isJumping == false && pos.y > 0 )
        {
            Move(Vector2(0.0, -1.0));
        }
    }

    //Down
    if( held & KEY_DOWN )
    {
        if( isJumping == false  && pos.y < ( 192 - size.y ) )
        {
            Move(Vector2(0.0, 1.0));
        }
    }

    
    //Auto move when jumping
    if( isJumping )
    {
        if( isLeftWall )
        {
            Move( Vector2(1.0, 0.0) );
        }
        else
        {
            Move( Vector2(-1.0, 0.0) );
        }
    }
}

//=================================================================
//=================================================================

void Boxxy::CheckCollision( Collectable* p_entity )
{
    if( p_entity == nullptr || active == false ) return;

    if( (pos.x <= p_entity->pos.x + p_entity->size.x)   && 
        (pos.x + size.x >= p_entity->pos.x)             && 
        (pos.y <= p_entity->pos.y + p_entity->size.y)   && 
        pos.y + size.y >= p_entity->pos.y)
    {
        
        switch (p_entity->ClassType())
        {
            case 1:
            {
                Spike* spike = static_cast<Spike*>(p_entity);
                //Increment Player Score
                if( spike != nullptr )
                {
                    GameScore::GetInstance().DecreaseLife();
                }
            }
            break;
        
            case 2:
            {
                Coin* coin = static_cast<Coin*>(p_entity);
                //Increment Player Score
                if( coin != nullptr )
                {
                    GameScore::GetInstance().IncrementScore();
                }
            }
            
            case 3:
            {
                Reverse* rev = static_cast<Reverse*>(p_entity);
                //Increment Player Score
                if( rev != nullptr )
                {
                    isLeftWall = !isLeftWall;
                }
            }

            break;
        
            default:
            break;
        }
        p_entity->Destroy();
    }
}

//=================================================================
//=================================================================

bool Boxxy::CanJump()
{
    if( state == BoxxyState::Left || state == BoxxyState::Right )
    {
        return true;
    }
    else
    {
        return false;
    }
}

//=================================================================
//=================================================================

enum BoxxyState Boxxy::CheckState()
{
    if( pos.x <= 28)
    {
        isLeftWall = true;
        isJumping = false;
        return BoxxyState::Left;
    }
    else if( pos.x >= 196)
    {
        isLeftWall = false;
        isJumping = false;
        return BoxxyState::Right;
    }
    else
    {
        isJumping = true;
        return BoxxyState::OnAir;
    }
}

//=================================================================
//=================================================================

Boxxy::~Boxxy()
{
}