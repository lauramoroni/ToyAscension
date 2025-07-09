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

Projectile::Projectile(Player * player, Scene * currScene, float angle, float aimRadius, bool rico) {
	sprite = new Sprite("Resources/buzz_projectile.jpg");
	currentScene = currScene;
	ricochet = rico;

	this->player = player;

	speed.RotateTo(player->shotDirection.Angle() + angle);
	speed.ScaleTo(player->shotDirection.Magnitude());

	// move para posição
	MoveTo(player->X() + aimRadius * cos(speed.Radians()), player->Y() - aimRadius * sin(speed.Radians()));
	
	RotateTo(-speed.Angle());
	BBox(new Rect(-8, -3, 8, 3));
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
				// Projetil está à esquerda da plataforma
				MoveTo(platform->Left() - 8, Y());
				reflexao = Vector(180.0f, 1.8 * speed.Magnitude());
			}
			else if (platform->Right() <= (X() + 4)) {
				// Proj está à direita da plataforma
				MoveTo(platform->Right() + 8, Y());
				reflexao = Vector(0.0f, 1.8 * speed.Magnitude());
			}
			else if (platform->Top() >= (Y() - 2)) {
				// Proj está acima da plataforma
				MoveTo(X(), platform->Top() - 4);
				reflexao = Vector(90.0f, 1.8 * speed.Magnitude());
			}
			else if (platform->Bottom() <= (Y() + 2)) {
				// Proj está abaixo da plataforma
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
	// Implementar lógica de impacto, se necessário
	ToyAscension::audio->Play(EXPLOSION);
	Explosion* explo = new Explosion(ToyAscension::exploSet, currentScene);
	explo->MoveTo(x, y);
	currentScene->Add(explo, STATIC);
	currentScene->Delete(this, MOVING);

	player->kill_count++;
}