#pragma once

#include <nds.h>
#include <stdio.h>

#include "Collectable.hpp"
#include "GarlicMath.hpp"
#include "Explosion.hpp"

class Collectable;

class Fire : public Collectable
{
public:
    Fire( const Vector2& p_spawnPos, Explosion* m_explosion );
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

public:
    bool endTravel;

private:
    Explosion* explosion;
};