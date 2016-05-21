#ifndef COORDENADA
#define COORDENADA

#include <math.h>
#include <iostream>

class Coordenada {
public:
	double _x;
	double _y;
	double _z;
	double _w;

	Coordenada() :
			_x(0), _y(0), _z(0), _w(0) {

	}

	Coordenada(double x, double y) :
			_x(x), _y(y), _z(1), _w(1) {
	}

	Coordenada(double x, double y, double z) :
			_x(x), _y(y), _z(z), _w(1) {
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

	double getW() const {
		return _w;
	}

	Coordenada negativa() {
		return Coordenada(-this->_x, -this->_y, -this->_z);
	}

	Coordenada operator+=(const Coordenada& c2) {
		this->_x += c2._x;
		this->_y += c2._y;
		this->_z += c2._z;

		return *this;
	}

	Coordenada operator*=(double escalar) {
		this->_x *= escalar;
		this->_y *= escalar;
		this->_z *= escalar;

		return *this;
	}

	Coordenada operator-=(const Coordenada& c2) {
		this->_x -= c2._x;
		this->_y -= c2._y;
		this->_z -= c2._z;

		return *this;
	}

	double tamanho() {
		return sqrt(pow(_x, 2) + pow(_y, 2) + pow(_z, 2));
	}

	double produtoEscalar(Coordenada other) {
		return (_x * other._x) + (_y * other._y) + (_z * other._z);
	}

	double angleWith(Coordenada other) {
		return acos(produtoEscalar(other) / (tamanho() * other.tamanho()));
	}

	void print() {
		std::cout << "(" << _x << ", " << _y << ", " << _z << ")" << std::endl;
	}

};

#endif
