#ifndef _TOYASCENSION_GAMEOVER_H_
#define _TOYASCENSION_GAMEOVER_H_

// ------------------------------------------------------------------------------
// Inclus�es

#include "Game.h"
#include "Sprite.h"
#include "Scene.h"
#include "Font.h"
#include "TileSet.h"

// ------------------------------------------------------------------------------
enum DIGITS { ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE }; 
// ------------------------------------------------------------------------------

class GameOver : public Game
{
private:
    Sprite* backg = nullptr;       // background
    Scene* scene = nullptr;        // gerenciador de cena
    Font* font = nullptr;

public:
    int buzz = 5;
    int zurg = 3;

    void Init(); // construtor com pontua����es
    void Update();                  // atualiza l�gica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza jogo
};

// -----------------------------------------------------------------------------

#endif