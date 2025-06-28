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

// ------------------------------------------------------------------------------

enum Sounds {CANNON, SPLASH};

// ------------------------------------------------------------------------------

class ToyAscension : public Game
{
private:
    Sprite * backg = nullptr;       // pano de fundo
    Sprite * base = nullptr;        // base do canh�o
    Sprite * infoBox = nullptr;     // caixa de informa��es
    Sprite * keyMap = nullptr;      // caixa para teclas de atalho    
    Platform* platform = nullptr;
    list<Platform*> scenario;
    list<Platform*> listPlatformDynamic;

public:
    static Scene * scene;           // cena do jogo
    static Audio * audio;           // sistema de �udio
    static Font  * font;            // fonte para texto
    bool viewBBox = true;
    void Init();                    // inicializa��o
    void Update();                  // atualiza��o
    void Draw();                    // desenho
    void Finalize();                // finaliza��o
};

// ---------------------------------------------------------------------------------

#endif