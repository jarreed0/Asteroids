#ifndef bullet_h
#define bullet_h

#define BULLET_SPEED 5
#define BULLET_LIFE 40

#include "flyingObject.h"
#include "uiDraw.h"

// Put your Bullet class here

class Bullet : public FlyingObject {

private:

public:

	Bullet();
	~Bullet();

	void draw();

};



#endif /* bullet_h */
