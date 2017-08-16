#ifndef ship_h
#define ship_h

#define SHIP_SIZE 10

#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 3

#include "flyingObject.h"
#include "uiDraw.h"
#include "uiInteract.h"

// Put your Ship class here

class Ship : public FlyingObject {

private:

	bool thrusting;

public:

	Ship();
	~Ship();

	void handleInput(const Interface & ui);
	void draw();

	float getRotAmount() const {return ROTATE_AMOUNT;}

	float aimAngle();

};


#endif /* ship_h */
