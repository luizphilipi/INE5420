#ifndef COORDENADA
#define COORDENADA

class Coordenada {
public:
	double _x;
	double _y;
	double _z;

	Coordenada(double x, double y) :
			_x(x), _y(y), _z(1) {
	}

	Coordenada(double x, double y, double z) :
			_x(x), _y(y), _z(z) {
	}

	double getX() const {
		return _x;
	}

	double getY() const {
		return _y;
	}

	double getZ() const {
		return _z;
	}

	Coordenada negativa() {
		return Coordenada(-this->_x, -this->_y);
	}

	Coordenada operator+=(const Coordenada& c2) {
		this->_x += c2._x;
		this->_y += c2._y;
		this->_z += c2._z;

		return *this;
	}

	Coordenada operator-=(const Coordenada& c2) {
		this->_x -= c2._x;
		this->_y -= c2._y;
		this->_z -= c2._z;

		return *this;
	}
};

#endif
