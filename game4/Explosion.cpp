#include "Explosion.h"
#include "EventStep.h"
#include "WorldManager.h"


Explosion::Explosion() {

	// Register the explosion for the step event
	registerInterest(df::STEP_EVENT);

	//Link to "explosion" sprite
	if (setSprite("explosion") == 0)

		// Set live time as long as sprite length.
		time_to_live = getAnimation().getSprite()->getFrameCount();
	else
		time_to_live = 0;

	setType("Explosion");

	// The Explosion should not cause a collision and impede movement
	setSolidness(df::SPECTRAL);


}

// The eventHandler will make the explosion decrease in the time_to_live. When it reaches to 0, delete it from the WorldManager.
int Explosion::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::STEP_EVENT)
	{
		step();
		return 1;
	}

	// If the event hit here, ignore it
	return 0;
}



// The step() method
void Explosion::step() {
	time_to_live--;
	if (time_to_live <= 0)
		WM.markForDelete(this);
}

