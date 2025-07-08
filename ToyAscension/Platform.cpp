#include "Engine.h"
#include "ToyAscension.h"
#include "Platform.h"


Platform::Platform(float x1, float y1, float x2, float y2, float PosX, float PosY, uint Type)
{
    type = Type;
    BBox(new Rect(x1, y1, x2, y2));
    MoveTo(PosX, PosY);
    posXinit = PosX;
    posX = PosX;
    posYinit = PosY;
    posY = PosY;

    if (type == DYNAMICX) {
        velX = 50.0f;
        
    }
    if (type == DYNAMICY) {
        velY = 50.0f;
    }

}

// ------------------------------------------------------------------------------
void Platform::OnCollision(Object* obj)
{
    // bola colide com bloco
    //if (type == DESTRUCTIVE && obj->Type() == PLAYER) {

        //ToyAscension::scene->Delete(obj, STATIC);
        //velY = 400.0f;
    //}
        
}

void Platform::Update()
{
    if (type == DYNAMICX) {

        

        posX = posX + (velX * gameTime);

        if ((posX) > posXinit+ 200 && velX > 0) {

            velX = -velX;

        }
        if (posX < (posXinit - 200) && velX < 0) {

            velX = -velX;
        }
        
    }

    if (type == DYNAMICY) {

        posY = posY + (velY * gameTime);

        if ((posY) > posYinit + 200 && velY > 0) {
            velY = -velY;
        }
        if (posY < (posYinit - 200) && velY < 0) {
            velY = -velY;
        }
    }

    // sai com o pressionamento de ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    Translate(velX * gameTime, velY * gameTime);
}

// ------------------------------------------------------------------------------

void Platform::setVelY(float vely) {
    velY = vely;
}

void Platform::setVelX(float velx) {
    velX = velx;
}

void Platform::Draw()
{
    

}

// ------------------------------------------------------------------------------

Platform::~Platform()
{
   

}
