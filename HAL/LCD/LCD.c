#include "LCD.h"
#include "../MCAL/Timer0/timer0.h"
#include "../MCAL/I2C/I2C.h"

#include "TM4C123GH6PM.h"
#include "driverlib/i2c.h"
#include "driverlib/i2c.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_i2c.h"


size_t write(LCD_I2C *display, uint8_t value ){
	send(display, value, Rs);
	return 1;
}

size_t write_string(LCD_I2C *display, const uint8_t *buffer, size_t size ){
	size_t n = 0;
	while (size--) {
    if (write(display, *buffer++)) n++;
    else break;
  }
  return n;
}

void LCDI2CInit(LCD_I2C *display, uint8_t lcd_address, uint8_t lcd_cols, uint8_t lcd_rows){
//	PLL_Init80MHz();
	
//	systick_config_t systickConfig;
	
//	 if (SysTick_Init(&systickConfig) != 0) {
//        // handle initialization failure
//        while (1);
//    }

//	SysTick_Init(&systickConfig);
	Timer0_Init();
	display->_Addr = lcd_address;
	display->_cols = lcd_cols;
	display->_rows = lcd_rows;
	display->_backlightval = LCD_BACKLIGHT;
	
	display->_displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
	begin(display);
}


void begin(LCD_I2C *display ){
	I2C_Init();
	display->_numlines = 2;
	display->_displayfunction = LCD_2LINE;
	
	// SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
	// according to datasheet, we need at least 40ms after power rises above 2.7V
	// before sending commands. Arduino can turn on way befer 4.5V so we'll wait 50
	timer0A_delayMs(50); 
	
	// Now we pull both RS and R/W low to begin commands
	expanderWrite(display, display->_backlightval);	// reset expanderand turn backlight off (Bit 8 =1)
	timer0A_delayMs(100); 

  //put the LCD into 4 bit mode
	// this is according to the hitachi HD44780 datasheet
	// figure 24, pg 46
	
	// we start in 8bit mode, try to set 4 bit mode
  write4bits(display, 0x03 << 4 );
  timer0A_delayMs(4);  // wait min 4.1ms
   
  // second try
  write4bits(display, 0x03 << 4);
  timer0A_delayMs(4);  // wait min 4.1ms
   
  // third go!
  write4bits(display, 0x03 << 4 ); 
  timer0A_delayMs(1); 
   
  // finally, set to 4-bit interface
  write4bits(display, 0x02 << 4 ); 


	// set # lines, font size, etc.
	command(display, LCD_FUNCTIONSET | display->_displayfunction );  
	
	// turn the display on with no cursor or blinking default
	display->_displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;

	configDisplay(display);
	
	// clear it off
	clear(display );
	
	// Initialize to default text direction (for roman languages)
	display->_displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
	
	// set the entry mode
	command(display, LCD_ENTRYMODESET | display->_displaymode);
	
	home(display);
}

void configDisplay(LCD_I2C *display ) {
	display->_displaycontrol |= LCD_DISPLAYON;
	command(display, LCD_DISPLAYCONTROL | display->_displaycontrol);
}

void clear(LCD_I2C *display){
	command(display, LCD_CLEARDISPLAY);// clear display, set cursor position to zero
	timer0A_delayMs(2);   // this command takes a long time!
}

void home(LCD_I2C *display ){
	command(display, LCD_RETURNHOME);  // set cursor position to zero
	timer0A_delayMs(2);   // this command takes a long time!
}

// Turns the underline cursor on/off
void noCursor(LCD_I2C *display  ) {
	display->_displaycontrol &= ~LCD_CURSORON;
	command(display, LCD_DISPLAYCONTROL | display->_displaycontrol );
}
void cursor(LCD_I2C *display  ) {
	display->_displaycontrol |= LCD_CURSORON;
	command(display, LCD_DISPLAYCONTROL | display->_displaycontrol );
}

void backlight(LCD_I2C *display) {
	display->_backlightval=LCD_BACKLIGHT;
	expanderWrite(display, 0);
}

void noBacklight(LCD_I2C *display) {
	display->_backlightval=LCD_NOBACKLIGHT;
	expanderWrite(display, 0);
}

void noBlink(LCD_I2C *display  ) {
	display->_displaycontrol &= ~LCD_BLINKON;
	command(display, LCD_DISPLAYCONTROL | display->_displaycontrol );
}

void blink(LCD_I2C *display  ) {
	display->_displaycontrol |= LCD_BLINKON;
	command(display, LCD_DISPLAYCONTROL | display->_displaycontrol );
}

// These commands scroll the display without changing the RAM
void scrollDisplayLeft(LCD_I2C *display) {
	command(display, LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT );
}
void scrollDisplayRight(LCD_I2C *display ) {
	command(display, LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT );
}

// Turn the display on/off (quickly)
void noDisplay(LCD_I2C *display  ) {
	display->_displaycontrol &= ~LCD_DISPLAYON;
	command(display, LCD_DISPLAYCONTROL | display->_displaycontrol );
}
void display(LCD_I2C *display) {
	display->_displaycontrol |= LCD_DISPLAYON;
	command(display, LCD_DISPLAYCONTROL | display->_displaycontrol );
}

// This is for text that flows Left to Right
void leftToRight(LCD_I2C *display  ) {
	display->_displaymode |= LCD_ENTRYLEFT;
	command(display, LCD_ENTRYMODESET | display->_displaymode );
}

// This is for text that flows Right to Left
void rightToLeft(LCD_I2C *display  ) {
	display->_displaymode &= ~LCD_ENTRYLEFT;
	command(display, LCD_ENTRYMODESET | display->_displaymode );
}

// This will 'right justify' text from the cursor
void autoscroll(LCD_I2C *display  ) {
	display->_displaymode |= LCD_ENTRYSHIFTINCREMENT;
	command(display, LCD_ENTRYMODESET | display->_displaymode );
}

// This will 'left justify' text from the cursor
void noAutoscroll(LCD_I2C *display ) {
	display->_displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
	command(display, LCD_ENTRYMODESET | display->_displaymode );
}

size_t printChar(LCD_I2C *display, const char c ){
	return write(display, c );
}

size_t print(LCD_I2C *display, const char* str  ){
	return write_string(display, (const uint8_t *)str, strlen(str) ); // beware of casting!!! Type safe in this case :)
}

//*********** Low-level LCD functions **************

void command(LCD_I2C *display, uint8_t value ) {
	send(display, value, 0);
}

void send(LCD_I2C *display, uint8_t value, uint8_t mode ) {
	uint8_t highnib=value&0xf0;
	uint8_t lownib=(value<<4)&0xf0;
  write4bits(display, (highnib)|mode);
	write4bits(display, (lownib)|mode); 
}

void write4bits(LCD_I2C *display, uint8_t value ) {
	expanderWrite(display, value);
	pulseEnable(display, value);
}

void expanderWrite(LCD_I2C *display, uint8_t _data){                                        
	I2CSendByte(display->_Addr, (int)_data | display->_backlightval);   
}

void pulseEnable(LCD_I2C *display, uint8_t _data ){
	expanderWrite(display, _data | En);	// En high
	timer0A_delayMs(0.01); 		// enable pulse must be >450ns
	
	expanderWrite(display, _data & ~En);	// En low
	timer0A_delayMs(0.05); 		// commands need > 37us to settle
}
