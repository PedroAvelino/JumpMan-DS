#pragma once

#include <nds.h>
#include <stdio.h>

#include "Collectable.hpp"
#include "GarlicMath.hpp"

class Collectable;

class Reverse : public Collectable
{
public:
    Reverse( const Vector2& p_spawnPos );
    ~Reverse();
public:
    virtual void Draw() override;
    virtual void Update() override;
    virtual void Destroy() override;
    virtual int ClassType() override;
private:
    float speed;
    
};


