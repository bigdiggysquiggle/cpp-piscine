#include <random>
#include <ncurses.h>
#include "GameState.h"

GameState::GameState()
{
	this->status = 1;
	this->spawn_timer = 0;
	this->in_game_time = 0;
	this->score = 0;
	this->high = 0;
	this->enemies = NULL;
	this->bullets = NULL;
	this->enemy_count = 0;
	this->bullet_count = 0;
	getmaxyx(stdscr, this->y_max, this->x_max);
}

GameState::GameState(GameState const &copy)
{
	operator=(copy);
}

GameState::~GameState()
{
	return ;
}

GameState	&GameState::operator=(GameState const &copy)
{
	if (&copy != this)
	{
		this->status = copy.status;
		this->spawn_timer = copy.spawn_timer;
		this->in_game_time = copy.in_game_time;
		this->score = copy.score;
		this->high = copy.high;
		this->enemy_count = copy.enemy_count;
		this->bullet_count = copy.bullet_count;
	}
	return (*this);
}

void	GameState::kill_enemy(int i)
{
	Enemy	*arr;
	int		offset = 0;

	arr = new Enemy[this->enemy_count - 1];
	for (int j = 0; j + offset < this->enemy_count; j++)
	{
		if (j == i)
			offset = 1;
		if (j + offset < this->enemy_count)
			arr[j] = this->enemies[j + offset];
	}
//	delete this->enemies;
	this->enemies = arr;
	this->enemy_count--;
}

void	GameState::remove_bullet(int i)
{
	Bullet	*arr;
	int		offset = 0;

	arr = new Bullet[this->bullet_count - 1];
	for (int j = 0; j + offset < this->bullet_count; j++)
	{
		if (j == i)
			offset = 1;
		if (j + offset < this->bullet_count)
			arr[j] = this->bullets[j + offset];
	}
//	delete this->bullets;
	this->bullets = arr;
	this->bullet_count--;
}

void	GameState::spawn_enemies(Player play)
{
	if (this->enemy_count < 7 && !spawn_timer)
	{
		int x = rand() % this->x_max;
		int y = rand() % this->y_max;
		if ((((y - play.y_pos) < 5) || ((play.y_pos - y) < 5)))
		{
			if (x >= play.x_pos)
				while (x - play.x_pos < 5)
					x++;
			else
				while (play.x_pos - x < 5)
					x--;
		}
		if ((((x - play.x_pos) < 5) || ((play.x_pos - x) < 5)))
		{
			if (y >= play.y_pos)
				while (y - play.y_pos < 5)
					y++;
			else
				while (play.y_pos - y < 5)
					y--;
		}
		Enemy fren(x, y);
		Enemy *arr = new Enemy[this->enemy_count + 1];
		for (int i = 0; i < this->enemy_count; i++)
			arr[i] = this->enemies[i];
		arr[this->enemy_count++] = fren;
//		delete this->enemies;
		this->enemies = arr;
		this->spawn_timer = 60 * (rand() % 7);
	}
	else
		this->spawn_timer -= 1;
}

void	GameState::enemy_behaviour(Player play)
{
	for (int i = 0; i < this->enemy_count; i++)
	{
		this->enemies[i].moveEnemy(this->y_max, this->x_max);
		if (this->enemies[i].checkPosition(this->y_max, this->x_max))
			this->kill_enemy(i);
		else if (!enemies[i].shot_cooldown)
		{
			Bullet fren = this->enemies[i].shootPlayer(play);
			this->add_bullet(fren);
		}
		else
			enemies[i].shot_cooldown -= 1;
	}
}

void	GameState::add_bullet(Bullet &shot)
{
	Bullet *arr = new Bullet[this->bullet_count + 1];

	for (int i = 0; i < this->bullet_count; i++)
		arr[i] = this->bullets[i];
	arr[bullet_count++] = shot;
//	delete this->bullets;
	this->bullets = arr;
}

void	GameState::move_bullets()
{
	for (int i = 0; i < bullet_count; i++)
	{
		this->bullets[i].move();
		if (this->bullets[i].checkPosition(this->y_max, this->x_max))
			this->remove_bullet(i);
	}
}

void	GameState::reset()
{
	this->status = 1;
	this->spawn_timer = 0;
	this->in_game_time = 0;
	if (this->score > this->high)
		this->high = this->score;
	this->score = 0;
	this->enemy_count = 0;
	this->bullet_count = 0;
//	delete this->enemies;
//	delete this->bullets;
}
