// Do not remove the include below
#include "Heating_Relays.h"
#include "Thermistor.h"

#define solar_therm_pin 0
#define solar_tank_therm_pin 1
#define fire_therm_pin 2
#define fire_tank_therm_pin 3
#define tank_therm_pin 4

Thermistor solar(solar_therm_pin);


//The setup function is called once at startup of the sketch
void setup()
{
	Serial.begin(9600);
}

// The loop function is called in an endless loop
void loop()
{

	Serial.print("Solar Temp: ");
	Serial.println(solar.readTemp());

	delay(1000);

}
