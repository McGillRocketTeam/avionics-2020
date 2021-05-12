/*
 * ejection.c
 *
 *  Created on: Mar 18, 2021
 *      Author: a cat
 */

#include "ejection.h"

uint32_t prevTick = 0;
float T;						// sampling period, time of each loop
float alpha;

// Private functions
void storeAltitude(float new_altitude, float time);

// cutoff frequency of lowpass filter
float cutoff = 0.00001; // idk what the units are but matlab simulation says this will work

// Public function implementation
float runAltitudeMeasurements(uint32_t currTick, uint16_t currAlt){
  T = (float)(currTick - prevTick) / 1000;

  prevTick = currTick;
  alt_meas = currAlt - alt_ground; // Measures AGL altitude in feet
  float alt_filtered = filterAltitude(alt_meas, T);
  storeAltitude(alt_filtered, T);
  return alt_filtered;
}

// Private function implementation

// Low-pass filter - rocket at high speeds pressure fluctuates and affects altitude reading, usually at a high frequency, so low pass filter filters those high freuqency changes out
// and keeps just the overall, low frequency changes (caused by altitude change)
float filterAltitude(float altitude, float time){
  float alpha = time / (cutoff + time);
//  return (1 - time * LPF_A) * alt_previous[NUM_MEAS_AVGING - 1] + LPF_A * time * altitude;
  return (altitude * alpha + (1 - alpha) * alt_previous[NUM_MEAS_AVGING - 1]);
}

void storeAltitude(float new_altitude, float time){
  for (uint8_t i = 0; i < NUM_MEAS_AVGING - 1; i++)
  {
    vel_previous[i] = vel_previous[i + 1];
    alt_previous[i] = alt_previous[i + 1];
  }
  alt_previous[NUM_MEAS_AVGING - 1] = new_altitude;
  vel_previous[NUM_MEAS_AVGING - 1] = (alt_previous[NUM_MEAS_AVGING - 2]-alt_previous[NUM_MEAS_AVGING - 1])/time;
}

float getAverageVelocity(){
  float average_vel = 0;
  for (int i = 0; i < NUM_MEAS_AVGING; i++)
  {
    average_vel += vel_previous[i];
  }
  return average_vel/NUM_MEAS_AVGING;
}

float getVelocityGradient() {
	float gradient = 0;
	for (int i = 0; i < NUM_MEAS_AVGING - 1; i++) {
//		gradient += (vel_previous[i+1] - vel_previous[i]);
		gradient += vel_previous[i];
	}
	gradient = gradient / NUM_MEAS_AVGING;

	return gradient;
}
