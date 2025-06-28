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

#include <string>
#include <fstream>
using std::ifstream;
using std::string;

// ------------------------------------------------------------------------------
// Inicializa membros est�ticos da classe

Scene* Level1::scene = nullptr;

enum PlatformType
{
	SMALL,       // plataforma pequena
	MEDIUM,      // plataforma m��dia
	LARGE,       // plataforma grande
	FALLEN, 	// plataforma quebrada
};

// ------------------------------------------------------------------------------

void Level1::Init()
{
    // cria gerenciador de cena
    scene = new Scene();

    // pano de fundo do jogo
	backg = new Sprite("Resources/background/backg-level1.png");

    // adiciona jogador na cena

    // ----------------------
    // plataformas (APENAS TESTE)
    // ----------------------
    float posX, posY;
    uint  platType;

    ifstream fin;
    fin.open("level1.txt");

    fin >> posX;
    while (!fin.eof())
    {
        if (fin.good())
        {
            // lê linha com informações da plataforma
            fin >> posY; fin >> platType;
            switch (platType)
            {
            case SMALL:  platform = new Sprite("Resources/platform/platform-small.png"); break;
            case MEDIUM: platform = new Sprite("Resources/platform/platform-medium.png"); break;
            case LARGE:  platform = new Sprite("Resources/platform/platform-large.png"); break;
            case FALLEN: platform = new Sprite("Resources/platform/platform-fallen.png"); break;
            }

			platform->Draw(posX, posY, Layer::FRONT);

        }
        else
        {
            // ignora comentários
            fin.clear();
            char temp[80];
            fin.getline(temp, 80);
        }

        fin >> posX;
    }
    fin.close();

    

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
    }
}

// ------------------------------------------------------------------------------

void Level1::Draw()
{
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
	platform->Draw(window->CenterX(), window->CenterY() + 100, Layer::FRONT);

    if (ToyAscension::viewBBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void Level1::Finalize()
{
    delete scene;
    delete backg;
	delete anim;
	delete tileset;
    delete platform;
}

// ------------------------------------------------------------------------------