/*********************************************************************
 * File: game.cpp
 * Description: Contains the implementaiton of the game class
 *  methods.
 *
 *********************************************************************/

#include "game.h"

// These are needed for the getClosestDistance function...
#include <limits>
#include <algorithm>
using namespace std;


Game :: Game() {
   initiate();
}

Game :: Game(Point tl, Point br) {
   this->topLeft = tl; this->bottomRight = br;
   initiate();
}

void Game :: initiate() {
   level = 0;
   score = 0;
   loop = 0;
   gameover = false;
   gunType = false;
   newWave = true;

   titlePoint.setCoord(-22, 65);
   descPoint.setCoord(-145, 20);
   controlsPoint.setCoord(-157, -35);
   scoreMenuPoint.setCoord(-184, 178);
   scoreBoardPoint.setCoord(scoreMenuPoint.getX(), scoreMenuPoint.getY());
   levelBoardPoint.setCoord(scoreMenuPoint.getX(), scoreMenuPoint.getY()-14);
   lifeTxtPoint.setCoord(scoreMenuPoint.getX(), scoreMenuPoint.getY()-28);
   for(int i = 0; i < ship.getLives(); i++) {
      Point tp;
      tp.setCoord(-157-(i*12), 138);
      shipLifePoint.push_back(tp);
   }
   levelTxt.setCoord(scoreMenuPoint.getX()+45, scoreMenuPoint.getY()-6);
   scoreTxt.setCoord(scoreMenuPoint.getX()+45, scoreMenuPoint.getY()+9);
   title = "Asteroids";
   desc = "Break apart asteroids by shooting them and survive.";
   controls = "Arrows to move - Space or z to shoot - q to change guns";
   scoreBoard = "Score:";
   levelBoard = "Level:";
   lifeTxt = "Life:";
}

Game :: ~Game() {

}

void Game :: handleInput(const Interface & ui) {

   ship.handleInput(ui);

   if(ui.isSpace()) {
      if(!gunType) {
         Bullet tempBul;
         tempBul.fire(ship, ship.aimAngle(), tempBul.getVel().getSpeed());
         bullets.push_back(tempBul);
      } else {
         for(int i = 0; i < 15; i++) {
            Bullet tempBul;
            tempBul.fire(ship, (i*24) + ship.aimAngle(), tempBul.getVel().getSpeed());
            bullets.push_back(tempBul);
         }
      }
   }

   if(ui.isQ()) {
      if(gunType) {gunType=0;} else {gunType=1;}
   }

}

void Game :: draw(const Interface & ui) {

   ship.draw();

   for(int i = 0; i < bullets.size(); i++) {
      bullets[i].draw();
   }

   for(int i = 0; i < asteroids.size(); i++) {
      asteroids[i]->draw();
   }

   drawDisplay();

   loop++;

}


void Game :: advance() {

   ship.advance();

   for(int i = 0; i < bullets.size(); i++) {
      bullets[i].advance();
      bullets[i].setLives(bullets[i].getLives() - 1);
      if(bullets[i].getLives() <= 0) { bullets[i].kill(); bullets.erase(bullets.begin() + i); }
   }

   for(int i = 0; i < asteroids.size(); i++) {
      asteroids[i]->advance();
      asteroids[i]->rotate(asteroids[i]->getSpin(), random(0,1));
   }

   handleWrap();

   handleCollision();

   int cx = 0;
   for(vector <Rock*> :: iterator i = asteroids.begin(); i != asteroids.end(); i++) {
      if(*i != NULL) {
         cx++;
      }
   }
   if(cx == 0) {createAsteroids(); level++; ship.setLives(ship.getLives()+1);}
}

// You may find this function helpful...

/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 **********************************************************/

float Game :: getClosestDistance(FlyingObject &obj1, FlyingObject &obj2) const {
   // find the maximum distance traveled
   float dMax = max(abs(obj1.getVel().getDx()), abs(obj1.getVel().getDy()));
   dMax = max(dMax, abs(obj2.getVel().getDx()));
   dMax = max(dMax, abs(obj2.getVel().getDy()));
   dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.
   
   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point point1(obj1.getPoint().getX() + (obj1.getVel().getDx() * i / dMax),
                     obj1.getPoint().getY() + (obj1.getVel().getDy() * i / dMax));
      Point point2(obj2.getPoint().getX() + (obj2.getVel().getDx() * i / dMax),
                     obj2.getPoint().getY() + (obj2.getVel().getDy() * i / dMax));
      
      float xDiff = point1.getX() - point2.getX();
      float yDiff = point1.getY() - point2.getY();
      
      float distSquared = (xDiff * xDiff) +(yDiff * yDiff);
      
      distMin = min(distMin, distSquared);
   }
   
   return sqrt(distMin);
}

void Game :: handleCollision() {
   //Collision with asteroids
   for(int r = 0; r < asteroids.size(); r++) {
      Rock asteroidPoint = *asteroids[r];
      
      //with bullets
      for(int b = 0; b < bullets.size(); b++) {
         if(getClosestDistance(bullets[b], asteroidPoint) <= fabs((bullets[b].getSize() + asteroids[r]->getSize()))) {
            createAsteroid(asteroids[r]->getType(), asteroidPoint);
            score += asteroids[r]->getType();

            asteroids.erase(asteroids.begin() + r);
            bullets.erase(bullets.begin() + b);
         }
      }

      //with ship
      if(getClosestDistance(ship, asteroidPoint) <= fabs((ship.getSize() + asteroids[r]->getSize()))) {
         ship.setLives(ship.getLives() - 1);
            createAsteroid(asteroids[r]->getType(), asteroidPoint);
            asteroids.erase(asteroids.begin() + r);
         if(ship.getLives() <= 0) {
            gameover = true;
            cout << "Gameover" << endl;
            cout << "You reached level " << level << " with " << score << " points.\n";
            level = 0;
            score = 0;
            ship.setLives(3);
            asteroids.erase(asteroids.begin(), asteroids.end());
            bullets.erase(bullets.begin(), bullets.end());
         }
      }
   }

}


void Game :: createAsteroids() {

   //if(random(0, 30) == 0 && asteroids.size() < (level*10))
   for (int i = 0; i < ((level*2)+10); i++) {
      Rock* newRock = NULL;
      newRock = new BigRock();
      newRock->setCoord(random(-200,0), random(0,200));
      newRock->fire(newRock->getPoint(), random(0, 360), newRock->getVel().getSpeed());
      asteroids.push_back(newRock);
   }

}

void Game :: createAsteroid(int type, Rock rock) {
   
   if(type == 1) {
      
      //1st medium asteroid
      Rock* newRock1 = NULL;
      newRock1 = new MediumRock();
      newRock1->setCoord(rock.getX(), rock.getY());
      newRock1->addY(1);
      newRock1->fire(newRock1->getPoint(), random(0, 360), rock.getVel().getSpeed());
      asteroids.push_back(newRock1);
      
      //2nd medium asteroid
      Rock* newRock2 = NULL;
      newRock2 = new MediumRock();
      newRock2->setCoord(rock.getX(), rock.getY());
      newRock2->addY(-1);
      newRock2->fire(newRock2->getPoint(), random(0, 360), rock.getVel().getSpeed());
      asteroids.push_back(newRock2);
      
      //small asteroid
      Rock* newRock3 = NULL;
      newRock3 = new SmallRock();
      newRock3->setCoord(rock.getX(), rock.getY());
      newRock3->addX(2);
      newRock3->fire(newRock3->getPoint(), random(0, 360), rock.getVel().getSpeed());
      asteroids.push_back(newRock3);

   } else if(type == 2) {

      //1st small asteroid
      Rock* newRock1 = NULL;
      newRock1 = new SmallRock();
      newRock1->setCoord(rock.getX(), rock.getY());
      newRock1->addX(3);
      newRock1->fire(newRock1->getPoint(), random(0, 360), rock.getVel().getSpeed());
      asteroids.push_back(newRock1);

      //2nd small asteroid
      Rock* newRock2 = NULL;
      newRock2 = new SmallRock();
      newRock2->setCoord(rock.getX(), rock.getY());
      newRock2->addX(-3);
      newRock2->fire(newRock2->getPoint(), random(0, 360), rock.getVel().getSpeed());
      asteroids.push_back(newRock2);

   }

}

void Game :: handleWrap() {

   ship.wrap(topLeft, bottomRight);

   for(int i = 0; i < bullets.size(); i++) {
      bullets[i].wrap(topLeft, bottomRight);
   }

   for(int i = 0; i < asteroids.size(); i++) {
      asteroids[i]->wrap(topLeft, bottomRight);
   }   

}

void Game :: drawDisplay() {
   if(loop < 220) {

      drawText(titlePoint, title);
      drawText(descPoint, desc);
      drawText(controlsPoint, controls);

   }

   drawText(scoreBoardPoint, scoreBoard);
   drawNumber(scoreTxt, score);
   drawText(levelBoardPoint, levelBoard);
   drawNumber(levelTxt, level);
   drawText(lifeTxtPoint, lifeTxt);
   for(int i = 0; i < ship.getLives(); i++) {
      drawShip(shipLifePoint[i], 0, false);
   }
}
