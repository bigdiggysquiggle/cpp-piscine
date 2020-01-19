#include "Player.h"
#include "ncurses.h"

Player::Player()
{
	this->x_pos = 0;
	this->y_pos = 0;
	this->shot_cooldown = 0;
	this->movement_cooldown = 0;
	this->direction = 0;
}

Player::Player(int x, int y)
{
	this->x_pos = x / 2;
	this->y_pos = y / 2;
	this->shot_cooldown = 0;
	this->movement_cooldown = 0;
	this->direction = 0;
}

Player::Player(Player const &copy)
{
	operator=(copy);
}

Player::~Player()
{
	this->x_pos = 0;
	this->y_pos = 0;
	this->shot_cooldown = 0;
	this->movement_cooldown = 0;
	this->direction = 0;
}

Player	&Player::operator=(Player const &copy)
{
	if (this != &copy)
	{
		this->x_pos = copy.x_pos;
		this->y_pos = copy.y_pos;
		this->shot_cooldown = copy.shot_cooldown;
		this->movement_cooldown = copy.movement_cooldown;
		this->direction = copy.direction;
	}
	return (*this);
}

void	Player::movePlayer(int ch, int maxy, int maxx)
{
	if (!this->movement_cooldown)
	{
		if (ch == KEY_LEFT)
		{
			this->direction = 0;
			this->x_pos -= 1;
		}
		if (ch == KEY_RIGHT)
		{
			this->direction = 1;
			this->x_pos += 1;
		}
		if (ch == KEY_UP)
		{
			this->direction = 2;
			this->y_pos -= 1;
		}
		if (ch == KEY_DOWN)
		{
			this->direction = 3;
			this->y_pos += 1;
		}
		this->movement_cooldown = 10;
	}
	else
		this->movement_cooldown -= 1;
	if (this->x_pos > maxx)
		this->x_pos = maxx - 1;
	if (this->y_pos > maxy)
		this->y_pos = maxy - 1;
}
