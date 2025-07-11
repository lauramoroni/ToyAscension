/**********************************************************************************
// ToyAscension (C�digo Fonte)
//
// Cria��o:     26 de jun de 2025
// Atualiza��o:
// Compilador:  Visual C++ 2022
//
// Descri��o:   Movimento de proj�til

**********************************************************************************/

#include "Engine.h"
#include "ToyAscension.h"
#include "Home.h"


// ------------------------------------------------------------------------------

Game* ToyAscension::level = nullptr;
Audio* ToyAscension::audio = nullptr;            // sistema de �udio
Font* ToyAscension::font = nullptr;            // fonte para texto
TileSet* ToyAscension::exploSet = nullptr; // explosao
bool ToyAscension::viewBBox = false;              // estado da bounding box

uint ToyAscension::buzzPoints = 0; // pontuação do buzz
uint ToyAscension::zurgPoints = 0; // pontuação do zurg
uint ToyAscension::buzzPower = 0; // power up do buzz
uint ToyAscension::zurgPower = 0; // power up do zurg

int windowWidth = GetSystemMetrics(SM_CXSCREEN);  // largura da janela
int windowHeight = GetSystemMetrics(SM_CYSCREEN); // altura da janela

// ------------------------------------------------------------------------------

void ToyAscension::Init()
{
    // cria sistema de áudio
	audio = new Audio();
	audio->Add(SHOT, "Resources/audio/shot.wav", 5);
    audio->Volume(SHOT, 0.3f);
    audio->Add(EXPLOSION, "Resources/audio/explosion.wav", 5);
    audio->Volume(EXPLOSION, 0.15f);
	audio->Add(MENU_SELECTION, "Resources/audio/menu-selection.wav", 5);
    audio->Add(ITEMPICKUP, "Resources/audio/ItemPickup.wav", 5);
    audio->Volume(ITEMPICKUP, 0.2f);
  
    audio->Add(SNIPER, "Resources/audio/Sniper.wav", 5);
    audio->Volume(SNIPER, 0.2f);
	audio->Add(INTRO, "Resources/audio/amigo-estou-aqui.wav", 1);

    exploSet = new TileSet("Resources/explosion.png", 20, 20, 5, 5);


    // bounding box não visível
    viewBBox = false;

    // inicializa nível de abertura do jogo
    level = new Home();
    level->Init();
}

// ------------------------------------------------------------------------------

void ToyAscension::Update()
{
    // habilita/desabilita visualização da bounding box
    if (window->KeyPress('B'))
        viewBBox = !viewBBox;

    // atualiza nível
    level->Update();
}

// ------------------------------------------------------------------------------

void ToyAscension::Draw()
{
    // desenha nível
    level->Draw();
}

// ------------------------------------------------------------------------------

void ToyAscension::Finalize()
{
    level->Finalize();
    delete audio;
    delete level;
}


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    Engine* engine = new Engine();

    // configura motor
    engine->window->Mode(WINDOWED);
    engine->window->Size(1280,1024);
    engine->window->Color(25, 25, 25);
    engine->window->Title("ToyAscension");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);
    // engine->graphics->VSync(true);

    // inicia o jogo
    int status = engine->Start(new ToyAscension());

    delete engine;
    return status;
}

// ----------------------------------------------------------------------------
