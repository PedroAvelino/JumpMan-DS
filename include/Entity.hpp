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
    virtual bool IsActive() { return active; }
    virtual void SetActive() { active = true; }

protected:
    virtual void LoadSprite();
public:
    virtual void Draw();
    virtual void Update();
    virtual void OnCollision( Entity* p_entity );
    virtual void Move( const Vector2& p_direction );
    virtual void Destroy();
    Vector2 pos;
    Vector2 size;

public:
    //THIS FUCKING SHIT ASS OLD MAKEFILE DOESN'T LET ME USE DYNAMIC CASTS SO I GOTTA DO THIS STUPID SHIT TO TELL CLASSES APART
    virtual int ClassType() { return -1; } 

protected:
    int spriteID;
    bool active;
};
