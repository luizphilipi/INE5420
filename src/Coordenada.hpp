#ifndef COORDENADA
#define COORDENADA

class Coordenada {
public:
	Coordenada(double x, double y) :
			x(x), y(y) {
	}

	double getX() const {
		return x;
	}

	double getY() const {
		return y;
	}

	void add(double x, double y) {
		this->x += x;
		this->y += y;
	}

	void sub(double x, double y) {
		this->x -= x;
		this->y -= y;
	}

private:
	double x;
	double y;
};

#endif
