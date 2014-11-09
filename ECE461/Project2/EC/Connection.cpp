#include "Connection.h"

Connection::Connection() {
	node1 = -1;
	node2 = -1;
	arrivalTime = -1.0;
	duration = -1.0;
	departureTime = -1.0;
	wavelength = -2;
	// fiber = -1;
	drop = false;
}

int Connection::getNode1() {
	return node1;
}

void Connection::setNode1(int n1) {
	node1 = n1;
}

int Connection::getNode2() {
	return node2;
}

void Connection::setNode2(int n2) {
	node2 = n2;
}

float Connection::getArrivalTime() {
	return arrivalTime;
}

void Connection::setArrivalTime(float arrival) {
	arrivalTime = arrival;
}

float Connection::getDuration() {
	return duration;
}

void Connection::setDuration(float dur) {
	duration = dur;
}

float Connection::getDepartureTime() {
	return departureTime;
}

void Connection::setDepartureTime(float departure) {
	departureTime = departure;
}

int Connection::getWavelength() {
	return wavelength;
}

void Connection::setWavelength(int w) {
	wavelength = w;
}

// int Connection::getFiber() {
// 	return fiber;
// }
//
// void Connection::setFiber(int f) {
// 	fiber = f;
// }

bool Connection::getDrop() {
	return drop;
}

void Connection::setDrop(bool flag) {
	drop = flag;
}