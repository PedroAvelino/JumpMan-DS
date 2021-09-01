#include <nds.h>
#include <gl2d.h>
#include <stdio.h>
#include <vector>


#include "Boxxy.hpp"
#include "Wall.hpp"
int main(void)
{
    std::vector<Entity*> entities;

    entities.push_back(new Boxxy()); //Create a new box
    entities.push_back(new Wall( true )); //Create left wall
    entities.push_back(new Wall( false )); //Create right wall
    
    videoSetMode(MODE_5_3D);
    glScreen2D();


    while (1)
    {
        scanKeys();
        glBegin2D();
        
        for ( auto e : entities )
        {
            e->Draw();
        }
        
        glEnd2D();

        for ( auto e : entities )
        {
            e->Update();
        }

        glFlush(0);
        swiWaitForVBlank();
    }
    

    for ( auto e : entities )
    {
        delete e;
    }
}