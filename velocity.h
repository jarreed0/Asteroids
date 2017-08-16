#ifndef VELOCITY_H
#define VELOCITY_H

using namespace std;
#include <iostream>
#include <math.h>


// Put your velocity class here, or overwrite this file with your own
// velocity class from the previous project

class Velocity {


private:

	float dX;
	float dY;
	float angle;
	float speed;

public:

	Velocity();
	Velocity(float x, float y);
	Velocity(float x, float y, float ang, float spd) {this->dX = x; this->dY = y; this->angle = ang, this->speed = spd;}
	~Velocity();

	float getDx() const {return dX;}
	float getDy() const {return dY;}
	void setDx(float x) {this->dX = x;}
	void setDy(float y) {this->dY = y;}
	void setDCoord(float x, float y) {this->dX = x; this->dY = y;}

	float getAngle() const {return angle;}
	void setAngle(float ang) {this->angle = ang;}

	float getSpeed() const {return speed;}
	void setSpeed(float spd) {this->speed = spd;}

	void setVelocity(float x, float y, float ang, float spd) {this->dX = x; this->dY = y; this->angle = ang, this->speed = spd;}

	void calcAng();

};


#endif /* velocity_h */
