
#pragma once
#include "actor.h"


class juego
{
public:
	juego(Vector2i resolution, std::string title);
	void setCamara();
	void iniciar_fisica();
	void iniciar_img();
	void actualizar_fisica();
	void procesar_eventos();
	void gameLoop();
	void dibujar();

private:
	RenderWindow* wnd;
	View *camara1;
	//Events
	Event *event1;
	//Clock
	Time* tiempo1;
	Clock* reloj;
	//FPS
	float fps, frameTime, time2;
	//Ragdoll
	b2Body* body_rag[6];
	b2BodyDef bodyDef_rag[6];
	b2Fixture* fix_rag[6];
	b2FixtureDef* fixDef_rag[6];
	//Floor
	b2Body* body_floor;
	b2BodyDef bodyDef_floor;
	b2Fixture* fix_floor;
	b2FixtureDef* fixDef_floor;

	RectangleShape* fig_rag[6]; //figura reagdoll
	RectangleShape* fig_suelo; 

	//Resortes
	b2DistanceJoint* joint_rag[5];
	b2DistanceJointDef jointDef_rag[5];

	//World
	b2World* world_1;

	actor* act_rag[6];
	actor* act_suelo;

};