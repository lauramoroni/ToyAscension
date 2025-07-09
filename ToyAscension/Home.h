#pragma once
#ifndef _TOYASCENSION_HOME_H_
#define _TOYASCENSION_HOME_H_

// ------------------------------------------------------------------------------
// Inclus�es

#include "Game.h"
#include "Sprite.h"
#include "Home.h"
#include "Animation.h"
#include "TileSet.h"

// ------------------------------------------------------------------------------
enum HOME_OPTIONS { PLAY, CONTROLS, EXIT };
// ------------------------------------------------------------------------------

class Home : public Game
{
private:
    TileSet* tileset = nullptr;    // tileset da animação
    Animation* anim = nullptr;     // animação do menu
    Sprite* backg = nullptr;       // pano de fundo
    bool ctrlKeyESC = false;        // controle do ESC
	int currentOption = PLAY;  // op����o atual do menu

public:
    void Init();                    // inicializa��o
    void Update();                  // atualiza��o
    void Draw();                    // desenho
    void Finalize();                // finaliza��o
};

// -----------------------------------------------------------------------------

#endif