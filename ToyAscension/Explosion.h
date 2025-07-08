/**********************************************************************************
// Explosion (Arquivo de Cabecalho)
//
// Criacao:     08 jul 2025
// Atualizacao: 08 jul 2025
// Compilador:  Visual C++ 2022
//
// Descricao:   Explosão (visual) dos projéteis
//
**********************************************************************************/

#ifndef TOYASCENSION_EXPLOSION_H
#define TOYASCENSION_EXPLOSION_H

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // objetos do jogo
#include "Animation.h"                  // animação de sprites
#include "Scene.h"
// ---------------------------------------------------------------------------------

class Explosion : public Object
{
private:
    Animation* anim;                   // animação
    Scene* currentScene;

public:
    Explosion(TileSet* tiles, Scene* currScene);         // construtor
    ~Explosion();                       // destrutor

    void Update();                      // atualização
    void Draw();                        // desenho
};

// ---------------------------------------------------------------------------------
// Função Membro Inline

inline void Explosion::Draw()
{
    anim->Draw(x, y, z);
}

// ---------------------------------------------------------------------------------
#endif