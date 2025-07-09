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

#include <algorithm>
#include <random>
#include <string>
#include <fstream>
using namespace std;
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
    buzz = new Player(true, 'R', "Resources/buzz.png", scene);
    zurg = new Player(false, 'L', "Resources/zurg.png", scene);

    scene->Add(buzz, MOVING);
    scene->Add(zurg, MOVING);

    scene->Add(new Aim(buzz), MOVING);
    scene->Add(new Aim(zurg), MOVING);

    // possíveis posições para spawn de itens
    struct Position {
        float x, y;
    };

    Position positions[3] = {
		{window->CenterX() + 20, 100},
		{window->CenterX() + 20, window->CenterY() + 50},
		{window->CenterX() - 100, window->CenterY() + 350}
    };

	random_device rd;
	mt19937 gen(rd());

	shuffle(begin(positions), end(positions), gen);

    item = new Item(SHIELD, positions[0].x, positions[0].y, scene);
    item2 = new Item(TRIPLE_SHOT, positions[1].x, positions[1].y , scene);
	item3 = new Item(RICOCHET_SHOT, positions[2].x, positions[2].y, scene);

    scene->Add(item, STATIC);
    scene->Add(item2, STATIC);
    scene->Add(item3, STATIC);

    // Tela de score
    scoreBg = new Sprite("Resources/background/backg-score.png");
    scoreBuzz = new TileSet("Resources/score/points.png", 274, 52, 1, 6);
    scoreZurg = new TileSet("Resources/score/points.png", 274, 52, 1, 6);

    scoreBuzzAnim = new Animation(scoreBuzz, 0.0f, false);
    scoreZurgAnim = new Animation(scoreZurg, 0.0f, false);

	scoreBuzzAnim->Add(1, new uint[1]{ 1 }, 1);
	scoreBuzzAnim->Add(2, new uint[1]{ 2 }, 1);
	scoreBuzzAnim->Add(3, new uint[1]{ 3 }, 1);
	scoreBuzzAnim->Add(4, new uint[1]{ 4 }, 1);
	scoreBuzzAnim->Add(5, new uint[1]{ 5 }, 1);
	scoreBuzzAnim->Add(0, new uint[1]{ 0 }, 1);

    scoreZurgAnim->Add(5, new uint[1]{ 5 }, 1);
    scoreZurgAnim->Add(4, new uint[1]{ 4 }, 1);
    scoreZurgAnim->Add(3, new uint[1]{ 3 }, 1);
    scoreZurgAnim->Add(2, new uint[1]{ 2 }, 1);
    scoreZurgAnim->Add(1, new uint[1]{ 1 }, 1);
    scoreZurgAnim->Add(0, new uint[1]{ 0 }, 1);

    // Zerar pontuação do ToyAscencion.h
	ToyAscension::buzzPoints = 0;
	ToyAscension::zurgPoints = 0;
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

	if (window->KeyPress('P') || game_ended)
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

    if (paused) {
		scoreBg->Draw(window->CenterX(), window->CenterY(), Layer::FRONT);
        scoreBuzzAnim->Draw(697.0f, 344.0f, Layer::FRONT);
		scoreZurgAnim->Draw(697.0f, 428.0f, Layer::FRONT);
    }
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

	scoreBuzzAnim->Select(buzz->kill_count);
	scoreZurgAnim->Select(zurg->kill_count);

	// Atualiza pontuação no ToyAscension.h
    ToyAscension::buzzPoints = buzz->kill_count;
    ToyAscension::zurgPoints = zurg->kill_count;

    if (buzz->kill_count == 5 || zurg->kill_count == 5){
        game_ended = true;
    }
}