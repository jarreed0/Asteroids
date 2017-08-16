#ifndef rocks_h
#define rocks_h

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10

#define ROCK_SPEED 1

#include "flyingObject.h"
#include "uiDraw.h"

// Define the following classes here:
//   Rock
class Rock : public FlyingObject {

private:

	int type;

public:

	Rock();
	~Rock();

	int getType() const {return type;}
	void setType(int t) {this->type = t;}

};

//   BigRock
class BigRock : public Rock {

private:

public:

	BigRock();
	~BigRock();

	void draw();

};

//   MediumRock
class MediumRock : public Rock {

private:

public:

	MediumRock();
	~MediumRock();

	void draw();

};

//   SmallRock
class SmallRock : public Rock {

private:

public:

	SmallRock();
	~SmallRock();

	void draw();

};


#endif /* rocks_h */
