#include <array>

using namespace std;

class Wavelength {
private:
	array<int, 9> fiber;
public:
	Wavelength();
	int getFiber(int l);
	void setFiber(int l, int flag);
	int checkFiber(int min, int max);
};