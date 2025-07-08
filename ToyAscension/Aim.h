/**********************************************************************************
// Aim (Arquivo de Cabecalho)
//
// Criacao:     08 jul 2025
// Atualizacao: 08 jul 2025
// Compilador:  Visual C++ 2019
//
// Descricao:   Classe visual para mira do jogador
//
**********************************************************************************/

#ifndef TOYASCENSION_AIM_H
#define TOYASCENSION_AIM_H

#include "Object.h"
#include "Sprite.h"
#include "Player.h"

class Player;
// enum AimType { DEFAULT = 0, RICOCHET = 1, TRIPLE = 2, HOMING = 3, TURRET = 4 };

class Aim : public Object
{
private:
	Sprite* sprite;
	Player* player;

public:
	Aim(Player * p );
	~Aim();

	void Update();
	void Draw();
};

#endif