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
    
    backg = new Sprite("Resources/map1.png");
    infoBox = new Sprite("Resources/InfoBox.png");
    keyMap  = new Sprite("Resources/Keymap.png");

    // listPlatform.push_back(platform);

    //superior esquerdo
    //                        x,y         x1,y1         posY   posY    tipo de plataforma
    platform = new Platform(0.0f, 0.0f, 330.0f, 45.0f, 10.0f, 0.0f, SCENARIO);
    scenario.push_back(platform);
    
    platform = new Platform(0.0f, 0.0f, 60.0f, 155.0f, 10.0f, 45.0f, SCENARIO);
    scenario.push_back(platform);

    //meio esquerdo

    platform = new Platform(0.0f, 0.0f, 85.0f, 50.0f, 10.0f, 330.0f, SCENARIO);
    scenario.push_back(platform);

    //inferior esquerdo
    platform = new Platform(0.0f, 0.0f, 175.0f, 50.0f, 10.0f, 520.0f, SCENARIO);
    scenario.push_back(platform);

    platform = new Platform(0.0f, 0.0f, 85.0f, 50.0f, 185.0f, 550.0f, SCENARIO);
    scenario.push_back(platform);

    //superior direito

    platform = new Platform(0.0f, 0.0f, 230.0f, 45.0f, 790.0f, 0.0f, SCENARIO);
    scenario.push_back(platform);

    platform = new Platform(0.0f, 0.0f, 120.0f, 220.0f, 900.0f, 45.0f, SCENARIO);
    scenario.push_back(platform);

    //inferior direito
    
    platform = new Platform(0.0f, 0.0f, 180.0f, 220.0f, 840.0f, 365.0f, SCENARIO);
    scenario.push_back(platform);

    //plataformas que tem um espinho 

    platform = new Platform(0.0f, 0.0f, 95.0f, 90.0f, 255.0f, 137.0f, SCENARIO);
    scenario.push_back(platform);
    platform = new Platform(0.0f, 0.0f, 160.0f, 30.0f, 353.0f, 150.0f, SCENARIO);
    scenario.push_back(platform);

    //plataforma que cai quando pisa ** checar o collision 

    platform = new Platform(0.0f, 0.0f, 120.0f, 50.0f, 330.0f, 355.0f, DESTRUCTIVE);
    listPlatformDynamic.push_back(platform);
    platform = new Platform(0.0f, 0.0f, 120.0f, 50.0f, 370.0f, 355.0f, DESTRUCTIVE);
    listPlatformDynamic.push_back(platform);
    platform = new Platform(0.0f, 0.0f, 120.0f, 50.0f, 420.0f, 355.0f, DESTRUCTIVE);
    listPlatformDynamic.push_back(platform);

    //plataformas que se mexem em x e y 
    platform = new Platform(0.0f, 0.0f, 185.0f, 30.0f, window->CenterX(), window->CenterY(), DYNAMICX);
    listPlatformDynamic.push_back(platform);

    platform = new Platform(0.0f, 0.0f, 115.0f, 30.0f, window->CenterX()+ 100, window->CenterY() - 100, DYNAMICY);
    listPlatformDynamic.push_back(platform);


    //chão

    platform = new Platform(0.0f, 0.0f, 410.0f, 40.0f, 430.0f, 550.0f, SCENARIO);
    scenario.push_back(platform);

    item = new Item(SHIELD, window->CenterX(), window->CenterY());
    scene->Add(item, STATIC);
    
    for (auto obj : scenario)
        scene->Add(obj, STATIC);

    for (auto obj : listPlatformDynamic)
        scene->Add(obj, MOVING);

}

// ------------------------------------------------------------------------------

void ToyAscension::Update()
{
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    if (window->KeyPress('B')) {
        viewBBox = !viewBBox;
    }

    if (window->KeyPress('Y')) {
        for (auto platform : listPlatformDynamic) {
            if (platform->type == DESTRUCTIVE) {
                platform->setVelY(400.0f);
                
            }
        }
    }

    
    scene->Update();
}

// ------------------------------------------------------------------------------

void ToyAscension::Draw()
{
    // desenha pano de fundo 
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    // desenha elementos sobrepostos

    // desenha cena
    scene->Draw();
    // define cor do texto

    // desenha texto
    if (viewBBox)
        scene->DrawBBox();

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

