/**********************************************************************************
// PowerUp (Arquivo de Cabeçalho)
//
// Criação:     08 Jul 2025
// Atualização: 08 Jul 2025
// Compilador:  Visual C++ 2022
//
// Descrição:   Power-ups para aumentar o poder do jogador temporariamente
//
**********************************************************************************/

#ifndef TOY_ASCENSION_POWER_UP_H
#define TOY_ASCENSION_POWER_UP_H

#include "Types.h"                          // tipos específicos da engine
#include "Object.h"							// interface de um objeto
#include "Animation.h"                      // desenha animação
#include "TileSet.h"                        // folha de sprites

class PowerUp : public Object
{
private:
	Animation* m_animation;                // animação do power-up
	TileSet* m_tileset;                    // folha de sprites do power-up

public:
	PowerUp();
	~PowerUp();
	void Update();
	void Draw();
	void OnCollision(Object* obj);
};
#endif