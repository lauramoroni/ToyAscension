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

Projectile::Projectile(Player * player, Scene * currScene, float angle, float aimRadius, bool rico) {
	sprite = new Sprite("Resources/buzz_projectile.jpg");
	currentScene = currScene;
	ricochet = rico;

	speed.RotateTo(player->shotDirection.Angle() + angle);
	speed.ScaleTo(player->shotDirection.Magnitude());


	// move para posi��o
	MoveTo(player->X() + aimRadius * cos(speed.Radians()), player->Y() - aimRadius * sin(speed.Radians()));
	
	RotateTo(-speed.Angle());
	BBox(new Rect(-8, -3, 8, 3));
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
		//ToyAscension::audio->Play(EXPLOSION);
		//Explosion* explo = new Explosion(ToyAscension::exploSet, currentScene);
		//explo->MoveTo(x, y);
		//currentScene->Add(explo, STATIC);
		currentScene->Delete();
	}
}

void Projectile::OnCollision(Object* obj) {

	if (obj->Type() == PLATFORM) {
		ToyAscension::audio->Play(EXPLOSION);
		Explosion* explo = new Explosion(ToyAscension::exploSet, currentScene);
		explo->MoveTo(x, y);
		currentScene->Add(explo, STATIC);

		if (ricochet) {
			Vector reflexao{ (360 - speed.Angle()) * 2, speed.Magnitude() };
			speed.RotateTo(reflexao.Angle());
			ricochet = false;
		}
		else {
			currentScene->Delete(this, MOVING);
		}
	}
}

void Projectile::Draw() {
	sprite->Draw(x, y, z, 1.0f, rotation);
}