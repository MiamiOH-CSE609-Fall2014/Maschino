class Connection {
private:
	int node1;
	int node2;
	float arrivalTime;
	float duration;
	float departureTime;
	int wavelength;
	int fiber;
	bool drop;
public:
	Connection();
	int getNode1();
	void setNode1(int n1);
	int getNode2();
	void setNode2(int n2);
	float getArrivalTime();
	void setArrivalTime(float arrival);
	float getDuration();
	void setDuration(float dur);
	float getDepartureTime();
	void setDepartureTime(float departure);
	int getWavelength();
	void setWavelength(int w);
	int getFiber();
	void setFiber(int f);
	bool getDrop();
	void setDrop(bool flag);
};