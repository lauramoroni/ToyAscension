#ifndef _ToyAscension_PLATFORM_H_
#define _ToyAscension_PLATFORM_H_

// ------------------------------------------------------------------------------

#include "Game.h"
#include "Object.h"
#include "Sprite.h"
#include "Scene.h"
#include "Audio.h"
#include "Font.h"
#include "Resources.h"     

// ------------------------------------------------------------------------------

enum PlatformType {SCENARIO_SMALL, SCENARIO_MEDIUM, SCENARIO_LARGE, DESTRUCTIVE, DYNAMICX, DYNAMICY};

// ------------------------------------------------------------------------------

class Platform : public Object
{
private:
    uint type;
    float velX = 0.0f;
    float velY = 0.0f;
    float posXinit = 0.0f;
    float posX = 0.0f;
    float posYinit = 0.0f;
    float posY = 0.0f;
	Sprite* sprite = nullptr; // sprite da plataforma

public:

    Platform(float PosX, float PosY, uint Type, uint level);                    // inicializa??o
    void OnCollision(Object* obj);     // tratamento de colisão
    void Update();                  // atualiza??o
    void Draw();                    // desenho
    ~Platform();                // finaliza??o
};

// --------------------------------------------------------------------------------

#endif