/**********************************************************************************
// Home (C�digo Fonte)
//
// Cria��o:     27 jun 2025
// Atualiza��o: 
// Compilador:  Visual C++ 2019
//
// Descri��o:   Tela de abertura do jogo
//
**********************************************************************************/

#include "Engine.h"
#include "ToyAscension.h"
#include "Home.h"
#include "Level1.h"

// ------------------------------------------------------------------------------

void Home::Init()
{
    backg = new Sprite("Resources/background/azul.png");
	enter = new Sprite("Resources/background/press-start.png");
    tileset = new TileSet("Resources/background/nuvem.png", window->Width(), window->Height(), 1, 20);
    anim = new Animation(tileset, 0.35f, true);
    //ToyAscension::audio->Play(MENU, true);
}

// ------------------------------------------------------------------------------

void Home::Update()
{
    // sai com o pressionar do ESC
    if (window->KeyPress(VK_ESCAPE))
        window->Close();

    // se a tecla ENTER for pressionada
    if (window->KeyPress(VK_RETURN))
    {
        //ToyAscension::audio->Stop(MENU);
        ToyAscension::NextLevel<Level1>();
        return;
    }
    else
    {
        anim->NextFrame();
    }
}

// ------------------------------------------------------------------------------

void Home::Draw()
{
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
	enter->Draw(window->CenterX(), window->Height() - enter->Height() * 2.0f, Layer::FRONT);
    anim->Draw(window->CenterX(), window->CenterY());
}

// ------------------------------------------------------------------------------

void Home::Finalize()
{
    delete anim;
    delete tileset;
    delete backg;
	delete enter;
}

// ------------------------------------------------------------------------------