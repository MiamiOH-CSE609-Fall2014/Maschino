#include "Wavelength.h"
#include <iostream>

Wavelength::Wavelength() {
	for (int i = 0; i < 9; i++) {
		fiber[i] = 0;
		endTime[i] = 0.0;
	}
}

int Wavelength::getFiber(int l) {
	return fiber[l];
}

void Wavelength::setPath(int node1, int node2, float end) {
	int minimum = min(node1,node2);
	int maximum = max(node1,node2);
	for (int i = minimum; i < maximum; i++) {
		fiber[i] = 1;
		endTime[i] = end;
	}
}

int Wavelength::checkPath(int node1, int node2, float start) {
	int minimum = min(node1,node2);
	int maximum = max(node1,node2);
	int count;
	for (int i = minimum; i < maximum; i++) {
		if (endTime[i] > start) {
			return 1;
		}
	}
	return 0;
}