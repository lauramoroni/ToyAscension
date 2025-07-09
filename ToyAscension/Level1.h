/**********************************************************************************
// Level1 (Arquivo de Cabe�alho)
//
// Cria��o:     27 jun 2025
// Atualiza��o: 
// Compilador:  Visual C++ 2019
//
// Descri��o:   N�vel 1 do jogo
//
**********************************************************************************/

#ifndef _TOYASCENSION_LEVEL1_H_
#define _TOYASCENSION_LEVEL1_H_

// ------------------------------------------------------------------------------
// Inclus�es

#include "Game.h"
#include "Sprite.h"
#include "Scene.h"
#include "Player.h"
#include "Item.h"
// ------------------------------------------------------------------------------

class Level1 : public Game
{
private:
    TileSet* tileset = nullptr;    // tileset da animação
    Animation* anim = nullptr;     // animação do menu
	Sprite* backg = nullptr;       // pano de fundo estatico
    Platform* platform = nullptr;
    list<Platform*> scenario;
    list<Platform*> listPlatformDynamic;
    Item* item = nullptr;
    Item* item2 = nullptr; 
	Item* item3 = nullptr;
	Item* item4 = nullptr;
    Item* item5 = nullptr;

public:
    static Player* buzz;
    static Player* zurg;
    static Scene* scene;           // cena do n�vel

    void Init();                    // inicializa��o do n�vel
    void Update();                  // atualiza l�gica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza��o do n�vel
};

// -----------------------------------------------------------------------------

#endif