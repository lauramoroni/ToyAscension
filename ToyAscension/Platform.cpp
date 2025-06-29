#include "Engine.h"
#include "ToyAscension.h"
#include "Platform.h"


Platform::Platform(float PosX, float PosY, uint Type)
{
    type = Type;

    switch (type)
	{
		case SCENARIO_SMALL:
			sprite = new Sprite("Resources/platform/platform-small.png");
			break;
		case SCENARIO_MEDIUM:
			sprite = new Sprite("Resources/platform/platform-medium.png");
			break;
		case SCENARIO_LARGE:
			sprite = new Sprite("Resources/platform/platform-large.png");
			break;
		case DESTRUCTIVE:
			sprite = new Sprite("Resources/platform/platform-fallen.png");
			break;
		case DYNAMICX:
			sprite = new Sprite("Resources/platform/platform-small.png");
            velX = 50.0f;
			break;
		case DYNAMICY:
			sprite = new Sprite("Resources/platform/platform-small.png");
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
