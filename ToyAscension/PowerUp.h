/**********************************************************************************
// PowerUp (Arquivo de Cabe�alho)
//
// Cria��o:     08 Jul 2025
// Atualiza��o: 08 Jul 2025
// Compilador:  Visual C++ 2022
//
// Descri��o:   Power-ups para aumentar o poder do jogador temporariamente
//
**********************************************************************************/

#ifndef TOY_ASCENSION_POWER_UP_H
#define TOY_ASCENSION_POWER_UP_H

#include "Types.h"                          // tipos espec�ficos da engine
#include "Object.h"							// interface de um objeto
#include "Animation.h"                      // desenha anima��o
#include "TileSet.h"                        // folha de sprites

class PowerUp : public Object
{
private:
	Animation* m_animation;                // anima��o do power-up
	TileSet* m_tileset;                    // folha de sprites do power-up

public:
	PowerUp();
	~PowerUp();
	void Update();
	void Draw();
	void OnCollision(Object* obj);
};
#endif