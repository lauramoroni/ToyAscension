#include "Player.h"


// --------------------------------------------------------------------------------

Player::Player(char up, char down, char left, char right, char initial_side, std::string file_name)
{
	// Parametrization setup
	this->up = up;
	this->down = down;
	this->left = left;
	this->right = right;
	this->initial_side = initial_side;

    tileset = new TileSet(file_name, 24, 31, 9, 72);
    anim = new Animation(tileset, 0.120f, true);

    // sequências de animação do player
	uint idle[2] = { 0,1 };
    uint run[3] = { 2,3,4 };
    uint jump[2] = { 6,7 };
    
    anim->Add(RUN, run, 3);
    anim->Add(IDLE, idle, 2);
    anim->Add(JUMP, jump, 2);

    // cria bounding box
    BBox(new Rect(
        -1.0f * tileset->TileWidth() / 2.0f,
        -1.0f * tileset->TileHeight() / 2.0f,
        tileset->TileWidth() / 2.0f,
        tileset->TileHeight() / 2.0f));

	// posiciona o player no centro da tela
	MoveTo(window->CenterX(), window->CenterY(), Layer::FRONT);
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

}

// ---------------------------------------------------------------------------------

void Player::Update()
{
    anim->Select(IDLE);

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