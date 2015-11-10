/*
 * ThermalDelta.cpp
 *
 *  Created on: Nov 10, 2015
 *      Author: sigmond
 */

#include "ThermalDelta.h"

ThermalDelta::ThermalDelta(Thermistor* high_side, Thermistor* low_side,
		float on_delta_threshold, float off_delta_threshold, int output_pin,
		bool active_high) {
	m_high = high_side;
	m_low = low_side;
	m_on = on_delta_threshold;
	m_off = off_delta_threshold;
	m_output_pin = output_pin;
	m_active_high = active_high;
	m_last = -273.15;
	m_active = false;

	pinMode(m_output_pin, OUTPUT);

	if (m_on < m_off) {
		float temp = m_off - m_on;
		m_off = temp - 0.5;
		m_on = temp + 0.5;
	}
}

ThermalDelta::~ThermalDelta() {
}

float ThermalDelta::runDelta() {
	m_high->readTemp();
	if (m_low)
		m_low->readTemp();

	m_last = m_high->average3Temp() - (m_low ? m_low->average3Temp() : 0.0);

	if (m_last > m_on) {
		digitalWrite(m_output_pin, m_active_high);
		m_active = true;
	} else if (m_last < m_off) {
		digitalWrite(m_output_pin, !m_active_high);
		m_active = false;
	}

	return m_last;
}

float ThermalDelta::runDeltaNoOutput() {
	m_high->readTemp();
	if (m_low)
		m_low->readTemp();

	m_last = m_high->average3Temp() - (m_low ? m_low->average3Temp() : 0.0);

	return m_last;
}

bool ThermalDelta::setOnThreshold(float on_delta_threshold) {
	if (on_delta_threshold < m_off) {
		return false;
	}
	m_on = on_delta_threshold;
	return true;
}

bool ThermalDelta::setOffThreshold(float off_delta_threshold) {
	if (off_delta_threshold > m_on) {
		return false;
	}
	m_off = off_delta_threshold;
	return true;
}

void ThermalDelta::setThresholds(float on_delta_threshold,
		float off_delta_threshold) {
	m_on = on_delta_threshold;
	m_off = off_delta_threshold;

	if (m_on < m_off) {
		float temp = m_off - m_on;
		m_off = temp - 0.5;
		m_on = temp + 0.5;
	}
}

void ThermalDelta::setOutputPin(int pin) {
	pinMode(pin, OUTPUT);
	m_output_pin = pin;
}

void ThermalDelta::setActiveHigh(bool active_high) {
	m_active_high = active_high;
}

float ThermalDelta::getLast() {
	return m_last;
}

bool ThermalDelta::Active() {
	return m_active;
}

