//
// Saucer.cpp
// Haiyang Yun

// Engine includes.
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
// Adding Event engine to the Saucer
#include "EventOut.h"

// Game includes.
#include "Saucer.h"
#include "Explosion.h"
// Additional Libs 
#include <stdlib.h> // To invode the rand() function

Saucer::Saucer() {

	// Setup "saucer" sprite.
	setSprite("saucer");

	// Set object type.
	setType("Saucer");

	// Set speed in horizontal direction.
	setVelocity(df::Vector(-1, 0)); // 1 space left every 4 frames --  I change the Speed of the Saucer to 1 space each frame. 

	// Set starting location in middle of window.                             
	/*int world_horiz = (int)WM.getBoundary().getHorizontal();
	int world_vert = (int)WM.getBoundary().getVertical();
	df::Vector p(world_horiz / 2, world_vert / 2);
	setPosition(p);*/

	// We will init the saucer by MoveToStart rather than in the middle
	moveToStart();

}

// Define the Event Handler 
int Saucer::eventHandler(const df::Event* p_e) {

	// If saucer run to the left, make it re-appear on the right bound 
	if (p_e->getType() == df::OUT_EVENT)
	{
		out();
		return 1;
	}
	// If the bullet hit the saucer, the collision will happen, call hit()method
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast <df::EventCollision const*> (p_e);
		hit(p_collision_event);
		return 1;
	}


	// If get here, ignore
	return 0;

}


// Define the 'out' method to indicating the saucer is out of the left bound
void Saucer::out() {

	// If the X position of saucer is large than 0, it means saucer is not out of the left bound
	if (getPosition().getX() >= 0) {
		return;
	}

	// Otherwise, move the saucer to the right and start again
	moveToStart();
}

// Define the method to move the saucer to right bound

void Saucer::moveToStart() {
	

	df::Vector temp_pos;

	// With many saucers spawned in the begaininer, handle the case that differnet saucer collision with each other.
	df::ObjectList collision_list = WM.getCollisions(this, temp_pos);

	while (!collision_list.isEmpty()) {
		temp_pos.setX(temp_pos.getX() + 1);
		collision_list = WM.getCollisions(this, temp_pos);
	}

	// Move the saucer to the right bound
	float world_horiz = WM.getBoundary().getHorizontal();
	float world_vert = WM.getBoundary().getVertical();

	// x is at the right edge of window, if want to make it off right, uncomment the right code of next line. 

	temp_pos.setX(world_horiz/* + rand() % (int)world_horiz + 3.0f*/);

	// y is in vertical range

	temp_pos.setY(rand() % (int)(world_vert - 1) + 1.0f);

	WM.moveObject(this, temp_pos);
}



// The saucer will respond to collision for a bullet hitting. With this hit method
void Saucer::hit(const df::EventCollision* p_collision_event) {
	// If Saucer on Saucer, ignore.
	if ((p_collision_event->getObject1()->getType() == "Saucer") &&
		(p_collision_event->getObject2()->getType() == "Saucer"))
		return;

	// If bullet
	if ((p_collision_event->getObject1()->getType() == "Bullet") || (p_collision_event->getObject2()->getType() == "Bullet"))
	{
		// Create an explosion 
		Explosion* p_explosion = new Explosion;
		p_explosion->setPosition(this->getPosition());

		// a new Saucer will be created 
		new Saucer;

	}

	// If Hero, mark both objects for destruction.
	if (((p_collision_event->getObject1()->getType()) == "Hero") ||
		((p_collision_event->getObject2()->getType()) == "Hero")) {
		WM.markForDelete(p_collision_event->getObject1());
		WM.markForDelete(p_collision_event->getObject2());
	}
}