#include "Bullet.h"
#include "Player.h"

Bullet::Bullet()
{
	this->x_velocity = 0;
	this->y_velocity = 0;
	this->movement_cooldown = 10;
}

Bullet::Bullet(int x, int y, Player &play)
{
	this->x_pos = play.x_pos + x;
	this->y_pos = play.y_pos + y;
	this->x_velocity = x;
	this->y_velocity = y;
}

Bullet::Bullet(Bullet const &bull)
{
	operator=(bull);
}

Bullet::~Bullet()
{
	return ;
}

Bullet	&Bullet::operator=(Bullet const &bull)
{
	if (this != &bull)
	{
		this->x_velocity = bull.x_velocity;
		this->y_velocity = bull.y_velocity;
		this->movement_cooldown = bull.movement_cooldown;
	}
	return (*this);
}

void	Bullet::move()
{
	this->x_pos += this->x_velocity;
	this->y_pos += this->y_velocity;
}

int		Bullet::checkPosition(int max_y, int max_x)
{
	if (this->x_pos < 0 || this->x_pos > max_x)
		return 1;
	if (this->y_pos < 0 || this->y_pos > max_y)
		return 1;
	return 0;
}

Bullet	fireBullet(Player &play)
{
	int x = 0;
	int y = 0;

	if (play.direction == 0)
		x = -1;
	else if (play.direction == 1)
		x = 1;
	else if (play.direction == 2)
		y = -1;
	else
		y = 1;
	return Bullet bullet(x, y, play);
}
