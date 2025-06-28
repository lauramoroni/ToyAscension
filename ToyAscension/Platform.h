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

enum PlatformType {SCENARIO, DYNAMICX, DYNAMICY, DESTRUCTIVE};

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

public:

    Platform(float x1, float y1, float x2, float y2, float PosX, float PosY, uint Type);                    // inicializa??o
    void OnCollision(Object* obj);     // tratamento de colisão
    void Update();                  // atualiza??o
    void Draw();                    // desenho
    ~Platform();                // finaliza??o
};


#endif