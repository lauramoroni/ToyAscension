#ifndef _Player_H_
#define _Player_H_

// ---------------------------------------------------------------------------------

#include "Vector.h"                     // representação de vetor
#include "Object.h"                     // objetos do jogo
#include "Animation.h"                  // animação de sprites
#include "Types.h"                      // tipos específicos da engine
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
    Sprite* barrier = nullptr;

	// variáveis de controle
	bool jumping = false;            // se o player está pulando
	bool crouching = false;           // se o player está agachado
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
    // power up de shield
    boolean shield = false;

    // power up de tiro triplo
    bool tripleShot;
    int tripleShotCount;

    // power up de tiro ricochete
	bool ricochetShot;
	int ricochetShotCount;

    const float SHOT_MAG = 400.0f;
    Vector shotDirection;
    
    Controller* gamepad = nullptr;     // controle de jogo

	uint kill_count = 0;            // contador de inimigos mortos
    uint death_count = 0;

    Player(bool, char, std::string, Scene* currScene);
    ~Player();

    void Update();                      // atualização
    void Draw();                        // desenho
    float Bottom();                     // coordenadas da base
    float Top();                        // coordenadas do topo
	float Left();                       // coordenadas da esquerda
	float Right();                      // coordenadas da direita

    void Reset();

    void OnCollision(Object* obj);      // resolução da colisão
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