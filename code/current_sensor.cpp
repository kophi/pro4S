#include "current_sensor.h"

/* 
Scale Factors:
50A bi-directional = 40
50A uni-directional = 60
100A bi-directional = 20
100A uni-directional = 40
150A bi-directional = 13.3
150A uni-directioal = 26.7
200A bi-directional = 10
200A uni-directional = 20

Offsets:
If bi-directional = 2500
If uni- directional = 600
*/
#define MV_PER_AMP 60
#define OFFSET 600
#define ADC_RESOLUTION 1023.0
#define REFERENCE_VOLTAGE 5000
#define CURRENT_AVERAGE_TIMES 10
#define INIT_CURRENT_AVERAGE_TIMES 100

const int analogIn = A0;

double floatingOffset = 0;

double getSingleCurrentValue() {
	int rawValue = analogRead(analogIn);
	double voltage = (rawValue / ADC_RESOLUTION) * REFERENCE_VOLTAGE;
	double amps = ((voltage - OFFSET) / MV_PER_AMP);
	amps -= floatingOffset;
	delay(2);	// wait for ADC
	return amps;
};

double getAveragedCurrent(int times) {
	double averageValueSummary = 0;
	for(int i = 0; i < times; i++) {
		averageValueSummary += getSingleCurrentValue();
	}
	return averageValueSummary / times;
};

void init_current_sensor() {
	Serial.begin(9600);
	floatingOffset = getAveragedCurrent(INIT_CURRENT_AVERAGE_TIMES);
};

double getCurrent() {
	return getAveragedCurrent(CURRENT_AVERAGE_TIMES);
};