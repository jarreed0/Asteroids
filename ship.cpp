#include "ship.h"

// Put your ship methods here

Ship :: Ship() {

	setVelSpeed(THRUST_AMOUNT);
	thrusting = 0;
	setSize(SHIP_SIZE);
	setWrapable();
	setLives(3);

}

Ship :: ~Ship() {

}

void Ship :: handleInput(const Interface & ui) {

	if(ui.isUp()) {
		move(true);
		thrusting = 1;
	} else {
		thrusting = 0;
	}

	if(ui.isRight()) {
		rotate(getRotAmount(), 0);
	}

	if(ui.isLeft()) {
		rotate(getRotAmount(), 1);
	}

	if(ui.isDown()) {
		move(false);
	}

}

void Ship :: draw() {

	drawShip(getPoint(), getVel().getAngle(), thrusting);

}

float Ship :: aimAngle() {
	float r;
	r = -getVel().getAngle()+90;
	return r;
}