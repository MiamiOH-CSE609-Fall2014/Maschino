#include <array>

using namespace std;

class Wavelength {
private:
	array<int, 15> fiber;
public:
	array<float, 15> endTime;
	Wavelength();
	int getFiber(int l);
	//void setFiber(int l, int flag);
	//int getPath(int node1, int node2);
	void setPath(int edge, float end);
	int checkPath(int edge, float start);
};