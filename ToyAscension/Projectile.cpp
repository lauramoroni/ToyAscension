/**********************************************************************************
// Projectile (Código Fonte)
//
// Criação:     08 Jul 2025
// Atualização: 08 Jul 2025
// Compilador:  Visual C++ 2022
//
// Descrição:   Define uma classe para um Projétil
//
**********************************************************************************/

#include "Projectile.h"

Projectile::Projectile(Player * player, Scene * currScene, float angle, float aimRadius) {
	sprite = new Sprite("Resources/buzz_projectile.jpg");
	currentScene = currScene;

	speed.RotateTo(player->shotDirection.Angle() + angle);
	speed.ScaleTo(player->shotDirection.Magnitude());

	// move para posição
	MoveTo(player->X() + aimRadius * cos(speed.Radians()), player->Y() - aimRadius * sin(speed.Radians()));
}

Projectile::~Projectile() {
	delete sprite;
}

void Projectile::Update() {
	// testes para modificadores de projétil aqui

	Translate(speed.XComponent() * gameTime, -speed.YComponent() * gameTime);

	if (X() < 0 || X() > window->Width() || Y() < 0 || Y() > window->Height())
	{
		// animação e som de explosão
		currentScene->Delete();
	}
}

void Projectile::OnCollision(Object* obj) {

}

void Projectile::Draw() {
	sprite->Draw(x, y, z);
}