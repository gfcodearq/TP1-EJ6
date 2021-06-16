#include "juego.h"

juego::juego(Vector2i resolution, std::string title)
{
	fps = 60;
	frameTime = 1 / 60.f;
	reloj = new Clock;
	tiempo1 = new Time;
	time2 = 0;
	wnd = new RenderWindow(VideoMode(resolution.x, resolution.y), title); 
	wnd->setFramerateLimit(fps);  
	setCamara();
	iniciar_fisica();
	iniciar_img();
	
	event1 = new Event;
	for (int i = 0; i < 6; i++)
	{
		act_rag[i] = new actor(body_rag[i], fig_rag[i]);
	}
	act_suelo = new actor(body_floor, fig_suelo);

	gameLoop();
}

void juego::setCamara()
{
	camara1 = new View({ 12.5f,12.5f }, { 25.f,25.f });
	camara1->move(47.f, 75.f);
	wnd->setView(*camara1);
}

void juego::iniciar_fisica()
{
	//World
	world_1 = new b2World(b2Vec2(0.f, 9.81f)); //Creo el mundo y le asigno la gravedad de la tierra 9.81
	
	//Suelo
	bodyDef_floor.type = b2_staticBody;
	bodyDef_floor.position = b2Vec2(50.f, 100.f);
	body_floor = world_1->CreateBody(&bodyDef_floor);
	b2PolygonShape shp_floor;
	shp_floor.SetAsBox(50.f, 2.5f);
	fixDef_floor->shape = &shp_floor;
	fixDef_floor->restitution = 0.f;
	fixDef_floor->friction = 0.3f;
	fixDef_floor->density = 1.f;

	fix_floor = body_floor->CreateFixture(&fixDef_floor);
	//Ragdooll
	
	//Posicion de las partes del ragdoll
	bodyDef_rag[0].position = b2Vec2(50.f, 95.1f); //Cabeza
	bodyDef_rag[1].position = b2Vec2(50.f, 95.65f); //Torso
	bodyDef_rag[2].position = b2Vec2(50.32f, 95.5f); //Brazo derecho
	bodyDef_rag[3].position = b2Vec2(49.68f, 95.5f); //Brazo izquierdo
	bodyDef_rag[4].position = b2Vec2(50.09f, 96.5f); //Pierna derecha
	bodyDef_rag[5].position = b2Vec2(49.91f, 96.5f); //Pierna izquierda
	for (int i = 0; i < 6; i++)
	{
		bodyDef_rag[i].type = b2_dynamicBody;
		body_rag[i] = world_1->CreateBody(&bodyDef_rag[i]);
	}
	b2PolygonShape shp_rage[6];	
	//Dimensiones del ragdoll
	shp_rage[0].SetAsBox(0.1, 0.1);
	shp_rage[1].SetAsBox(0.4,0.2);
	shp_rage[2].SetAsBox(0.07, 0.3);
	shp_rage[3].SetAsBox(0.07, 0.3);
	shp_rage[4].SetAsBox(0.07, 0.4);
	shp_rage[5].SetAsBox(0.07, 0.4);

	for (int i = 0; i < 6; i++)
	{
		fixDef_rag[i]->shape = &shp_rage[i];
		fixDef_rag[i]->density = 1.f;
		fixDef_rag[i]->friction = 0.3f;
		fixDef_rag[i]->restitution = 0.3f;
		fix_rag[i] = body_rag[i]->CreateFixture(&fixDef_rag[i]);
	}
	//Resortica
	jointDef_rag[0].Initialize(body_rag[0], body_rag[1], b2Vec2(body_rag[0]->GetPosition().x,body_rag[0]->GetPosition().y+0.08),b2Vec2(body_rag[1]->GetPosition().x,body_rag[1]->GetPosition().y+-0.38));
	jointDef_rag[1].Initialize(body_rag[1], body_rag[2], b2Vec2(body_rag[1]->GetPosition().x + 0.18, body_rag[1]->GetPosition().y - 0.38), b2Vec2(body_rag[2]->GetPosition().x - 0.05, body_rag[2]->GetPosition().y - 0.28));
	jointDef_rag[2].Initialize(body_rag[1], body_rag[3], b2Vec2(body_rag[1]->GetPosition().x - 0.18, body_rag[3]->GetPosition().y - 0.38), b2Vec2(body_rag[3]->GetPosition().x + 0.05, body_rag[2]->GetPosition().y - 0.28));
	jointDef_rag[3].Initialize(body_rag[1], body_rag[4], b2Vec2(body_rag[1]->GetPosition().x + 0.09, body_rag[1]->GetPosition().y + 0.38), b2Vec2(body_rag[4]->GetPosition().x, body_rag[4]->GetPosition().y - 0.38));
	jointDef_rag[4].Initialize(body_rag[1], body_rag[5], b2Vec2(body_rag[1]->GetPosition().x + 0.09, body_rag[1]->GetPosition().y + 0.38), b2Vec2(body_rag[5]->GetPosition().x, body_rag[5]->GetPosition().y - 0.38));

	for (int i = 0; i < 5; i++)
	{
		jointDef_rag[i].damping = 0.3f;
		jointDef_rag[i].length = 0.025f;
		jointDef_rag[i].collideConnected = true;
		joint_rag[i] = (b2DistanceJoint*)world_1->CreateJoint(&jointDef_rag[i]);

	}
}


void juego::iniciar_img()
{
	for (int i = 0; i < 6; i++)
	{
		fig_rag[i] = new RectangleShape;
		fig_rag[i]->setFillColor(Color::Red);
	}
	fig_suelo = new RectangleShape;
	fig_suelo->setFillColor(Color::Green);
}

void juego::actualizar_fisica()
{
	world_1->Step(frameTime, 8, 8);
	world_1->ClearForces();
}

void juego::procesar_eventos()
{
	while (wnd->pollEvent(*event1))
	{
		switch (event1->type)
		{
		case Event::Closed:
			exit(1);
			break;
		}
	}
}

void juego::gameLoop()
{
	while (wnd->isOpen())
	{
		*tiempo1 = reloj->getElapsedTime();
		if (time2 + frameTime < tiempo1->asSeconds())
		{
			time2 = tiempo1->asSeconds();
			wnd->clear();
			procesar_eventos();
			actualizar_fisica();
			dibujar();
			wnd->display();
			procesar_eventos();
		}
	}
}

void juego::dibujar()
{
	act_suelo->dibujar(*wnd);

	for (int i = 0; i < 6; i++)
	{
		act_rag[i]->dibujar(*wnd);
	}
}