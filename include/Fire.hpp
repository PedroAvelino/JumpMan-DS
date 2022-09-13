#pragma once

#include <nds.h>
#include <stdio.h>

#include "Collectable.hpp"
#include "GarlicMath.hpp"

class Collectable;

class Fire : public Collectable
{
public:
    Fire( const Vector2& p_spawnPos );
    ~Fire();
public:
    virtual void Draw() override;
    virtual void Update() override;
    virtual void Destroy() override;

    virtual int ClassType() override;


private:
    void TravelToOrigin();
private:
    float speed;
    float startX;

};