/**********************************************************************************
// Level1 (C�digo Fonte)
//
// Cria��o:     27 jun 2025
// Atualiza��o:
// Compilador:  Visual C++ 2019
//
// Descri��o:   N�vel 2 do jogo
//
**********************************************************************************/

#include "ToyAscension.h"
#include "Home.h"
#include "Level1.h"
#include "Level2.h"
#include "Platform.h"
#include "Aim.h"
#include <string>
#include <fstream>
#include "GameOver.h"
using std::ifstream;
using std::string;

// ------------------------------------------------------------------------------
// Inicializa membros est�ticos da classe

Scene* Level2::scene = nullptr;
Player* Level2::buzz = nullptr;           // player do jogo
Player* Level2::zurg = nullptr;

// ------------------------------------------------------------------------------

void Level2::Init()
{
    // cria gerenciador de cena
    scene = new Scene();

    // pano de fundo do jogo
    backg = new Sprite("Resources/background/backg-level2.png");

    // adiciona jogador na cena

    // ----------------------
    // plataformas
    // ----------------------

    Platform* platform;
    float posX, posY;
    uint platType;

    ifstream fin;
    fin.open("Level2.txt");

    fin >> posX;
    while (!fin.eof())
    {
        if (fin.good())
        {
            // lê linha com informações da plataforma
            fin >> posY; fin >> platType;
            platform = new Platform(posX, posY, platType, 2);
            scenario.push_back(platform);
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

    for (auto obj : scenario)
        scene->Add(obj, STATIC);

    // Player
    buzz = new Player(true, 'R', "Resources/buzz.png", scene);
    zurg = new Player(false, 'L', "Resources/zurg.png", scene);

    scene->Add(buzz, MOVING);
    scene->Add(zurg, MOVING);

    scene->Add(new Aim(buzz), MOVING);
    scene->Add(new Aim(zurg), MOVING);

    item = new Item(SHIELD, window->CenterX(), window->CenterY(), scene);
    item2 = new Item(TRIPLE_SHOT, window->CenterX() + 100, window->CenterY(), scene);
    item3 = new Item(RICOCHET_SHOT, window->CenterX() - 100, window->CenterY(), scene);

    scene->Add(item, STATIC);
    scene->Add(item2, STATIC);
    scene->Add(item3, STATIC);
    // ----------------------

    // inicia com m�sica
    //ToyAscension::audio->Frequency(MUSIC, 0.94f);
    //ToyAscension::audio->Frequency(TRANSITION, 1.0f);
    //ToyAscension::audio->Play(MUSIC);
    // ----------------------

   
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
        ToyAscension::NextLevel<Level2>();
        return;
    }

    if (window->KeyPress('N'))
    {
        ToyAscension::NextLevel<GameOver>();
        return;
    }

    if (window->KeyPress('P'))
    {
        ToyAscension::NextLevel<GameOver>();
        return;
    }

    scene->Update();
    scene->CollisionDetection();


}

// ------------------------------------------------------------------------------
void Level2::Draw()
{
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    scene->Draw();

    if (ToyAscension::viewBBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void Level2::Finalize()
{
    delete scene;
    delete backg;
    delete anim;
    delete tileset;
    delete platform;
}

// ------------------------------------------------------------------------------