#include "Engine.h"
#include "ToyAscension.h"
#include "Platform.h"
#include "Item.h"
#include "Player.h"

Item::Item(uint Type, float posX, float posY, Scene* currScene)
{
    currentScene = currScene;
    type = Type;
    folha = new TileSet("Resources/Shield.png", 50, 50, 3, 9);
   
    anim = new Animation(folha, 0.2f, true);
    MoveTo(posX, posY);

    if (type == SHIELD) {
        uint Shield[9] = { 0,1,2,3,4,5,6,7,8 };
        anim->Add(SHIELD, Shield, 9);
    }
    
    BBox(new Rect(-18, -25, 20, 25));

}

// ------------------------------------------------------------------------------
void Item::OnCollision(Object* obj) {
    if (obj->Type() == PLAYER) {
        Player* player = static_cast<Player*>(obj);
        player->shield = true;
        
    }
}

void Item::Update()
{
    anim->Select(type);
    anim->NextFrame();
}

// ------------------------------------------------------------------------------


void Item::Draw()
{
    anim->Draw(x, y, z);

}

// ------------------------------------------------------------------------------

Item::~Item()
{


}
