#include "Object.h"
#include "EventCollision.h"
 
class Saucer : public df::Object {
 public:
  Saucer();
  int eventHandler(const df::Event* p_e) override;


private:
	void hit(const df::EventCollision* p_c);
	void out();
	void moveToStart();
};



