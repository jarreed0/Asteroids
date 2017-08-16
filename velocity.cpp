#include "velocity.h"


// Put your velocity methods here

Velocity :: Velocity() {

}

Velocity :: ~Velocity() {

}

void Velocity :: calcAng() {
	dX = speed * (-cos(M_PI / 180.0 * angle));
	dY = speed * (sin(M_PI / 180.0 * angle));
}