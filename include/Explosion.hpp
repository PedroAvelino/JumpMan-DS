#pragma once
#include <nds.h>
#include <stdio.h>

#include "Collectable.hpp"
#include "Boxxy.hpp"

class Collectable;
class Explosion : public Collectable
{
 
public:
    Explosion( float m_X, Collectable* p_TargetFire );
    ~Explosion();

public:
    void SetActive( float m_Y );

public:
    virtual void Draw() override;
    virtual void Update() override;
    virtual int ClassType() override;
private:
    float explosionDuration;
    float currentExplositionDuration;
    bool isLeftWall;

    Collectable* targetFire;
};