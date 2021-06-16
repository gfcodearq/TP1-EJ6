#include "actor.h"

actor::actor(b2Body* cuerpo, RectangleShape* figura) : body_actor(cuerpo),fig_actor(figura)
{
	posicion = body_actor->GetPosition();
	
	dimensiones->lowerBound = b2Vec2(FLT_MAX, FLT_MAX);
	dimensiones->upperBound = b2Vec2(-FLT_MIN, -FLT_MIN);
	for (b2Fixture * i = body_actor->GetFixtureList(); i; i=i->GetNext())
	{
		dimensiones = i->GetAABB(0);
	}
	fig_actor->setSize({ dimensiones->GetExtents().x * 2,dimensiones->GetExtents().y * 2 });
	fig_actor->setOrigin(fig_actor->getSize().x / 2.f, fig_actor->getSize().y / 2.f);
	fig_actor->setPosition(posicion.x, posicion.y); 
}

void actor::dibujar(RenderWindow &wnd)
{
	posicion = body_actor->GetPosition();
	fig_actor->setPosition(posicion.x, posicion.y);
	fig_actor->setRotation(radToDeg(body_actor->GetAngle()));
	wnd.draw(*fig_actor);
}

float actor::radToDeg(float radianes)
{
	return radianes * 180 / 3.14;
}