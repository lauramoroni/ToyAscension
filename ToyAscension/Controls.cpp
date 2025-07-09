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
#include "Controls.h"

// ------------------------------------------------------------------------------

void Controls::Init()
{
	backg = new Sprite("Resources/background/controls.png");
}

// ------------------------------------------------------------------------------

void Controls::Update()
{
	// se a tecla ENTER for pressionada
	if (window->KeyPress(VK_ESCAPE))
	{
		ToyAscension::NextLevel<Home>();

	}
}

// ------------------------------------------------------------------------------

void Controls::Draw()
{
	backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
}

// ------------------------------------------------------------------------------

void Controls::Finalize()
{
	delete backg;
}

// ------------------------------------------------------------------------------