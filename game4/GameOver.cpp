#include "GameOver.h"
#include "EventStep.h"
#include "WorldManager.h"
#include "GameManager.h"


GameOver::GameOver() {
	// Link it to "gameover" sprite and set it type to GameOver.
	setType("GameOver");

	// Link to "message" sprite.
	if (setSprite("gameover") == 0)
		time_to_live = getAnimation().getSprite()->getFrameCount() * getAnimation().getSprite()->getSlowdown();
	else
		time_to_live = 0;

	// Put in center of window.
	setLocation(df::CENTER_CENTER);

	// Register for step event.
	registerInterest(df::STEP_EVENT);

}

// eventHandler
int GameOver::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::STEP_EVENT)
	{
		step();
		return 1;
	}

	// If the event hit here, ignore it
	return 0;
}

// Count down to end of message.
void GameOver::step() {
	time_to_live--;
	if (time_to_live <= 0)
		WM.markForDelete(this);
}

// In the destructor, indicate the game manager that the game is over.
GameOver:: ~GameOver() {
	GM.setGameOver();
}

// Override default draw so as not to display "value".
int GameOver::draw() {
	return df::Object::draw();
}