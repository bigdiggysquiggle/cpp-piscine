#ifndef bullet
#define bullet
#include "Entity.h"
#include "Player.h"
// consider drawing them directionally using one of '-' '\' '/' '|' 

class Bullet : public Entity	{
	public:
		Bullet();
		Bullet(int, int, Player &);
		Bullet(Bullet const &);
		~Bullet();
		Bullet	&operator=(Bullet const &);
		void	move();
		int		checkPosition(int, int);

		int		x_velocity;
		int		y_velocity;
		int		movement_cooldown;
};

Bullet	fireBullet(Player &);

#endif
