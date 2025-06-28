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

Scene* Level1::scene = nullptr;

// ------------------------------------------------------------------------------

void Level1::Init()
{
    // cria gerenciador de cena
    scene = new Scene();

    // pano de fundo do jogo
	backf = new Sprite("Resources/background/backf-level1.png");
	tileset = new TileSet("Resources/background/backg-level1.png", window->Width(), window->Height(), 1, 4);
	anim = new Animation(tileset, 0.4f, true);

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

void Level1::Update()
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
		anim->NextFrame();
    }
}

// ------------------------------------------------------------------------------

void Level1::Draw()
{
    backf->Draw(window->CenterX(), window->CenterY(), Layer::FRONT);
    anim->Draw(window->CenterX(), window->CenterY());

    if (ToyAscension::viewBBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void Level1::Finalize()
{
    delete scene;
    delete backf;
	delete anim;
	delete tileset;
}

// ------------------------------------------------------------------------------