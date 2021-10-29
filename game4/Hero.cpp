// Add dependency for multiple libs
#include "Hero.h"
#include "Bullet.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "EventStep.h" // to register for "Step" events
#include "EventMouse.h"
//#include "Reticle.h"

// Define the constructor
Hero::Hero() {
	// Link to "ship" sprit
	setSprite("ship");

	// Register for the event "keyboard" by registerInterest()
	registerInterest(df::KEYBOARD_EVENT);

	// Register for the event "step"
	registerInterest(df::STEP_EVENT);

	// Register for the mouse event
	registerInterest(df::MSE_EVENT);

	// Create a new Reticle for firing bullets

	p_reticle = new Reticle();
	p_reticle->draw();

	// Set the Object Type and Hero location
	setType("Hero");
	df::Vector p(7, WM.getBoundary().getVertical() / 2);
	setPosition(p);
}

// Define the Destructor

Hero::~Hero() {
	GM.setGameOver();
}
// Setup the eventhandler method for Hero
int Hero::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == df::KEYBOARD_EVENT)
	{
		const df::EventKeyboard *p_keyboard_event = dynamic_cast <const df::EventKeyboard *> (p_e);
		kbd(p_keyboard_event);
		return 1;
	}
	if (p_e -> getType() == df::STEP_EVENT)
	{
		step();
		return 1;
	}
	// Handle the mouse event for firing bullets 
	if (p_e->getType() == df::MSE_EVENT) {
		const df::EventMouse* p_mouse_event =
			dynamic_cast <const df::EventMouse*> (p_e);
		mouse(p_mouse_event);
		return 1;
	}

	return 0;
}

// Take appropriate action according to key pressed.
// Setup the kbd() method.
void Hero::kbd(const df::EventKeyboard *p_keyboard_event) {

	switch (p_keyboard_event->getKey())
	{
		//By pressing different key, we want the hero can move accordingly, or quit the game directly
	case df::Keyboard::Q:   // Quit
			if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
				GM.setGameOver();
			break;
	case df::Keyboard::W:   // Move up
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			move(-1);
		break;
	case df::Keyboard::S:   // Move down
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			move(1);
		break;
	}
}

// Setup the move() method. It creates a new Vector object, setting the location either 1 up or down from the hero's position.
// Move up or down
void Hero::move(int dy) {

	// See if time to move
	if (move_countdown > 0 )
	{
		return;
	}
	move_countdown = move_slowdown;
	// if stays on the current window, allow move
	df::Vector new_pos(getPosition().getX(), getPosition().getY() + dy);
	if ((new_pos.getY() > 3) && (new_pos.getY() < WM.getBoundary().getVertical() - 1))
	{
		WM.moveObject(this,new_pos);
	}
}

// Decrease rate restriction counters
void Hero::step() {
	// Move countdown
	move_countdown--;
	// NOTE - in step()
	// Fire countdown.
	fire_countdown--;
	if (move_countdown < 0)
	{
		move_countdown = 0;
	}
	if (fire_countdown < 0)
		fire_countdown = 0;
}

//Define the method fire() to fire the bullet
void Hero::fire(df::Vector target) {
	if (fire_countdown > 0)
		return;
	fire_countdown = fire_slowdown;

	// Fire Bullet towards target.
	// Compute normalized vector to position, then scale by speed (1).
	df::Vector v = target - getPosition();
	v.normalize();
	v.scale(1);
	Bullet *p = new Bullet(getPosition());
	p->setVelocity(v);

	// Note: in Bullet constructor
	// Make the Bullets soft so can pass through Hero.
	setSolidness(df::SOFT);
}

// Take appropriate action according to mouse action.
void Hero::mouse(const df::EventMouse* p_mouse_event) {
	// Pressed button?
	if ((p_mouse_event->getMouseAction() == df::CLICKED) &&
		(p_mouse_event->getMouseButton() == df::Mouse::LEFT))
		fire(p_mouse_event->getMousePosition());
}

