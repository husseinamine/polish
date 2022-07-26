#include <stdlib.h>
#include <stdio.h>
#include "entity.h"

static Entity* entities;

Entity CreateEntity(int x, int y)
{
	Entity entity = {{0,0},0,0};
	entity.components = malloc(sizeof(void (*)(void*)) * entity._components_count);

	return entity;
}

void AddComponent(Entity* entity, void (*component)())
{
	entity->_components_count++;

	entity->components = realloc(entity->components, sizeof(void (*)(void*)) * entity->_components_count);
	entity->components[entity->_components_count - 1] = component;
}