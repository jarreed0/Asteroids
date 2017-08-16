#include "flyingObject.h"


// Put your FlyingObject method bodies here

FlyingObject :: FlyingObject() {
	alive = true;
}

FlyingObject :: ~FlyingObject() {
	alive = false;
}

void FlyingObject :: advance() {
	addY(vel.getDy());
	addX(vel.getDx());
}

void FlyingObject :: fire(Point point, float ang, float spd) {
	setCoord(point.getX(), point.getY());
	setVelSpeed(spd);
	vel.setAngle(ang);
	vel.calcAng();
	alive = true;
}

void FlyingObject :: rotate(float rot, bool dir) {
	if(dir) {
		vel.setAngle(vel.getAngle() + rot);
	} else {
		vel.setAngle(vel.getAngle() - rot);
	}
}

void FlyingObject :: move(bool dir) {
	float x, y;
	x = vel.getSpeed() * (-sin(M_PI / 180.0 * vel.getAngle()));
	y = vel.getSpeed() * (cos(M_PI / 180.0 * vel.getAngle()));
	if(dir) {
		addY(y);
		addX(x);
	} else {
		addY(-y);
		addX(-x);
	}
}

Point FlyingObject :: getPoint() {
	Point r;
	r.setCoord(getX(), getY());
	return r;
}

void FlyingObject :: setPoint(Point p) {
	setCoord(p.getX(), p.getX());
}

void FlyingObject :: wrap(Point tl, Point br) {
	if(isWrapable()) {
		if(getX() < tl.getX()) {
			setX(br.getX());
		}
		if(getX() > br.getX()) {
			setX(tl.getX());
		}
		if(getY() > tl.getY()) {
			setY(br.getY());
		}
		if(getY() < br.getY()) {
			setY(tl.getY());
		}

	}
}