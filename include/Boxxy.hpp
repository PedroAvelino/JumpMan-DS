#pragma once
#include <nds.h>
#include <stdio.h>

#include "Entity.hpp"

class Entity;

enum BoxxyState
{
	Left = 0,
	Right = 1,
	OnAir = 2,
	MAX = 3
};

class Boxxy : public Entity
{
 
public:
    Boxxy();
    ~Boxxy();

public:
    void CheckCollision( Entity* p_entity);

public:
    virtual void Draw() override;
    virtual void Update() override;
    virtual void Move( const Vector2& p_direction ) override;

private:
    enum BoxxyState CheckState();
    bool CanJump();


private:
    float speed;
    bool isLeftWall;
    BoxxyState state;
    bool isJumping;

};