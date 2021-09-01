#include <nds.h>
#include <gl2d.h>
#include <stdio.h>
#include <vector>


#include "Boxxy.hpp"
int main(void)
{
    Boxxy* boxxy = new Boxxy();

    std::vector<Entity*> entities;

    entities.push_back(boxxy);
    
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
    

    delete boxxy;
}