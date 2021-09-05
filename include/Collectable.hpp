#pragma once

#include <nds.h>
#include <stdio.h>

#include "Entity.hpp"
#include "GarlicMath.hpp"

class Entity;

class Collectable : public Entity
{
public:
    bool IsActive() { return active; }
protected:
    float speed;
    bool active;
};