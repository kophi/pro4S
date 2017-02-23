#include "current_sensor.h"

void setup() {
  init_current_sensor();
}

void loop() {
	double current = getCurrent();
}
