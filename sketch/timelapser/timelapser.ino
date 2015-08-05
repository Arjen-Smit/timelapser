#include <TM1637.h>

#define SLOW_INTERVAL 10 // Time between photos in seconds
#define FAST_INTERVAL 3 // Time between photos at start and end in seconds

#define DURATION 60 // Duration in seconds
#define EASING 10 // Duration of the easing between fast and slow interval

#define FPS 24 // Frames per Second;

#define CLK 12
#define DIO 13

TM1637 disp(CLK,DIO);
int next_delay;

void setup() {
   pinMode(7,OUTPUT);
   digitalWrite(7,HIGH);
   disp.set(5);
   disp.init(D4056A);
   disp.display(DURATION * FPS);
}

void loop() {
  delay(2000);
  
 
  next_delay = FAST_INTERVAL * 1000;
  for (int i=1;i<=DURATION*FPS;i++) {
    if (i <= FPS*EASING) {
      next_delay = easeIn(i, FAST_INTERVAL * 1000, (SLOW_INTERVAL - FAST_INTERVAL) * 1000, EASING * FPS);
    } else if (i >= FPS * (DURATION - EASING)) {
      next_delay = easeOut(i -((DURATION - EASING) * FPS), SLOW_INTERVAL * 1000, (FAST_INTERVAL - SLOW_INTERVAL) * 1000, EASING * FPS);
    } else {
      next_delay = SLOW_INTERVAL * 1000;
    }
    digitalWrite(7,LOW);
    delay(500);
    digitalWrite(7,HIGH);
    disp.display(DURATION * FPS - i);
    delay(next_delay - 500);
  }
  exit(0);
}

/**
 * easeIn
 * 
 * Function to create easing in
 */
int easeIn(double t,  double b, double c, double d) {
  t /= d;
  return c * t * t + b;
}

/**
 * easeOut
 * 
 * Function to create easing out
 */
int easeOut(double t, double b, double c, double d) {
  t /= d;
  return -c * t * (t-2) + b;
}

