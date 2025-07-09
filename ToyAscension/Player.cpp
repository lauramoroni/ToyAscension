#include "Player.h"
#include "Projectile.h"
#include "ToyAscension.h"



// --------------------------------------------------------------------------------

Player::Player(bool keyboard, char initial_side, std::string file_name, Scene* currScene)
{
	this->currentScene = currScene;

	barrier = new Sprite("Resources/Barrier.png");
	// Parametrization setup
	this->keyboard = keyboard;
	this->looking_side = initial_side;
	this->initial_side = initial_side;

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

	if (initial_side == 'L') {
		MoveTo(750.0f, 400.0f, Layer::FRONT);
		anim->Select(IDLE_RIGHT);
	}
	else {
		MoveTo(565.0f, 400.0f, Layer::FRONT);
		anim->Select(IDLE_LEFT);
	}

    type = PLAYER;
	jumping = false;
	jump_factor = 0;
  
	tripleShot = false;
	tripleShotCount = 3;

	ricochetShot = false;
	ricochetShotCount = 5;

	kill_count = 0;

	shotDirection.ScaleTo(SHOT_MAG);
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
	if (initial_side == 'L') {
		MoveTo(750.0f, 400.0f, Layer::FRONT);
		anim->Select(IDLE_RIGHT);
	}
	else {
		MoveTo(565.0f, 400.0f, Layer::FRONT);
		anim->Select(IDLE_LEFT);
	}
}

// ---------------------------------------------------------------------------------

void Player::OnCollision(Object* obj)
{
	if (obj->Type() == PROJECTILE) {
		OutputDebugString("Player hit by projectile!\n");
		if (shield) {
			shield = false;
			Projectile* projectile = static_cast<Projectile*>(obj);
			currentScene->Delete(projectile, MOVING);
		}
		else if (!dead){
			Projectile* projectile = static_cast<Projectile*>(obj);
			projectile->Hit();
			dead = true; // Player morreu
			death_count++;
		}
	}

	if (obj->Type() == PLATFORM) {
		Platform* platform = static_cast<Platform*>(obj);

		// Calcula as distâncias de sobreposição
		float dxLeft = Right() - platform->Left();   // quanto invadiu pela esquerda
		float dxRight = platform->Right() - Left();   // quanto invadiu pela direita
		float dyTop = Bottom() - platform->Top();   // quanto invadiu por cima
		float dyBottom = platform->Bottom() - Top();   // quanto invadiu por baixo

		float min_dx = (dxLeft < dxRight) ? dxLeft : dxRight;
		float min_dy = (dyTop < dyBottom) ? dyTop : dyBottom;


		// Decide se a colisão é vertical (pular/parar) ou lateral (parede)
		if (min_dy < min_dx) {
			// Colisão vertical
			if (platform->Top() >= Top()) {
				// Player está acima da plataforma (pisou nela)
				MoveTo(X(), platform->Top() - 31);
				jumping = false;
				jump_count = 0;
			}
			else {
				// Player bateu por baixo da plataforma
				MoveTo(X(), platform->Bottom() + 31);
				jump_factor = 0;
			}
		}
		else {
			// Colisão lateral (paredes)
			if (Right() > platform->Left() && Right() < platform->Left() + 15) {
				MoveTo(platform->Left() - 23, Y());
			}
			// Apenas para colisão direita -> esquerda
			if (Left() <= platform->Right() && Left() >= platform->Right() - 15) {
				MoveTo(platform->Right() + 22, Y());
			}

		}


		touch = true;
	}

}

// ---------------------------------------------------------------------------------

void Player::Update()
{
	if (paused)
		return;


	touch = false;

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
			if (tripleShot && tripleShotCount > 0) {
				currentScene->Add(new Projectile(this, currentScene, -10.0f, 52.0f, false, false), MOVING);
				currentScene->Add(new Projectile(this, currentScene, 0.0f, 52.0f, false, false), MOVING);
				currentScene->Add(new Projectile(this, currentScene, 10.0f, 52.0f, false, false), MOVING);
				tripleShotCount--;

				if (tripleShotCount == 0) {
					tripleShot = false; // Desativa o triple shot após usar
					tripleShotCount = 3; // Reseta o contador de triple shot
				}
			}

			else if (ricochetShot && ricochetShotCount > 0) {
				currentScene->Add(new Projectile(this, currentScene, 0.0f, 52.0f, true, false), MOVING);
				ricochetShotCount--;

				if (ricochetShotCount == 0) {
					ricochetShot = false; // Desativa o ricochet shot após usar
					ricochetShotCount = 5; // Reseta o contador de ricochet shot
				}
			}
			else if (piercingShot) {
				ToyAscension::audio->Play(SNIPER);
				currentScene->Add(new Projectile(this, currentScene, 0.0f, 52.0f, false, true), MOVING);
				// adicionar sons

				piercingShot = false; // Desativa o piercing shot após usar
				
			}
			else if (gatlingShot) {
				// ao atirar, "pressiona" o botão de tiro para disparar vários projéteis

				currentScene->Add(new Projectile(this, currentScene, -2.5f, 20.0f, false, false), MOVING);
				currentScene->Add(new Projectile(this, currentScene, -1.5f, 40.0f, false, false), MOVING);
				currentScene->Add(new Projectile(this, currentScene, -0.5f, 60.0f, false, false), MOVING);
				currentScene->Add(new Projectile(this, currentScene, 0.0f, 80.0f, false, false), MOVING);
				currentScene->Add(new Projectile(this, currentScene, 0.5f, 120.0f, false, false), MOVING);
				currentScene->Add(new Projectile(this, currentScene, 1.5f, 100.0f, false, false), MOVING);
				currentScene->Add(new Projectile(this, currentScene, 2.5f, 120.0f, false, false), MOVING);
				gatlingShot = false;
			}

			else {
				currentScene->Add(new Projectile(this, currentScene, 0.0f, 52.0f, false, false), MOVING);
			}

			ToyAscension::audio->Play(SHOT);
			shooting = true;
		}
	}
	else if (controller_on) {
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

		Vector controllerX = Vector(0.0f, gamepad->Axis(AxisRX));
		Vector controllerY = Vector(270.0f, gamepad->Axis(AxisRY));

		shotDirection.Add(controllerX);
		shotDirection.Add(controllerY);
		shotDirection.ScaleTo(SHOT_MAG);

		if (gamepad->Axis(AxisZ) == 0)
			shooting = false;

		if ((gamepad->Axis(AxisZ) < 0) && !shooting) {
			if (tripleShot && tripleShotCount > 0) {
				currentScene->Add(new Projectile(this, currentScene, -10.0f, 52.0f, false, false), MOVING);
				currentScene->Add(new Projectile(this, currentScene, 0.0f, 52.0f, false, false), MOVING);
				currentScene->Add(new Projectile(this, currentScene, 10.0f, 52.0f, false, false), MOVING);
				tripleShotCount--;

				if (tripleShotCount == 0) {
					tripleShot = false; // Desativa o triple shot após usar
					tripleShotCount = 3; // Reseta o contador de triple shot
				}
			}

			else if (ricochetShot && ricochetShotCount > 0) {
				currentScene->Add(new Projectile(this, currentScene, 0.0f, 52.0f, true, false), MOVING);
				ricochetShotCount--;

				if (ricochetShotCount == 0) {
					ricochetShot = false; // Desativa o ricochet shot após usar
					ricochetShotCount = 5; // Reseta o contador de ricochet shot
				}
			}
			else if (piercingShot) {
				ToyAscension::audio->Play(SNIPER);
				currentScene->Add(new Projectile(this, currentScene, 0.0f, 52.0f, false, true), MOVING);
				// adicionar sons

				piercingShot = false; // Desativa o piercing shot após usar

			}
			else if (gatlingShot) {
				// ao atirar, "pressiona" o botão de tiro para disparar vários projéteis

				currentScene->Add(new Projectile(this, currentScene, -2.5f, 52.0f, false, false), MOVING);
				currentScene->Add(new Projectile(this, currentScene, -1.5f, 52.0f, false, false), MOVING);
				currentScene->Add(new Projectile(this, currentScene, -0.5f, 52.0f, false, false), MOVING);
				currentScene->Add(new Projectile(this, currentScene, 0.0f, 52.0f, false, false), MOVING);
				currentScene->Add(new Projectile(this, currentScene, 0.5f, 52.0f, false, false), MOVING);
				currentScene->Add(new Projectile(this, currentScene, 1.5f, 52.0f, false, false), MOVING);
				currentScene->Add(new Projectile(this, currentScene, 2.5f, 52.0f, false, false), MOVING);
				gatlingShot = false;
			}
			else {
				currentScene->Add(new Projectile(this, currentScene, 0.0f, 52.0f, false, false), MOVING);
			}

			OutputDebugString("Player shot!\n");
			ToyAscension::audio->Play(SHOT);
			shooting = true;
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
	}

	// Teletransporte horizontal do player
	if (X() < -20) {
		MoveTo(1300, Y()); // Saiu pela esquerda, aparece à direita
	}
	else if (X() > 1300) {
		if (Y() > 800) {
			MoveTo(0, Y() - 120); // Saiu pela direita, aparece à esquerda
		}
		else {
			MoveTo(0, Y()); // Saiu pela direita, aparece à esquerda
		}
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
