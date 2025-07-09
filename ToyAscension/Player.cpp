#include "Player.h"
#include "Projectile.h"
#include "ToyAscension.h"


// --------------------------------------------------------------------------------

Player::Player(char up, char down, char left, char right, char looking_side, std::string file_name, Scene* currScene)
{
	currentScene = currScene;
	barrier = new Sprite("Resources/Barrier.png");
	// Parametrization setup
	this->up = up;
	this->down = down;
	this->left = left;
	this->right = right;
	this->looking_side = looking_side;

    tileset = new TileSet(file_name, 44, 60, 6, 24);
    anim = new Animation(tileset, 0.120f, true);

    // sequências de animação do player
	uint idle_l[2] = { 0,1 };
    uint run_l[3] = { 6,7,8 };
	uint crouch_l[1] = { 12 };
    uint jump_l[1] = { 18 };

	uint idle_r[2] = { 3,4 };
	uint run_r[3] = { 9,10,11 };
	uint crouch_r[1] = { 14 };
	uint jump_r[1] = { 20 };
    
    anim->Add(RUN_LEFT, run_l, 3);
    anim->Add(IDLE_LEFT, idle_l, 2);
    anim->Add(JUMP_LEFT, jump_l, 1);
	anim->Add(CROUCH_LEFT, crouch_l, 1);
	anim->Add(RUN_RIGHT, run_r, 3);
	anim->Add(IDLE_RIGHT, idle_r, 2);
	anim->Add(JUMP_RIGHT, jump_r, 1);
	anim->Add(CROUCH_RIGHT, crouch_r, 1);

    // cria bounding box
	Point playerVertexs[4] = {
		Point(-22.0f, -30.0f), // Top Left
		Point(22.0f, -30.0f),  // Top Right
		Point(22.0f, 30.0f),   // Bottom Right
		Point(-22.0f, 30.0f)   // Bottom Left
	};

	BBox(new Poly(playerVertexs, 4));

	// posiciona o player no centro da tela
	MoveTo(window->CenterX() - 100, window->CenterY() - 200, Layer::FRONT);

    type = PLAYER;

	jumping = false;
	tripleShot = false;
	tripleShotCount = 3;

	ricochetShot = false;
	ricochetShotCount = 3;

	shotDirection.ScaleTo(400.0f);
}

// ---------------------------------------------------------------------------------

Player::~Player()
{
    delete anim;
    delete tileset;
	delete barrier;
}

// ---------------------------------------------------------------------------------

void Player::Reset()
{
    // volta ao estado inicial
    MoveTo(window->CenterX(), 24.0f, Layer::FRONT);
}

// ---------------------------------------------------------------------------------

void Player::OnCollision(Object* obj)
{
	if (obj->Type() == PROJECTILE) {
		if (shield) {
			shield = false;
		}
	}
	OutputDebugString("Player colidiu com ");

	if (obj->Type() == PLATFORM) {
		OutputDebugString("uma plataforma\n");

		Platform* platform = static_cast<Platform*>(obj);

        if (platform->Left() >= (Right() - 10)) {
            // Player está à esquerda da plataforma
            OutputDebugStringA("  - Player está à esquerda da plataforma\n");
            MoveTo(platform->Left() - 23, Y());
        }

        else if (platform->Right() < (Left() + 10)) {
            // Player está à direita da plataforma
            OutputDebugStringA("  - Player está à direita da plataforma\n");
            MoveTo(platform->Right() + 23, Y());
        }
		
		// Ajuste da posição do player
        else if (platform->Top() >= Top()) {
			// Player está acima da plataforma
			OutputDebugStringA("  - Player está acima da plataforma\n");
            MoveTo(X(), platform->Top() - 31);
			jumping = false; // Reseta o estado de pulo
			jump_count = 0; // Reseta o contador de pulos
		}
        
        else if (platform->Bottom() < Bottom()) {
			// Player está abaixo da plataforma
            OutputDebugStringA("  - Player está abaixo da plataforma\n");
            MoveTo(X(), platform->Bottom() + 31);
		}

        // plataforma destrutiva
	}
}

// ---------------------------------------------------------------------------------

void Player::Update()
{
	if (looking_side == 'R')
		anim->Select(IDLE_RIGHT);
	else
		anim->Select(IDLE_LEFT);

	// Gravity
	Translate(0.00f, GRAVITY * gameTime);

	if (window->KeyDown(right)) {
		anim->Select(RUN_RIGHT);
		Translate((SPEED - jumping * SPEED_JUMP_PENALTY) * gameTime, 0.0f);
		looking_side = 'R';
	}

	else if (window->KeyDown(left)) {
		anim->Select(RUN_LEFT);
		Translate((-SPEED + jumping * SPEED_JUMP_PENALTY) * gameTime, 0.0f);
		looking_side = 'L';
	}

	else if (window->KeyDown(down)) {
		if (looking_side == 'R')
			anim->Select(CROUCH_RIGHT);
		else
			anim->Select(CROUCH_LEFT);
	}

	if (window->KeyDown(VK_SPACE))
	{
		if (jump_count <= 2) {  // Double jump
			if (looking_side == 'R')
				anim->Select(JUMP_RIGHT);
			else
				anim->Select(JUMP_LEFT);

			if (jump_factor == JUMP) // O pulo iniciou
				jump_count++;

			Translate(0.0f, -jump_factor * gameTime);
			jump_factor -= GRAVITY * 3 * gameTime;

			if (jump_factor < 0.0f)
				jump_factor = 0.0f; // Limita o fator de pulo para não ficar negativo

			jumping = true;
		}
	}
	else {
		jump_factor = JUMP;
	}

	float dx = window->MouseX() - x;
	float dy = window->MouseY() - y;

	float mouseAngle = -(atan2(dy, dx) * (180.0f / 3.14159f)); // angulo entre o eixo X e o vetor (dx, dy) em graus
	shotDirection.RotateTo(mouseAngle);

	if (window->KeyPress(VK_LBUTTON)) {
		if (tripleShot && tripleShotCount > 0) {
			currentScene->Add(new Projectile(this, currentScene, -10.0f, 52.0f, false), MOVING);
			currentScene->Add(new Projectile(this, currentScene, 0.0f, 52.0f, false), MOVING);
			currentScene->Add(new Projectile(this, currentScene, 10.0f, 52.0f, false), MOVING);
			tripleShotCount--;

			if (tripleShotCount == 0) {
				tripleShot = false; // Desativa o triple shot após usar
				tripleShotCount = 3; // Reseta o contador de triple shot
			}
		}

		else if (ricochetShot && ricochetShotCount > 0) {
				currentScene->Add(new Projectile(this, currentScene, 0.0f, 52.0f, true), MOVING);
				ricochetShotCount--;

				if (ricochetShotCount == 0) {
					ricochetShot = false; // Desativa o ricochet shot após usar
					ricochetShotCount = 3; // Reseta o contador de ricochet shot
				}
		}
		else{
			currentScene->Add(new Projectile(this, currentScene, 0.0f, 52.0f, false), MOVING);
		}
		
		ToyAscension::audio->Play(SHOT);
	}
	
    anim->NextFrame();
}

// ---------------------------------------------------------------------------------

void Player::Draw() {

	if (shield) {
		barrier->Draw(X(), Y(), 0.0f);

	}

	anim->Draw(x, y, z);

	
}