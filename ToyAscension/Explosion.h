/**********************************************************************************
// Explosion (Arquivo de Cabecalho)
//
// Criacao:     08 jul 2025
// Atualizacao: 08 jul 2025
// Compilador:  Visual C++ 2022
//
// Descricao:   Explos�o (visual) dos proj�teis
//
**********************************************************************************/

#ifndef TOYASCENSION_EXPLOSION_H
#define TOYASCENSION_EXPLOSION_H

// ---------------------------------------------------------------------------------
// Inclus�es

#include "Types.h"                      // tipos espec�ficos da engine
#include "Object.h"                     // objetos do jogo
#include "Animation.h"                  // anima��o de sprites
#include "Scene.h"
// ---------------------------------------------------------------------------------

class Explosion : public Object
{
private:
    Animation* anim;                   // anima��o
    Scene* currentScene;

public:
    Explosion(TileSet* tiles, Scene* currScene);         // construtor
    ~Explosion();                       // destrutor

    void Update();                      // atualiza��o
    void Draw();                        // desenho
};

// ---------------------------------------------------------------------------------
// Fun��o Membro Inline

inline void Explosion::Draw()
{
    anim->Draw(x, y, z);
}

// ---------------------------------------------------------------------------------
#endif