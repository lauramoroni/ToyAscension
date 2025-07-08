/**********************************************************************************
// Explosion (Código Fonte)
//
// Criacao:     08 jul 2025
// Atualizacao: 08 jul 2025
// Compilador:  Visual C++ 2022
//
// Descrição:   Animação de uma explosão
//
**********************************************************************************/

#include "Explosion.h"
#include "ToyAscension.h"

// ---------------------------------------------------------------------------------

Explosion::Explosion(TileSet* tiles, Scene * currScene)
{
    currentScene = currScene;
    anim = new Animation(tiles, 0.020f, false);
}

// ---------------------------------------------------------------------------------

Explosion::~Explosion()
{
    delete anim;
}

// ---------------------------------------------------------------------------------

void Explosion::Update()
{
    anim->NextFrame();

    if (anim->Inactive())
        currentScene->Delete();
}

// ---------------------------------------------------------------------------------