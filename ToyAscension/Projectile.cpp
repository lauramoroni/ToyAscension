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
#include "ToyAscension.h"
#include "Explosion.h"

Projectile::Projectile(Player * player, Scene * currScene, float angle, float aimRadius) {
	sprite = new Sprite("Resources/buzz_projectile.jpg");
	currentScene = currScene;

	//Rotacionar o projétil para a direção do tiro

	speed.RotateTo(player->shotDirection.Angle() + angle);
	speed.ScaleTo(player->shotDirection.Magnitude());

	// move para posição
	MoveTo(player->X() + aimRadius * cos(speed.Radians()), player->Y() - aimRadius * sin(speed.Radians()));
	
	RotateTo(-speed.Angle());
	type = PROJECTILE;
}

Projectile::~Projectile() {
	delete sprite;
}

void Projectile::Update() {
	// testes para modificadores de projétil aqui

	Translate(speed.XComponent() * gameTime, -speed.YComponent() * gameTime);

	//TODO implementar relação com colisões 
	if (X() < 0 || X() > window->Width() || Y() < 0 || Y() > window->Height())
	{
		// animação e som de explosão
		ToyAscension::audio->Play(EXPLOSION);
		Explosion* explo = new Explosion(ToyAscension::exploSet, currentScene);
		explo->MoveTo(x, y);
		currentScene->Add(explo, STATIC);
		currentScene->Delete();
	}
}

void Projectile::OnCollision(Object* obj) {

}

void Projectile::Draw() {
	sprite->Draw(x, y, z, 1.0f, rotation);
}