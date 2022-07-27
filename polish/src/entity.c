#include <stdlib.h>
#include <stdio.h>
#include "entity.h"

static Entity* entities;
static int entities_count = 0;
static int allocated_entities = 0;


Entity* CreateEntity(int x, int y)
{
	Entity entity = {0,0,0};
	entity.position.x = x;
	entity.position.y = y;
	entity.components = malloc(sizeof(void (*)(void*)) * entity._components_count);
	entities_count++;

	if (!allocated_entities)
	{
		entities = malloc(sizeof(Entity*) * entities_count);
		allocated_entities = 1;
	}
	else
	{
		entities = realloc(entities, sizeof(Entity*) * entities_count);
	}

	entities[entities_count - 1] = entity;

	return &entities[entities_count - 1];
}

void AddComponent(Entity* entity, void (*component)(void*))
{
	entity->_components_count++;

	entity->components = realloc(entity->components, sizeof(void (*)(void*)) * entity->_components_count);
	entity->components[entity->_components_count - 1] = component;
}

Entities GetEntities()
{
	Entities _entities = { 0,0 };
	_entities.entities = &entities;
	_entities.entities_count = entities_count;

	return _entities;
}