#include <array>

using namespace std;

class Wavelength {
private:
	array<int, 9> fiber;
public:
	array<float, 9> endTime;
	Wavelength();
	int getFiber(int l);
	//void setFiber(int l, int flag);
	//int getPath(int node1, int node2);
	void setPath(int node1, int node2, float end);
	int checkPath(int node1, int node2, float start);
};