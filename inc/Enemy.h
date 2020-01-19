#ifndef enemy
#define enemy
#include "Player.h"
#include "Bullet.h"

class	Enemy: public Player	{
	public:
		Enemy();
		Enemy(int, int);
		Enemy(Enemy const &);
		~Enemy();
		Enemy	&operator=(Enemy const &);

		void	moveEnemy(int, int);
		Bullet	shootPlayer(Player);
		int		checkPosition(int, int);
};

#endif
