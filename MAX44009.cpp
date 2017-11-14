/******************************************************************************
MAX44009.cpp
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

#include <Wire.h> // Wire library is used for I2C
#include "MAX44009.h"

MAX44009::MAX44009(int _ADR)
// Base library type I2C
{
	// Wire.begin(); // Arduino Wire library initializer
	ADR = _ADR; //set interface used for communication
	
}

uint8_t MAX44009::Begin(unsigned long Min, unsigned long Max)
// Initialize library for subsequent pressure measurements
{  
	Wire.begin();
  	SetReg(ConfigReg, CONFIG); 
  	delay(2000); //FIX is this needed? 
}

uint8_t MAX44009::SetRate(uint8_t Rate) //Start conversion every 800ms, or as soon as reading is ready
{
	ConfigReg = ConfigReg | Rate << 7; //Set/Clear bit 7
	SetReg(ConfigReg, CONFIG);
}

uint8_t MAX44009::SetMode(Mode Val) //Set operation mode to auto or manual
{
	ConfigReg = ConfigReg | Val << 6; //Set/Clear bit 6
	SetReg(ConfigReg, CONFIG);
}

uint8_t MAX44009::SetState(uint8_t CurrDiv, uint8_t Time) //Set the CDR and integration time
{
	ConfigReg = (ConfigReg & 0xF0) | (Time << 1 | CurrDiv); //Set/Clear bit 6
	SetReg(ConfigReg, CONFIG);
}

uint8_t MAX44009::SetInt(uint8_t Mode) //Set up the interrupt 
{
	IntReg = IntReg | Mode;
	SetReg(IntReg, INTEN);
}

uint8_t MAX44009::GetInt() //Set up the interrupt 
{
	return ReadReg(INTSTAT);
}

uint8_t MAX44009::SetReg(int Val, int Reg) {
	Wire.beginTransmission(ADR);
  	Wire.write(Reg); //Configuration register location
  	Wire.write(Val);
	Wire.endTransmission(); 
}

int MAX44009::ReadReg(int Reg) {
	int Temp = 0;

	Wire.beginTransmission(ADR);
  	Wire.write(Reg);
  	Wire.endTransmission();
  	Wire.requestFrom(ADR, 1);
  	Temp = Wire.read();

  	return Temp;
}

float MAX44009::GetLux()
{
	int LuxLow = 0;
	int LuxHigh = 0;

	LuxHigh = ReadReg(LUXHIGH);
	LuxLow = ReadReg(LUXLOW);
  	int LuxExpo = (LuxHigh&0xF0)>>4;
  	int LuxMantesa = (LuxHigh&0x0F)<<4 | LuxLow&0x0F;
  	float Lux = pow(2, float(LuxExpo))*float(LuxMantesa)*0.045;
  	return Lux;
}

float MAX44009::GetWpm() 
{
	float Wpm = 0;
	Wpm = GetLux();
	Wpm *= SunLuxCoef;
	return Wpm;
}


