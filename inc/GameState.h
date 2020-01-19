#ifndef STATE
#define STATE
#include "Enemy.h"
#include "Bullet.h"
#include "Player.h"

class	GameState	{
	public :
		GameState();
		GameState(GameState const &);
		~GameState();
		GameState	&operator=(GameState const &);
		void		spawn_enemies(Player);
		void		enemy_behaviour(Player);
		void		move_bullets();
		void		add_bullet(Bullet &);
		void		kill_enemy(int);
		void		remove_bullet(int);
		void		reset();

		Enemy	*enemies;
		Bullet	*bullets;
		int		enemy_count;
		int		bullet_count;

		int		status;
		int		spawn_timer;
		int		in_game_time;
		int		score;
		int		high;

		int		x_max;
		int		y_max;
};

#endif
