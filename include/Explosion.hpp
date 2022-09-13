#pragma once
#include <nds.h>
#include <stdio.h>

#include "Entity.hpp"
#include "Boxxy.hpp"

class Entity;
class Explosion : public Entity
{
 
public:
    Explosion( float m_X );
    ~Explosion();

public:
    void CheckCollision( Collectable* p_entity);
    void SetActive( float m_Y );

public:
    virtual void Draw() override;
    virtual void Update() override;
    virtual void LoadSprite() override;
    virtual int ClassType() override;
private:
    float explosionDuration;
    float currentExplositionDuration;
    bool isLeftWall;

};