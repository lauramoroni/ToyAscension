
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

	buzzPoints = ToyAscension::buzzPoints;
	zurgPoints = ToyAscension::zurgPoints;
	buzzPowers = ToyAscension::buzzPower;
	zurgPowers = ToyAscension::zurgPower;

	if (buzzPoints > zurgPoints) {
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
		ToyAscension::NextLevel<Home>();
		return;
	}
}

// ----------------------------------------------------------------------

void GameOver::Draw()
{
	Color white{ 1.0f, 1.0f, 1.0f, 1.0f };

	backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
	font->Draw(545, 505, std::to_string(buzzPoints), white, Layer::FRONT, 1.5f);
	font->Draw(880, 505, std::to_string(zurgPoints), white, Layer::FRONT, 1.5f);

	font->Draw(575, 550, std::to_string(buzzPowers), white, Layer::FRONT, 1.5f);
	font->Draw(915, 550, std::to_string(zurgPowers), white, Layer::FRONT, 1.5f);
}

void GameOver::Finalize()
{
	delete backg;
	delete font;
}

// ----------------------------------------------------------------------