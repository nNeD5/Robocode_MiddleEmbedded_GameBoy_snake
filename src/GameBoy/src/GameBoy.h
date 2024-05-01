#ifndef GameBoy_h
#define GameBoy_h

#include <avr/pgmspace.h>
#include <Arduino.h>

#define UP    1
#define DOWN  2
#define LEFT  3
#define RIGHT 4
#define SCORE 1
#define COLLISION 2

class GameBoy {
    private :
        /* The array for shifting the data to the devices */
        byte spidata[16];
        /* Send out a single command to the device */
        void spiTransfer(int addr, byte opcode, byte data);

        /* We keep track of the led-status for all 8 devices in this array */
        byte status[64];
        /* Data is shifted out of this pin*/
        int SPI_MOSI;
        /* The clock is signaled on this pin */
        int SPI_CLK;
        /* This one is driven LOW for chip selectzion */
        int SPI_CS;
        /* The maximum number of devices we use */

    public:
       int maxDevices=2;
       const int addr=1;
       bool display[8][16];
	   byte block[4][4][4];
        /*
         * Create a new controler
         * Params :
         * dataPin		pin on the Arduino where data gets shifted out
         * clockPin		pin for the clock
         * csPin		pin for selecting the device
         * numDevices	maximum number of devices that can be controled
         */
        GameBoy();

        /*
         * Set the shutdown (power saving) mode for the device
         * Params :
         * addr	The address of the display to control
         * status	If true the device goes into power-down mode. Set to false
         *		for normal operation.
         */
        void shutdown(bool status);

		void sound(int melody);

        /*
         * Set the brightness of the display.
         * Params:
         * addr		the address of the display to control
         * intensity	the brightness of the display. (0..15)
         */
        void setIntensity(int intensity);

        /*
         * Switch all Leds on the display off.
         * Params:
         * addr	address of the display to control
         */
        void clearDisplay();

        /*
         * Set the status of a single Led.
         * Params :
         * addr	address of the display
         * row	the row of the Led (0..7)
         * col	the column of the Led (0..7)
         * state	If true the led is switched on,
         *		if false it is switched off
         */
        void setLed(int row, int col, boolean state);
        /*
        Тестирует матрицу по горизонтали и вертикале
        параметр:
        delaytime время переключение между светодиодами
         */
        void testMatrix(short int delaytime);
        /*
        Заносит в масив данных статический элемент картинки на дисплее
        х и у - координаты точки.
         */
        void memDisplay(short int x,short int y);
        /*
        Включает один пиксель на дисплее, без запоминания в память.
        */
        void drawPoint(int x,int y);
        /*
        Выключает один пиксель на дисплее, без стирания из памяти
        */
        void wipePoint(int x,int y);
        /*
        Проверяет данную точку на условие включен ли этот пиксель и занесен ли он память.
        Так же проверяет не выходит ли за границы дисплея данный пиксель.
        */
        bool checkCollision(int x, int y);
        /*
        Отрисовывает матрицу которая содержит в себе сохраненные точки установленные в высокий уровень.
        */
        void drawDisplay();
        /*
        Проверяет данную точку на условие включен ли этот пиксель и занесен ли он память.
        */
        bool chekState(int x,int y);
        /*
        Очищает линию
        */
        void clearLine(byte num_line);
        /*
        заставляет падать все точки которые занесены в память дисплея вниз.
        */
        void gravity(int vector_name);
        /*
        Изменяет положение точки, старое положение удаляет, новое отрисовывает.
        */
        int moveX(int start_x, int start_y,int left_x,int right_x, int move_var);
        /*
        Ищет заполненную линию в памяти дисплея и очищает ее.
        */
        int fullLine();
        /*
        Проверяет данную точку на условие включен ли этот пиксель и занесен ли он память.
        Так же проверяет не выходит ли за границы дисплея данный пиксель.
        */
        bool isFree(int x,int y);

        /*
         keyCode=1; KEY1
         keyCode=2; KEY2
         keyCode=5; Right
         keyCode=4; Down
         keyCode=3; Up
         keyCode=6; Left
        */
        int getKey();


        void begin(int Intensity);

		void generateBlock(byte block[4][4][4], byte arr1[4][4], byte arr2[4][4], byte arr3[4][4], byte arr4[4][4]);

		void memBlock(byte arr[4][4], int x, int y);

		bool checkBlockCollision(byte arr[4][4], int x, int y);
};



#endif	//GameBoy.h



