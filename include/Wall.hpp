#pragma once

#include <nds.h>
#include <gl2d.h>
#include <stdio.h>

#include "Entity.hpp"
#include "GarlicMath.hpp"

class Entity;

class Wall : public Entity
{
public:
    Wall( bool p_Left );
    ~Wall();

    virtual void Draw() override;

private:
    Vector2 pos;
    bool isLeft;
};
