#include <ctime>
#include <random>
#include <iostream>
#include <ncurses.h>
#include "GameState.h"

//CLOCKS_PER_SEC is 1000000
//
//about 16667 clocks per frame
//
//might consider switching to a float so we don't run too slow
//--negligible but still
//----also might switch timing methods to avoid int overflow
//
//currently checking to see if it's been between 1/61 and 1/59 of a second
//to account for timing inconsistencies in displays
//
//don't spawn enemies within 5 tiles of player

void	draw(GameState game, Player play)
{
	clear();
	for (int i = 0; i < game.bullet_count; i++)
	{
		char c;
		if ((game.bullets[i].y_velocity == -1 && game.bullets[i].x_velocity == -1) || (game.bullets[i].y_velocity == 1 && game.bullets[i].x_velocity == 1))
			c = '/';
		else if ((game.bullets[i].y_velocity == 1 && game.bullets[i].x_velocity == -1) || (game.bullets[i].y_velocity == -1 && game.bullets[i].x_velocity == 1))
			c = '\\';
		else if (game.bullets[i].y_velocity)
			c = '|';
		else
			c = '-';
		mvprintw(game.bullets[i].y_pos, game.bullets[i].x_pos, "%c", c);
	}
	for (int i = 0; i < game.enemy_count; i++)
		mvprintw(game.enemies[i].y_pos, game.enemies[i].x_pos, "x");
	mvprintw(play.y_pos, play.x_pos, "o");
	mvprintw(0, 0, "time: %d\tscore: %d\thighscore: %d", game.in_game_time, game.score, game.high);
	wrefresh(stdscr);
}

void	collision_detection(GameState *game, Player *play)
{
	for (int i = 0; i < game->enemy_count; i++)
	{
		if (game->enemies[i].collision(*play))
		{
			game->status = 2;
			return ;
		}
	}
	for (int i = 0; i < game->bullet_count; i++)
	{
		if (game->bullets[i].collision(*play))
		{
			game->status = 2;
			return ;
		}
	}
	for (int i = 0; i < game->bullet_count; i++)
		for (int j = 0; j < game->enemy_count; j++)
		{
			if (game->bullets[i].collision(game->enemies[j]))
			{
				game->kill_enemy(j);
				game->remove_bullet(i);
			}
		}
}

void	move_player(GameState *game, Player *play)
{
	int	ch = getch();

	if (ch == 27)
	{
		ch = getch();
		if (ch == -1)
			game->status = 0;
	}
	else if (ch == ' ')
	{
		if (!play->shot_cooldown)
		{
			play->shot_cooldown = 11;
			Bullet bill = fireBullet(*play);
			game->add_bullet(bill);
		}
	}
	else
		play->movePlayer(ch, game->y_max, game->x_max);
	if (play->shot_cooldown)
		play->shot_cooldown--;
}

//find a way to make the game clock start time agnostic so we don't need to worry
//about int overflow

void	game_loop()
{
	int		last_frame;
	int		clock_accumulator;
	int		delta;
	int		seconds;
	GameState	game;
	Player	play;

	last_frame = 0;
	clock_accumulator = 0;
	seconds = 0;
	while (game.status)
	{
		delta = clock_accumulator - last_frame;
		if (16393 <= delta && delta >= 16949) //somewhere between 1/61 and 1/59 of a sec
		{
			getmaxyx(stdscr, game.y_max, game.x_max);
			collision_detection(&game, &play);
			if (game.status == 2)
				game.reset();
			else
			{
				game.enemy_behaviour(play);
				game.spawn_enemies(play);
				game.move_bullets();
				move_player(&game, &play);
				draw(game, play);
			}
			last_frame += clock_accumulator;//might just force this to think 16667
			clock_accumulator = 0;
		}
		if (last_frame - (seconds * 1000000) > 0)
		{
			seconds++;
			game.in_game_time++;
		}
		clock_accumulator = clock() - last_frame;
	}
}

int		main()
{
	initscr();
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	srand(time(0));
	game_loop();
	return (0);
}
