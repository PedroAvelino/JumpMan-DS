#include "Boxxy.hpp"

Boxxy::Boxxy()
:speed(3.0), isLeftWall(true),state(BoxxyState::Left), isJumping(false)
{
    pos.x = 28;
    pos.y = 50;

    size.x = 16.0f;
    size.y = 16.0f;

    NF_LoadSpriteGfx("sprite/Boxxy", 0, 32, 32);
    NF_LoadSpritePal("palettes/Boxxy", 0);

    NF_VramSpriteGfx(0, 0, 0, true);
	NF_VramSpritePal(0, 0, 0);
}

//=================================================================
//=================================================================

void Boxxy::Draw()
{
    NF_CreateSprite(0,0,0,0, pos.x, pos.y);
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
    int held = keysHeld();

    state = CheckState();


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
        if( isJumping == false )
        {
            Move(Vector2(0.0, -1.0));
        }
    }

    //Down
    if( held & KEY_DOWN )
    {
        if( isJumping == false )
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

void Boxxy::CheckCollision( Entity* p_entity )
{
    if( p_entity == nullptr ) return;


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