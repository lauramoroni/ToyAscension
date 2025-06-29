/**********************************************************************************
// Level1 (C�digo Fonte)
//
// Cria��o:     27 jun 2025
// Atualiza��o:
// Compilador:  Visual C++ 2019
//
// Descri��o:   N�vel 1 do jogo
//
**********************************************************************************/

#include "ToyAscension.h"
#include "Home.h"
#include "Level1.h"
#include "Level2.h"

// ------------------------------------------------------------------------------
// Inicializa membros est�ticos da classe

Scene* Level2::scene = nullptr;

// ------------------------------------------------------------------------------

void Level2::Init()
{
    // cria gerenciador de cena
    scene = new Scene();

    // pano de fundo do jogo
    backg = new Sprite("Resources/background/level2.png");

    // adiciona jogador na cena

    // ----------------------
    // plataformas
    // ----------------------

    // ----------------------

    // inicia com m�sica
    //ToyAscension::audio->Frequency(MUSIC, 0.94f);
    //ToyAscension::audio->Frequency(TRANSITION, 1.0f);
    //ToyAscension::audio->Play(MUSIC);
}

// ------------------------------------------------------------------------------

void Level2::Update()
{
    if (window->KeyPress(VK_ESCAPE))
    {
        //ToyAscension::audio->Stop(MUSIC);
        ToyAscension::NextLevel<Home>();
        return;
    }

    if (window->KeyDown('R'))
    {
        ToyAscension::NextLevel<Level1>();
        return;
    }

    if (window->KeyPress('N'))
    {
        ToyAscension::NextLevel<Level2>();
        return;
    }
    else
    {
        scene->Update();
        scene->CollisionDetection();
    }
}

// ------------------------------------------------------------------------------

void Level2::Draw()
{
    scene->Draw();
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);

    if (ToyAscension::viewBBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void Level2::Finalize()
{
    delete scene;
    delete backg;
}

// ------------------------------------------------------------------------------