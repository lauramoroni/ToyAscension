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
    Scene* currentScene;
    uint type;
    float velX = 0.0f;
    float velY = 0.0f;
    
    Item(uint Type, float posX, float posY, Scene* currScene);                    // inicializa??o
    void OnCollision(Object* obj);     // tratamento de colisão
    void Update();                  // atualiza??o
    void Draw();                    // desenho
    ~Item();                // finaliza??o

};


#endif