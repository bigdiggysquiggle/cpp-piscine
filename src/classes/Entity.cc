#include "Entity.h"

Entity::Entity()
{
	this->x_pos = 0;
	this->y_pos = 0;
}

Entity::Entity(Entity const &en)
{
	operator=(en);
}

Entity::~Entity()
{
	return ;
}

Entity	&Entity::operator=(Entity const &en)
{
	if (this != &en)
	{
		this->x_pos = en.x_pos;
		this->y_pos = en.y_pos;
	}
	return (*this);
}

int		Entity::collision(Entity &en)
{
	return this->x_pos == en.x_pos && this->y_pos == en.y_pos;
}
