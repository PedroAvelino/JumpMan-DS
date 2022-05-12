#pragma once

#include <nds.h>
#include <stdio.h>

#include "Collectable.hpp"
#include "GarlicMath.hpp"

class Collectable;

class Spike : public Collectable
{
public:
    Spike( const Vector2& p_spawnPos );
    ~Spike();
public:
    virtual void Draw() override;
    virtual void Update() override;
    virtual void OnCollision( Entity* p_entity ) override;
    virtual void Destroy() override;

    virtual int ClassType() override;
private:
    float speed;
};


