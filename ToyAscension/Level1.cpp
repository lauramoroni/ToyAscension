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
#include "GameOver.h"
#include "Platform.h"
#include "Aim.h"

#include <string>
#include <fstream>
using std::ifstream;
using std::string;

// ------------------------------------------------------------------------------
// Inicializa membros est�ticos da classe

Player* Level1::buzz = nullptr;           // player do jogo
Player* Level1::zurg = nullptr;
Scene* Level1::scene = nullptr;

// ------------------------------------------------------------------------------

void Level1::Init()
{
    // cria gerenciador de cena
    scene = new Scene();

    // pano de fundo do jogo
	backg = new Sprite("Resources/background/backg-level1.png");

    // adiciona jogador na cena

    // ----------------------
    // plataformas
    // ----------------------
   
    Platform* platform;
	float posX, posY;
    uint platType;

    ifstream fin;
    fin.open("Level1.txt");

    fin >> posX;
    while (!fin.eof())
    {
        if (fin.good())
        {
            // lê linha com informações da plataforma
            fin >> posY; fin >> platType;
            platform = new Platform(posX, posY, platType, 1);
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
    buzz = new Player(true, 'R', "Resources/buzz.png", scene, this);
    zurg = new Player(false, 'L', "Resources/zurg.png", scene, this);

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

    // Tela de score
    scoreBg = new Sprite("Resources/background/backg-score.png");
    scoreBuzz = new TileSet("Resources/background/points.png", 274, 50, 1, 6);
    scoreZurge = new TileSet("Resources/background/points.png", 274, 50, 1, 6);
}

// ------------------------------------------------------------------------------

void Level1::Update()
{
	if (buzz->dead || zurg->dead)
		Hit();

	buzz->paused = paused;
	zurg->paused = paused;

    if (paused)
        if (window->KeyPress(VK_RETURN)) {
            buzz->Reset();
            zurg->Reset();
			paused = false;
        }

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

	if (window->KeyPress('P'))
    {
        ToyAscension::NextLevel<GameOver>();
        return;
	}

    scene->Update();
    scene->CollisionDetection();
}

// ------------------------------------------------------------------------------

void Level1::Draw()
{
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
	scene->Draw();

    if (ToyAscension::viewBBox)
        scene->DrawBBox();

	if (paused)
		scoreBg->Draw(window->CenterX(), window->CenterY(), Layer::FRONT);
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

void Level1::Hit() {
    // Reset nos players
    // Pausa a partida
    // Exibe a scoreBg
	paused = true;

	buzz->dead = false;
	zurg->dead = false;
}