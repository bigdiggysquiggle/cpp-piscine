#include "Enemy.h"
#include <random>

Enemy::Enemy()
{
	return ;
}

Enemy::Enemy(Enemy const &en)
{
	return ;
	(void)en;
}

Enemy::Enemy(int x, int y)
{
	this->x_pos = x;
	this->y_pos = y;
	this->movement_cooldown = 60;
}

Enemy::~Enemy()
{
	return ;
}

Enemy	&Enemy::operator=(Enemy const &copy)
{
	if (this != &copy)
	{
		this->x_pos = copy.x_pos;
		this->y_pos = copy.y_pos;
	}
	return *this;
}

void	Enemy::moveEnemy(int y_max, int x_max)
{
	if (!this->movement_cooldown)
	{
		int	up = rand() % 3 - 1;
		int	side = rand() % 3 - 1;
		this->y_pos += up;
		this->x_pos += side;
		if (!(0 <= this->y_pos && this->y_pos < y_max))
			this->y_pos += (this->y_pos > 0) ? 1 : -1;
		if (!(0 <= this->x_pos && this->x_pos < x_max))
			this->x_pos += (this->x_pos > 0) ? 1 : -1;
		this->movement_cooldown = 60 * (rand() % 5);
	}
	else
		this->movement_cooldown -= 1;
}

Bullet	Enemy::shootPlayer(Player play)
{
	int		x = 0;
	int		y = 0;

	if (play.x_pos < this->x_pos)
		x = -1;
	else if (play.x_pos > this->x_pos)
		x = 1;
	if (play.y_pos < this->y_pos)
		y = -1;
	else if (play.y_pos > this->y_pos)
		y = 1;
	this->shot_cooldown = 60 * (rand() % 5);
	Bullet shoot(x, y, *this);
	return shoot;
}


int		Enemy::checkPosition(int y_max, int x_max)
{
	if (this->x_pos < 0 || this->x_pos > x_max)
		return 1;
	if (this->y_pos < 0 || this->y_pos > y_max)
		return 1;
	return 0;
}
