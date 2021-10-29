#include "Object.h"

#define RETICLE_CHAR '+'

class Reticle : public df::Object {
public:

	Reticle();
	int draw(void) override;
	int eventHandler(const df::Event* p_e) override;

private:
	void MoveToStart();

};