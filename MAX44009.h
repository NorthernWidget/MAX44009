/******************************************************************************
MAX44009.h
Library for MAX44009 ambient light sensor.
Bobby Schulz @ Northern Widget LLC
11/13/2017
https://github.com/NorthernWidget/MAX44009

The MAX44009 is an ambient light sensor with dynamic ranging, able to measure down to 0.045 Lux (Lumens/m^2), 
the brightness of a full moon, all the way up to 188,000 Lux, equivilent to almost 1.5x direct sunlight (At sea level). 
This allows for a low cost, small scale, sensor which is able to aproximate the energy which is hitting the earth (in W/m^2)
at any given time. 

"All existing things are really one"
-Zhuangzi

Distributed as-is; no warranty is given.
******************************************************************************/

#ifndef MAX44009_h
#define MAX44009_h

#include <Arduino.h>

// Define units for conversions. 
enum Mode 
{
	Auto = 0,
	Manual = 1
};

enum Time
{
	T800ms = 0,
	T400ms = 1,
	T200ms = 2,
	T100ms = 3,
	T50ms = 4,
	T25ms = 5,
	T12_5ms = 6,
	T6_25ms = 7
};


//Commands
#define CMD_RESET 0x1E // reset command 
#define CONFIG 	0x02
#define INTSTAT 0x00
#define INTEN 	0x01
#define LUXHIGH	0x03
#define LUXLOW	0x04
#define UPPERTH	0x05
#define LOWERTH 0x06
#define TIMERTH	0x07

#define CURRDIV_ON 	1
#define CURRDIV_OFF 0

class MAX44009
{
	public:	
		MAX44009(int _ADR); //FIX use enumeration for high and low values? 
		uint8_t Begin(unsigned long Min, unsigned long Max); // Collect coefficients from sensor
		uint8_t SetRate(uint8_t Rate); //Start conversion every 800ms, or as soon as reading is ready
		uint8_t SetMode(Mode Val); //Set operation mode to auto or manual
		uint8_t SetState(uint8_t CurrDiv, uint8_t Time); //Set the CDR and integration time
		uint8_t SetInt(uint8_t Mode);//Set up the interrupt 
		uint8_t GetInt(); //Set up the interrupt 

		float GetLux();
		float GetWpm(); 
	private:
		float SunLuxCoef = 0.0079;
		int ConfigReg = 0x80; //Initialize config reg
		int IntReg = 0x00;
		int ADR;
		uint8_t SetReg(int Val, int Reg);
		int ReadReg(int Reg);
		
};

#endif
