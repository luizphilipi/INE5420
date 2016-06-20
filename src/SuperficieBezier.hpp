#ifndef SUPERFICIE_BEZIER_HPP
#define SUPERFICIE_BEZIER_HPP

#include "ObjetoGrafico.hpp"
#include "Linha.hpp"
#include "MatrizUtil.hpp"

class SuperficieBezier: public ObjetoGrafico {
private:
	Matriz coordsX = Matriz(4, 4);
	Matriz coordsY = Matriz(4, 4);
	Matriz coordsZ = Matriz(4, 4);

	Matriz coefX = Matriz(4, 4);
	Matriz coefY = Matriz(4, 4);
	Matriz coefZ = Matriz(4, 4);

	Matriz deltaMatrixS = Matriz(4, 4);
	Matriz deltaMatrixT = Matriz(4, 4);

	Matriz DDx = Matriz(4, 4);
	Matriz DDy = Matriz(4, 4);
	Matriz DDz = Matriz(4, 4);

public:
	SuperficieBezier(std::string nome, std::vector<Coordenada> coords) :
			ObjetoGrafico(nome, SUPERFICIE_BEZIER, coords) {
		regeneratePath(10, 10);
	}

	void updateCoords() {
		for (int i = 0; i < 4; i++) {
			coordsX(0, i) = coordenadasTela[i]._x;
			coordsY(0, i) = coordenadasTela[i]._y;
			coordsZ(0, i) = coordenadasTela[i]._z;
		}
		for (int i = 0; i < 4; i++) {
			coordsX(1, i) = coordenadasTela[i + 4]._x;
			coordsY(1, i) = coordenadasTela[i + 4]._y;
			coordsZ(1, i) = coordenadasTela[i + 4]._z;
		}
		for (int i = 0; i < 4; i++) {
			coordsX(2, i) = coordenadasTela[i + 8]._x;
			coordsY(2, i) = coordenadasTela[i + 8]._y;
			coordsZ(2, i) = coordenadasTela[i + 8]._z;
		}
		for (int i = 0; i < 4; i++) {
			coordsX(3, i) = coordenadasTela[i + 12]._x;
			coordsY(3, i) = coordenadasTela[i + 12]._y;
			coordsZ(3, i) = coordenadasTela[i + 12]._z;
		}
	}

	void calculateCoefficients() {
		Matriz mBezier = MatrizUtil::matrizBezier();
		Matriz mBezierTransposta = MatrizUtil::matrizBezier().transpose();

		coefX = mBezier * coordsX * mBezierTransposta;
		coefY = mBezier * coordsY * mBezierTransposta;
		coefZ = mBezier * coordsZ * mBezierTransposta;
	}

	void createDeltaMatrices(double delta_s, double delta_t) {
		deltaMatrixS(0, 0) = 0;
		deltaMatrixS(0, 1) = 0;
		deltaMatrixS(0, 2) = 0;
		deltaMatrixS(0, 3) = 1;

		deltaMatrixS(1, 0) = delta_s * delta_s * delta_s;
		deltaMatrixS(1, 1) = delta_s * delta_s;
		deltaMatrixS(1, 2) = delta_s;
		deltaMatrixS(1, 3) = 0;

		deltaMatrixS(2, 0) = 6 * delta_s * delta_s * delta_s;
		deltaMatrixS(2, 1) = 2 * delta_s * delta_s;
		deltaMatrixS(2, 2) = 0;
		deltaMatrixS(2, 3) = 0;

		deltaMatrixS(3, 0) = 6 * delta_s * delta_s * delta_s;
		deltaMatrixS(3, 1) = 0;
		deltaMatrixS(3, 2) = 0;
		deltaMatrixS(3, 3) = 0;

		// Delta t
		deltaMatrixT(0, 0) = 0;
		deltaMatrixT(1, 0) = 0;
		deltaMatrixT(2, 0) = 0;
		deltaMatrixT(3, 0) = 1;

		deltaMatrixT(0, 1) = delta_t * delta_t * delta_t;
		deltaMatrixT(1, 1) = delta_t * delta_t;
		deltaMatrixT(2, 1) = delta_t;
		deltaMatrixT(3, 1) = 0;

		deltaMatrixT(0, 2) = 6 * delta_t * delta_t * delta_t;
		deltaMatrixT(1, 2) = 2 * delta_t * delta_t;
		deltaMatrixT(2, 2) = 0;
		deltaMatrixT(3, 2) = 0;

		deltaMatrixT(0, 3) = 6 * delta_t * delta_t * delta_t;
		deltaMatrixT(1, 3) = 0;
		deltaMatrixT(2, 3) = 0;
		deltaMatrixT(3, 3) = 0;
	}

	void createForwardDiffMatrices() {
		DDx = deltaMatrixS * coefX * deltaMatrixT;
		DDy = deltaMatrixS * coefY * deltaMatrixT;
		DDz = deltaMatrixS * coefZ * deltaMatrixT;
	}

	void makeCurve(int n, double x, double Dx, double D2x, double D3x, double y,
			double Dy, double D2y, double D3y, double z, double Dz, double D2z,
			double D3z) {
		int i = 0;
		coordenadasTela.push_back(Coordenada(x, y, z));
		for (i = 1; i < n; i++) {
			x = x + Dx;
			Dx = Dx + D2x;
			D2x = D2x + D3x;
			y = y + Dy;
			Dy = Dy + D2y;
			D2y = D2y + D3y;
			z = z + Dz;
			Dz = Dz + D2z;
			D2z = D2z + D3z;
			coordenadasTela.push_back(Coordenada(x, y, z));
		}
	}

	void UpdateForwardDiffMatrices() {
		for(int i=0; i<3;i++){
			for(int j=0;j<4; j++){
				DDx(i, j) = DDx(i, j) + DDx(i+1, j);
				DDy(i, j) = DDy(i, j) + DDy(i+1, j);
				DDz(i, j) = DDz(i, j) + DDz(i+1, j);
			}
		}
	}

	void regeneratePath(int ns, int nt) {
		updateCoords();
		calculateCoefficients();
		double delta_s = 1.0 / (ns - 1);
		double delta_t = 1.0 / (nt - 1);
		createDeltaMatrices(delta_s, delta_t);
		createForwardDiffMatrices();
		coordenadasTela.clear();

		for (int i = 0; i < ns; i++) {
			makeCurve(nt, DDx(0, 0), DDx(0, 1), DDx(0, 2), DDx(0, 3), DDy(0, 0),
					DDy(0, 1), DDy(0, 2), DDy(0, 3), DDz(0, 0), DDz(0, 1),
					DDz(0, 2), DDz(0, 3));
			UpdateForwardDiffMatrices();
		}

		createForwardDiffMatrices();
		DDx = DDx.transpose();
		DDy = DDy.transpose();
		DDz = DDz.transpose();
		for (int i = 0; i < nt; i++) {
			makeCurve(ns, DDx(0, 0), DDx(0, 1), DDx(0, 2), DDx(0, 3), DDy(0, 0),
					DDy(0, 1), DDy(0, 2), DDy(0, 3), DDz(0, 0), DDz(0, 1),
					DDz(0, 2), DDz(0, 3));
			UpdateForwardDiffMatrices();
		}
	}

	std::vector<Coordenada> clip(int status) {
		regeneratePath(50, 50);

		return coordenadasTela;
	}

};
#endif
