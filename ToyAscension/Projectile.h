/**********************************************************************************
// Projectile (Arquivo de Cabecalho)
//
// Criacao:     08 jul 2025
// Atualizacao: 08 jul 2025
// Compilador:  Visual C++ 2019
//
// Descricao:   Projétil dos players
//
**********************************************************************************/

#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Vector.h"                             // representação de vetor
#include "Object.h"                             // objetos do jogo
#include "Sprite.h"                             // desenho de sprites
#include "Player.h"
#include "Scene.h"

class Projectile : public Object {
private:
	Sprite* sprite;
	Vector speed;
	Scene* currentScene = nullptr;
	Player* player = nullptr;
	bool ricochet;

public:
	Projectile(Player* player, Scene* currentScene, float angle, float aimRadius, bool ricochet);
	~Projectile();

	void Update();
	void Draw();
	void OnCollision(Object* obj);
	void Hit();
};

#endif