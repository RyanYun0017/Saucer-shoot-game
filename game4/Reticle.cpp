#include "Reticle.h"
#include "EventMouse.h"
#include "WorldManager.h"
#include "DisplayManager.h"


// Create the constructor for Reticle

Reticle::Reticle() {
	// Set the Object type to "Reticle"
	setType("Reticle");

	// The Reticle should not cause a collision and impede movement
	setSolidness(df::SPECTRAL);

	//The reticle should always be in foregroun, we can assign it by using different layers for display.
	setAltitude(df::MAX_ALTITUDE);

	// The Reticle should be init to the middle of the window
	MoveToStart();

	// Register for Mouse event
	registerInterest(df::MSE_EVENT);

}

// Initialization the reticle to the middle of the window, by using the method.
void Reticle::MoveToStart() {
	df::Vector temp_pos;
	float world_horiz = WM.getBoundary().getHorizontal();
	float world_vert = WM.getBoundary().getVertical();

// Intialize the Reticle in the middle of the window. 

	temp_pos.setX(world_horiz/2);
	temp_pos.setY(world_vert/2);

	WM.moveObject(this, temp_pos);
}

// Set up for eventHandler, responding to mouse event. The reticle position is changed to the mouse's new location
int Reticle::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::MSE_EVENT)
	{
		const df::EventMouse* p_mouse_movement = dynamic_cast<const df::EventMouse*> (p_e);
		if (p_mouse_movement->getMouseAction() == df::MOVED)
		{
			// Change location to new mouse position
			setPosition(p_mouse_movement->getMousePosition());
			return 1;
		}
	}
	// If get here, ignore the event
	return 0;

}

// Unlike Saucer and Hero, the Reticle use draw()
int Reticle::draw() {
	return DM.drawCh(getPosition(), RETICLE_CHAR, df::RED);

}