#ifndef entity
#define entity

class	Entity	{
	public:
		Entity();
		Entity(Entity const &);
		~Entity();
		Entity	&operator=(Entity const &);
		int		collision(Entity &);

		int				x_pos;
		int				y_pos;
};

#endif
