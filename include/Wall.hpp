#pragma once

#include <nds.h>
#include <stdio.h>
#include <vector>

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

    int wallSpriteAmount;
    std::vector<int> spriteIDS;

};
