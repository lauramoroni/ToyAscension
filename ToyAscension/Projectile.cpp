/**********************************************************************************
// Projectile (C�digo Fonte)
//
// Cria��o:     08 Jul 2025
// Atualiza��o: 08 Jul 2025
// Compilador:  Visual C++ 2022
//
// Descri��o:   Define uma classe para um Proj�til
//
**********************************************************************************/

#include "Projectile.h"
#include "ToyAscension.h"
#include "Explosion.h"

Projectile::Projectile(Player * player, Scene * currScene, float angle, float aimRadius) {
	sprite = new Sprite("Resources/buzz_projectile.jpg");
	currentScene = currScene;

	//Rotacionar o proj�til para a dire��o do tiro

	speed.RotateTo(player->shotDirection.Angle() + angle);
	speed.ScaleTo(player->shotDirection.Magnitude());

	// move para posi��o
	MoveTo(player->X() + aimRadius * cos(speed.Radians()), player->Y() - aimRadius * sin(speed.Radians()));
	
	RotateTo(-speed.Angle());
	type = PROJECTILE;
}

Projectile::~Projectile() {
	delete sprite;
}

void Projectile::Update() {
	// testes para modificadores de proj�til aqui

	Translate(speed.XComponent() * gameTime, -speed.YComponent() * gameTime);

	//TODO implementar rela��o com colis�es 
	if (X() < 0 || X() > window->Width() || Y() < 0 || Y() > window->Height())
	{
		// anima��o e som de explos�o
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