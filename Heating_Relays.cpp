// Do not remove the include below
#include "Heating_Relays.h"
#include "Thermistor.h"
#include "ThermalDelta.h"

#define solar_therm_pin 0
#define solar_tank_therm_pin 1
#define fire_therm_pin 2
#define fire_tank_therm_pin 3
#define tank_therm_pin 4

#define solar_relay_pin 2
#define fire_relay_pin 3
#define HVAC_relay_pin 4

#define HVAC_fan_on_pin 5

#define relay_active_high false

Thermistor solar(solar_therm_pin);
Thermistor solar_tank(solar_tank_therm_pin);
Thermistor fire(fire_therm_pin);
Thermistor fire_tank(fire_tank_therm_pin);
Thermistor tank(tank_therm_pin);
ThermalDelta solar_delta(&solar, &solar_tank, 10.0, 5.0, solar_relay_pin,
relay_active_high);
ThermalDelta fire_delta(&fire, &fire_tank, 10.0, 5.0, fire_relay_pin,
relay_active_high);
ThermalDelta HVAC_delta(&tank, 0, 100.0, 90.0, HVAC_relay_pin,
relay_active_high);

//The setup function is called once at startup of the sketch
void setup() {
	Serial.begin(9600);
	pinMode(solar_relay_pin, OUTPUT);
	pinMode(fire_relay_pin, OUTPUT);
	pinMode(HVAC_relay_pin, OUTPUT);
	pinMode(HVAC_fan_on_pin, INPUT);

}

// The loop function is called in an endless loop
void loop() {

	tank.readTemp();

	fire_delta.runDelta();

	if (!fire_delta.Active()) {
		solar_delta.runDelta();
	} else {
		solar_delta.runDeltaNoOutput();
		digitalWrite(solar_relay_pin, !relay_active_high);
	}

	if (digitalRead(HVAC_fan_on_pin)) {
		HVAC_delta.runDelta();
	} else {
		HVAC_delta.runDeltaNoOutput();
		digitalWrite(HVAC_relay_pin, !relay_active_high);
	}

	Serial.print("Solar Delta: ");
	Serial.print(solar_delta.getLast());
	Serial.print(" Fire Delta: ");
	Serial.print(fire_delta.getLast());
	Serial.print(" Tank Temp: ");
	Serial.println(HVAC_delta.getLast());

	/*Serial.print("Solar Temp: ");
	 Serial.println(solar.lastTemp());
	 Serial.print("Solar Tank Temp: ");
	 Serial.println(solar_tank.lastTemp());
	 Serial.print("Fire Temp: ");
	 Serial.println(fire.lastTemp());
	 Serial.print("Fire Tank Temp: ");
	 Serial.println(fire_tank.lastTemp());
	 Serial.print("Tank Temp: ");
	 Serial.println(tank.lastTemp());*/

	delay(1000);

}
