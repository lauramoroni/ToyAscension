#ifndef _ToyAscension_ITEM_H_
#define _ToyAscension_ITEM_H_

// ------------------------------------------------------------------------------

#include "Game.h"
#include "Object.h"
#include "Sprite.h"
#include "Scene.h"
#include "Audio.h"
#include "Font.h"
#include "Resources.h"     
#include "Animation.h"

// ------------------------------------------------------------------------------

enum ItemType { JUMPBUFF, SHIELD, RICOCHET_SHOT, TRIPLE_SHOT, HOMING_SHOT };

// ------------------------------------------------------------------------------

class Item : public Object
{
private:
    TileSet* folha;
    Animation* anim;
public:
    uint type;
    float velX = 0.0f;
    float velY = 0.0f;
    Item(uint Type, float posX, float posY);    // inicializacao
    void OnCollision(Object* obj);              // tratamento de colisão
    void Update();                              // atualizacao
    void Draw();                                // desenho
    ~Item();                                    // finalizacao
};


#endif