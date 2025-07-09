/**********************************************************************************
// Aim (Código Fonte)
//
// Criação:     08 Jul 2025
// Atualização: 08 Jul 2025
// Compilador:  Visual C++ 2022
//
// Descrição:   Definições da classe visual Aim
//
**********************************************************************************/

#include "Aim.h"
#include "ToyAscension.h"
#include "Player.h"

Aim::Aim(Player * p) {
	sprite = new Sprite("Resources/aimDefault2.png");
	player = p;

	RotateTo(player->shotDirection.Angle());

	MoveTo(player->X(), player->Y()); //TODO fazer ele rodar fixo ao redor do player
}

Aim::~Aim() {
	delete sprite;
}

void Aim::Update() {
	float px = player->X();
	float py = player->Y();

	float raio = 45.0f;

	MoveTo(px, py - 45); //TODO fazer ele rodar fixo ao redor do player
	
	float angle = 0.0f;

	// get angle and convert to radians
	float shotAngle = player->shotDirection.Radians();

	float aimX = px + raio * cos(shotAngle);
	float aimY = py - raio * sin(shotAngle);

	// Move o Aim para a posição calculada
	MoveTo(aimX, aimY);
	
	float degAngle = -player->shotDirection.Angle();
	RotateTo(degAngle);
}

void Aim::Draw() {
	sprite->Draw(x, y, z, 1.0f, rotation);
}

