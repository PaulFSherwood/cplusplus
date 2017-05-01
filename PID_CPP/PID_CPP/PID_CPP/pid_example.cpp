#include "pid.h"
#include <stdio.h>
#include <ctime>

void pause(int dur) {
	int temp = time(NULL) + dur;
	while(temp > time(NULL));
}

int main() {
	PID pid = PID(0.1, 100, -100, 0.1, 0.01, 0.5);

	double val = 20;
	for (int i = 0; i < 100; i++) {
		double inc = pid.calculate(0, val);
		printf("val: % 7.3f inc: % 7.3f\n", val, inc);
		val += inc;
		pause(1);
	}

	return 0;
}