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

// ------------------------------------------------------------------------------

Scene * ToyAscension::scene = nullptr;            // cena do jogo
Audio * ToyAscension::audio = nullptr;            // sistema de �udio
Font  * ToyAscension::font  = nullptr;            // fonte para texto

// ------------------------------------------------------------------------------

void ToyAscension::Init() 
{
    // cria sistema de �udio
    
    // cria fontes para exibi��o de texto

    // cria cena do jogo
	scene = new Scene();
    
    backg   = new Sprite("Resources/Sky.png");
    infoBox = new Sprite("Resources/InfoBox.png");
    keyMap  = new Sprite("Resources/Keymap.png");
}

// ------------------------------------------------------------------------------

void ToyAscension::Update()
{
    // sai com o pressionamento de ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    // atualiza a cena
    scene->Update();
} 

// ------------------------------------------------------------------------------

void ToyAscension::Draw()
{
    // desenha pano de fundo 

    // desenha elementos sobrepostos

    // desenha cena

    // define cor do texto

    // desenha texto

} 

// ------------------------------------------------------------------------------

void ToyAscension::Finalize()
{
    delete backg;
    delete keyMap;
    delete infoBox;
    delete scene;
}


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, 
                     _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    Engine * engine = new Engine();

    // configura motor
    engine->window->Mode(WINDOWED);
    engine->window->Size(1024,600);
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

