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
    }
   
    MoveTo(posX, posY);
    
    BBox(new Rect(-18, -25, 20, 25));   

}

// ------------------------------------------------------------------------------
void Item::OnCollision(Object* obj) {
    if (obj->Type() == PLAYER) {
        Player* player = static_cast<Player*>(obj);

        if (type == SHIELD) {
            player->shield = true;
        }
        if (type == TRIPLE_SHOT) {
            player->tripleShot = true;
		}
        currentScene->Delete(this, STATIC);
        // timer de respawn do item?
    }
}

void Item::Update()
{
    // contadores? timer de spawn?
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
