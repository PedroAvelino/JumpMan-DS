#pragma once

#include <nds.h>
#include <stdio.h>

#include "Singleton.hpp"

class SpriteIDServer : public Singleton<SpriteIDServer>
{
    friend class Singleton<SpriteIDServer>;

public:
    int GetID();
protected:
    SpriteIDServer( ) { };
    ~SpriteIDServer( ) { };
private:
    int currentID = 3;
    
};


