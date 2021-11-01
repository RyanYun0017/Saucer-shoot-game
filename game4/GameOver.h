#include "ViewObject.h"
class GameOver: public df::ViewObject{
public: 
	GameOver();
	int eventHandler(const df::Event* p_e) override;
	~GameOver();
	int draw() override;
private:
	int time_to_live;
	void step();
};
