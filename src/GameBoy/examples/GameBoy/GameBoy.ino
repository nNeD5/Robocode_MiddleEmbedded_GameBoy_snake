#include "GameBoy.h"

GameBoy lc;
byte position=5;
byte gameis=0;
int x_cube,y_cube;
bool isChoos=false;  
unsigned long delaytime=100;
int x,y;

void testFoo(){
    x=1;
    for(y=0;y<16;y++){
        lc.drawDisplay();    
        if(lc.getKey()==3||lc.getKey()==6) x=x+lc.moveX(x,y,0,0,1);
        if(lc.checkCollision(x,y+1)) {
            lc.memDisplay(x,y);
            return;
        }
        lc.drawPoint(x,y);
        lc.fullLine();
        delay(100);
    }
}
void Stick(){
    x=1;
    byte rotate=0;
    for(y=0;y<16;y++){
        lc.drawDisplay();
        if(lc.getKey()==2) rotate++;
        if(lc.getKey()==3||lc.getKey()==6) {
            if(rotate>1) rotate=0;
            lc.clearDisplay();
            lc.drawDisplay();
            if(rotate=0){
                x=x+lc.moveX(x,y,0,0,1);
                lc.drawPoint(x,y);
                lc.drawPoint(x,y-1);
                lc.drawPoint(x,y-2);
                lc.drawPoint(x,y-3);
            }
            if(rotate=1){
                x=x+lc.moveX(x,y,0,0,1);
                lc.drawPoint(x,y);
                lc.drawPoint(x-1,y);
                lc.drawPoint(x-2,y);
                lc.drawPoint(x-3,y);
            }
        }
        if(lc.checkCollision(x,y+1)) {
            if(rotate=0){
                lc.memDisplay(x,y);
                lc.memDisplay(x,y-1);
                lc.memDisplay(x,y-2);
                lc.memDisplay(x,y-3);
                return;
            }
            if(rotate=1){
                lc.memDisplay(x,y);
                lc.memDisplay(x-1,y);
                lc.memDisplay(x-2,y);
                lc.memDisplay(x-3,y);
            }
         }
        lc.drawPoint(x,y);
        lc.drawPoint(x,y-1);
        lc.drawPoint(x,y-2);
        lc.drawPoint(x,y-3);
        lc.fullLine();
        delay(100);
    }    
}
void Cube(){
    x=1;
    for(y=0;y<16;y++){
        lc.drawDisplay();
        if(lc.getKey()==4||lc.getKey()==5) {
            lc.clearDisplay();
            lc.drawDisplay();
            x=x+lc.moveX(x,y,0,1,1);
            lc.drawPoint(x,y);
            lc.drawPoint(x,y+1);
            lc.drawPoint(x+1,y);
            lc.drawPoint(x+1,y+1);
        }
        if(lc.checkCollision(x,y+2)||lc.checkCollision(x+1,y+2)) {
            lc.memDisplay(x,y);
            lc.memDisplay(x,y+1);
            lc.memDisplay(x+1,y);
            lc.memDisplay(x+1,y+1);
            return;
        }
        lc.drawPoint(x,y);
        lc.drawPoint(x,y+1);
        lc.drawPoint(x+1,y);
        lc.drawPoint(x+1,y+1);
        lc.fullLine();
        delay(100);
    }
}
void bigPixel(int x, int y){
    lc.setLed(x,y,1);
    lc.setLed(x,y+1,1);
    lc.setLed(x+1,y,1);
    lc.setLed(x+1,y+1,1);
}

void bootloader(){  
    gameis=0;
    for(;;){
        if(lc.getKey()==4) gameis=1;
        delay(10);
        if(lc.getKey()==5) gameis=2;
        delay(10);
        if(gameis==1){
            lc.clearDisplay();
            bigPixel(3,1);
            bigPixel(3,3);
            bigPixel(1,3);
            bigPixel(5,3);
            bigPixel(3,5);
            bigPixel(1,7);
            bigPixel(5,7);
            delay(100);   
        }
        if(gameis==2){
            lc.clearDisplay();
            bigPixel(3,1);
            bigPixel(1,1);
            bigPixel(5,1);
            bigPixel(3,3);
            delay(100);
        }
        if(lc.getKey()==1) return;
    }
}

void createLine(int y){
    if(y>15) y=abs(y-15);
    lc.setLed(0,y,1);
    lc.setLed(0,y+1,1);
    lc.setLed(0,y+2,1);
    lc.setLed(7,y,1);
    lc.setLed(7,y+1,1);
    lc.setLed(7,y+2,1);
    
}
void deletLine(int y){
    if(y>15) y=abs(y-15);
    lc.setLed(0,y,0);
    lc.setLed(0,y+1,0);
    lc.setLed(0,y+2,0);
    lc.setLed(7,y,0);
    lc.setLed(7,y+1,0);
    lc.setLed(7,y+2,0);
}
void creatCar(int x,int y){
    lc.setLed(x,y,1);
    lc.setLed(x,y-1,1);
    lc.setLed(x-1,y-1,1);
    lc.setLed(x+1,y-1,1);
    lc.setLed(x,y-2,1);
    lc.setLed(x-1,y-3,1);
    lc.setLed(x+1,y-3,1);
}
void Car(int x,int y){
    lc.drawPoint(x,y);
    lc.drawPoint(x,y-1);
    lc.drawPoint(x-1,y-1);
    lc.drawPoint(x+1,y-1);
    lc.drawPoint(x,y-2);
    lc.drawPoint(x-1,y-3);
    lc.drawPoint(x+1,y-3);
}
void deletCar(int x,int y){
    lc.setLed(x,y,0);
    lc.setLed(x,y-1,0);
    lc.setLed(x-1,y-1,0);
    lc.setLed(x+1,y-1,0);
    lc.setLed(x,y-2,0);
    lc.setLed(x-1,y-3,0);
    lc.setLed(x+1,y-3,0);  
}
void creatMyCar(int position){
    lc.setLed(position,12,1);
    lc.setLed(position,13,1);
    lc.setLed(position-1,13,1);
    lc.setLed(position+1,13,1);
    lc.setLed(position,14,1);
    lc.setLed(position-1,15,1);
    lc.setLed(position+1,15,1);
}
void deletMyCar(int position){
    lc.setLed(position,12,0);
    lc.setLed(position,13,0);
    lc.setLed(position-1,13,0);
    lc.setLed(position+1,13,0);
    lc.setLed(position,14,0);
    lc.setLed(position-1,15,0);
    lc.setLed(position+1,15,0);
}
void gonka(){
    int car_speed=50;
    lc.clearDisplay();
    byte x_car_bot=random(0,10);
    if(x_car_bot>5) x_car_bot=2;
    else x_car_bot=5;
    for(int y=0;y<16;y++){
        createLine(y);
        createLine(y+5);
        createLine(y+10);
        creatCar(x_car_bot,y+3);
        creatMyCar(position);
        if(lc.getKey()==5){
            deletMyCar(position);
            position=2;
            creatMyCar(position);
        }
        if(lc.getKey()==4){
            deletMyCar(position);
            position=5;
            creatMyCar(position); 
        }
        delay(car_speed);
        deletCar(x_car_bot,y+3);
        deletLine(y-1);
        deletLine(y+4);
        deletLine(y+9);
    }
}

void setup() {
    lc.begin(0);
    //lc.testMatrix(100);  
    Serial.begin(9600);

    bootloader();
}

  
void loop() {
    delay(10);
    if(gameis==1){
        for(;;){
            gonka();
        }
    } 
    if(gameis==2){
        for(;;){
            lc.drawDisplay();
            x=3;
            //byte rand_block=random(0,8);
           // Stick();
            Cube();
        }
    }
}
