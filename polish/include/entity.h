#pragma once 

typedef struct Vector2D
{
	int x;
	int y;
} Vector2D;

typedef struct Entity
{
	Vector2D position;
	void (**components)(void * args);
	
	int _components_count; // do not modify
} Entity;

Entity CreateEntity(int x, int y);
void AddComponent(Entity* entity, void (*component)());