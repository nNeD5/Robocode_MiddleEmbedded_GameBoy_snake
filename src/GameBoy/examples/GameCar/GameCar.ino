#include <GameBoy.h>

GameBoy gb;
int pos=2;
void setup() {

gb.begin(0);

}

void loop() {

  gameCar();

}
void gameCar(){

int enemy_position=random(0,10);

if(enemy_position>5) enemy_position=2;
else enemy_position=5;  

  for(int yT=-3;yT<16;yT++){
    creatMyCar(pos);
    Car(enemy_position,yT+4);
    creatLine(yT);
    creatLine(yT+5);
    creatLine(yT+10);
    creatLine(yT+15);
    creatLine(yT-5);
    creatLine(yT-10);
    creatLine(yT-15);
    if(gb.getKey()==5) {
      deletMyCar(pos);
      pos=5;
    }
    if(gb.getKey()==4) {
      deletMyCar(pos);
      pos=2;
    }
    if(yT==11){
      gb.sound(SCORE);
    }
    if((pos==enemy_position&&yT==8) or (gb.getKey()==4 and (gb.checkCollision(2,13))) or (gb.getKey()==5 and (gb.checkCollision(5,13)))) {
      gb.testMatrix(10);
      gb.clearDisplay();
      return;
    }
   
    delay(200);
    deletCar(enemy_position,yT+4);
    deletLine(yT);
    deletLine(yT+5);
    deletLine(yT+10);
    deletLine(yT+15);
    deletLine(yT-5);
    deletLine(yT-10);
    deletLine(yT-15);
  }
}
void creatLine(int y){
    gb.drawPoint(0,y);
    gb.drawPoint(0,y+1);
    gb.drawPoint(0,y+2);
    gb.drawPoint(7,y);
    gb.drawPoint(7,y+1);
    gb.drawPoint(7,y+2);  
}
void deletLine(int y){
    gb.wipePoint(0,y);
    gb.wipePoint(0,y+1);
    gb.wipePoint(0,y+2);
    gb.wipePoint(7,y);
    gb.wipePoint(7,y+1);
    gb.wipePoint(7,y+2);
}
void Car(int x,int y){
    gb.drawPoint(x,y);
    gb.drawPoint(x,y-1);
    gb.drawPoint(x-1,y-1);
    gb.drawPoint(x+1,y-1);
    gb.drawPoint(x,y-2);
    gb.drawPoint(x-1,y-3);
    gb.drawPoint(x+1,y-3);
}
void deletCar(int x,int y){
    gb.wipePoint(x,y);
    gb.wipePoint(x,y-1);
    gb.wipePoint(x-1,y-1);
    gb.wipePoint(x+1,y-1);
    gb.wipePoint(x,y-2);
    gb.wipePoint(x-1,y-3);
    gb.wipePoint(x+1,y-3);  
}
void creatMyCar(int position){
    gb.drawPoint(position,12);
    gb.drawPoint(position,13);
    gb.drawPoint(position-1,13);
    gb.drawPoint(position+1,13);
    gb.drawPoint(position,14);
    gb.drawPoint(position-1,15);
    gb.drawPoint(position+1,15);
}

void  deletMyCar(int position){
    gb.wipePoint(position,12);
    gb.wipePoint(position,13);
    gb.wipePoint(position-1,13);
    gb.wipePoint(position+1,13);
    gb.wipePoint(position,14);
    gb.wipePoint(position-1,15);
    gb.wipePoint(position+1,15);
}