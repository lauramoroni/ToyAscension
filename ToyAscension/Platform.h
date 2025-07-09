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

enum PlatformType {SCENARIO_SMALL, SCENARIO_MEDIUM, SCENARIO_LARGE, DESTRUCTIVE, DYNAMICX, DYNAMICY, WALL_SMALL, WALL_MEDIUM, WALL_LARGE };

// ------------------------------------------------------------------------------

class Platform : public Object
{
private:
    uint variationType;
    float velX = 0.0f;
    float velY = 0.0f;
    float posXinit = 0.0f;
    float posX = 0.0f;
    float posYinit = 0.0f;
    float posY = 0.0f;
	Sprite* sprite = nullptr; // sprite da plataforma

public:

    Platform(float PosX, float PosY, uint Type, uint level);                    // inicializa??o
    void OnCollision(Object* obj);     // tratamento de colis�o
    void Update();                  // atualiza??o
    void Draw();                    // desenho
    void setVelY(float vely);
    void setVelX(float velx);
    ~Platform();                // finaliza??o

	inline float Top() const { return posY - sprite->Height() / 2.0f; }    // coordenadas do topo
	inline float Bottom() const { return posY + sprite->Height() / 2.0f; } // coordenadas da base
	inline float Left() const { return posX - sprite->Width() / 2.0f; }   // coordenadas da esquerda
	inline float Right() const { return posX + sprite->Width() / 2.0f; }  // coordenadas da direita
};

// --------------------------------------------------------------------------------

#endif