#include "SpriteIDServer.hpp"
SpriteIDServer::SpriteIDServer()
:currentID(15)
{

}

int SpriteIDServer::GetID()
{
    currentID++; //I don't want to create a new function just to increase it lol
    return (currentID - 1);
}
SpriteIDServer::~SpriteIDServer( ) 
{
    currentID = 0;
};