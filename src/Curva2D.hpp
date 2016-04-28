#ifndef CURVA2D_HPP
#define CURVA2D_HPP

#include "ObjetoGrafico.hpp"
#include "Matriz.cpp"
#include "MatrizUtil.hpp"

class Curva2D: public ObjetoGrafico {
public:
	Curva2D(std::string nome, std::vector<Coordenada> pontos){
		Matriz bezier = MatrizUtil::matrizBezier();

		Matriz x = Matriz(1,4);
		x(0,0) = pontos[0]._x;
		x(0,1) = pontos[1]._x;
		x(0,2) = pontos[2]._x;
		x(0,3) = pontos[3]._x;
		Matriz y = Matriz(1,4);
		y(0,0) = pontos[0]._y;
		y(0,1) = pontos[1]._y;
		y(0,2) = pontos[2]._y;
		y(0,3) = pontos[3]._y;

		Matriz xb = x*bezier;
		Matriz yb = y*bezier;

		vector<Coordenada> result = {
				Coordenada(xb(0,0), yb(0,0)),
				Coordenada(xb(0,1), yb(0,1)),
				Coordenada(xb(0,2), yb(0,2)),
				Coordenada(xb(0,3), yb(0,3))
		};

	}


	std::vector<Coordenada> clip(int status) {
		//TODO
		return coordenadasTela;
	}
};
#endif
