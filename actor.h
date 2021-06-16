#pragma once
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

using namespace sf;

class actor {
public:
	actor(b2Body* cuerpo, RectangleShape* figura);
	void dibujar(RenderWindow& wnd);
	float radToDeg(float radianes); 
private:
	b2Body* body_actor;
	RectangleShape* fig_actor;
	b2AABB* dimensiones;
	b2Vec2 posicion;
};
