#include "Player.h"
#include "Projectile.h"
#include "ToyAscension.h"


// --------------------------------------------------------------------------------

Player::Player(bool keyboard, char looking_side, std::string file_name, Scene* currScene)
{
	currentScene = currScene;

	// Parametrization setup
	this->keyboard = keyboard;
	this->looking_side = looking_side;

	if (!keyboard) {
		// Controller
		gamepad = new Controller();

		// tenta inicializar um controle do xbox
		controller_on = gamepad->Initialize();
	}

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
	MoveTo(window->CenterX(), window->CenterY(), Layer::FRONT);

    type = PLAYER;

	jumping = false;
	jump_factor = 0;

	shotDirection.ScaleTo(SHOT_MAG);
}

// ---------------------------------------------------------------------------------

Player::~Player()
{
    delete anim;
    delete tileset;
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
	if (obj->Type() == PLATFORM) {

		Platform* platform = static_cast<Platform*>(obj);

        if (platform->Left() >= (Right() - 10)) {
            // Player está à esquerda da plataforma
            MoveTo(platform->Left() - 23, Y());
        }

        else if (platform->Right() < (Left() + 10)) {
            // Player está à direita da plataforma
            MoveTo(platform->Right() + 23, Y());
        }
		
		// Ajuste da posição do player
        else if (platform->Top() >= Top()) {
			// Player está acima da plataforma
            MoveTo(X(), platform->Top() - 31);
			jumping = false; // Reseta o estado de pulo
			jump_count = 0; // Reseta o contador de pulos
		}
        
        else if (platform->Bottom() < Bottom()) {
			// Player está abaixo da plataforma
            MoveTo(X(), platform->Bottom() + 31);
			jump_factor = 0;
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
	crouching = false;

	if (keyboard) {
		if (window->KeyDown('D')) {
			anim->Select(RUN_RIGHT);
			Translate((SPEED - jumping * SPEED_JUMP_PENALTY) * gameTime, 0.0f);
			looking_side = 'R';
		}

		else if (window->KeyDown('A')) {
			anim->Select(RUN_LEFT);
			Translate((-SPEED + jumping * SPEED_JUMP_PENALTY) * gameTime, 0.0f);
			looking_side = 'L';
		}

		else if (window->KeyDown('S')) {
			if (looking_side == 'R')
				anim->Select(CROUCH_RIGHT);
			else
				anim->Select(CROUCH_LEFT);
			crouching = true;
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
			currentScene->Add(new Projectile(this, currentScene, 0.0f, 52.0f), MOVING);
			ToyAscension::audio->Play(SHOT);
		}
	}
	else if (controller_on){
		gamepad->UpdateState();

		float x_mov = (gamepad->Axis(AxisX) / AXIS_MAX) * SPEED;
		float y_mov = (gamepad->Axis(AxisY) / AXIS_MAX) * SPEED;

		Translate(x_mov * gameTime, 0.0f);
		Translate(0.0f, y_mov * gameTime);

		if (x_mov > 0) {
			anim->Select(RUN_RIGHT);
			looking_side = 'R';
		}
		else if (x_mov < 0) {
			anim->Select(RUN_LEFT);
			looking_side = 'L';
		}

		if (y_mov > 0) {
			if (looking_side == 'R')
				anim->Select(CROUCH_RIGHT);
			else
				anim->Select(CROUCH_LEFT);
			crouching = true;
		}

		if (gamepad->ButtonDown(0)) {
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

		Vector controllerX = Vector(0.0, gamepad->Axis(AxisRX));
		Vector controllerY = Vector(270.0, gamepad->Axis(AxisRY));

		shotDirection.Add(controllerX);
		shotDirection.Add(controllerY);
		shotDirection.ScaleTo(SHOT_MAG);

		if (gamepad->Axis(AxisZ) == 0)
			shooting = false;

		if ((gamepad->Axis(AxisZ) < 0) && !shooting) {
			OutputDebugString("Player shot!\n");
			currentScene->Add(new Projectile(this, currentScene, 0.0f, 52.0f), MOVING);
			ToyAscension::audio->Play(SHOT);
			shooting = true;
		}
	}

	if (crouching) {
		Point playerVertexs[4] = {
			Point(-22.0f, -16.0f), // Top Left
			Point(22.0f, -16.0f),  // Top Right
			Point(22.0f, 30.0f),   // Bottom Right
			Point(-22.0f, 30.0f)   // Bottom Left
		};

		BBox(new Poly(playerVertexs, 4));
	}
	else {
		Point playerVertexs[4] = {
			Point(-22.0f, -30.0f), // Top Left
			Point(22.0f, -30.0f),  // Top Right
			Point(22.0f, 30.0f),   // Bottom Right
			Point(-22.0f, 30.0f)   // Bottom Left
		};

		BBox(new Poly(playerVertexs, 4));
	}

    anim->NextFrame();
}

// ---------------------------------------------------------------------------------

void Player::Draw() {
	anim->Draw(x, y, z);
}