#include "Object.h"

#define STAR_CHAR '.'

class Star : public df::Object {

private:
    void out(); // To handle the out of bound event

public:
    Star();
    int draw(void) override;
    int eventHandler(const df::Event* p_e) override;
};