#pragma once
#include <nds.h>
#include <gl2d.h>
#include <stdio.h>

#include "Entity.hpp"

class Entity;

class Boxxy : public Entity
{
 
public:
    Boxxy(/* args */);
    ~Boxxy();
    void Move( const Vector2& p_direction );

public:
    virtual void Draw() override;
    virtual void Update() override;

private:
    float speed;
};


