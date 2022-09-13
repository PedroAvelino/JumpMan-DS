#pragma once

#include <nds.h>
#include <stdio.h>

#include "Collectable.hpp"
#include "GarlicMath.hpp"

class Collectable;

class Bomb : public Collectable
{
public:
    Bomb( const Vector2& p_spawnPos );
    ~Bomb();
public:
    void SetHeightToExplode( float pY );
    virtual void Draw() override;
    virtual void Update() override;
    virtual void Destroy() override;

    virtual int ClassType() override;
    
private:
    void Explode();
private:
    float speed;
    float heightToExplode;

};


