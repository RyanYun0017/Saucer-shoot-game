#include "Object.h"
#include "EventCollision.h"


class Bullet : public df::Object
{
public:
	int eventHandler(const df::Event* p_e) override;
	Bullet(df::Vector hero_pos);

private:
	void out();
	void hit(const df::EventCollision* p_collision_event);

	
};
