/*
 * ThermalDelta.h
 *
 *  Created on: Nov 10, 2015
 *      Author: sigmond
 */

#ifndef THERMALDELTA_H_
#define THERMALDELTA_H_

#include "Thermistor.h"

class ThermalDelta {
public:
	ThermalDelta(Thermistor* high_side, Thermistor* low_side,
			float on_delta_threshold, float off_delta_threshold, int output_pin,
			bool active_high = false);
	virtual ~ThermalDelta();

	float runDelta();
	float runDeltaNoOutput();
	bool setOnThreshold(float on_delta_threshold);
	bool setOffThreshold(float off_delta_threshold);
	void setThresholds(float on_delta_threshold, float off_delta_threshold);
	void setOutputPin(int pin);
	void setActiveHigh(bool active_high);
	float getLast();
	bool Active();

private:
	Thermistor* m_high;
	Thermistor* m_low;
	float m_on;
	float m_off;
	int m_output_pin;
	bool m_active_high;
	float m_last;
	bool m_active;
};

#endif /* THERMALDELTA_H_ */
