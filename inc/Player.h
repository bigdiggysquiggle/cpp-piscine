#ifndef player
#define player
#include "Entity.h"

class Player: public Entity	{
	public:
		Player();
		Player(Player const &);
		~Player();
		Player	&operator=(Player const &);

		void	movePlayer(int, int, int);
		int		shot_cooldown;
		int		movement_cooldown;
		unsigned char	direction;
};

#endif
