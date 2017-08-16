/*********************************************************************
 * File: game.h
 * Description: Defines the game class for Asteroids
 *
 *********************************************************************/

#ifndef GAME_H
#define GAME_H

using namespace std;
#include <vector>
#include <sstream>


#include "uiDraw.h"
#include "uiInteract.h"
#include "ship.h"
#include "rocks.h"
#include "bullet.h"

class Game {

private:

	Point topLeft;
	Point bottomRight;

	Ship ship;
	vector<Bullet> bullets;

	vector<Rock*> asteroids;

	int level;
	int score;

	bool newWave;

	int loop;

	bool gunType;

	bool gameover;

	Point titlePoint;
    Point descPoint;
    Point controlsPoint;
    Point scoreBoardPoint;
    Point levelBoardPoint;
    Point lifeTxtPoint;
    Point scoreMenuPoint;
    vector<Point> shipLifePoint;
    Point levelTxt;
    Point scoreTxt;
    const char* title;
    const char* desc;
    const char* controls;
    const char* scoreBoard;
    const char* levelBoard;
    const char* lifeTxt;

public:

	Game();
	Game(Point tl, Point br);
	~Game();

	void initiate();

	void handleInput(const Interface & ui);
	void draw(const Interface & ui);
	void advance();

	float getClosestDistance(FlyingObject &obj1, FlyingObject &obj2) const;

	void handleCollision();

	void createAsteroids();
	void createAsteroid(int type, Rock rock);

	void handleWrap();

	void drawDisplay();

};


#endif /* GAME_H */
