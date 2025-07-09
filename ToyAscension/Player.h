#ifndef _Player_H_
#define _Player_H_

// ---------------------------------------------------------------------------------

#include "Vector.h"                     // representa��o de vetor
#include "Object.h"                     // objetos do jogo
#include "Animation.h"                  // anima��o de sprites
#include "Types.h"                      // tipos espec�ficos da engine
#include "Scene.h"
#include <string>

#include "ToyAscension.h"

// ---------------------------------------------------------------------------------

enum Gravity { IDLE_LEFT, RUN_LEFT, JUMP_LEFT, CROUCH_LEFT, IDLE_RIGHT, RUN_RIGHT, JUMP_RIGHT, CROUCH_RIGHT };                   // animacoes

// ---------------------------------------------------------------------------------

class Player : public Object
{
private:
    TileSet* tileset;
    Animation* anim;

    bool keyboard;

	// vari�veis de controle
	bool jumping = false;            // se o player est� pulando
	bool crouching = false;           // se o player est� agachado
    bool shooting = false;
    char looking_side;                  // L ou R
    float jump_factor = JUMP;
    char jump_count = 0;

    bool started = false;

    // constantes de controle 
    const float SPEED = 300.0f;
	const float JUMP = 850.0f;
	const float GRAVITY = 325.0f;
	const float SPEED_JUMP_PENALTY = 100.0f; // desconto na velocidade durante o pulo

    Scene* currentScene;

    bool controller_on = false;
    const float AXIS_MAX = 1000.0f;
public:
    Vector shotDirection;
    Controller* gamepad = nullptr;     // controle de jogo
    const float SHOT_MAG = 400.0f;

    Player(bool, char, std::string, Scene* currScene);
    ~Player();

    void Update();                      // atualiza��o
    void Draw();                        // desenho
    float Bottom();                     // coordenadas da base
    float Top();                        // coordenadas do topo
	float Left();                       // coordenadas da esquerda
	float Right();                      // coordenadas da direita
    bool Keyboard();

    void Reset();

    void OnCollision(Object* obj);      // resolu��o da colis�o
};

// ---------------------------------------------------------------------------------

inline bool Player::Keyboard() 
{
    return keyboard;
}

inline float Player::Bottom()
{
    return y + tileset ->TileHeight() / 2.0f;
}

inline float Player::Top()
{
    return y - tileset->TileHeight() / 2.0f;
}

inline float Player::Left()
{
	return x - tileset->TileWidth() / 2.0f;
}

inline float Player::Right()
{
    return x + tileset->TileWidth() / 2.0f;
}

// ---------------------------------------------------------------------------------

#endif