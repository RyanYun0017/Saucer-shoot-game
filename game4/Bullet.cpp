// Add dependancy for Bullet.cpp
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "Bullet.h"
// Adding Event engine to the bullet (OUT_EVENT)
#include "EventOut.h"

Bullet::Bullet(df::Vector hero_pos) {
	// Link to "bullet" sprit
	setSprite("bullet");

	// Set object type.
	setType("Bullet");

	// Set starting location, based on hero's position passed in.
	df::Vector p(hero_pos.getX() + 3, hero_pos.getY());
	setPosition(p);

	// Bullets move 1 space each game loop.
	// The direction is set when the Hero fires.
	setSpeed(1);

}

int Bullet::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::OUT_EVENT)
	{
		out();
		return 1;
	}

	
	// Handle the event when the bullet hit saucer and the 'collision' event happens 
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event =
			dynamic_cast <const df::EventCollision*> (p_e);
		hit(p_collision_event);
		return 1;
	}
	return 0;
}

void Bullet::out() {
	// If the bullet move outside world, mark self for deletion
	WM.markForDelete(this);
}

// If bullet hit the saucer, mark saucer and bullet for deletion 
void Bullet::hit(const df::EventCollision* p_collision_event) {
	if ((p_collision_event->getObject1()->getType() == "Saucer") ||
		(p_collision_event->getObject2()->getType() == "Saucer")) {
		WM.markForDelete(p_collision_event->getObject1());
		WM.markForDelete(p_collision_event->getObject2());
	}
}