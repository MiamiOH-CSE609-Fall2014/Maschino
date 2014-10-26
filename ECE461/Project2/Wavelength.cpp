#include "Wavelength.h"

Wavelength::Wavelength() {
	for (int i = 0; i < 9; i++) {
		fiber[i] = 0;
	}
}

int Wavelength::getFiber(int l) {
	return fiber[l];
}

void Wavelength::setFiber(int l, int flag) {
	fiber[l] = flag;
}

int Wavelength::checkFiber(int min, int max) {
	int count = 0;
	for (int i = min; i < max-1; i++) {
		if (fiber[i] == 1) {
			return 1; //return 1 if occupied
		}
		else {
			count++;
		}
	}
	if (count == (max-min)) {
		for (int i = min; i < max-1; i++) {
			fiber[i] = 1;
		}
		return 0; //return 0 if vacant
	}
	return 1;
}