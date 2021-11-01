#include "Star.h"
#include "WorldManager.h"
#include "EventOut.h"
#include "DisplayManager.h"

#include <stdlib.h> // Standard lib, for rand()


// Construct of Star()
Star::Star() {
	setType("Star");

	setSolidness(df::SPECTRAL); // Will not cause the collision

	setVelocity(df::Vector((float)-1.0 / (rand() % 9 + 2), 0)); // (float) of Vector will cause a bug

	setAltitude(0); // Make star in the background

	// Put Star randomly choosen over the whole window
	df::Vector p((float)(rand() % (int)WM.getBoundary().getHorizontal()),
		(float)(rand() % (int)WM.getBoundary().getVertical()));
	setPosition(p);

}

// Define the Event Handler 
int Star::eventHandler(const df::Event* p_e) {

	// Only handle the event that when star is out 
	if (p_e->getType() == df::OUT_EVENT)
	{
		out();
		return 1;
	}

	// If get here, ignore
	return 0;

}

// If Star moved off window, move back to far right.
void Star::out() {
	df::Vector p((float)(WM.getBoundary().getHorizontal() + rand() % 20),
		(float)(rand() % (int)WM.getBoundary().getVertical()));
	setPosition(p);
	setVelocity(df::Vector(-1.0 / (rand() % 9 + 2), 0));
}

int Star::draw() {
	return DM.drawCh(getPosition(), STAR_CHAR, df::WHITE);
}
