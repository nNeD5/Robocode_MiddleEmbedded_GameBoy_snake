#include "GameBoy.h"
#define OP_NOOP   0
#define OP_DECODEMODE  9
#define OP_INTENSITY   10
#define OP_SCANLIMIT   11
#define OP_SHUTDOWN    12
#define OP_DISPLAYTEST 15
#define UP             1
#define DOWN           2
#define LEFT           3
#define RIGHT          4
#define NOTE_B3  247
#define NOTE_C4  262
#define SCORE 1
#define COLLISION 2
#define BUZZER 4


GameBoy::GameBoy() {
    SPI_MOSI=12;
    SPI_CLK=11;
    SPI_CS=10;
    pinMode(SPI_MOSI,OUTPUT);
    pinMode(SPI_CLK,OUTPUT);
    pinMode(SPI_CS,OUTPUT);
    digitalWrite(SPI_CS,HIGH);
    //SPI_MOSI=dataPin;
    for(int i=0;i<64;i++) status[i]=0x00;
    for(int i=0;i<maxDevices;i++) {
        spiTransfer(i,OP_DISPLAYTEST,0);
        spiTransfer(i, OP_SCANLIMIT,7);
        spiTransfer(i,OP_DECODEMODE,0);
        clearDisplay();
        shutdown(true);
    }
}
void GameBoy::sound(int melody) {
    if (melody == SCORE) {
    tone(BUZZER, NOTE_B3, 100);
    int pauseBetweenNotes = 100 * 1.30;
    delay(pauseBetweenNotes);
    noTone(BUZZER);
  }
  else if (melody == COLLISION) {
    int melody[] = {

      NOTE_B3, NOTE_C4
    };
    for (int i = 0; i < 2; i++) {
      tone(BUZZER, melody[i], 100);
      int pauseBetweenNotes = 100 * 1.30;
      delay(pauseBetweenNotes);
      noTone(BUZZER);
  }
    }
}

void GameBoy::shutdown(bool b) {

    if(b){
        spiTransfer(addr, OP_SHUTDOWN,0);
        spiTransfer(addr-1, OP_SHUTDOWN,0);
        }
    else{
        spiTransfer(addr, OP_SHUTDOWN,1);
        spiTransfer(addr-1, OP_SHUTDOWN,1);
        }
}

void GameBoy::setIntensity(int intensity) {
    if(intensity>=0 && intensity<16)
        spiTransfer(addr, OP_INTENSITY,intensity);
        spiTransfer(addr-1, OP_INTENSITY,intensity);
}
void GameBoy::clearDisplay() {
    short int offset1;
    short int offset2;
    offset1=addr*8;
    offset2=(addr-1)*8;
    for(int i=0;i<8;i++) {
        status[offset1+i]=0;
        spiTransfer(addr, i+1,status[offset1+i]);
    }
    for(int i=0;i<8;i++) {
    status[offset2+i]=0;
    spiTransfer((addr-1), i+1,status[offset2+i]);
    }

}
void GameBoy::setLed(int row, int column, boolean state) {
    if(column>=8){
        column=abs(column-8);
    int offset;
    byte val=0x00;

    offset=(addr-1)*8;
    val=B10000000 >> column;
    if(state)
        status[offset+row] = status[offset+row]|val;
    else {
        val=~val;
        status[offset+row] = status[offset+row]&val;
    }
        spiTransfer(addr-1, abs(row-8), status[offset+row]);
    }
    else{
    int offset;
    byte val=0x00;
    if(addr<0 || addr>=maxDevices)
        return;
        offset=addr*8;
    val=B10000000 >> column;
    if(state)
        status[offset+row]=status[offset+row]|val;
    else {
        val=~val;
        status[offset+row]=status[offset+row]&val;
    }
        spiTransfer(addr, abs(row-8),status[offset+row]);
    }

}
void GameBoy::spiTransfer(int addr, volatile byte opcode, volatile byte data) {
    //Create an array with the data to shift out
    int offset=addr*2;
    int maxbytes=maxDevices*2;

    for(int i=0;i<maxbytes;i++)
        spidata[i]=(byte)0;
    //put our device data into the array
    spidata[offset+1]=opcode;
    spidata[offset]=data;
    //enable the line
    digitalWrite(SPI_CS,LOW);
    //Now shift out the data
    for(int i=maxbytes;i>0;i--)
        shiftOut(SPI_MOSI,SPI_CLK,MSBFIRST,spidata[i-1]);
    //latch the data onto the display
    digitalWrite(SPI_CS,HIGH);
}

void GameBoy::testMatrix(short int delaytime){
for(int x = 0; x < 8; x++){
    for(int y = 0; y < 16; y++){
        setLed(x, y, true);
        delay(delaytime);
    }
}
delay(delaytime * 10);
clearDisplay();
delay(delaytime / 10);
for(int y1 = 0; y1 < 16; y1++){
    for(int x1 = 0; x1 < 8; x1++){
        setLed(x1, y1, true);
        delay(delaytime);
    }
}
clearDisplay();
}

void GameBoy::memDisplay(short int x, short int y){
    display[x][y] = true;
}
void GameBoy::drawPoint(int x, int y){
    if(x < 8 && x > -1){
        if(y > -1 && y < 16){
            setLed(x, y, 1);
        }
        else return;
    }
    else return;
}
void GameBoy::wipePoint(int x, int y){
    if(x < 8 && x >- 1){
        if(y >-1 && y < 16){
            setLed(x, y, 0);
            display[x][y] = 0;
        }
        else return;
    }
    else return;
}
bool GameBoy::checkCollision(int x, int y){
    if(x < 8 && x > -1){
        if(display[x][y] == 1 || y > 15) return true;
        else return false;
    }
    else return true;
}

void GameBoy::drawDisplay(){
    for(int x = 0; x < 8; x++){
        for(int y = 0; y < 16; y++){
            setLed(x, y, display[x][y]);
        }
    }
}

bool GameBoy::chekState(int x, int y){
        if(display[x][y] == 1) return true;
        else false;
}

bool GameBoy::isFree(int x,int y){
    if(x<8 && x>-1){
        if(display[x][y]==1 || y>15 || y < 0) return false;
        else return true;
    }
    else return false;
}
int GameBoy::moveX(int start_x, int start_y,int left_x,int right_x, int move_var ){
    if(getKey() == 4){
        if(display[start_x-move_var-right_x][start_y]==1||start_x-move_var-right_x<0) return 0;
        else return move_var;
    }
    else if(getKey() == 5){
        if(display[start_x+move_var+left_x][start_y]==1||start_x+move_var+left_x>7) return 0;
        else return -move_var;
    }
    else return 0;
}
void GameBoy::clearLine(byte num_line){
    for(int x = 0; x < 8; x++) {
        display[x][num_line] = false;
        setLed(x, num_line, 0);
    }
}
int GameBoy::fullLine(){
    int lines = 0;
    bool res = false;
    for(int y = 15; y > -1; y--){
        byte count = 0;
        for(int x = 0; x < 8; x++){
            if(display[x][y] == true){
                count++;
            }
        }
        if(count == 8) {
            lines++;
            res = true;
            clearLine(y);
            for(int _y = y; _y > 0; _y--){
                for(int x = 0; x < 8; x++){
                    display[x][_y] = display[x][_y-1];
                }
            }
            y++;
        }
    }
    return lines;
}

int GameBoy::getKey(){
    pinMode(A1, INPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    int keyCode = 0;
    int a = analogRead(A1);
    if(a > 160 && a < 180) keyCode = 5; // Right
    if(a > 190 && a < 210) keyCode = 6; //Down
    if(a > 240 && a < 260) keyCode = 3; //Up
    if(a > 330 && a < 350) keyCode = 4; //Left
    if(digitalRead(2)) keyCode = 1;//KEY1
    if(digitalRead(3)) keyCode = 2;//KEY2
    return keyCode;
}
void GameBoy::begin(int Intensity){
    shutdown(false);
    setIntensity(Intensity);
    clearDisplay();
	random(0,7);
}

/* UPDATE */

void GameBoy::generateBlock(byte block[4][4][4], byte arr1[4][4], byte arr2[4][4], byte arr3[4][4], byte arr4[4][4] ) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      block[0][i][j] = arr1[i][j];
      block[1][i][j] = arr2[i][j];
      block[2][i][j] = arr3[i][j];
      block[3][i][j] = arr4[i][j];
    }
  }
}

void GameBoy::memBlock(byte arr[4][4], int x, int y) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (arr[j][i] == 1) {
        memDisplay(x + i, y + j);
      }
    }
  }
}

bool GameBoy::checkBlockCollision(byte arr[4][4], int x, int y) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (arr[j][i] == 1 && (checkCollision(x + i, y + j))) return true;
    }
  }
  return false;
}

