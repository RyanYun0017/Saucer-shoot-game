///
/// Text for splash screen
/// 

#ifndef __SPLASH_H__
#define __SPLASH_H__

#include "EventStep.h"
#include "Object.h"	
#include "Sprite.h"	

namespace df {

class Splash : public Object {

 private:
  int m_countdown;          /// Countdown to event actions.
  Sprite *m_p_local_sprite; /// Temporary Sprite for Object.
  
 public:
  Splash();
  ~Splash();
  int eventHandler(const Event *p_e);
};
 
} // end of namespace df
#endif // __SPLASH_H__
