#pragma once

#include <nds.h>
#include <gl2d.h>
#include <stdio.h>

#include "Collectable.hpp"
#include "GarlicMath.hpp"

class Collectable;

class Coin : public Collectable
{
public:
    Coin( const Vector2& p_spawnPos );
    ~Coin();
public:
    virtual void Draw() override;
    virtual void Update() override;
    virtual void OnCollision( Entity* p_entity ) override;
    
};


