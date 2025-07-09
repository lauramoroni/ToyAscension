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
    backg = new Sprite("Resources/background/home.png");
    tileset = new TileSet("Resources/background/mouse/tileset-mouse-options.png", 1186, 700, 3, 3);
    anim = new Animation(tileset, 0.0f, false);

    uint play[1] = {0};
    uint controls[1] = {1};
	uint exit[1] = {2};

    anim->Add(PLAY, play, 1);
	anim->Add(CONTROLS, controls, 1);
	anim->Add(EXIT, exit, 1);

    //ToyAscension::audio->Play(MENU, true);
}

// ------------------------------------------------------------------------------

void Home::Update()
{
    // se a tecla ENTER for pressionada
    if (window->KeyPress(VK_RETURN))
    {
        if (currentOption == PLAY) {
            ToyAscension::NextLevel<Level1>();
            return;
		}
		else if (currentOption == CONTROLS) {
			ToyAscension::NextLevel<Level1>();
			return;
		}
		else if (currentOption == EXIT) {
			window->Close();
			return;
		}
        
    }
	if (window->KeyPress(VK_DOWN))
    {
		ToyAscension::audio->Play(MENU_SELECTION);
		currentOption++;
		if (currentOption > EXIT)
			currentOption = PLAY;
	}
	if (window->KeyPress(VK_UP))
	{
		ToyAscension::audio->Play(MENU_SELECTION);
		currentOption--;
		if (currentOption < PLAY)
			currentOption = EXIT;
	}

	anim->Select(currentOption);
}

// ------------------------------------------------------------------------------

void Home::Draw()
{
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    anim->Draw(688, 674);
}

// ------------------------------------------------------------------------------

void Home::Finalize()
{
    delete anim;
    delete tileset;
    delete backg;
}

// ------------------------------------------------------------------------------