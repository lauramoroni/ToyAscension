#include "Player.h"
#include "ToyAscension.h"


// --------------------------------------------------------------------------------

Player::Player(char up, char down, char left, char right, char initial_side, std::string file_name)
{
	// Parametrization setup
	this->up = up;
	this->down = down;
	this->left = left;
	this->right = right;
	this->initial_side = initial_side;

    tileset = new TileSet(file_name, 44, 60, 3, 12);
    anim = new Animation(tileset, 0.120f, true);

    // sequências de animação do player
	uint idle[2] = { 0,1 };
    uint run[3] = { 3,4,5 };
    uint jump[1] = { 9 };
	uint crouch[1] = { 6 };
    
    anim->Add(RUN, run, 3);
    anim->Add(IDLE, idle, 2);
    anim->Add(JUMP, jump, 1);
	anim->Add(CROUCH, crouch, 1);

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
    anim->Select(IDLE);

    // Gravity
    Translate(0.00f, GRAVITY * gameTime);

    if (window->KeyDown(right)) {
        anim->Select(RUN);
        Translate(SPEED * gameTime, 0.0f);
    }

    else if (window->KeyDown(left)) {
        anim->Select(RUN);
        Translate(-SPEED * gameTime, 0.0f);
    }

    else if (window->KeyDown(down)) {
        anim->Select(CROUCH);
    }

    if (window->KeyDown(VK_SPACE))
    {
        anim->Select(JUMP);
        Translate(0.0f, -JUMP * gameTime);
    }

    anim->NextFrame();
}

// ---------------------------------------------------------------------------------