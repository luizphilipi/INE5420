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

			double delta = 0.01;
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
		//x = forwDifx(0,0), Dx = forwDifx(1,0), D²x = forwDifx(2,0), D³x = forwDifx(3,0)
		coordenadasMundo.push_back(Coordenada(forwDifx(0, 0), forwDify(0, 0), 1));
		for(int i = 1; i < n; i++){
			forwDifx(0,0) = forwDifx(0,0) + forwDifx(1,0);
			forwDifx(1,0) = forwDifx(1,0) + forwDifx(2,0);
			forwDifx(2,0) = forwDifx(2,0) + forwDifx(3,0);

			forwDify(0,0) = forwDify(0,0) + forwDify(1,0);
			forwDify(1,0) = forwDify(1,0) + forwDify(2,0);
			forwDify(2,0) = forwDify(2,0) + forwDify(3,0);

			std::cout << "---ForwDiff---" <<endl;
			std::cout << i <<endl;
			std::cout << forwDifx <<endl;
			std::cout << forwDify <<endl;
			coordenadasMundo.push_back(Coordenada(forwDifx(0, 0), forwDify(0, 0), 1));
		}
	}

	std::vector<Coordenada> clip(int status) {
		if (status) {
			vector<Coordenada> clip;
			int qtdCoords = coordenadasTela.size();
			Linha * aux;
			for (int i = 0; i < qtdCoords - 1; i++) {
				Coordenada coord = coordenadasTela[i];
				// Dentro da tela?
				if (!(coord._x < -1 || coord._x > 1 || coord._y < -1 || coord._y > 1)) {
					clip.push_back(coord);
				} else if(!clip.empty()) {
					aux = new Linha(clip.back(), coord);
					clip.push_back(aux->clip(status)[1]);
				}

			}
			return clip;
		}
		return coordenadasTela;
	}
};
#endif
