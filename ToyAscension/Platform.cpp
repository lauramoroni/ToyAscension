#include "Engine.h"
#include "ToyAscension.h"
#include "Platform.h"


Platform::Platform(float PosX, float PosY, uint Type)
{
    variationType = Type;

    switch (variationType)
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

	Point platformVertexs[4] = {
		Point(-sprite->Width() / 2.0f, -sprite->Height() / 2.0f), // Top Left
		Point(sprite->Width() / 2.0f, -sprite->Height() / 2.0f),  // Top Right
		Point(sprite->Width() / 2.0f, sprite->Height() / 2.0f),   // Bottom Right
		Point(-sprite->Width() / 2.0f, sprite->Height() / 2.0f)   // Bottom Left
	};

	BBox(new Poly(platformVertexs, 4));

    MoveTo(posX, posY, Layer::MIDDLE);

    type = PLATFORM;
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
    if (variationType == DYNAMICX) {

        

        posX = posX + (velX * gameTime);

        if ((posX) > posXinit+ 200 && velX > 0) {

            velX = -velX;

        }
        if (posX < (posXinit - 200) && velX < 0) {

            velX = -velX;
        }
        
    }

    if (variationType == DYNAMICY) {

        

        posY = posY + (velY * gameTime);

        if ((posY) > posYinit + 80 && velY > 0) {

            velY = -velY;

        }
        if (posY < (posYinit - 300) && velY < 0) {

            velY = -velY;
        }

    }

    if (variationType == DESTRUCTIVE) {
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
