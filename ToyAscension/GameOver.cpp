
#include "ToyAscension.h"

#include "Engine.h"
#include "GameOver.h"
#include "Home.h"
#include "Sprite.h"

// ----------------------------------------------------------------------

void GameOver::Init()
{
	font = new Font("Resources/font/Tahoma14.png");
	font->Spacing("Resources/font/Tahoma14.dat");

	buzz = 2;
	zurg = 5;

	if (buzz > zurg) {
		backg = new Sprite("Resources/score/buzz-wins.png");
	}
	else {
		backg = new Sprite("Resources/score/zurg-wins.png");
	}
}

// ----------------------------------------------------------------------


void GameOver::Update()
{
	if (window->KeyPress(VK_ESCAPE)) {
		Engine::Next<Home>();
		return;
	}
}

// ----------------------------------------------------------------------

void GameOver::Draw()
{
	Color white{ 1.0f, 1.0f, 1.0f, 1.0f };

	backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
	font->Draw(559, 505, std::to_string(buzz), white, Layer::FRONT, 1.5f);
	font->Draw(895, 505, std::to_string(zurg), white, Layer::FRONT, 1.5f);

}

void GameOver::Finalize()
{
	delete backg;
	delete font;
}

// ----------------------------------------------------------------------