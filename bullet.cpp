#include "bullet.h"


// Put your bullet methods here

Bullet :: Bullet() {
	setVelSpeed(BULLET_SPEED);
	setWrapable();
	setLives(60);
}

Bullet :: ~Bullet() {

}

void Bullet :: draw() {

	drawDot(getPoint());

}