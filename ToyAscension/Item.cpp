#include "Engine.h"
#include "ToyAscension.h"
#include "Platform.h"
#include "Item.h"
#include "Player.h"

Item::Item(uint Type, float posX, float posY, Scene* currScene)
{
    sprite = nullptr;
    currentScene = currScene;
    type = Type;

    switch (type) {
    case SHIELD:
        sprite = new Sprite("Resources/Shield.png");
        break;

    case TRIPLE_SHOT:
        sprite = new Sprite("Resources/TripleShot.png");
		break;
    case RICOCHET_SHOT:
        sprite = new Sprite("Resources/Ricochet.png");
		break;
    }
   
    MoveTo(posX, posY);
    
    BBox(new Rect(-18, -25, 20, 25));   

}

// ------------------------------------------------------------------------------
void Item::OnCollision(Object* obj) {
    if (obj->Type() == PLAYER) {
        Player* player = static_cast<Player*>(obj);
        if (!player->shield && !player->tripleShot && !player->ricochetShot) {
            if (type == SHIELD) {
                player->shield = true;
            }
            if (type == TRIPLE_SHOT) {
                player->tripleShot = true;
            }
            if (type == RICOCHET_SHOT) {
                player->ricochetShot = true;
			}
            currentScene->Delete(this, STATIC);
		}

        
    }
}

void Item::Update()
{
    
}

// ------------------------------------------------------------------------------


void Item::Draw()
{
    Timer* time = new Timer();
    sprite->Draw(x, y + sin(time->Elapsed()) * 10, z);

}

// ------------------------------------------------------------------------------

Item::~Item()
{
    delete sprite;
}
