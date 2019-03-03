/*
 Name:		ArduinoNano.ino
 Created:	3/2/2019 2:59:16 PM
 Author:	y.tan

 Few rules
 > Storage of records and configs will be in EEPROM (1KB)
 > Has serial console for dumping data (csv) 
 > 2 modes of startup
   Mode 1: console
   - set logging parameters and save to flash
   Mode 2: logger (Activated by pull down to a pin)
   - log data until memory is full
 */
#include <EEPROM.h>
//EEPROM.write(0, 12);

const int pin_mode_sel{ 7 };
const int eeprom_addr_interval_ms{ 0 }; // uint16_t
const int eeprom_addr_last_addr{ 2 }; // uint16_t
const int eeprom_addr_elapsed{ 4 }; // uint32_t

uint32_t poll_interval = 1000*60;


// the setup function runs once when you press reset or power the board
void setup() {
	pinMode(pin_mode_sel, INPUT_PULLUP);

	if (digitalRead(pin_mode_sel) == HIGH)
	{
		// console mode
		consoleMode();
	}
	else
	{
		// logging mode
		EEPROM.update(5, 0xff);
		EEPROM.put(5, uint16_t(0xffff));
	}


}

// the loop function runs over and over again until power down or reset
void loop() {
  
}


void consoleMode()
{
	Serial.begin(115200);
	while(1)
	{ 
		String buffer = "";
		while (Serial.available())
		{
			char c = Serial.read();
			Serial.print("c: ");
			Serial.println(c);
			if (0 != c)
			{
				buffer += c;

			}
		}
	
	}
}