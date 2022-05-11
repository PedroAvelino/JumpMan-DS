#pragma once

#include <nds.h>
#include <stdio.h>

#include "Entity.hpp"
#include "GarlicMath.hpp"

class Entity;

class Collectable : public Entity
{
protected:
    float speed;
    bool spriteCreated;
};