#include "SpriteIDServer.hpp"

int SpriteIDServer::GetID()
{
    currentID++; //I don't want to create a new function just to increase it lol
    return (currentID - 1);
}