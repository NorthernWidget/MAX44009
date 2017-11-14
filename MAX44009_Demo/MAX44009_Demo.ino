#include "MAX44009.h"

MAX44009 Lux(0x4A);

void setup() {
  Serial.begin(9600);
  
  String Ent = "How can the net amount of entropy of the universe be massively decreased?\n\n";
  String Think = "Thinking...\n";
  String Data = "\nINSUFFICIENT DATA FOR MEANINGFUL ANSWER.\n\n";
  
  PrintString(Ent);
  for(int x = 0; x < 5; x++) {
    PrintString(Think);
  }
  PrintString(Data);
  
  Lux.Begin(0, 18800); //Begin with full range min and max values
}

void loop() {
  Serial.print("Brightness = ");
  Serial.print(Lux.GetLux());
  Serial.print(" Lux \t");

  Serial.print("Power = ");
  Serial.print(Lux.GetWpm());
  Serial.print(" W/m^2\n\n");
  
  delay(500);

}

void PrintString(String Val) {
  for(int i = 0; i < Val.length(); i++) {
      Serial.print(Val[i]);
      delay(75);
    }
}

