#ifndef BSPLINE_HPP
#define BSPLINE_HPP

#include "ObjetoGrafico.hpp"
#include "Linha.hpp"
#include "MatrizUtil.hpp"

class BSpline: public ObjetoGrafico {
public:
	BSpline(std::string nome, std::vector<Coordenada> pontosControle) :
			ObjetoGrafico(nome, BSPLINE) {
		blending(pontosControle);
	}


	void blending(std::vector<Coordenada> pontosControle) {
			Matriz bSpline = MatrizUtil::matrizBSpline();

			double delta = 0.1;
			Matriz D = MatrizUtil::matrizD(delta);

			double n = 1/delta;


			for (int i = 0; i < pontosControle.size() - 3; i++) {
				Matriz x = Matriz(4, 1);
				x(0, 0) = pontosControle[i]._x;
				x(1, 0) = pontosControle[i + 1]._x;
				x(2, 0) = pontosControle[i + 2]._x;
				x(3, 0) = pontosControle[i + 3]._x;

				Matriz y = Matriz(4, 1);
				y(0, 0) = pontosControle[i]._y;
				y(1, 0) = pontosControle[i + 1]._y;
				y(2, 0) = pontosControle[i + 2]._y;
				y(3, 0) = pontosControle[i + 3]._y;

				//Mbspline*Gxy
				Matriz bx = bSpline * x;
				Matriz by = bSpline * y;

				//D*(Mbspline * Gxy)
				Matriz forwDifx = D*bx;
				Matriz forwDify = D*by;

				forwardDifferences(n, forwDifx, forwDify);
			}
		}

	void forwardDifferences(double n, Matriz forwDifx, Matriz forwDify){
		//x = forwDifx(0,0), Dx = forwDifx(0,1), D²x = forwDifx(0,2), D³x = forwDifx(0,3)
		coordenadasMundo.push_back(Coordenada(forwDifx(0, 0), forwDify(0, 0), 1));
		std::cout << "--------------matrizes------------------\n\n"<<endl;

		for(int i = 1; i < n; i++){
			std::cout << forwDifx <<endl;
			std::cout << forwDify <<endl;

			forwDifx(0,0) = (double)(forwDifx(0,0) + forwDifx(0,1));
			forwDifx(0,1) = (double)(forwDifx(0,1) + forwDifx(0,2));
			forwDifx(0,2) = (double)(forwDifx(0,2) + forwDifx(0,3));

			forwDify(0,0) = forwDify(0,0) + forwDify(0,1);
			forwDify(0,1) = forwDify(0,1) + forwDify(0,2);
			forwDify(0,2) = forwDify(0,2) + forwDify(0,3);

			coordenadasMundo.push_back(Coordenada(forwDifx(0, 0), forwDify(0, 0), 1));
		}
	}

	std::vector<Coordenada> clip(int status) {
		if (status) {
			//TODO
		}
		return coordenadasTela;
	}
};
#endif
