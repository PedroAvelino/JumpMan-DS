#pragma once

#include <nds.h>
#include <gl2d.h>
#include <stdio.h>

#include "GarlicMath.hpp"

class Entity
{
public:
    Entity(/* args */);
    ~Entity();

public:
    virtual void Draw();
    virtual void Update();

protected:

    Vector2 pos;
    int size;
};
