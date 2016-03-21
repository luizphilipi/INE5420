#ifndef BASE_POINT
#define BASE_POINT

class BasePoint {
public:
	BasePoint(int x, int y) :
			x(x), y(y) {
	}

	int getX() {
		return x;
	}

	int getY() {
		return y;
	}

public:
	BasePoint() :
			x(0), y(0) {
	}

private:
	int x;
	int y;
};

#endif
