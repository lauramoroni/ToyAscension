#include "Engine.h"
#include "ToyAscension.h"
#include "Platform.h"

#include <iostream>
#include <format>

Platform::Platform(float PosX, float PosY, uint Type, uint level)
{
    type = Type;

    switch (type)
	{
		case SCENARIO_SMALL:
			sprite = new Sprite(std::format("Resources/platform/level{}/platform-small.png", level));
			break;
		case SCENARIO_MEDIUM:
			sprite = new Sprite(std::format("Resources/platform/level{}/platform-medium.png", level));
			break;
		case SCENARIO_LARGE:
			sprite = new Sprite(std::format("Resources/platform/level{}/platform-large.png", level));
			break;
		case DESTRUCTIVE:
			sprite = new Sprite(std::format("Resources/platform/level{}/platform-fallen.png", level));
			break;
		case DYNAMICX:
			sprite = new Sprite(std::format("Resources/platform/level{}/platform-small.png", level));
            velX = 50.0f;
			break;
		case DYNAMICY:
			sprite = new Sprite(std::format("Resources/platform/level{}/platform-small.png", level));
            velY = 50.0f;
			break;
	}

    posXinit = PosX;
    posX = PosX;
    posYinit = PosY;
    posY = PosY;

    BBox(new Rect(-sprite->Width() / 2, sprite->Height() / 2, sprite->Width() / 2, -sprite->Height() / 2));
    MoveTo(posX, posY, Layer::MIDDLE);

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

        if ((posY) > posYinit + 80 && velY > 0) {

            velY = -velY;

        }
        if (posY < (posYinit - 300) && velY < 0) {

            velY = -velY;
        }

    }

    if (type == DESTRUCTIVE) {
        if (window->KeyPress('Y')) {
            velY = 400.0f;
        }
    }
    // sai com o pressionamento de ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    Translate(velX * gameTime, velY * gameTime);
}
// -------------------------------------------------------------------------------
void Platform::Draw()
{
    sprite->Draw(posX, posY, Layer::MIDDLE);
}
// ------------------------------------------------------------------------------

Platform::~Platform()
{
	delete sprite;
}
