#pragma once

#include <nds.h>
#include <stdio.h>
#include <nf_lib.h>

#include "GarlicMath.hpp"

class Entity
{
public:
    Entity(/* args */);
    ~Entity();

public:
    virtual void Draw();
    virtual void Update();
    virtual void OnCollision( Entity* p_entity );
    virtual void Move( const Vector2& p_direction );
    virtual void Destroy();
    Vector2 pos;
    Vector2 size;

};
