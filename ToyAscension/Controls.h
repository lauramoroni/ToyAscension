#pragma once
#ifndef _TOYASCENSION_CONTROLS_H_
#define _TOYASCENSION_CONTROLS_H_

// ------------------------------------------------------------------------------
// Inclus�es

#include "Game.h"
#include "Sprite.h"

// ------------------------------------------------------------------------------

class Controls : public Game
{
private:
    Sprite* backg = nullptr;

public:
    void Init();                    // inicializa��o
    void Update();                  // atualiza��o
    void Draw();                    // desenho
    void Finalize();                // finaliza��o
};

// -----------------------------------------------------------------------------

#endif