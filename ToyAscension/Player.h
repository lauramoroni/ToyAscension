#ifndef _Player_H_
#define _Player_H_

// ---------------------------------------------------------------------------------

#include "Vector.h"                     // representa��o de vetor
#include "Object.h"                     // objetos do jogo
#include "Animation.h"                  // anima��o de sprites
#include "Types.h"                      // tipos espec�ficos da engine
#include "Scene.h"
#include <string>

// ---------------------------------------------------------------------------------

enum Gravity { IDLE_LEFT, RUN_LEFT, JUMP_LEFT, CROUCH_LEFT, IDLE_RIGHT, RUN_RIGHT, JUMP_RIGHT, CROUCH_RIGHT };                   // animacoes

// ---------------------------------------------------------------------------------

class Player : public Object
{
private:
    TileSet* tileset;
    Animation* anim;
    Sprite* barrier = nullptr;
    // teclas de controle 
    char up;
    char down;
    char left;
    char right;

	// vari�veis de controle
    char looking_side;                  // L ou R
	bool jumping = false;            // se o player est� pulando
    float jump_factor = JUMP;
    char jump_count = 0;

    bool started = false;

    // constantes de controle 
    const float SPEED = 300.0f;
	const float JUMP = 850.0f;
	const float GRAVITY = 300.0f;
	const float SPEED_JUMP_PENALTY = 100.0f; // desconto na velocidade durante o pulo

    Scene* currentScene;

public:
    // vari�veis de power up

    // power up de shield
    boolean shield = false;

    // power up de tiro triplo
    bool tripleShot;
    int tripleShotCount;

    // power up de tiro ricochete
	bool ricochetShot;
	int ricochetShotCount;

    Vector shotDirection;
    
    Player(char, char, char, char, char, std::string, Scene* currScene);
    ~Player();

    void Update();                      // atualiza��o
    void Draw();                        // desenho
    float Bottom();                     // coordenadas da base
    float Top();                        // coordenadas do topo
	float Left();                       // coordenadas da esquerda
	float Right();                      // coordenadas da direita

    void Reset();

    void OnCollision(Object* obj);      // resolu��o da colis�o
};

// ---------------------------------------------------------------------------------

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