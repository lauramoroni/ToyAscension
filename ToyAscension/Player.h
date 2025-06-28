#ifndef _Player_H_
#define _Player_H_

// ---------------------------------------------------------------------------------

#include "Vector.h"                     // representa��o de vetor
#include "Object.h"                     // objetos do jogo
#include "Animation.h"                  // anima��o de sprites
#include "Types.h"                      // tipos espec�ficos da engine
#include <string>

// ---------------------------------------------------------------------------------

enum Gravity { IDLE, RUN, JUMP, CROUCH };                   // animacoes

// ---------------------------------------------------------------------------------

class Player : public Object
{
private:
    TileSet* tileset;
    Animation* anim;

    // teclas de controle 
    char up;
    char down;
    char left;
    char right;

    char initial_side;                  // lado inicial  (L ou R)

    bool started = false;

    // constantes de controle 
    const float SPEED = 300.0f;
	const float JUMP = 200.0f;

public:
    Player(char, char, char, char, char, std::string);
    ~Player();

    void Update();                      // atualiza��o
    void Draw();                        // desenho
    float Bottom();                     // coordenadas da base
    float Top();                        // coordenadas do topo

    void Reset();

    void OnCollision(Object* obj);      // resolu��o da colis�o
};

// ---------------------------------------------------------------------------------

inline float Player::Bottom()
{
    return y + tileset->Height() / 2;
}

inline float Player::Top()
{
    return y - tileset->Height() / 2;
}

inline void Player::Draw()
{
    anim->Draw(x, y, z);
}

// ---------------------------------------------------------------------------------

#endif