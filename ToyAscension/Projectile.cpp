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

	this->player = player;

	speed.RotateTo(player->shotDirection.Angle() + angle);
	speed.ScaleTo(player->shotDirection.Magnitude());

	// move para posi��o
	MoveTo(player->X() + aimRadius * cos(speed.Radians()), player->Y() - aimRadius * sin(speed.Radians()));
	
	RotateTo(-speed.Angle());
	BBox(new Rect(-8, -3, 8, 3));
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
			Vector reflexao{ 0.0f, 0.0f };

			// Descobrir a face que atingiu
			Platform* platform = static_cast<Platform*>(obj);

			if (platform->Left() >= (X() - 4)) {
				// Projetil est� � esquerda da plataforma
				MoveTo(platform->Left() - 8, Y());
				reflexao = Vector(180.0f, 1.8 * speed.Magnitude());
			}
			else if (platform->Right() <= (X() + 4)) {
				// Proj est� � direita da plataforma
				MoveTo(platform->Right() + 8, Y());
				reflexao = Vector(0.0f, 1.8 * speed.Magnitude());
			}
			else if (platform->Top() >= (Y() - 2)) {
				// Proj est� acima da plataforma
				MoveTo(X(), platform->Top() - 4);
				reflexao = Vector(90.0f, 1.8 * speed.Magnitude());
			}
			else if (platform->Bottom() <= (Y() + 2)) {
				// Proj est� abaixo da plataforma
				MoveTo(X(), platform->Bottom() + 4);
				reflexao = Vector(270.0f, 1.8 * speed.Magnitude());
			}

			speed.Add(reflexao);
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

void Projectile::Hit() {
	// Implementar l�gica de impacto, se necess�rio
	ToyAscension::audio->Play(EXPLOSION);
	Explosion* explo = new Explosion(ToyAscension::exploSet, currentScene);
	explo->MoveTo(x, y);
	currentScene->Add(explo, STATIC);
	currentScene->Delete(this, MOVING);

	player->kill_count++;
}