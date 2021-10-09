#include <simplecpp>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
using namespace simplecpp;

//movingObject.h
#ifndef _MOVINGOBJECT_INCLUDED_
#define _MOVINGOBJECT_INCLUDED_

#include <simplecpp>
#include <vector>
#include <composite.h>
#include <sprite.h>

using namespace simplecpp;

class MovingObject : public Sprite {
  vector<Sprite*> parts;
  double vx, vy;
  double ax, ay;
  bool paused;
  void initMO(double argvx, double argvy, double argax, double argay, bool argpaused=true) {
    vx=argvx; vy=argvy; ax=argax; ay=argay; paused=argpaused;
  }
 public:
 MovingObject(double argvx, double argvy, double argax, double argay, bool argpaused=true)
    : Sprite() {
    initMO(argvx, argvy, argax, argay, argpaused);
  }
 MovingObject(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : Sprite() {
   double angle_rad = angle_deg*PI/180.0;
   double argvx = speed*cos(angle_rad);
   double argvy = -speed*sin(angle_rad);
   initMO(argvx, argvy, argax, argay, argpaused);
  }
  void set_vx(double argvx) { vx = argvx; }
  void set_vy(double argvy) { vy = argvy; }
  void set_ax(double argax) { ax = argax; }
  void set_ay(double argay) { ay = argay; }
  double getXPos();
  double getYPos();
  void reset_all(double argx, double argy, double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta);

  void pause() { paused = true; }
  void unpause() { paused = false; }
  bool isPaused() { return paused; }

  void addPart(Sprite* p) {
    parts.push_back(p);
  }
  void nextStep(double t);
  void getAttachedTo(MovingObject *m);
};

#endif

//MovingObject.cpp

void MovingObject::nextStep(double t) {
  if(paused) { return; }
  //cerr << "x=" << getXPos() << ",y=" << getYPos() << endl;
  //cerr << "vx=" << vx << ",vy=" << vy << endl;
  //cerr << "ax=" << ax << ",ay=" << ay << endl;

  for(size_t i=0; i<parts.size(); i++){
    parts[i]->move(vx*t, vy*t);
  }
  vx += ax*t;
  vy += ay*t;
} // End MovingObject::nextStep()

double MovingObject::getXPos() {
  return (parts.size() > 0) ? parts[0]->getX() : -1;
}

double MovingObject::getYPos() {
  return (parts.size() > 0) ? parts[0]->getY() : -1;
}

void MovingObject::reset_all(double argx, double argy, double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) {
  for(size_t i=0; i<parts.size(); i++){
    parts[i]->moveTo(argx, argy);
  }
  double angle_rad = angle_deg*PI/180.0;
  double argvx = speed*cos(angle_rad);
  double argvy = -speed*sin(angle_rad);
  vx = argvx; vy = argvy; ax = argax; ay = argay; paused = argpaused;
} // End MovingObject::reset_all()

void MovingObject::getAttachedTo(MovingObject *m) {
  double xpos = m->getXPos();
  double ypos = m->getYPos();
  for(size_t i=0; i<parts.size(); i++){
    parts[i]->moveTo(xpos, ypos);
  }
  initMO(m->vx, m->vy, m->ax, m->ay, m->paused);
}
//Nothing has been changed above this part, if at all it has, tis insignificant
//coin.h
#ifndef __COIN_H__
#define __COIN_H__

class Coin : public MovingObject {
  double coin_start_x;
  double coin_start_y;
  double release_speed;
  double release_angle_deg;
  double coin_ax;
  double coin_ay;

  // Moving parts
  Circle coin_circle;

 public:
 Coin(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
    release_speed = speed;
    release_angle_deg = angle_deg;
    coin_ax = argax;
    coin_ay = argay;
    initCoin();
  }

  void initCoin();==+++
  void resetCoin();

}; // End class Coin........Unchanged

#endif
#ifndef __COINTWO_H__
#define __COINTWO_H__

//A different Coin Class for 2nd player as we dont want any confusion in terms of which coin is which player's
class Cointwo : public MovingObject {
  double coin_start_x;
  double coin_start_y;
  double release_speed;
  double release_angle_deg;
  double coin_ax;
  double coin_ay;

  // Moving parts
  Circle coin_circle;

 public:
 Cointwo(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
    release_speed = speed;
    release_angle_deg = angle_deg;
    coin_ax = argax;
    coin_ay = argay;
    initCointwo();
  }

  void initCointwo();
  void resetCointwo();

}; // End class Cointwo

#endif
//lasso.h
#ifndef __LASSO_H__
#define __LASSO_H__

#define WINDOW_X 1200
#define WINDOW_Y 900

#define STEP_TIME 0.05

#define PLAY_X_START 0
#define PLAY_Y_START 0
#define PLAY_X_WIDTH (WINDOW_X-PLAY_X_START)
#define PLAY_Y_HEIGHT (WINDOW_Y-100)

#define LASSO_X_OFFSET 100
#define LASSO_Y_HEIGHT 100
#define LASSO_BAND_LENGTH LASSO_X_OFFSET
#define LASSO_THICKNESS 5

#define COIN_GAP 1

#define RELEASE_ANGLE_STEP_DEG 5
#define MIN_RELEASE_ANGLE_DEG 0
#define MAX_RELEASE_ANGLE_DEG 90
#define INIT_RELEASE_ANGLE_DEG 45

#define RELEASE_SPEED_STEP 20
#define MIN_RELEASE_SPEED 0
#define MAX_RELEASE_SPEED 200
#define INIT_RELEASE_SPEED 200

#define COIN_SPEED 160
#define COIN_ANGLE_DEG 80

#define LASSO_G 30
#define COIN_G 30

#define LASSO_SIZE 10
#define LASSO_RADIUS 30
#define COIN_SIZE 5

class Lasso : public MovingObject {
  double lasso_start_x;
  double lasso_start_y;
  double release_speed;
  double release_angle_deg;
  double lasso_ax;
  double lasso_ay;

  // Moving parts
  Circle lasso_circle;
  Circle lasso_loop;

  // Non-moving parts
  Line lasso_line;
  Line lasso_band;

  // State info
  bool lasso_looped;
  Coin *the_coin;
  int num_coins;

  void initLasso();
 public:
 Lasso(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta ) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
    release_speed = speed;
    release_angle_deg = angle_deg;
    lasso_ax = argax;
    lasso_ay = argay;
    initLasso();

  }

  void draw_lasso_band();
  void yank();
  void loopit();
  void addAngle(double angle_deg);
  void addSpeed(double speed);

  void nextStep(double t);
  bool check_for_coin(Coin *coin);
  int getNumCoins() { return num_coins; }

}; // End class Lasso
//2nd player's lasso defined seperately as so the game remains clean and we dont have worry about ambiguity error
#endif
#ifndef __LASSOTWO_H__
#define __LASSOTWO_H__
//Defining common stuff(which remain same for 2nd player's lasso/coin again for reference
//#define WINDOW_X 1200
//#define WINDOW_Y 900
//#define STEP_TIME 0.05
//#define PLAY_Y_START 0
//#define LASSO_X_OFFSET 100
//#define LASSO_Y_HEIGHT 100
//#define LASSO_BAND_LENGTH LASSO_X_OFFSET
//#define LASSO_THICKNESS 5

//#define COIN_GAP 1

#define PLAY_X_START_TWO 1200

#define PLAY_X_WIDTH_TWO (WINDOW_X-PLAY_X_START_TWO)
//#define PLAY_Y_HEIGHT (WINDOW_Y-100)


//#define RELEASE_ANGLE_STEP_DEG 5
#define MIN_RELEASE_ANGLE_DEG_TWO 90
#define MAX_RELEASE_ANGLE_DEG_TWO 180
#define INIT_RELEASE_ANGLE_DEG_TWO 135

//#define RELEASE_SPEED_STEP 20
//#define MIN_RELEASE_SPEED 0
//#define MAX_RELEASE_SPEED 200
//#define INIT_RELEASE_SPEED 100
#define COIN_ANGLE_DEG_TWO 100
/*#define COIN_SPEED 160
COIN PARAMETERS REMAIN SAME

#define LASSO_G 30
#define COIN_G 30

#define LASSO_SIZE 10
#define LASSO_RADIUS 30
#define COIN_SIZE 5*/

class Lassotwo : public MovingObject {
  double lasso_start_x;
  double lasso_start_y;
  double release_speed;
  double release_angle_deg;
  double lasso_ax;
  double lasso_ay;

  // Moving parts
  Circle lasso_circle;
  Circle lasso_loop;

  // Non-moving parts
  Line lasso_line;
  Line lasso_band;

  // State info
  bool lasso_looped;
  Cointwo *the_coin;
  int num_coins;

  void initLassotwo();
 public:
 Lassotwo(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
    release_speed = speed;
    release_angle_deg = angle_deg;
    lasso_ax = argax;
    lasso_ay = argay;
    initLassotwo();
  }

  void draw_lasso_band();
  void yank();
  void loopit();
  void addAngle(double angle_deg);
  void addSpeed(double speed);

  void nextStep(double t);
  bool check_for_coin(Cointwo *coin);
  int getNumCoins() { return num_coins; }

}; // End class Lassotwo

#endif
//member functions for respective coin classes
//coin.h

void Coin::initCoin() { //Initializes the coin
  coin_start_x = (PLAY_X_START+WINDOW_X/2)/2;
  coin_start_y = PLAY_Y_HEIGHT;
  coin_circle.reset(coin_start_x, coin_start_y, COIN_SIZE);
  coin_circle.setColor(COLOR("blue"));
  coin_circle.setFill(true);
  addPart(&coin_circle);
}

void Coin::resetCoin() { //resets coin at appropriate sitch
  double coin_speed = COIN_SPEED;
  double coin_angle_deg = COIN_ANGLE_DEG;
  coin_ax = 0;
  coin_ay = COIN_G;
  bool paused = true, rtheta = true;
  int randx=200+(rand()%109);
  double xx=randx/1.0;
  reset_all(xx,PLAY_Y_HEIGHT, coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);

}
//cointwo.h
void Cointwo::initCointwo() { //Initializes the coin
  coin_start_x = (PLAY_X_START_TWO+WINDOW_X/2)/2;
  coin_start_y = PLAY_Y_HEIGHT;
  coin_circle.reset(coin_start_x, coin_start_y, COIN_SIZE);
  coin_circle.setColor(COLOR("red"));
  coin_circle.setFill(true);
  addPart(&coin_circle);
}

void Cointwo::resetCointwo() { //resets coin at appropriate sitch
  double coin_speed = COIN_SPEED;
  double coin_angle_deg = COIN_ANGLE_DEG_TWO;
  coin_ax = 0;
  coin_ay = COIN_G;
  bool paused = true, rtheta = true;
  int randx=891+(rand()%109);
  double xx=randx/1.0;
  reset_all(xx,PLAY_Y_HEIGHT, coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);

}

//lasso.cpp

void Lasso::draw_lasso_band() {
  double len = (release_speed/MAX_RELEASE_SPEED)*LASSO_BAND_LENGTH;
  double arad = release_angle_deg*PI/180.0;
  double xlen = len*cos(arad);
  double ylen = len*sin(arad);
  lasso_band.reset(lasso_start_x, lasso_start_y, (lasso_start_x-xlen), (lasso_start_y+ylen));
  lasso_band.setThickness(LASSO_THICKNESS);
} // End Lasso::draw_lasso_band()

void Lasso::initLasso() {
  lasso_start_x = (PLAY_X_START+LASSO_X_OFFSET);
  lasso_start_y = (PLAY_Y_HEIGHT-LASSO_Y_HEIGHT);
  lasso_circle.reset(lasso_start_x, lasso_start_y, LASSO_SIZE);
  lasso_circle.setColor(COLOR("blue"));
  lasso_circle.setFill(true);
  lasso_loop.reset(lasso_start_x, lasso_start_y, LASSO_SIZE/2);
  lasso_loop.setColor(COLOR("white"));
  lasso_loop.setFill(true);
  addPart(&lasso_circle);
  addPart(&lasso_loop);
  lasso_looped = false;
  the_coin = NULL;
  num_coins = 0;

  lasso_line.reset(lasso_start_x, lasso_start_y, lasso_start_x, lasso_start_y);
  lasso_line.setColor(COLOR("white"));

  lasso_band.setColor(COLOR("blue"));
  draw_lasso_band();

} // End Lasso::initLasso()

void Lasso::yank() {
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
  lasso_loop.reset(lasso_start_x, lasso_start_y, LASSO_SIZE/2);
  lasso_loop.setFill(true);
  lasso_looped = false;
  if(the_coin !=NULL) {
    num_coins++;
    if(num_coins<3){
    addSpeed(-RELEASE_SPEED_STEP);
    }

    the_coin->resetCoin();
    the_coin=NULL;
  }
} // End Lasso::yank()

void Lasso::loopit() {
  if(lasso_looped) { return; } // Already looped
  lasso_loop.reset(getXPos(), getYPos(), LASSO_RADIUS);
  lasso_loop.setFill(false);
  lasso_looped = true;
} // End Lasso::loopit()

void Lasso::addAngle(double angle_deg) {
  release_angle_deg += angle_deg;
  if(release_angle_deg < MIN_RELEASE_ANGLE_DEG) { release_angle_deg = MIN_RELEASE_ANGLE_DEG; }
  if(release_angle_deg > MAX_RELEASE_ANGLE_DEG) { release_angle_deg = MAX_RELEASE_ANGLE_DEG; }
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
} // End Lasso::addAngle()

void Lasso::addSpeed(double speed) {
  release_speed += speed;
  if(release_speed < MIN_RELEASE_SPEED) {
    release_speed = MIN_RELEASE_SPEED;

    }
  if(release_speed > MAX_RELEASE_SPEED) { release_speed = MAX_RELEASE_SPEED; }
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
} // End Lasso::addSpeed()

void Lasso::nextStep(double stepTime) {
  draw_lasso_band();
  MovingObject::nextStep(stepTime);
  if(getYPos() > PLAY_Y_HEIGHT) { yank(); }
  lasso_line.reset(lasso_start_x, lasso_start_y, getXPos(), getYPos());
} // End Lasso::nextStep()

bool Lasso::check_for_coin(Coin *coinPtr) {
  double lasso_x = getXPos();
  double lasso_y = getYPos();
  double coin_x = coinPtr->getXPos();
  double coin_y = coinPtr->getYPos();
  double xdiff = (lasso_x - coin_x);
  double ydiff = (lasso_y - coin_y);
  double distance = sqrt((xdiff*xdiff)+(ydiff*ydiff));
  if(distance <= LASSO_RADIUS) {
    the_coin = coinPtr;
    the_coin->getAttachedTo(this);
    return true;
  }
  if(distance > LASSO_RADIUS){
  the_coin=NULL;
  return false;
  }
} // End Lasso::check_for_coin()
void Lassotwo::draw_lasso_band() {
  double len = (release_speed/MAX_RELEASE_SPEED)*LASSO_BAND_LENGTH;
  double arad = release_angle_deg*PI/180.0;
  double xlen = len*cos(arad);
  double ylen = len*sin(arad);
  lasso_band.reset(lasso_start_x, lasso_start_y, (lasso_start_x-xlen), (lasso_start_y+ylen));
  lasso_band.setThickness(LASSO_THICKNESS);
} // End Lassotwo::draw_lasso_band()

void Lassotwo::initLassotwo() {
  lasso_start_x = (PLAY_X_START_TWO-LASSO_X_OFFSET);
  lasso_start_y = (PLAY_Y_HEIGHT-LASSO_Y_HEIGHT);
  lasso_circle.reset(lasso_start_x, lasso_start_y, LASSO_SIZE);
  lasso_circle.setColor(COLOR("red"));
  lasso_circle.setFill(true);
  lasso_loop.reset(lasso_start_x, lasso_start_y, LASSO_SIZE/2);
  lasso_loop.setColor(COLOR("white"));
  lasso_loop.setFill(true);
  addPart(&lasso_circle);
  addPart(&lasso_loop);
  lasso_looped = false;
  the_coin = NULL;
  num_coins = 0;

  lasso_line.reset(lasso_start_x, lasso_start_y, lasso_start_x, lasso_start_y);
  lasso_line.setColor(COLOR("white"));

  lasso_band.setColor(COLOR("red"));
  draw_lasso_band();

} // End Lassotwo::initLasso()

void Lassotwo::yank() {
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
  lasso_loop.reset(lasso_start_x, lasso_start_y, LASSO_SIZE/2);
  lasso_loop.setFill(true);
  lasso_looped = false;
  if(the_coin !=NULL) {
    num_coins++;
    the_coin->resetCointwo();
    the_coin=NULL;
  }
} // End Lassotwo::yank()

void Lassotwo::loopit() {
  if(lasso_looped) { return; } // Already looped
  lasso_loop.reset(getXPos(), getYPos(), LASSO_RADIUS);
  lasso_loop.setFill(false);
  lasso_looped = true;
} // End Lassotwo::loopit()

void Lassotwo::addAngle(double angle_deg) {
  release_angle_deg += angle_deg;
  if(release_angle_deg < MIN_RELEASE_ANGLE_DEG_TWO) { release_angle_deg = MIN_RELEASE_ANGLE_DEG_TWO; }
  if(release_angle_deg > MAX_RELEASE_ANGLE_DEG_TWO) { release_angle_deg = MAX_RELEASE_ANGLE_DEG_TWO; }
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
} // End Lasso::addAngle()

void Lassotwo::addSpeed(double speed) {
  release_speed += speed;
  if(release_speed < MIN_RELEASE_SPEED) { release_speed = MIN_RELEASE_SPEED; }
  if(release_speed > MAX_RELEASE_SPEED) { release_speed = MAX_RELEASE_SPEED; }
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
} // End Lassotwo::addSpeed()

void Lassotwo::nextStep(double stepTime) {
  draw_lasso_band();
  MovingObject::nextStep(stepTime);
  if(getYPos() > PLAY_Y_HEIGHT) { yank(); }
  lasso_line.reset(lasso_start_x, lasso_start_y, getXPos(), getYPos());
} // End Lassotwo::nextStep()

bool Lassotwo::check_for_coin(Cointwo *coinPtr) {
  double lasso_x = getXPos();
  double lasso_y = getYPos();
  double coin_x = coinPtr->getXPos();
  double coin_y = coinPtr->getYPos();
  double xdiff = (lasso_x - coin_x);
  double ydiff = (lasso_y - coin_y);
  double distance = sqrt((xdiff*xdiff)+(ydiff*ydiff));
  if(distance <= LASSO_RADIUS) {
    the_coin = coinPtr;
    the_coin->getAttachedTo(this);
    return true;
  }
  if(distance > LASSO_RADIUS){
  the_coin=NULL;
  return false;
  }
} // End Lassotwo::check_for_coin()


main_program {
    cout<<"This is the LASSO GAME"<<endl;
    cout<<"The basic concept of this game is that, You have a lasso/rope, which you can use ";
    cout<<"to pull coins, which in turn increases your score by 1 per coin."<<endl;
    cout<<"This is a 2 player game."<<endl;
    cout<<"Player 1 is blue and on the left side."<<endl;
    cout<<"For player 1, below are the instructions:"<<endl;
    cout<<"Press 'e' to throw lasso"<<endl;
    cout<<"Press 'd' to loop the coin with the lasso"<<endl;
    cout<<"Press 'a' to yank the coin"<<endl;
    cout<<"Press 's' to reduce release angle"<<endl;
    cout<<"Press 'w' to increase release angle"<<endl;
    cout<<"Press 'b' to stop the game"<<endl;
    cout<<"Player 2 is red and is on the right side"<<endl;
    cout<<"For player 2, below are the instructions:"<<endl;
    cout<<"Press 'u' to throw lasso"<<endl;
    cout<<"Press 'j' to loop the coin with the lasso"<<endl;
    cout<<"Press 'l' to yank the coin"<<endl;
    cout<<"Press 'k' to reduce release angle"<<endl;
    cout<<"Press 'i' to increase release angle"<<endl;
    cout<<"Press 'b' to stop the game"<<endl;
    cout<<"Player 1/Blue has to collect blue coins and likewise Player 2/Red has to collect Red coins"<<endl;
    /*
    cout<<"Press 'n' if u want to read instructions. else press any other key to load game"<<endl;
    char f;
    cin>>f;
    if(f=='n'){
    wait(20);
    }                                  //THIS CODE IS FOR REAL GAME, KEPT OFF FOR EFFICIENT TESTING.
    cout<<"Loading";
    repeat(3){
    wait(0.75);
    cout<<".";
    }*/
 initCanvas("Lasso", WINDOW_X, WINDOW_Y);
  int stepCount = 0;
  float stepTime = STEP_TIME;
  float runTime = -100; // sec; -ve means infinite
  float currTime = 0;
  Rectangle r(0,0,2400,1800);
  r.setColor(COLOR("black"));
  r.setFill(true);
  // Draw lasso at start position
  double release_speed = INIT_RELEASE_SPEED; // m/s
  double release_angle_deg = INIT_RELEASE_ANGLE_DEG; // degrees
  double release_angle_deg_two = INIT_RELEASE_ANGLE_DEG_TWO; // degrees
  double lasso_ax = 0;
  double lasso_ay = LASSO_G;
  bool paused = true;
  bool rtheta = true;
  Lasso lasso(release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
  Lassotwo lassotwo(release_speed, release_angle_deg_two, lasso_ax, lasso_ay, paused, rtheta);
  Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);
  b1.setColor(COLOR("white"));
  Line b2(PLAY_X_START+50, 0, PLAY_X_START+50, WINDOW_Y);
  b2.setColor(COLOR("white"));
  Line b3(WINDOW_X-50, 0, WINDOW_X-50, WINDOW_Y);
  b3.setColor(COLOR("white"));
  Line b4(WINDOW_X/2, 0, WINDOW_X/2, WINDOW_Y);
  b4.setColor(COLOR("white"));

  string msg("Cmd: _");

  Text charPressed(PLAY_X_START+600, PLAY_Y_HEIGHT+20, msg);
  char coinScoreStr[256];
  sprintf(coinScoreStr, "Player 1 Score : %d", lasso.getNumCoins());
  Text coinScore(PLAY_X_START+300, PLAY_Y_HEIGHT+20, coinScoreStr);
  char coinScoreStr2[256];
  sprintf(coinScoreStr2, "Player 2 Score : %d", lassotwo.getNumCoins());
  Text coinScore2(WINDOW_X-300, PLAY_Y_HEIGHT+20, coinScoreStr2);

  paused = true; rtheta = true;
  double coin_speed = COIN_SPEED;
  double coin_angle_deg = COIN_ANGLE_DEG;
  double coin_angle_deg_two = COIN_ANGLE_DEG_TWO;
  double coin_ax = 0;
  double coin_ay = COIN_G;
  Coin coin(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
  Cointwo coin2(coin_speed, coin_angle_deg_two, coin_ax, coin_ay, paused, rtheta);

  // After every COIN_GAP sec, make the coin jump
  double last_coin_jump_end = 0;

  for(int x=0;x!=99;) {
    if((runTime > 0) && (currTime > runTime)) { break; }

    XEvent e;
    bool pendingEv = checkEvent(e);
    if(pendingEv) {
      char c = charFromEvent(e);
      msg[msg.length()-1] = c;
      charPressed.setMessage(msg);
      switch(c) {
      case 'e':
	lasso.unpause();
	break;
      case 'a':
	lasso.yank();
	break;
      case 'd':
	lasso.loopit();
    lasso.check_for_coin(&coin);
	wait(STEP_TIME*5);
	break;
      case 'w':
	if(lasso.isPaused()) { lasso.addAngle(-RELEASE_ANGLE_STEP_DEG);	}
	break;
      case 's':
	if(lasso.isPaused()) { lasso.addAngle(+RELEASE_ANGLE_STEP_DEG); }
	break;
    /*  case '-':
	if(lasso.isPaused()) { lasso.addSpeed(-RELEASE_SPEED_STEP); }
	break;
      case '=':
	if(lasso.isPaused()) { lasso.addSpeed(+RELEASE_SPEED_STEP); }
	break;*/ //GAME DECREASES SPEED OF LASSO AUTOMATICALLY WITH EACH POINT INCREASING DIFFICULTY
      case 'b':

	x=99;
	break;
	case 'u':
	lassotwo.unpause();
	break;
      case 'l':
	lassotwo.yank();
	break;
      case 'j':
	lassotwo.loopit();


	lassotwo.check_for_coin(&coin2);
	wait(STEP_TIME*5);
	break;
      case 'i':
	if(lassotwo.isPaused()) { lassotwo.addAngle(-RELEASE_ANGLE_STEP_DEG);	}
	break==++
      case 'k':
	if(lassotwo.isPaused()) { lassotwo.addAngle(+RELEASE_ANGLE_STEP_DEG); }
	break;
      default:
	break;
      }
    }

    lasso.nextStep(stepTime);

    lassotwo.nextStep(stepTime);
    if(lasso.getNumCoins()>=3){//may use 1 for testing
    x=99;
    }
    if(lassotwo.getNumCoins()>=3){
    x=99;
    }
    coin.nextStep(stepTime);
    if(coin.isPaused()) {
      if((currTime-last_coin_jump_end) >= COIN_GAP) {
	coin.unpause();
      }
    }

    if(coin.getYPos() > PLAY_Y_HEIGHT) {
      coin.resetCoin();
      last_coin_jump_end = currTime;
    }

    sprintf(coinScoreStr, "Player 1 Score: %d", lasso.getNumCoins());
    coinScore.setMessage(coinScoreStr);

    stepCount++;
    currTime += stepTime;
    wait(stepTime);
    coin2.nextStep(stepTime);
    if(coin2.isPaused()) {
      if((currTime-last_coin_jump_end) >= COIN_GAP) {
	coin2.unpause();
      }
    }

    if(coin2.getYPos() > PLAY_Y_HEIGHT) {
      coin2.resetCointwo();
      last_coin_jump_end = currTime;
    }

    sprintf(coinScoreStr2, "Player 2 Score : %d", lassotwo.getNumCoins());

    coinScore2.setMessage(coinScoreStr2);

    currTime += stepTime;
    wait(stepTime);

  }
   // End for
  int p1s=lasso.getNumCoins(),p2s=lassotwo.getNumCoins();
  closeCanvas();
  cout<<"Player 1 score :"<<p1s<<endl;
  cout<<"Player 2 score :"<<p2s<<endl;
  if(p1s>p2s){cout<<"Player 1 won"<<endl;}
  else if(p1s<p2s){cout<<"Player 2 won"<<endl;}
  else{cout<<"its a tie"<<endl;}
//VIDEO RECORDING LINK
//https://drive.google.com/drive/folders/1aPnfADs_EzPRqreRP2SgdsJ6fEQO_z7_?usp=sharing
} // End main_program
