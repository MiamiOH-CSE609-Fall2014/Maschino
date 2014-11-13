#include "Wavelength.h"
#include <iostream>

Wavelength::Wavelength() {
	for (int i = 0; i < 15; i++) {
		fiber[i] = 0;
		endTime[i] = 0.0;
	}
}

int Wavelength::getFiber(int l) {
	return fiber[l];
}

void Wavelength::setPath(int edge, float end) {
		endTime[edge] = end;
}

int Wavelength::checkPath(int edge, float start) {
		if (endTime[edge] > start) {
			return 1;
		}
	return 0;
}