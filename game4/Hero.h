
// The Hero Class need to inherit from Object.h and EventKeyboard.h
#include "Object.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "Reticle.h"

class Hero : public df::Object
{
public:
	Hero();
	int eventHandler(const df::Event* p_e) override;
	~Hero();

private:
	void kbd(const df::EventKeyboard* p_keyboard_event);
	void move(int dy);
	int move_slowdown = 2;
	int move_countdown = move_slowdown;
	void step();
	void fire(df::Vector target);
	// Deifne methods for fire the bullet 
	int fire_slowdown = 15;
	int fire_countdown = fire_slowdown;

	// Take appropriate action according to mouse action.
	void mouse(const df::EventMouse* p_mouse_event);
	
	// to make the hero holding the Reticle
	Reticle* p_reticle;
};

