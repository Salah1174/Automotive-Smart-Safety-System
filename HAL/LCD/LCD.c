#include "LCD.h"
#include "../MCAL/Systick (for i2c)/systick.h"
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


size_t write(LCD_I2C *display, uint8_t value ,systick_config_t* config){
	send(display, value, Rs,&config);
	return 1;
}

size_t write_string(LCD_I2C *display, const uint8_t *buffer, size_t size ,systick_config_t* config){
	size_t n = 0;
	while (size--) {
    if (write(display, *buffer++,&config)) n++;
    else break;
  }
  return n;
}

void LCDI2CInit(LCD_I2C *display, uint8_t lcd_address, uint8_t lcd_cols, uint8_t lcd_rows){
	PLL_Init80MHz();
	
	systick_config_t systickConfig;
	
	 if (SysTick_Init(&systickConfig) != 0) {
        // handle initialization failure
        while (1);
    }

	SysTick_Init(&systickConfig);
	display->_Addr = lcd_address;
	display->_cols = lcd_cols;
	display->_rows = lcd_rows;
	display->_backlightval = LCD_NOBACKLIGHT;
	
	display->_displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
	begin(display,&systickConfig);
}


void begin(LCD_I2C *display , systick_config_t* config){
	I2C_Init();
	display->_numlines = 2;
	display->_displayfunction = LCD_2LINE;
	
	// SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
	// according to datasheet, we need at least 40ms after power rises above 2.7V
	// before sending commands. Arduino can turn on way befer 4.5V so we'll wait 50
	SysTick_Wait10ms(&config,5);
	
	// Now we pull both RS and R/W low to begin commands
	expanderWrite(display, display->_backlightval);	// reset expanderand turn backlight off (Bit 8 =1)
	SysTick_Wait10ms(&config,100);

  //put the LCD into 4 bit mode
	// this is according to the hitachi HD44780 datasheet
	// figure 24, pg 46
	
	// we start in 8bit mode, try to set 4 bit mode
  write4bits(display, 0x03 << 4 ,&config);
  SysTick_Wait10us(&config,450); // wait min 4.1ms
   
  // second try
  write4bits(display, 0x03 << 4,&config);
  SysTick_Wait10us(&config,450); // wait min 4.1ms
   
  // third go!
  write4bits(display, 0x03 << 4 ,&config); 
  SysTick_Wait10us(&config,15);
   
  // finally, set to 4-bit interface
  write4bits(display, 0x02 << 4 ,&config); 


	// set # lines, font size, etc.
	command(display, LCD_FUNCTIONSET | display->_displayfunction ,&config);  
	
	// turn the display on with no cursor or blinking default
	display->_displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
	configDisplay(display,&config);
	
	// clear it off
	clear(display ,&config);
	
	// Initialize to default text direction (for roman languages)
	display->_displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
	
	// set the entry mode
	command(display, LCD_ENTRYMODESET | display->_displaymode,&config);
	
	home(display,&config);
}

void configDisplay(LCD_I2C *display ,systick_config_t* config) {
	display->_displaycontrol |= LCD_DISPLAYON;
	command(display, LCD_DISPLAYCONTROL | display->_displaycontrol,&config);
}

void clear(LCD_I2C *display,systick_config_t* config){
	command(display, LCD_CLEARDISPLAY,&config);// clear display, set cursor position to zero
	SysTick_Wait10us(&config,200);  // this command takes a long time!
}

void home(LCD_I2C *display ,systick_config_t* config){
	command(display, LCD_RETURNHOME,&config);  // set cursor position to zero
	SysTick_Wait10us(&config,200);  // this command takes a long time!
}


//*********** Low-level LCD functions **************

void command(LCD_I2C *display, uint8_t value , systick_config_t* config) {
	send(display, value, 0,&config);
}

void send(LCD_I2C *display, uint8_t value, uint8_t mode ,systick_config_t* config) {
	uint8_t highnib=value&0xf0;
	uint8_t lownib=(value<<4)&0xf0;
  write4bits(display, (highnib)|mode,&config);
	write4bits(display, (lownib)|mode,&config); 
}

void write4bits(LCD_I2C *display, uint8_t value ,systick_config_t* config) {
	expanderWrite(display, value);
	pulseEnable(display, value,&config);
}

void expanderWrite(LCD_I2C *display, uint8_t _data){                                        
	I2CSendByte(display->_Addr, (int)_data | display->_backlightval);   
}

void pulseEnable(LCD_I2C *display, uint8_t _data ,systick_config_t* config){
	expanderWrite(display, _data | En);	// En high
	SysTick_Wait_us(&config,1);		// enable pulse must be >450ns
	
	expanderWrite(display, _data & ~En);	// En low
	SysTick_Wait10us(&config,5);		// commands need > 37us to settle
}
