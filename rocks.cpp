#include "rocks.h"

// Put your Rock methods here

Rock :: Rock() {

	setVelSpeed(ROCK_SPEED);

}

Rock :: ~Rock() {

}

BigRock :: BigRock() {

	setSize(BIG_ROCK_SIZE);
	setSpin(BIG_ROCK_SPIN);
	setVelSpeed(ROCK_SPEED);
	setType(1);
	setWrapable();

}

BigRock :: ~BigRock() {

}

void BigRock :: draw() {

	drawLargeAsteroid(getPoint(), getSpin());

}

MediumRock :: MediumRock() {

	setSize(MEDIUM_ROCK_SIZE);
	setSpin(MEDIUM_ROCK_SPIN);
	setVelSpeed(ROCK_SPEED);
	setType(2);
	setWrapable();

}

MediumRock :: ~MediumRock() {

}

void MediumRock :: draw() {

	drawMediumAsteroid(getPoint(), getSpin());

}

SmallRock :: SmallRock() {

	setSize(SMALL_ROCK_SIZE);
	setSpin(SMALL_ROCK_SPIN);
	setVelSpeed(ROCK_SPEED);
	setType(3);
	setWrapable();
}

SmallRock :: ~SmallRock() {

}

void SmallRock :: draw() {

	drawSmallAsteroid(getPoint(), getSpin());
}

