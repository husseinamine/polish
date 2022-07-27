#pragma once 

#define INIT_COMPONENTS_COUNT 3

typedef struct Vector2D
{
	int x;
	int y;
} Vector2D;

typedef struct Entity
{
	Vector2D position;
	void (**components)(void*);
	
	int _components_count; // do not modify
} Entity;

typedef struct Entities
{
	Entity** entities;
	int entities_count;
} Entities;

Entity* CreateEntity(int x, int y);
void AddComponent(Entity* entity, void (*component)(void*));
Entities GetEntities();