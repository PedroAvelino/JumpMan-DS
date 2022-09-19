#pragma once
#include <nds.h>
#include <stdio.h>

#include "Collectable.hpp"
#include "Boxxy.hpp"

class Collectable;
class Explosion : public Collectable
{
 
public:
    Explosion( float m_X );
    ~Explosion();

public:
    void SetActive( float m_Y );

public:
    virtual void Draw() override;
    virtual void Update() override;
    virtual int ClassType() override;
    virtual void Destroy() override;
private:
    int explosionDuration;
    int currentExplositionDuration;
    bool isLeftWall;
};