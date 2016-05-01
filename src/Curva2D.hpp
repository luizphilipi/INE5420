#ifndef CURVA2D_HPP
#define CURVA2D_HPP

#include "ObjetoGrafico.hpp"
#include "Linha.hpp"
#include "MatrizUtil.hpp"

class Curva2D: public ObjetoGrafico {
public:
	Curva2D(std::string nome, std::vector<Coordenada> pontosControle) :
			ObjetoGrafico(nome, CURVA2D) {
		blending(pontosControle);
	}

	void blending(std::vector<Coordenada> pontosControle) {
		if (pontosControle.size() % 3 != 1) {
			throw std::runtime_error("Curva não possui continuidade G(0).");
		}
		Matriz bezier = MatrizUtil::matrizBezier();
		for (int i = 0; i < pontosControle.size() - 1; i += 3) {
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

			int nroPassos = 1000;
			for (int i = 0; i < nroPassos + 1; i++) {
				double t = (double) i / nroPassos;
				Matriz T = MatrizUtil::matrizT(t);
				//T*Mb*G
				Matriz tbx = T * bezier * x;
				Matriz tby = T * bezier * y;
				coordenadasMundo.push_back(Coordenada(tbx(0, 0), tby(0, 0), 1));
			}
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
