#include <GameBoy.h>
GameBoy gb;
int xG,yG;

void movePoint(){
if(gb.getKey()>0){
  gb.wipePoint(xG,yG);  
  if(gb.getKey()==4&&gb.isFree(xG-1,yG)) {
    xG--;
  }
  if(gb.getKey()==5&&gb.isFree(xG+1,yG)) {
  xG++;
  }
  if(gb.getKey()==6&&gb.isFree(xG,yG+1)) {
    yG++;
  }
  if(gb.getKey()==3&&gb.isFree(xG,yG-1)) {
    yG--;
  }
}
  gb.drawPoint(xG,yG);
  delay(15);
  
}
void setup() {
  Serial.begin(9600);
  gb.begin(0);
  //gb.testMatrix(10);
}

void loop() {
movePoint();
}
