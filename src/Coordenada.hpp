#ifndef COORDENADA
#define COORDENADA

#include <math.h>

class Coordenada {
public:
	double _x;
	double _y;
	double _z;

	Coordenada() :
			_x(0), _y(0), _z(0) {

	}

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

	double tamanho() {
		return sqrt(pow(_x, 2) + pow(_y, 2));
	}

	double produtoEscalar(Coordenada other) {
		return (_x * other._x) + (_y * other._y);
	}

	double angleWith(Coordenada other) {
		return acos(produtoEscalar(other) / (tamanho() * other.tamanho()));
	}
};

#endif
