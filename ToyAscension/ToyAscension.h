/**********************************************************************************
// ToyAscension (Arquivo de Cabe�alho)
// 
// Cria��o:     01 Out 2012
// Atualiza��o: 20 Set 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   Movimento de proj�til
//
**********************************************************************************/

#ifndef _ToyAscension_H_
#define _ToyAscension_H_

// ------------------------------------------------------------------------------

#include "Game.h"
#include "Sprite.h"
#include "Scene.h"
#include "Audio.h"
#include "Font.h"
#include "Resources.h"     
#include "Platform.h"
#include "Item.h"
#include "TileSet.h"

// ------------------------------------------------------------------------------

enum ToyAscencionObjects { PLAYER, PLATFORM, PROJECTILE, ITEM };
enum Sounds { INIT, BUZZ, ZURG, SHOT, EXPLOSION, ITEMPICKUP, INTRO, MENU_SELECTION };

// ------------------------------------------------------------------------------

class ToyAscension : public Game
{
private:
    static Game* level;            // nível atual do jogo
    Item* item = nullptr;
public:
    static TileSet* exploSet;      // tileset da explosão
    static Audio* audio;           // sistema de áudio
    static bool viewBBox;           // estado da bounding box
	static Font* font;             // fonte para texto

    void Init();                    // inicializa jogo
    void Update();                  // atualiza lógica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza jogo

    template<class T>
    static void NextLevel()         // muda para próximo nível do jogo
    {
        if (level)
        {
            level->Finalize();
            delete level;
            level = new T();
            level->Init();
        }
    };
};

// ---------------------------------------------------------------------------------

#endif